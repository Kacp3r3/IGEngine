#include "Engine.h"
Engine::Engine()
	:
	m_sWindowName("Kacp3r3 Playground")
	,m_Timer()
	,imgui()
	,m_Camera({0.f,1.50f,-3.f})
	,m_bInputEnabled(true)
{
	
	//================================================================
	//= Initialize GLFW and force to use 4.4 OpenGL
	//================================================================
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	//================================================================
	//= Creating the Window
	//================================================================
	m_pWnd = std::make_unique<Window>(SCR_WIDTH, SCR_HEIGHT, m_sWindowName);

	// Position of the Window
	int count = 2;
	int chosen = 2;
	Monitor* m_pMonitor;
	GLFWmonitor** tmp = glfwGetMonitors(&count);
	if (chosen>count) throw IGEXCEPTION_ENG("Nie ma wybranego monitora");
	m_pMonitor = new Monitor(tmp[chosen-1], "Lewy");
	m_pMonitor->calculateCenter(SCR_WIDTH, SCR_HEIGHT);
	glfwSetWindowPos(m_pWnd->getWnd(), m_pMonitor->m_veciCenter._x, m_pMonitor->m_veciCenter._y);
	glfwSetWindowUserPointer(m_pWnd->getWnd(), m_pWnd.get());
	glfwSetInputMode(m_pWnd->getWnd(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	//================================================================
	//= Glad Initialization
	//================================================================
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::exception("Failed to load glad");
	
	std::cout << glGetString(GL_VERSION) << std::endl;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	const char* glsl_version = "#version 440";
	ImGui_ImplGlfw_InitForOpenGL(m_pWnd->getWnd(), true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	//================================================================
	//= Callbacks
	//================================================================
	GLFWwindow* x = m_pWnd->getWnd();
	glfwMakeContextCurrent(x);
	glfwSetKeyCallback(x, key_callback);
	glfwSetMouseButtonCallback(x, mouse_button_callback);
	glfwSetCursorPosCallback(x, cursor_position_callback);
	glfwSetCursorEnterCallback(x, cursor_enter_callback);
	glfwSetScrollCallback(x, scroll_callback);
	glfwSetFramebufferSizeCallback(x, framebuffer_size_callback);

	//Input options
	//glfwSetInputMode(x, GLFW_STICKY_KEYS | GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	//GL_CULL_FACE(GL_BACK);

	m_Shader = new Shader("Graphics/Shaders/vs.vs", "Graphics/Shaders/fs.fs");
	m_Shader->use();
	m_Shader->setInt("texture1", 0);

	m_SkyBoxShader = new Shader("Graphics/Shaders/sky.vs", "Graphics/Shaders/sky.fs");
	m_SkyBoxShader->use();
	m_SkyBoxShader->setInt("skybox", 0);
	//m_matProj = glm::perspective(glm::radians(75.f), (float)SCR_WIDTH / SCR_HEIGHT, camNear, camFar);

	AssetManager::get();
	AssetManager::get().loadTextures();
	AssetManager::get().loadMeshes();
	
	m_pWnd->initRenderer();
	m_CameraHUD = new CameraHUD(AssetManager::get().getTexture("Cursor"), AssetManager::get().getMesh("Plane"));
	cube = new Model();
	cube->addData(AssetManager::get().getMesh("Cube"));
	cube->setTexture(AssetManager::get().getTexture("JanSzescian"));
	SkyBox = new Model();
	SkyBox->addData(AssetManager::get().getMesh("SkyBox"));
	SkyBox->setTexture(AssetManager::get().getTexture("SkyBox"));
}

Engine::~Engine()
{
	delete m_Shader;
}

int Engine::Go()
{
	//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	float x = 0.f, y = 0.f, z = 0.f;
	glfwSetCursorPos(m_pWnd->getWnd(), SCR_WIDTH / 2.f, SCR_HEIGHT / 2.f);
	while (!glfwWindowShouldClose(m_pWnd->getWnd()))
	{
		//Providing delta Time
		m_Timer.Mark();
		while (m_Timer.getDelta() < m_Timer.getSingleFrameTime())
			m_Timer.Mark();

		//Updating Label name
		//std::string a = m_sWindowName + " FPS: " + std::to_string((int)round(1 / m_Timer.getDelta()));
		//glfwSetWindowTitle(m_pWnd->getWnd(), a.c_str());

		
		//================================================================
		//= GAME LOOP
		//================================================================

		//Input
		//glfwSetCursorPos(m_pWnd->getWnd(), SCR_WIDTH / 2.f, SCR_HEIGHT / 2.f);
		processInput();

		//UpdateModels
		updateModels(m_Timer.getDelta());

		//Render scene
		composeFrame();
	
		//================================================================
		//= ImGui Stuff
		//================================================================
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{
			ImGui::Begin("IGEngine");                          // Create a window called "Hello, world!" and append into it.
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			//ImGui::SameLine();
			ImGui::Text("Cursor %s", m_bInputEnabled?"Disabled":"Enabled");               // Display some text (you can use a format strings too)
			if (!m_bInputEnabled)
			{
				ImGui::Text("Cursor inside window: %s", m_pWnd->mouse.insideWindow() ? "True" : "False");               // Display some text (you can use a format strings too)
				ImGui::Text("Mouse pos x: %d y: %d", (int)m_pWnd->mouse.getPos().x, (int)m_pWnd->mouse.getPos().y);               // Display some text (you can use a format strings too)

				ImGui::Begin("Camera properties");
				ImGui::Text("Perspective");
				if (ImGui::SliderFloat("Far", m_Camera.ptrFar(), 10.0f, 400.0f)) m_Camera.updateProjection();
				if (ImGui::SliderFloat("Near", m_Camera.ptrNear(), 0.1f, 10.0f)) m_Camera.updateProjection();
				if (ImGui::SliderFloat("Fov", m_Camera.ptrFov(), 1.0f, 150.0f)) m_Camera.updateProjection();
				ImGui::Text("Properties");
				ImGui::SliderFloat("Velocity", m_Camera.ptrVelocity(), 1.0f, 20.0f);
				if (!m_Camera.getFly())
					if (ImGui::SliderFloat("Height", m_Camera.ptrHeight(), 0.0f, 4.0f)) m_Camera.updatePos();
				ImGui::SliderFloat("Sensitivity", m_Camera.ptrSensitivity(), 0.05f, 2.0f);
				ImGui::End();
			}
			ImGui::Text("Camera pos x: %2.2f y: %2.2f z: %2.2f", m_Camera.getPos().x, m_Camera.getPos().y, m_Camera.getPos().z);               // Display some text (you can use a format strings too)
			ImGui::Text("Camera angles yaw: %2.2f pitch: %2.2f", m_Camera.getYaw(), m_Camera.getPitch());               // Display some text (you can use a format strings too)
			ImGui::Text("Camera speed: %2.2f/s", m_Camera.getSpeed());               // Display some text (you can use a format strings too)
			if(ImGui::Checkbox("Camera fly", m_Camera.ptrFly())) m_Camera.updatePos();      // Edit bools storing our window open/close state
			//ImGui::Checkbox("Another Window", &show_another_window);
			//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				//counter++;
			//ImGui::SameLine();
			//ImGui::Text("counter = %d", counter);

			ImGui::End();

			
		}
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(m_pWnd->getWnd());
		
		/* Poll for and process events */
		m_pWnd->mouse.resetScroll();
		glfwPollEvents();
		
	}

	glfwTerminate();
	return 0;
}

void Engine::processInput()
{
	while (!m_pWnd->mouse.empty())
	{
		auto event = m_pWnd->mouse.getEvent();
		switch (event.first)
		{
			case Event::MOUSE_MOVE:
			{
				if(m_bInputEnabled) m_Camera.processMouse(m_pWnd->mouse.getDiff(), true);
				break;
			}
			case Event::MOUSE_SCROLL:
			{
				if (m_bInputEnabled) m_Camera.processScroll(m_pWnd->mouse.getScrollYOffset());
				break;
			}
			case Event::MOUSE_KEY_DOWN:
			{
				
			}
			default:
				break;
		}
	}

	while (!m_pWnd->kbd.empty())
	{
		auto event = m_pWnd->kbd.getEvent();
		switch (event.first)
		{
			case Event::KBD_KEY_DOWN:
			{
				switch (event.second)
				{
					case GLFW_KEY_LEFT_SHIFT:
							m_Camera.doubleSpeed();
							break;
					case GLFW_KEY_SPACE:
							m_Camera.reset();
							break;
					case GLFW_KEY_1:
							glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
							break;
					case GLFW_KEY_2:
							glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
							break;
					case GLFW_KEY_3:
							cube->setTexture(AssetManager::get().getTexture("Zuza"));
							break;
					case GLFW_KEY_4:
							cube->setTexture(AssetManager::get().getTexture("JanSzescian"));
							break;
					case GLFW_KEY_5:
							SkyBox->setTexture(AssetManager::get().getTexture("SkyBox"));
							break;
					case GLFW_KEY_6:
							SkyBox->setTexture(AssetManager::get().getTexture("SkyBoxDoom"));
							break;
					case GLFW_KEY_ESCAPE:
							glfwSetWindowShouldClose(m_pWnd->getWnd(), GLFW_TRUE);
							break;
					case 321:
							glfwSetInputMode(m_pWnd->getWnd(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
							m_bInputEnabled = false;
							break;
					case 322:
							glfwSetInputMode(m_pWnd->getWnd(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
							m_bInputEnabled = true;
							break;
					default:
						break;
					
				}
				break;
			}

			case Event::KBD_KEY_UP:
			{
				switch (event.second)
				{
					case GLFW_KEY_LEFT_SHIFT:
							m_Camera.normalSpeed();
							break;
				}
				break;
			}
		}
	}

	if (m_bInputEnabled)
	{
		m_Camera.setSpeed(0.f);
		if (m_pWnd->kbd.getKey(GLFW_KEY_W) == KeyState::PRESSED)
			m_Camera.processKeyboard(Movement::FORWARD, m_Timer.getDelta());

		if (m_pWnd->kbd.getKey(GLFW_KEY_S) == KeyState::PRESSED)
			m_Camera.processKeyboard(Movement::BACKWARD, m_Timer.getDelta());

		if (m_pWnd->kbd.getKey(GLFW_KEY_A) == KeyState::PRESSED)
			m_Camera.processKeyboard(Movement::LEFT, m_Timer.getDelta());

		if (m_pWnd->kbd.getKey(GLFW_KEY_D) == KeyState::PRESSED)
			m_Camera.processKeyboard(Movement::RIGHT, m_Timer.getDelta());
	}

}

void Engine::composeFrame()
{
	m_pWnd->m_pGfx->renderClearFrame(0.2f,0.5f,0.7f);

	m_Shader->use();
	glm::mat4 projview = m_Camera.getMatrix();
	//Draw Cursor
	m_CameraHUD->drawHUD(*m_Shader, *m_pWnd->m_pGfx);
	
	//Draw we
	//D�
	int x = 50; int z = 50;
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < z; ++j)
		{
			glm::mat4 model = projview;
			model = glm::translate(model, glm::vec3(((float)i - x / 2.f) - .5f, -.5f, ((float)j - z / 2.f) - .5f));
			model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
			m_Shader->setMat4("model", model);
			m_pWnd->m_pGfx->drawModel(cube);
		}
	}

	//�ciany
	int y = 5;
	for (int i = 0; i < x; i++)
	{
		for (int j = 1; j < y+1; ++j)
		{
			if((i==25 || i==26 )&& (j==1 || j ==2)) continue;
			glm::mat4 model = projview;
			model = glm::translate(model, glm::vec3((float)i - x / 2.f -.5f, (float)j-.5f,2.f-.5f));
			model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
			m_Shader->setMat4("model", model);
			m_pWnd->m_pGfx->drawModel(cube);
		}
	}


	//SKYBOX STUFF XD
	glm::mat4 tmp = projview;
	tmp = glm::scale(tmp, glm::vec3(150.f, 150.f, 150.f));
	glDepthMask(GL_FALSE);
	m_SkyBoxShader->use();
	m_SkyBoxShader->setMat4("model", tmp);
	SkyBox->bindVAO();
	glBindTexture(GL_TEXTURE_CUBE_MAP, SkyBox->getTexture());
	glDrawElements(GL_TRIANGLES, SkyBox->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	glDepthMask(GL_TRUE);
}

void Engine::updateModels(float dt)
{

}

void Engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static_cast<Window*>(glfwGetWindowUserPointer(window))->kbd.update(key, scancode, action, mods);
}

void Engine::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	static_cast<Window*>(glfwGetWindowUserPointer(window))->mouse.updatePos(xpos, ypos);
}

void Engine::cursor_enter_callback(GLFWwindow* window, int entered)
{
	static_cast<Window*>(glfwGetWindowUserPointer(window))->mouse.updteEnter(entered);
}

void Engine::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	static_cast<Window*>(glfwGetWindowUserPointer(window))->mouse.update(button, action, mods);
}

void Engine::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	static_cast<Window*>(glfwGetWindowUserPointer(window))->mouse.updateScroll(xoffset, yoffset);
}
void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


Engine::Exception::Exception(int line, const char* file, const char* what) noexcept
	:
	IGException(line, file, what)
{}

const char* Engine::Exception::getType() const noexcept
{
	return "IO Exception";
}

//float angle = 20.0f * 0;
//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//model = glm::rotate(model, glm::radians(x * 180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//model = glm::rotate(model, glm::radians(y * 180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//model = glm::rotate(model, glm::radians(z * 180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 1.0f));