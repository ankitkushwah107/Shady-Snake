//Declaration header
#include"resources.h"


//C++ headers
#include<sstream>
#include<fstream>

//Engine headers
#include"logger.h"



namespace shady_engine
{
	

	resources::resources()
	{

	}


	std::shared_ptr<shader> resources::load_shader(
		const std::string& pName,
		const std::string& pVSPath,
		const std::string& pFSPath
	)

	{
		std::ifstream vsFile;
		std::ifstream fsFile;

		vsFile.exceptions(std::ifstream::badbit);
		fsFile.exceptions(std::ifstream::badbit);

		try
		{
			vsFile.open(pVSPath.c_str());
			fsFile.open(pFSPath.c_str());
		}
		catch (std::ios::failure& f) 
		{
			throw std::runtime_error("failed to open shader file!");
		}

		std::stringstream vsSStream;
		std::stringstream fsSStream;

		vsSStream << vsFile.rdbuf();
		fsSStream << fsFile.rdbuf();

		std::string vsString = vsSStream.str();
		std::string fsString = fsSStream.str();

		const char* vertexShader = vsString.c_str();
		const char* fragmentShader = fsString.c_str();


		try {
			shaders[pName] = std::make_shared<shader>(vertexShader, fragmentShader);
		}
		catch (std::bad_alloc& e)
		{
			throw std::bad_alloc(e);
		}

		return shaders[pName];

	}


	std::shared_ptr<texture2D> resources::load_texture(
		const std::string& pName, 
		const std::string& pPath, 
		GLenum pFormat
	)
	{

		unsigned char *image = nullptr;
		GLint width = 0;
		GLint height = 0;

		if (pFormat == GL_RGB)
			image = SOIL_load_image(pPath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		else if (pFormat == GL_RGBA)
			image = SOIL_load_image(pPath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

		if (image == nullptr){
			throw std::runtime_error("failed to load image file!");
		}

		try {
			textures[pName] = std::make_shared<texture2D>(image,width,height,pFormat);
		}
		catch (std::bad_alloc& e) 
		{
			throw std::bad_alloc(e);
		}

		return textures[pName];
	}


	std::shared_ptr<shader> resources::use_shader(const std::string& pName)
	{
		shaders[pName]->use();
		return shaders[pName];
	}


}