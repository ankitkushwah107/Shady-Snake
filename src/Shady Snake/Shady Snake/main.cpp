#include<shadyengine/app_manager.h>
#include<shadyengine/logger.h>
#include<memory>
#include"Game.h"
#include"Globals.h"


using namespace shady_engine;


int main()
{

	logger::getInstance()->init("Shady Snake");

	try {
		std::unique_ptr<application> app =
			std::make_unique<Game>("Lasers", Globals::WIDTH , Globals::HEIGHT,true);
		app_manager::start_app(app.get());
		app->start();
	}
	catch (std::runtime_error& e) {
		logger::getInstance()->log(e.what());
	}
	return 0;
}