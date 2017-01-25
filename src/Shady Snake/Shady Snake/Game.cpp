//Declaration header
#include"Game.h"

//C++ headers
#include<iostream>


//shady_engine headers
#include<shadyengine/timer.h>
#include<shadyengine/random.h>
#include<shadyengine/particles_renderer.h>

//Exposing namespaces
using namespace shady_engine;
using namespace std;



//Constructor
Game::Game(
	const std::string& name,
	int windowWidth,
	int windowHeight,
	bool fullScreen
)
	:

	application(
		name,
		windowWidth,
		windowHeight,
		fullScreen
	)

{
	
	//Loading texture atlas
	resources::getInstance()->load_texture("font texture", "Bitmap Fonts/gothic.png", GL_RGBA);

	//snake textures
	resources::getInstance()->load_texture("eyes", "textures/eyes.png", GL_RGBA);
	resources::getInstance()->load_texture("explosion", "sprite sheets/sprite_asteroid_explosion2.png", GL_RGBA);
	mGameOverTexture = resources::getInstance()->load_texture("2","textures/game_over_screen.png",GL_RGBA);
	 resources::getInstance()->load_texture("star", "textures/star.png", GL_RGBA);
	resources::getInstance()->load_texture("wave", "textures/wave.png", GL_RGBA);
	

	//projection matrix for game 
	mGameProjection = glm::ortho(0.0f, float(Globals::WIDTH), float(Globals::HEIGHT), 0.0f);

	//sprite renderer for drawing bitmaps
	mSpriteRenderer = std::make_shared<sprite_renderer>();

	//particle renderer
	mParticleRenderer = new particles_renderer();

	//text renderer for rendering text
	mText = new text_renderer(
		resources::getInstance()->get_texture("font texture"),
		"Bitmap Fonts/gothic.fnt"
		);
	


	mLevelManager = new level_manager(128.0f);
	mMapSize = mLevelManager->getMapSize();
	
	
	snake = new Snake(
		mSpriteRenderer,
		resources::getInstance()->get_texture("eyes"),
		mLevelManager->getPlayerStart(),
		glm::vec2(0, -1),
		300.0f,
		30.0f,
		10,
		glm::vec4(random::getInstance()->inside_unit_sphere(),1.0f),
		false
	);


	mCamera = new Camera(snake->getHeadCenter());
	mCamera->update(snake->getHeadCenter());
	mCamera->setMapSize(mMapSize - glm::vec2(mWindowWidth,mWindowHeight));


	
	mCurrentState = game_states::running;
	mGameOverPosition.x = mCamera->getPosition().x;
	mGameOverPosition.y = mCamera->getPosition().y - 720.0f;

	mSoundManager = new sound_manager();
	mTimer = new timer();
#pragma endregion


//	glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glViewport(0, 0, Globals::WIDTH, Globals::HEIGHT);

	//Enabling states
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mSoundManager->play_music("music/farty.mp3");

}

void Game::destroy()
{
	delete snake;
	enemies.clear();
	orbs.clear();
	mWavePoints.clear();

}

void Game::reset()
{

	snake = new Snake(
		mSpriteRenderer,
		resources::getInstance()->get_texture("eyes"),
		mLevelManager->getPlayerStart(),
		glm::vec2(0, -1),
		300.0f,
		20.0f,
		10,
		glm::vec4(random::getInstance()->inside_unit_sphere(), 1.0f),
		false
	);

	mCurrentState = game_states::running;
}


void Game::key_callback(
	GLFWwindow* window,
	int key,
	int scancode,
	int action,
	int mods
)
{

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS)
		keys[key] = true;
	if (action == GLFW_RELEASE)
		keys[key] = false;

}



void Game::doMovements()
{

	switch (mCurrentState)
	{
		case game_states::running:
			if (keys[GLFW_KEY_ESCAPE])
				return;
			break;
		case game_states::game_over:

			if (reached)
			{
				if (keys[GLFW_KEY_ESCAPE])
					return;
				if (keys[GLFW_KEY_SPACE])
				{
					destroy();
					reset();
				}

				reached = false;
			}

			break;
	}

}


void Game::window_resize_callback(
	GLFWwindow* window,
	int width,
	int height
)
{
	glViewport(0, 0, width, height);
}



void Game::mouse_button_callback(
	GLFWwindow* window,
	int key,
	int action,
	int mods
)

{

}



void Game::cursor_pos_callback(
	GLFWwindow* window,
	double xPos,
	double yPos
)

{

	glm::vec2 pos = mCamera->getPosition() + glm::vec2(xPos,yPos);
	snake->onMouseMove(pos);

}



Game::~Game()
{

}



void Game::loop()
{

	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	mTimer->update();
	doMovements();
	tick();
	render();
}






