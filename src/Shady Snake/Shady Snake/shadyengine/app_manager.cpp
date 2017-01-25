#include"app_manager.h"


namespace shady_engine
{


	void app_manager::start_app(application* pApp)
	{
		mApp = pApp;

		glfwSetKeyCallback(mApp->get_window(), key_callback);

		glfwSetFramebufferSizeCallback(mApp->get_window(), window_resize_callback);

		glfwSetMouseButtonCallback(mApp->get_window(), mouse_button_callback);
		glfwSetCursorPosCallback(mApp->get_window(), cursor_pos_callback);

		glfwSetErrorCallback(error_callback);
	}


	void app_manager::key_callback(
		GLFWwindow* window,
		int key,
		int scancode,
		int action,
		int mods
	)

	{
		if (mApp) mApp->key_callback(window, key, scancode, action, mods);
	}


	void app_manager::error_callback(
		int error,
		const char* desc
	)

	{
		if (mApp) mApp->error_callback(error, desc);
	}



	void app_manager::window_resize_callback(
		GLFWwindow* window,
		int width,
		int height
	)

	{
		if (mApp) mApp->window_resize_callback(window, width, height);
	}



	void app_manager::mouse_button_callback(
		GLFWwindow* window,
		int key,
		int action,
		int mods
	)

	{
		if (mApp) mApp->mouse_button_callback(window, key, action, mods);
	}



	void app_manager::cursor_pos_callback(
		GLFWwindow* window,
		double xPos,
		double yPos
	)
	{
		if (mApp) mApp->cursor_pos_callback(window, xPos, yPos);
	}


	application* app_manager::mApp = nullptr;
	

}