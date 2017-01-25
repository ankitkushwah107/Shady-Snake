//Declaration headers
#include"shader.h"


//C++ headers
#include<iostream>




namespace shady_engine
{


	shader::shader() {}


	shader::shader(
		const char* pVertexShader,
		const char* pFragShader
	)

	{
		//Creating and Compiling shaders

		//Vertex shader

		GLuint vsObj = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vsObj, 1, &pVertexShader, 0);
		glCompileShader(vsObj);

		//Fragment shader
		GLuint fsObj = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fsObj, 1, &pFragShader, 0);
		glCompileShader(fsObj);



		//Creating,Attaching and linking shaders with program

		mProgramID = glCreateProgram();
		glAttachShader(mProgramID, vsObj);
		glAttachShader(mProgramID, fsObj);
		glLinkProgram(mProgramID);

		try
		{
			check_for_errors_bro(std::string("vertex shader"), vsObj);
			check_for_errors_bro(std::string("fragment shader"), fsObj);
			check_for_errors_bro(std::string("program"), mProgramID);
		}
		catch (std::runtime_error& e)
		{

			glDeleteShader(vsObj);
			glDeleteShader(fsObj);
			glDeleteProgram(mProgramID);
			
			
			logger::getInstance()->log(pVertexShader);
			throw e;
		}

		//deleting both shaders objects because we no longer need them

		glDeleteShader(vsObj);
		glDeleteShader(fsObj);
	}


	shader::~shader() {}


	void shader::check_for_errors_bro(
		std::string &pType, 
		GLuint pID
	)
	{

		if (pType == "program")
		{

			GLint success;
			glGetProgramiv(pID, GL_LINK_STATUS, &success);
			
			if (!success)
			{
				
				GLchar errInfo[512];
				glGetProgramInfoLog(pID, 512, 0, errInfo);
				//writing error to log file

				throw std::runtime_error(

				"Error :: Failed to link shader program :: " + std::string(errInfo)

				);

			}

		}
		else
		{
			
			GLint success;
			glGetShaderiv(pID, GL_COMPILE_STATUS, &success);
			
			if (!success)
			{
			
				GLchar errInfo[512];
				glGetShaderInfoLog(pID, 512, 0, errInfo);

				throw std::runtime_error(

					"Error :: Failed to compile shader:: " + std::string(errInfo)

				);
		
			}
		
		}
	}


	void shader::create_shader(
		const char* pVertexShader,
		const char* pFragShader
	)

	{

		//Creating and Compiling shaders

		//Vertex shader

		GLuint vsObj = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vsObj, 1, &pVertexShader, 0);
		glCompileShader(vsObj);

		//Fragment shader
		GLuint fsObj = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fsObj, 1, &pFragShader, 0);
		glCompileShader(fsObj);



		//Creating,Attaching and linking shaders with program

		mProgramID = glCreateProgram();
		glAttachShader(mProgramID, vsObj);
		glAttachShader(mProgramID, fsObj);
		glLinkProgram(mProgramID);
	
		try
		{
			check_for_errors_bro(std::string("vertex shader"), vsObj);
			check_for_errors_bro(std::string("fragment shader"), fsObj);
			check_for_errors_bro(std::string("program"), mProgramID);
		}
		catch (std::runtime_error& e)
		{
			glDeleteShader(vsObj);
			glDeleteShader(fsObj);
			glDeleteProgram(mProgramID);


			throw e;
		}

		//deleting both shaders objects because we no longer need them

		glDeleteShader(vsObj);
		glDeleteShader(fsObj);
	}


	void shader::use()
	{
		glUseProgram(mProgramID);
	}


	void shader::set1i(
		const std::string& pName, 
		GLint pValue
	)
	{
		glUniform1i(glGetUniformLocation(mProgramID, pName.c_str()), pValue);
	}


	void shader::set1f(
		const std::string& pName, 
		GLfloat pValue
	)
	{
		glUniform1f(glGetUniformLocation(mProgramID, pName.c_str()), pValue);
	}


	void shader::set2fv(
		const std::string& pName, 
		const glm::vec2& pVector
	)
	{
		glUniform2f(glGetUniformLocation(mProgramID, pName.c_str()), pVector.x, pVector.y);
	}


	void shader::set3fv(
		const std::string& pName, 
		const glm::vec3& pVector
	)
	{
		glUniform3f(glGetUniformLocation(mProgramID, pName.c_str()), pVector.x, pVector.y, pVector.z);
	}


	void shader::set4fv(
		const std::string& pName, 
		const glm::vec4& pVector
	)
	{
		glUniform4f(glGetUniformLocation(mProgramID, pName.c_str()), 
			pVector.x, pVector.y, pVector.z, pVector.w);
	}


	void shader::setMat4(
		const std::string& pName, 
		const glm::mat4& pMat
	)
	{
		glUniformMatrix4fv(glGetUniformLocation(mProgramID, pName.c_str()),
			1, GL_FALSE, glm::value_ptr(pMat));
	}


}