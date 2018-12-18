#ifndef Renderer_h__
#define Renderer_h__

#include <gl/glew.h>
#include <gl/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include <iostream>

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
    
	// Transformation
	GLuint MatrixID;
	
	unique_ptr<Model> myTriangle;

	//unique_ptr<FPCamera> myCamera;
	unique_ptr<EulerCamera> myCamera;

	//collectables
	unique_ptr<Model> collectables;
	unique_ptr<Texture> collectablesTexture;
	mat4 collectablesFM;
	mat4 collectablesBM;
	mat4 collectablesRM;
	mat4 collectablesLM;
	mat4 collectablesTM;


	//hero object
	unique_ptr<Model> hero;
	//hero texture for each face
	unique_ptr<Texture> heroFrontTexture;
	unique_ptr<Texture> heroBackTexture;
	unique_ptr<Texture> heroTopTexture;
	unique_ptr<Texture> heroLeftTexture;
	unique_ptr<Texture> heroRightTexture;
	unique_ptr<Texture> heroBottomTexture;
	//hero modle for each face
	mat4 heroFM;
	mat4 heroBM;
	mat4 heroRM;
	mat4 heroLM;
	mat4 heroTM;
	mat4 heroBtM;

	mat4 herofrontMVP, heroMVPBack, heroMVPRight, heroMVPLeft;
	bool heroF = true, heroB = false, heroR = false, heroL = false;
	
	//floor
	::unique_ptr<Model> floor;
	mat4 floorM;
	unique_ptr<Texture>floortex;

	mat4 upM;
	unique_ptr<Texture>uptex;


	mat4 backgroundM;
	unique_ptr<Texture>bkgtex;

	GLuint mRenderingModeID;
	RenderingMode mRenderingMode;

	mat4 triangle1M;
	mat4 triangle2M;
	mat4 triangle3M;
	mat4 triangle4M;

	::unique_ptr<Texture> mTexture1;
	::unique_ptr<Texture> mTexture2;

	mat4 skybox;


public:
    Renderer();
    ~Renderer();
	bool done;
    
	void Initialize();
    void Draw();
	void HandleKeyboardInput(int key);
	void HandleMouse(double deltaX,double deltaY);
	void Update(double deltaTime);
    void Cleanup();
};

#endif // Renderer_h__