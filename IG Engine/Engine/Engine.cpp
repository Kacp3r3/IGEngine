#include "Engine.h"

int Engine::SCR_WIDTH = 1600;
int Engine::SCR_HEIGHT = 900;

Engine::Engine()
	:
	 m_Timer()
	,m_Imgui()
	,m_Camera({0.f,5.50f,0.f})
	,m_bInputEnabled(true)
	,m_Sun({ -169.f,177.f,-245.f }, {1.f,1.f,1.f})
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
	std::cout << glGetString(GL_VERSION) << std::endl;


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


	//================================================================
	//= load Resources
	//================================================================
	AssetManager::get();
	AssetManager::get().loadTextures();
	AssetManager::get().loadModels();
	AssetManager::get().loadPictures();

	//================================================================
	//= Render init
	//================================================================
	m_Imgui.initImGui(m_pWnd->getWnd());
	m_pWnd->initRenderer();

	//Input options
	//glfwSetInputMode(x, GLFW_STICKY_KEYS | GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

	//m_vecTerrains.push_back(new Terrain(0, 0, AssetManager::get().getTexture("Grass"),  AssetManager::get().getPicture("test")));
	//m_vecTerrains.push_back(new Terrain(1, 0, AssetManager::get().getTexture("Grass"), AssetManager::get().getPicture("terrain")));
	//m_vecTerrains.push_back(new Terrain(1, 1, AssetManager::get().getTexture("Grass"), AssetManager::get().getPicture("terrain")));
	//m_vecTerrains.push_back(new Terrain(0, 1, AssetManager::get().getTexture("Grass"),AssetManager::get().getPicture("terrain")));
	//for(auto ter : m_vecTerrains)
		//m_pWnd->m_pGfx->addTerrain(ter);
	//SkyBox = new Entity(AssetManager::get().getModel("SkyBox"), AssetManager::get().getTexture("SkyBox"));
	m_vecEntities.reserve(3);

	stall = new Entity(AssetManager::get().getModel("Mapka"), AssetManager::get().getTexture("mapka"));
	//stall2 = new Entity(AssetManager::get().getModel("Cube"), AssetManager::get().getTexture("JanSzescian"));
	//stall2->setPos({ 20.f,0,20.f });
	//stall->setScale(2.5f);
	//stall->setPos({ 400.f,checkForHeight({400.f,400.f}),400.f });
	m_pWnd->m_pGfx->addEntity(stall);
	//stall2 = new Entity(AssetManager::get().getModel("Cube"), AssetManager::get().getTexture("JanSzescian"));
	//stall2->setScale(10.f);
	//stall2->setPos(m_Sun.getPos());
	//m_pWnd->m_pGfx->addEntity(stall2);
}

Engine::~Engine()
{
	for (auto entity : m_vecEntities)
		delete entity;

	for (auto terrain : m_vecTerrains)
		delete terrain;
}

