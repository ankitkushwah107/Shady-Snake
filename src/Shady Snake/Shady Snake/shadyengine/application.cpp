#include"application.h"



//shady_engine headers
#include"Debugger.h"
#include"Logger.h"

namespace shady_engine
{


	application::application(
		const std::string& pName,
		int pWindowWidth,
		int pWindowHeight,
		bool pFullScreen
	)
		:

		mWindowWidth(pWindowWidth),
		mWindowHeight(pWindowHeight)
	{

		if (!glfwInit())
		{
			throw std::runtime_error(
				"failed to initialize glfw library"
			);
		}


		//Creating OpenGL 4.3 context
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		mWindow = glfwCreateWindow(
			pWindowWidth,
			pWindowHeight,
			pName.c_str(),
			pFullScreen ? glfwGetPrimaryMonitor() : nullptr,
			nullptr
		);

		if (!mWindow)
		{
			glfwTerminate();
			throw std::runtime_error(
				"failed to create window!"
			);
		}


		glfwMakeContextCurrent(mWindow);


		glewExperimental = true;
		if (glewInit() != GLEW_OK)
		{
			glfwTerminate();
			glfwDestroyWindow(mWindow);

			throw std::runtime_error(
				"failed to initialize glfw library"
			);
		}

		glGetError();

		GLint flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(debug_output_callback, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
		}
		else
		{
			glfwDestroyWindow(mWindow);
			glfwTerminate();
			throw std::runtime_error(
				"failed to get debugger!"
			);
		}
	}



	application::~application()
	{
		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}


	void application::start()
	{
		this->glfw_loop();
	}


	void application::glfw_loop()
	{



		while (!glfwWindowShouldClose(mWindow))
		{
			glfwPollEvents();
			//calling custom loop
			this->loop();

			glfwSwapBuffers(mWindow);

		}
	}



	//Callbacks
	void application::key_callback(
		GLFWwindow* pWindow,
		int pKey,
		int pScancode,
		int pAction,
		int pMods
	) {}



	void application::error_callback(
		int pError,
		const char* pDesc
	) {}



	void application::window_resize_callback(
		GLFWwindow* pWindow,
		int pWidth,
		int pHeight
	) {}



	void application::mouse_button_callback(
		GLFWwindow* pWindow,
		int pKey,
		int pAction,
		int pMods
	) {}



	void application::cursor_pos_callback(
		GLFWwindow* pWindow,
		double pX,
		double pY
	) {}



}