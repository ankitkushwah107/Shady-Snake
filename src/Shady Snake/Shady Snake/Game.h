#ifndef INC_GAME_MANAGER_H
#define INC_GAME_MANAGER_H


//Parent class
#include<shadyengine/application.h>

//C++ headers
#include<vector>
#include<list>


//Third party headers
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

//shady_engine Headers
#include<shadyengine/resources.h>
#include<shadyengine/sprite_renderer.h>
#include<shadyengine/text_renderer.h>
#include<shadyengine/timer.h>
#include<shadyengine/sound_manager.h>
#include<shadyengine/particles_renderer.h>


#include"Globals.h"
#include"Camera.h"
#include"Snake.h"
#include"level_manager.h"
#include"orb.h"
#include"EnemySnake.h"
#include"explosion.h"
#include"wave_point.h"
#include"wave.h"

class Game : public shady_engine::application
{
	glm::vec2 mGameOverPosition;
	bool reached;
	std::shared_ptr<shady_engine::texture2D> mGameOverTexture;

	enum game_states {running,game_over};
	game_states mCurrentState;
	//glm::vector<glm::vec4> colors;

	bool keys[1024];
	//Sprite Renderer

	shady_engine::sound_manager *mSoundManager;
	std::shared_ptr<shady_engine::sprite_renderer> mSpriteRenderer;
	
	shady_engine::particles_renderer *mParticleRenderer;

	//Text Renderer
	shady_engine::text_renderer* mText;
	shady_engine::timer* mTimer;

	glm::mat4 mGameProjection;

	Snake *snake;
	Camera *mCamera;
	

	
	level_manager* mLevelManager;
	glm::vec2 mMapSize;

	std::vector<AABB> tiles;
	

	const int MAX_ORBS = 20;
	std::vector<orb*> orbs;

	const int MAX_ENEMIES = 20;
	std::vector<EnemySnake*> enemies;
	std::vector<explosion*> mExplosions;
	std::vector<wave*> mWaves;

	const int MAX_WAVE_POINTS = 20;
	std::vector<wave_point*> mWavePoints;


	std::vector<AABB> colliders;
	std::vector<glm::vec2> offsets;
	std::vector<glm::vec2> scalers;
	std::vector<glm::vec4> colors;

	

public:
	


	Game(
		const std::string& name,
		int windowWidth,
		int windowHeight,
		bool fullScreen
	);


	void destroy();
	void reset();

	~Game();



	void key_callback(
		GLFWwindow* window, 
		int key, 
		int scancode, 
		int action, 
		int mods
	) override;



	void window_resize_callback(
		GLFWwindow* window, 
		int width, 
		int height
	) override;



	void mouse_button_callback(
		GLFWwindow* window, 
		int key, 
		int action, 
		int mods
	) override;



	void cursor_pos_callback(
		GLFWwindow* window, 
		double xPos, 
		double yPos
	)override;

	void loop() override;
	
	void doMovements();
	void tick();
	void render();
};


#endif