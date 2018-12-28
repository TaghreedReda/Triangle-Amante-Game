#ifndef Renderer_h__
#define Renderer_h__

#include <gl/glew.h>
#include <gl/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Renderer.h"
#include <iostream>
#include <cstdio>
#include <ctime>

#include "Shaders/shader.hpp"
#include "Texture/texture.h"
#include "Model/Model.h"
#include "FPCamera/FPCamera.h"
#include "EulerCamera/EulerCamera.h"
//#include "Application Manager/ApplicationManager.h"
using namespace std;
using namespace glm;

class Renderer
{
	enum RenderingMode
	{
		NO_TEXTURE,
		TEXTURE_ONLY,
		BLEND
	};

    GLuint programID;
	GLuint mRenderingModeID;
	RenderingMode mRenderingMode;
	// Transformation
	GLuint MatrixID;
	
	// unique_ptr<FPCamera> myCamera;
	unique_ptr<EulerCamera> myCamera;

	//skybox
	unique_ptr<Model> skybox;
	unique_ptr<Texture> skyboxTexture;
	mat4 skyboxFM;
	mat4 skyboxBM;
	mat4 skyboxRM;
	mat4 skyboxLM;
	mat4 skyboxTM;
	mat4 skyboxBTM;


	//hero object
	//hero texture for each face
	//hero modle for each face
	unique_ptr<Model> hero;
	unique_ptr<Texture> heroFrontTexture;
	unique_ptr<Texture> heroBackTexture;
	unique_ptr<Texture> heroTopTexture;
	unique_ptr<Texture> heroLeftTexture;
	unique_ptr<Texture> heroRightTexture;
	unique_ptr<Texture> heroBottomTexture;
	mat4 heroFM;
	
	
	mat4 herofrontMVP, heroMVPBack, heroMVPRight, heroMVPLeft;
	bool heroF = true, heroB = false, heroR = false, heroL = false;


	// moster
	unique_ptr<Model> monster;
	unique_ptr<Texture> monsterFrontTexture;
	unique_ptr<Texture> monsterBackTexture;
	unique_ptr<Texture> monsterTopTexture;
	unique_ptr<Texture> monsterLeftTexture;
	unique_ptr<Texture> monsterRightTexture;
	mat4 monsterFM;
	mat4 monsterBM;
	mat4 monsterRM;
	mat4 monsterLM;
	mat4 monsterTM;
	mat4 monsterBTM;

	//wall
	unique_ptr<Model> wall;
	unique_ptr<Texture> wallTexture;
	mat4 wallFM;
	mat4 wallBM;
	mat4 wallRM;
	mat4 wallLM;
	mat4 wallTM;
	mat4 wallBTM;

	mat4 monsterMVPFront;
	bool onRight = false, onleft = false, above = false, below = false;

	bool monsF = true, monsB = false, monsR = false, monsL = false;

	bool timestart;
	bool cal_time = false ;
	//floor
	::unique_ptr<Model> floor;
	unique_ptr<Texture> floortex;
	mat4 floorM;

	// Triangle
	unique_ptr<Model> myTriangle;
	mat4 triangle1M;
	mat4 triangle2M;
	mat4 triangle3M;
	mat4 triangle4M;
	mat4 triangle5M;
	mat4 triangle6M;
	mat4 triangle7M;
	mat4 triangle8M;
	mat4 triangle9M;
	mat4 triangle10M;

	mat4 triangle6MVP;

	::unique_ptr<Texture> mTexture1;
	::unique_ptr<Texture> mTexture2;

	std::clock_t start;
	double duration;
	bool draw1 = false;

public:
    Renderer();
    ~Renderer();
	bool done;
    
	void Initialize();
    void Draw();
	void HandleKeyboardInput(int key);
	void HandleMouse(double deltaX,double deltaY);
	void Update();
    void Cleanup();
};

#endif // Renderer_h__