#include "Engine.h"

int Engine::SCR_WIDTH = 1280;
int Engine::SCR_HEIGHT = 720;

Engine::Engine()
	:
	m_Timer()
	,imgui()
	,m_Camera({0.f,1.50f,-3.f})
	,m_bInputEnabled(true)
	, l({ 0.f,10.f,0.f }, {1.f,1.f,1.f})
{
	//================================================================
	//= Initialize GLFW and force to use 4.4 OpenGL
	//================================================================
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);


	//================================================================
	//= Creating the Window
	//================================================================
	m_pWnd = std::make_unique<Window>(SCR_WIDTH, SCR_HEIGHT, "Kacp3r3 Playground");


	//================================================================
	//= Glad Initialization
	//================================================================
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw IGEXCEPTION_ENG("Failed to load glad");
	

	//================================================================
	//= ImGui Initialization
	//================================================================
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
	glfwSetWindowSizeCallback(x, window_size_callback);

	//Input options
	//glfwSetInputMode(x, GLFW_STICKY_KEYS | GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	m_Shader = new Shader("Graphics/Shaders/vs.vs", "Graphics/Shaders/fs.fs");
	m_Shader->use();
	m_Shader->setInt("texture1", 0);
	m_Shader->setVec3("lightColor", l.getColor());
	m_Shader->setVec3("lightPosition", l.getPos());

	m_SkyBoxShader = new Shader("Graphics/Shaders/sky.vs", "Graphics/Shaders/sky.fs");
	m_SkyBoxShader->use();
	m_SkyBoxShader->setInt("skybox", 0);

	m_HUDShader = new Shader("Graphics/Shaders/hud.vs", "Graphics/Shaders/hud.fs");
	m_HUDShader->use();
	m_HUDShader->setInt("texture1", 0);

	AssetManager::get();
	AssetManager::get().loadTextures();
	AssetManager::get().loadModels();
	
	m_pWnd->initRenderer();
	m_CameraHUD = new CameraHUD(AssetManager::get().getModel("Plane"),AssetManager::get().getTexture("Cursor"),*m_HUDShader);
	
	stall = new Entity(AssetManager::get().getModel("Dragon"), AssetManager::get().getTexture("JanSzescian"));
	SkyBox = new Entity(AssetManager::get().getModel("SkyBox"), AssetManager::get().getTexture("SkyBox"));
	SkyBox->setScale(2.f);
	//stall = new Entity(AssetManager::get().getModel("Stall"), AssetManager::get().getTexture("Stall"));
	int w = 50; int z = 50;
	int y = 5;
	m_vecEntities.reserve(w * z + y * w);
	//Prepare scene
	for (int i = 0; i < w; i++)
		for (int j = 0; j < z; ++j)
		{
			m_vecEntities.push_back(new Entity(AssetManager::get().getModel("Cube"), AssetManager::get().getTexture("JanSzescian")));
			m_vecEntities.back()->setPos(glm::vec3(((float)i - w / 2.f) - .5f, -.5f, ((float)j - z / 2.f) - .5f));
		}

	//Œciany
	for (int i = 0; i < w; i++)
		for (int j = 1; j < y + 1; ++j)
		{
			if ((i == 25 || i == 26) && (j == 1 || j == 2)) continue;
			m_vecEntities.push_back(new Entity(AssetManager::get().getModel("Cube"), AssetManager::get().getTexture("JanSzescian")));
			m_vecEntities.back()->setPos(glm::vec3((float)i - w / 2.f - .5f, (float)j - .5f, 2.f - .5f));
		}
}

Engine::~Engine()
{
	delete m_Shader;
	delete m_SkyBoxShader;
	delete SkyBox;
	for (auto entity : m_vecEntities)
		delete entity;
}

int Engine::Go()
{
	float color[3] = { l.getColor().r,l.getColor().g,l.getColor().b };
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
			ImGui::Text("Cursor %s", m_bInputEnabled ? "Disabled" : "Enabled");               // Display some text (you can use a format strings too)
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
			if (ImGui::Checkbox("Camera fly", m_Camera.ptrFly())) m_Camera.updatePos();      // Edit bools storing our window open/close state
			//ImGui::Checkbox("Another Window", &show_another_window);
			//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			if (!m_bInputEnabled)
			{
				ImGui::Begin("Light properties");
				if (ImGui::SliderFloat3("Position ", (float*)l.ptrPos(), 0.f, 10.f))
				{
					m_Shader->use();
					m_Shader->setVec3("lightPosition", l.getPos());
				}
				if (ImGui::ColorEdit3("Light Color", (float*)l.ptrColor()))
				{
					m_Shader->use();
					m_Shader->setVec3("lightColor", l.getColor());
				}
				ImGui::End();
				ImGui::InputInt("Width: ", &SCR_WIDTH, 10, 100);
				ImGui::InputInt("Height: ", &SCR_HEIGHT, 10, 100);
				if (ImGui::Button("Change Size"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				{
					glfwSetWindowSize(m_pWnd->getWnd(), SCR_WIDTH, SCR_HEIGHT);
					m_Camera.updateProjection();
				}
			}
			//ImGui::SameLine();
			//ImGui::Text("counter = %d", counter);

			ImGui::End();
			//ImGui::ShowDemoWindow();
			
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
							//cube->setTexture(AssetManager::get().getTexture("Zuza"));
							break;
					case GLFW_KEY_4:
							//cube->setTexture(AssetManager::get().getTexture("JanSzescian"));
							break;
					case GLFW_KEY_5:
							//SkyBox->setTexture(AssetManager::get().getTexture("SkyBox"));
							break;
					case GLFW_KEY_6:
							//SkyBox->setTexture(AssetManager::get().getTexture("SkyBoxDoom"));
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

	glm::mat4 projview = m_Camera.getProjection() * m_Camera.getMatrix();
	//Draw Cursor
	m_HUDShader->use();
	m_CameraHUD->drawHUD(*m_HUDShader, *m_pWnd->m_pGfx);
	
	//Draw scene
	m_Shader->use();
	m_Shader->setMat4("viewMatrix", m_Camera.getMatrix());
	m_Shader->setMat4("projectionMatrix", m_Camera.getProjection());
	//for (auto cube : m_vecEntities)
	//{
	//	m_Shader->setMat4("transformationMatrix", cube->getTransformationMatrix());
	//	m_pWnd->m_pGfx->drawModel(cube->getModel());
	//}
	m_Shader->setMat4("transformationMatrix", stall->getTransformationMatrix());
	m_pWnd->m_pGfx->drawModel(stall->getModel());


	//SKYBOX STUFF XD
	glm::mat4 tmp = projview;
	tmp = glm::scale(tmp, glm::vec3(150.f, 150.f, 150.f));
	glDepthMask(GL_FALSE);
	m_SkyBoxShader->use();
	m_SkyBoxShader->setMat4("model", tmp);
	auto model = SkyBox->getModel();
	model->bindVAO();
	glBindTexture(GL_TEXTURE_CUBE_MAP, model->getTexture());
	glDrawElements(GL_TRIANGLES, model->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
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
void Engine::window_size_callback(GLFWwindow* window, int width, int height)
{
	static_cast<Window*>(glfwGetWindowUserPointer(window))->updateSize(width, height);
	ImGui::GetIO().DisplaySize.x = width;
	ImGui::GetIO().DisplaySize.y = height;
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