#include"particles_renderer.h"


//Third Party headers
#include<glm/gtc/matrix_transform.hpp>


//shady_engine headers
#include"shader.h"
#include"texture2D.h"
#include"resources.h"
#include<iostream>



namespace shady_engine
{


	particles_renderer::particles_renderer() {
		
		init();
	
	
	}

	particles_renderer::~particles_renderer()
	{
		glDeleteBuffers(1, &this->VBO);
		glDeleteVertexArrays(1, &this->VAO);
	}


	void particles_renderer::init()
	{

		mShader = resources::getInstance()->load_shader("shader for particles",
			"shadyengine/shaders/particles_renderer_vs.glsl",
			"shadyengine/shaders/particles_renderer_fs.glsl"
		);

		float vertexAttrs[] =
		{
			0.0f,1.0f, 0.0f,0.0f,
			1.0f,1.0f, 1.0f,0.0f,
			0.0f,0.0f, 0.0f,1.0f,
			1.0f,0.0f, 1.0f,1.0f
		};


		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);

		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexAttrs), vertexAttrs, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (GLvoid*)(sizeof(float) * 2));


		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

	}



	void particles_renderer::render(
		const glm::mat4& pProjection,
		const glm::mat4& pView,
		int num,
		const std::vector<glm::vec4>& colors,
		const std::vector<glm::vec2>& translations,
		const std::vector<glm::vec2>& scalers
	)
	{


		glGenBuffers(1, &this->VBOcolors);
		glGenBuffers(1, &this->VBOoffsets);
		glGenBuffers(1,&this->VBOscalers);


		glBindVertexArray(this->VAO);

		//COLORS
		glBindBuffer(GL_ARRAY_BUFFER, this->VBOcolors);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*colors.size(), colors.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexAttribDivisor(2, 1);

		//OFFSETS
		glBindBuffer(GL_ARRAY_BUFFER, this->VBOoffsets);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*translations.size(), translations.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexAttribDivisor(3, 1);

		//SCALERS
		glBindBuffer(GL_ARRAY_BUFFER, this->VBOscalers);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*scalers.size(),scalers.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexAttribDivisor(4, 1);

		glBindVertexArray(0);

		glBindVertexArray(VAO);
		mShader->use();
		mShader->setMat4("projection",pProjection);
		mShader->setMat4("view",pView);
		mShader->set1i("use_color",1);
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, num);
	
		glBindVertexArray(0);

		glDeleteBuffers(1, &this->VBOoffsets);
		glDeleteBuffers(1,&this->VBOcolors);
	glDeleteBuffers(1,&this->VBOscalers);

	}



}//End of namespace