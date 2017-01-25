#include "sound_manager.h"


using namespace irrklang;


namespace shady_engine
{

	sound_manager::sound_manager()
	{
		mEngine = createIrrKlangDevice();
		
		init();
	}


	sound_manager::~sound_manager()
	{
		mEngine->drop();
	}


	void sound_manager::init()
	{
		mEngine = createIrrKlangDevice();

		if (!mEngine)
			throw std::runtime_error("failed to initialize sound manager!");
	}

	void sound_manager::play_sfx(const std::string & pLocation) const
	{
		mEngine->play2D(pLocation.c_str());
	}

	void sound_manager::play_music(const std::string & pLocation) const
	{
		mEngine->play2D(pLocation.c_str(),true);
	}

}