int Engine::Go()
{
	//float x = 0.f, y = 0.f, z = 0.f;
	//glfwSetCursorPos(m_pWnd->getWnd(), SCR_WIDTH / 2.f, SCR_HEIGHT / 2.f);
	while (!glfwWindowShouldClose(m_pWnd->getWnd()))
	{
		//Providing delta Time
		m_Timer.Mark();
		while (m_Timer.getDelta() < m_Timer.getSingleFrameTime())
			m_Timer.Mark();

		
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
		m_Imgui.beginFrame();
		{
			ImGui::Begin("IGEngine");                          // Create a window called "Hello, world!" and append into it.
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			//ImGui::SameLine();
			ImGui::Text("Current material: %s", Entity::m_Material.getCurrName());
			ImGui::Text("Cursor %s", m_bInputEnabled ? "Disabled" : "Enabled");               // Display some text (you can use a format strings too)
			if (!m_bInputEnabled)
			{
				ImGui::Text("Cursor inside window: %s", m_pWnd->mouse.insideWindow() ? "True" : "False");               // Display some text (you can use a format strings too)
				ImGui::Text("Mouse pos x: %d y: %d", (int)m_pWnd->mouse.getPos().x, (int)m_pWnd->mouse.getPos().y);               // Display some text (you can use a format strings too)

				ImGui::Begin("Camera properties");
				ImGui::Text("Perspective");
				if (ImGui::SliderFloat("Far", m_pWnd->m_pGfx->ptrFar(), 10.0f, 400.0f)) m_pWnd->m_pGfx->updateProjection();
				if (ImGui::SliderFloat("Near", m_pWnd->m_pGfx->ptrNear(), 0.1f, 10.0f)) m_pWnd->m_pGfx->updateProjection();
				if (ImGui::SliderFloat("Fov", m_pWnd->m_pGfx->ptrFov(), 1.0f, 150.0f)) m_pWnd->m_pGfx->updateProjection();
				ImGui::Text("Properties");
				ImGui::SliderFloat("Velocity", m_Camera.ptrVelocity(), 1.0f, 60.0f);
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
				ImGui::SliderFloat3("Position ", (float*)m_Sun.ptrPos(), -20.f, 20.f);
				ImGui::ColorEdit3("Light Color", (float*)m_Sun.ptrColor());
				ImGui::End();


				ImGui::InputInt("Width: ", &SCR_WIDTH, 10, 100);
				ImGui::InputInt("Height: ", &SCR_HEIGHT, 10, 100);
				if (ImGui::Button("Change Size"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				{
					glfwSetWindowSize(m_pWnd->getWnd(), SCR_WIDTH, SCR_HEIGHT);
					m_pWnd->m_pGfx->updateProjection();
				}

				ImGui::Begin("Light terrain properties");
				ImGui::SliderFloat3("Ambient ", (float*)&RendererMaster::ambient, 0.f, 1.f);
				ImGui::SliderFloat3("Specular ", (float*)&RendererMaster::specular, 0.f, 1.f);
				ImGui::SliderFloat3("Diffuse ", (float*)&RendererMaster::diffuse, 0.f, 1.f);
				ImGui::SliderFloat("Shininess", &RendererMaster::shininees, 0.f,2.f);
				ImGui::End();
			}
			//ImGui::SameLine();
			//ImGui::Text("counter = %d", counter);

			ImGui::End();
			//ImGui::ShowDemoWindow();
			
		}
		m_Imgui.endFrame();

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
				if (m_bInputEnabled) m_pWnd->m_pGfx->processScroll(m_pWnd->mouse.getScrollYOffset());
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
							m_pWnd->m_pGfx->resetProjection();
							break;
					case GLFW_KEY_1:
							glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
							break;
					case GLFW_KEY_2:
							glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
							break;
					case GLFW_KEY_3:
							//cube->setTexture(AssetManager::get().getTexture("Zuza"));
							Entity::m_Material.nextMaterial();
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
	m_pWnd->m_pGfx->renderScene(m_Sun, m_Camera);
}

void Engine::updateModels(float dt)
{
	m_Sun.setPos({ sin(glfwGetTime()) * 160.f + 400.f,185.f,cos(glfwGetTime()) * 160.f + 400.f });
	//stall2->setPos(m_Sun.getPos());
	if (!m_Camera.getFly())
	{
		glm::vec3 x = m_Camera.getPos();
		m_Camera.setPos({ x.x,checkForHeight({x.x,x.z}) + 4.f ,x.z });
	}
}

float Engine::checkForHeight(glm::vec2 coords)
{
	float height;
	float tmp = Terrain::m_MaxHeight + 0.1f;
	for (auto& terrain : m_vecTerrains)
	{
		height = terrain->getHeight(coords.x, coords.y);
		if (height <= tmp && height >= -tmp)
			return height;
	}
	return 0.f;
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
	ImGui::GetIO().DisplaySize.x = (float)width;
	ImGui::GetIO().DisplaySize.y = (float)height;
}

Engine::Exception::Exception(int line, const char* file, const char* what) noexcept
	:
	IGException(line, file, what)
{}

const char* Engine::Exception::getType() const noexcept
{
	return "IO Exception";
}

//Updating Label name
		//std::string a = m_sWindowName + " FPS: " + std::to_string((int)round(1 / m_Timer.getDelta()));
		//glfwSetWindowTitle(m_pWnd->getWnd(), a.c_str());


	//int w = 50; int z = 50;
	//int y = 5;
	////Prepare scene
	//for (int i = 0; i < w; i++)
	//	for (int j = 0; j < z; ++j)
	//	{
	//		m_vecEntities.push_back(new Entity(AssetManager::get().getModel("Cube"), AssetManager::get().getTexture("JanSzescian")));
	//		m_vecEntities.back()->setPos(glm::vec3(((float)i - w / 2.f) - .5f, -.5f, ((float)j - z / 2.f) - .5f));
	//		//m_pWnd->m_pGfx->addEntity(m_vecEntities.back());
	//	}

	////Œciany
	//for (int i = 0; i < w; i++)
	//	for (int j = 1; j < y + 1; ++j)
	//	{
	//		if ((i == 25 || i == 26) && (j == 1 || j == 2)) continue;
	//		m_vecEntities.push_back(new Entity(AssetManager::get().getModel("Cube"), AssetManager::get().getTexture("JanSzescian")));
	//		m_vecEntities.back()->setPos(glm::vec3((float)i - w / 2.f - .5f, (float)j - .5f, 24.f - .5f));
	//		//m_pWnd->m_pGfx->addEntity(m_vecEntities.back());
	//	}