void Game::tick()
{


	double dt = mTimer->get_elapsed_time();

	if (mCurrentState == game_states::running)
	{


#pragma region collision



		for (auto iter = orbs.begin(); iter != orbs.end();)
		{
			orb *object = *(iter);

			if (object->getCollider().colliding_with(snake->getHeadCollider()))
			{
				mSoundManager->play_sfx("sfx/bite.mp3");
				snake->pushNewBlock();
				delete (*iter);
				iter = orbs.erase(iter);
			}
			else
				iter++;
		}



		for (auto enemy : enemies)
		{

			for (auto iter = orbs.begin(); iter != orbs.end();)
			{
				orb *object = *(iter);
				if (object->getCollider().colliding_with(enemy->getHeadCollider()))
				{
					delete (*iter);
					iter = orbs.erase(iter);
				}
				else
					iter++;
			}

			glm::vec2 position = enemy->getHeadPosition();

			if (
				position.x < 0.0f ||
				position.x > mMapSize.x + 128.0f ||
				position.y < 0.0f ||
				position.y > mMapSize.y + 128.0f
				)

				enemy->negateVelocity();

		}



		std::vector<AABB> collidables;
		for (auto enemy : enemies)
		{
			auto blocks = enemy->getBlocks();

			for (auto block : blocks)
			{
				if (
					block.position.x > mCamera->getPosition().x &&
					block.position.x < mCamera->getPosition().x + mWindowWidth &&
					block.position.y > mCamera->getPosition().y &&
					block.position.y < mCamera->getPosition().y + mWindowHeight
					)
					collidables.push_back(block.collider);
			}
		}

		for (auto collidable : collidables)
		{
			if (snake->getHeadCollider().colliding_with(collidable))
			{
				auto blocks = snake->getBlocks();

				for (auto block : blocks)
				{
					if ((random::getInstance()->integer(1, 3) % 3 == 0))
						continue;
						mExplosions.push_back(new explosion(
							block.position,
							snake->getSize() * 2.0f,
							resources::getInstance()->get_texture("explosion"),
							mSpriteRenderer,
							4,
							7,
							1
						));
			
				}
				mCurrentState = game_states::game_over;
			}
		}



		for (auto iter2 = mWavePoints.begin(); iter2 != mWavePoints.end();)
		{
			if (snake->getHeadCollider().colliding_with((*iter2)->getCollider()))
			{
				mWaves.push_back(
					new wave(
						resources::getInstance()->get_texture("wave"),
						mSpriteRenderer,
						snake->getHeadCenter(),
						glm::vec2(20.0f),
						10.0f
					)
				);

				snake->set_secured(true);

				iter2 = mWavePoints.erase(iter2);
			}
			else
				iter2++;
		}



			for (auto iter2 = mWaves.begin(); iter2 != mWaves.end();iter2++)
			{
				
				bool collided = false;
				for (auto iter = enemies.begin(); iter != enemies.end();)
				{

					if ((*iter)->getHeadCollider().colliding_with((*iter2)->getCollider()))
					{


						auto blocks = (*iter)->getBlocks();

						for (auto block : blocks)
						{
							if ((random::getInstance()->integer(1, 3) % 3 == 0))
								continue;
							mExplosions.push_back(new explosion(
								block.position,
								(*iter)->getSize() * 2.0f,
								resources::getInstance()->get_texture("explosion"),
								mSpriteRenderer,
								4,
								7,
								1
							));

						}

						iter = enemies.erase(iter);
						break;
					}
					else
					{
						iter++;
					}
					
					
				}

				if (collided)
					break;
		   }

#pragma endregion


#pragma region update

	


		snake->tick(dt);
		mCamera->update(snake->getHeadCenter());
		mGameOverPosition.x = mCamera->getPosition().x;
		mGameOverPosition.y = mCamera->getPosition().y - 720.0f;


		float W = Globals::WIDTH;
		float H = Globals::HEIGHT;
		float halfW = W / 2.0f;
		float halfH = H / 2.0f;

		float cameraX = mCamera->getPosition().x;
		float cameraY = mCamera->getPosition().y;


		int wavePointSize = mWavePoints.size();

		for (int i = 0; i < MAX_WAVE_POINTS - wavePointSize; i++)
		{

			enum Sides { LEFT, RIGHT, UP, DOWN };
			int side = random::getInstance()->integer(0, 3);

			glm::vec2 position;

			position.x = random::getInstance()->integer(0, mMapSize.x);
			position.y = random::getInstance()->integer(0, mMapSize.y);

			int radius = random::getInstance()->integer(10, 30);
			glm::vec4 color = glm::vec4(random::getInstance()->inside_unit_sphere(), 1.0f);

			mWavePoints.push_back(new wave_point(
				resources::getInstance()->get_texture("star"),
				mSpriteRenderer,
				position,
				(resources::getInstance()->get_texture("star")->get_size()*0.3f)
			));

		}

		//Orbs
		int orbsSize = orbs.size();

		for (int i = 0; i < MAX_ORBS - orbsSize; i++)
		{

			float minX = glm::clamp(cameraX - halfW, 0.0f, cameraX + 50.0f);
			float maxX = glm::clamp(cameraX + W + halfW, cameraX + W, mMapSize.x);

			float minY = glm::clamp(cameraY - halfH, 0.0f, cameraY + 50.0f);
			float maxY = glm::clamp(cameraY + H + halfH, cameraY + H, mMapSize.y);

			glm::vec2 position;
			position.x = random::getInstance()->real(minX, maxX);
			position.y = random::getInstance()->real(minY, maxY);

			int radius = random::getInstance()->integer(10, 30);
			glm::vec4 color = glm::vec4(random::getInstance()->inside_unit_sphere(), 1.0f);

			orbs.push_back(new orb(mSpriteRenderer, position, radius, color));

		}


		//Enemy



		int enemiesSize = enemies.size();

		for (int i = 0; i < MAX_ENEMIES - enemiesSize; i++)
		{

			enum Sides { LEFT, RIGHT, UP, DOWN };
			int side = random::getInstance()->integer(0, 3);

			glm::vec2 position;

			position.x = random::getInstance()->integer(0, mMapSize.x);
			position.y = random::getInstance()->integer(0, mMapSize.y);
			int radius = random::getInstance()->integer(10, 70);
			float angle = random::getInstance()->real(0.0f, 360.0f);
			glm::vec2 velocity = glm::normalize(snake->getHeadCenter() - position);

			glm::vec4 color = glm::vec4(random::getInstance()->inside_unit_sphere(), 1.0f);

			enemies.push_back(new EnemySnake(
				mSpriteRenderer,
				resources::getInstance()->get_texture("eyes"),
				position,
				glm::normalize(velocity),
				random::getInstance()->integer(40, 200),
				radius,
				random::getInstance()->integer(10, 200),
				color,
				false

			));


		}

		for (auto enemy : enemies)
			enemy->tick(dt);

#pragma endregion


#pragma region screen_test



		//ORBS
		for (auto iter = orbs.begin(); iter != orbs.end();)
		{
			orb *object = *iter;

			if (
				(object->getPosition().x + object->getSize().x < cameraX - halfW) ||
				(object->getPosition().x > (cameraX + halfW + W)) ||
				(object->getPosition().y + object->getSize().y < cameraY - halfH) ||
				(object->getPosition().y > (cameraY + halfH + H))
				)
			{
				delete (*iter);
				iter = orbs.erase(iter);
			}
			else
				iter++;
		}



#pragma endregion
	
}
	if(mCurrentState == game_states::game_over)
	{

		if (mGameOverPosition.y > (mCamera->getPosition().y - 5.0f))
			reached = true;
		else
			mGameOverPosition.y += 800.0f*dt;
		
	}


	//eliminating explosions first

	for (auto iter = mExplosions.begin(); iter != mExplosions.end();)
	{
		(*iter)->update();

		bool explosion_done = (*iter)->is_done();

		if (explosion_done)
			iter = mExplosions.erase(iter);
		else iter++;
	}


	for (auto iter = mWaves.begin(); iter != mWaves.end();)
	{
		(*iter)->tick(dt);

		bool wave_done = (*iter)->is_done();

		if (wave_done)
			iter = mWaves.erase(iter);
		else
			iter++;
	}


#pragma region instancing


		//enemies
		for (auto enemy : enemies)
		{
			auto blocks = enemy->getBlocks();
			for (auto block : blocks)
			{
				offsets.push_back(block.position);
				scalers.push_back(enemy->getSize());
				colors.push_back(enemy->getColor());
			}
		}


		//orbs

		for (auto orb : orbs)
		{
			offsets.push_back(orb->getPosition());
			scalers.push_back(orb->getSize());
			colors.push_back(orb->getColor());
		}


		//player
		if (mCurrentState == game_states::running)
		{
			auto& blocks = snake->getBlocks();

			for (auto block : blocks)
			{
				offsets.push_back(block.position);
				scalers.push_back(snake->getSize());
				colors.push_back(snake->getColor());
			}
		}


#pragma endregion
	
}





void Game::render()
{



		//first level will be drawn
		mLevelManager->render(mGameProjection, mCamera->getView());
		//then objects




		mParticleRenderer->render(
			mGameProjection,
			mCamera->getView(),
			scalers.size(),
			colors,
			offsets,
			scalers
		);



		if(mCurrentState == game_states::running)
			snake->render(mGameProjection, mCamera->getView());


		for (auto orb : orbs)
			orb->render(mGameProjection, mCamera->getView());

		for (auto wavepoint : mWavePoints)
			wavepoint->render(mGameProjection,mCamera->getView());


		for (auto enemy : enemies)
			enemy->render(mGameProjection, mCamera->getView());

		for (auto explosion : mExplosions)
			explosion->render(mGameProjection,mCamera->getView());

		for (auto wave : mWaves)
			wave->render(mGameProjection, mCamera->getView());


		if(mCurrentState == game_states::game_over)
			mSpriteRenderer->draw_image(mGameProjection,mCamera->getView(),mGameOverTexture,
				mGameOverPosition,mGameOverTexture->get_size(),0.0f
				);

# pragma region GUI


#pragma endregion

		offsets.clear();
		scalers.clear();
		colors.clear();
	


}