//Declaration header
#include"sprite_renderer.h"
#include"resources.h"




namespace shady_engine
{


	sprite_renderer::sprite_renderer()
	{

		logger::getInstance()->log("sprite renderer");
		
		mShader = resources::getInstance()->load_shader(
			"unlit shader for sprite renderer",
			"shadyengine/shaders/sprite_renderer_vs.glsl",
			"shadyengine/shaders/sprite_renderer_fs.glsl"
			);

		mCircleShader = resources::getInstance()->load_shader(
			"circle shader",
			"shaders/circle_vs.glsl",
			"shaders/circle_fs.glsl"
		);

		float points[] =
		{
			0.0f,1.0f,
			1.0f,1.0f,
			0.0f,0.0f,
			1.0f,0.0f
		};

		glGenBuffers(1, &mVBO);

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);


		/*
		I am  going to need same amount of texture
		coords as points so allocating 2*sizeof(points) buffer
		so that you can store texture coordinates later.
		*/

		glBufferData(GL_ARRAY_BUFFER, sizeof(points) * 2, 0, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &mVAO);

		glBindVertexArray(mVAO);

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(points)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

	}



	void sprite_renderer::init()
	{

		mShader = resources::getInstance()->load_shader(
			"unlit shader for sprite renderer",
			"shadyengine/shaders/sprite_renderer_vs.glsl",
			"shadyengine/shaders/sprite_renderer_fs.glsl"
		);


		float points[] =
		{
			0.0f,1.0f,
			1.0f,1.0f,
			0.0f,0.0f,
			1.0f,0.0f
		};

		glGenBuffers(1, &mVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);


		/*
		I am  going to need same amount of texture
		coords as points so allocating 2*sizeof(points) buffer
		so that you can store texture coordinates later.
		*/

		glBufferData(GL_ARRAY_BUFFER,sizeof(points)*2, 0, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &mVAO);

		glBindVertexArray(mVAO);

		glBindBuffer(GL_ARRAY_BUFFER,mVBO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(points)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);


	}



	sprite_renderer::~sprite_renderer()
	{
		glDeleteVertexArrays(1, &mVAO);
		glDeleteBuffers(1, &mVBO);
	}



	void sprite_renderer::draw_quad(
		const glm::mat4& pProjection,
		const glm::mat4& pView,
		const glm::vec2& pPos,
		const glm::vec2& pSize,
		const glm::vec4& pColor,
		float pRotationInRadians
	)
	{

		glm::mat4 model = glm::mat4();

		model = glm::translate(model, glm::vec3(pPos, 0.0f));

		model = glm::translate(model, glm::vec3((0.5f*pSize), 0.0f));
		model = glm::rotate(model, pRotationInRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3((-0.5f*pSize), 0.0f));

		model = glm::scale(model, glm::vec3(pSize, 0.0f));


		float texCoords[] =
		{
			0.0f,1.0f,
			1.0f,1.0f,
			0.0f,0.0f,
			1.0f,0.0f
		};

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		/*
			The amount of texture coordinates size is same as vertices size
		*/

		glBufferSubData(GL_ARRAY_BUFFER, sizeof(texCoords), sizeof(texCoords), texCoords);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		mShader->use();

		mShader->setMat4("projection",pProjection);
		mShader->setMat4("view",pView);
		mShader->setMat4("model",model);

		mShader->set1i("use_color", 1);
		mShader->set4fv("color", pColor);

		glBindVertexArray(mVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

	}



	void sprite_renderer::draw_image(
		const glm::mat4& pProjection,
		const glm::mat4& pView,
		const std::shared_ptr<texture2D> pTexture,
		const glm::vec2& pPos,
		const glm::vec2& pSize,
		float pRotationInRadians
	)

	{
		glm::mat4 model = glm::mat4();

		model = glm::translate(model, glm::vec3(pPos, 0.0f));

		model = glm::translate(model,glm::vec3((0.5f*pSize),0.0f));
		model = glm::rotate(model,pRotationInRadians,glm::vec3(0.0f,0.0f,1.0f));
		model = glm::translate(model, glm::vec3((-0.5f*pSize), 0.0f));

		model = glm::scale(model, glm::vec3(pSize, 0.0f));


		float texCoords[] =
		{
			0.0f,0.0f,
			1.0f,0.0f,
			0.0f,1.0f,
			1.0f,1.0f
		};

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		/*
		The amount of texture coordinates pSize is same as vertices pSize
		*/

		glBufferSubData(GL_ARRAY_BUFFER, sizeof(texCoords), sizeof(texCoords), texCoords);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		mShader->use();
	

		mShader->setMat4("projection", pProjection);
		mShader->setMat4("view", pView);
		mShader->setMat4("model", model);

		mShader->set1i("use_color", 0);
		mShader->set1i("sampler0", 0);

		glActiveTexture(GL_TEXTURE0);
		pTexture->bind();

		glBindVertexArray(mVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

	}


	void sprite_renderer::draw_circle(
		const glm::mat4& pProjection,
		const glm::mat4& pView,
		const glm::vec2& pPosition,
		const glm::vec2& pSize,
		const glm::vec4& pColor
	)
	{

		glm::mat4 model = glm::mat4();

		model = glm::translate(model, glm::vec3(pPosition, 0.0f));
		model = glm::scale(model, glm::vec3(pSize, 0.0f));


		float texCoords[] =
		{
			0.0f,1.0f,
			1.0f,1.0f,
			0.0f,0.0f,
			1.0f,0.0f
		};

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		/*
		The amount of texture coordinates size is same as vertices size
		*/

		glBufferSubData(GL_ARRAY_BUFFER, sizeof(texCoords), sizeof(texCoords), texCoords);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		mCircleShader->use();

		mCircleShader->setMat4("projection", pProjection);
		mCircleShader->setMat4("view", pView);
		mCircleShader->setMat4("model", model);

		mCircleShader->set1i("usecolor", 1);
		mCircleShader->set4fv("color",pColor);

		glBindVertexArray(mVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

	}

	void sprite_renderer::draw_textured_circle(const glm::mat4 & pProjection, const glm::mat4 & pView, const glm::vec2 & pPosition, const glm::vec2 & pSize, std::shared_ptr<shady_engine::texture2D> pTexture)
	{
		glm::mat4 model = glm::mat4();

		model = glm::translate(model, glm::vec3(pPosition, 0.0f));
		model = glm::scale(model, glm::vec3(pSize, 0.0f));


		float texCoords[] =
		{
			0.0f,1.0f,
			1.0f,1.0f,
			0.0f,0.0f,
			1.0f,0.0f
		};

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		/*
		The amount of texture coordinates size is same as vertices size
		*/

		glBufferSubData(GL_ARRAY_BUFFER, sizeof(texCoords), sizeof(texCoords), texCoords);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		mCircleShader->use();

		mCircleShader->setMat4("projection", pProjection);
		mCircleShader->setMat4("view", pView);
		mCircleShader->setMat4("model", model);

		mCircleShader->set1i("usecolor",0);
		mCircleShader->set1i("sampler0",0);
		glActiveTexture(GL_TEXTURE0);
		pTexture->bind();

		glBindVertexArray(mVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}



	void sprite_renderer::draw_image_region(
		const glm::mat4& pProjection,
		const glm::mat4& pView,
		const std::shared_ptr<texture2D> pTexture,
		const glm::vec2& pSrcPos,
		const glm::vec2& pSrcDim,
		const glm::vec2& pPos,
		const glm::vec2& pSize
	)

	{

		glm::mat4 model = glm::mat4();
		model = glm::translate(model, glm::vec3(pPos, 0.0f));
		model = glm::scale(model, glm::vec3(pSize, 0.0f));

		//Mapping values from one range to other
		float dw = pSrcDim.x / pTexture->get_size().x;
		float dh = pSrcDim.y / pTexture->get_size().y;
		float dx = pSrcPos.x / pTexture->get_size().x;
		float dy = pSrcPos.y / pTexture->get_size().y;

		float texCoords[] =
		{
			dx,dy,
			dx + dw,dy,
			dx,dy + dh,
			dx + dw,dy + dh
		};


		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		/*
		The amount of texture coordinates size is same as vertices size
		*/

		glBufferSubData(GL_ARRAY_BUFFER, sizeof(texCoords), sizeof(texCoords), texCoords);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		mShader->use();

		mShader->setMat4("projection", pProjection);
		mShader->setMat4("view", pView);
		mShader->setMat4("model", model);

		mShader->set1i("sampler0", 0);
		mShader->set1i("use_color", 0);

		glActiveTexture(GL_TEXTURE0);
		pTexture->bind();

		glBindVertexArray(mVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

		glActiveTexture(GL_TEXTURE0);
		pTexture->unbind();


	}

	

}

