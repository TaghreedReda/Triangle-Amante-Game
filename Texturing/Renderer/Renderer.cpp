#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <math.h> 
#include <cstdio>
#include <ctime>

Renderer::Renderer()
{
	
}

Renderer::~Renderer()
{
    Cleanup();
}

void Renderer::Initialize()
{
	done = false;
	myCamera = unique_ptr<EulerCamera>(new EulerCamera());
	

	// skybox
	skybox = unique_ptr<Model>(new Model());
	skybox->VertexData.push_back(vec3(-1.0f, -1.0f, -2.0f));
	skybox->VertexData.push_back(vec3(1.0f, -1.0f, -2.0f));
	skybox->VertexData.push_back(vec3(1.0f, 1.0f, -2.0f));
	skybox->VertexData.push_back(vec3(-1.0f, 1.0f, -2.0f));

	skybox->ColorData.push_back(vec4(1.0f, 0.0f, 0.0f, 0.0f));
	skybox->ColorData.push_back(vec4(1.0f, 0.0f, 0.0f, 0.0f));
	skybox->ColorData.push_back(vec4(1.0f, 0.0f, 0.0f, 0.0f));

	skybox->UVData.push_back(vec2(0.0f, 0.0f));
	skybox->UVData.push_back(vec2(1.0f, 0.0f));
	skybox->UVData.push_back(vec2(1.0f, 1.0f));
	skybox->UVData.push_back(vec2(0.0f, 1.0f));

	skybox->IndicesData.push_back(0);
	skybox->IndicesData.push_back(1);
	skybox->IndicesData.push_back(3);

	skybox->IndicesData.push_back(1);
	skybox->IndicesData.push_back(2);
	skybox->IndicesData.push_back(3);
	skybox->Initialize();


	//monster
	monster = unique_ptr<Model>(new Model());
	monster->VertexData.push_back(vec3(-1.0f, -1.0f, -2.0f));
	monster->VertexData.push_back(vec3(1.0f, -1.0f, -2.0f));
	monster->VertexData.push_back(vec3(1.0f, 1.0f, -2.0f));
	monster->VertexData.push_back(vec3(-1.0f, 1.0f, -2.0f));
	
	monster->ColorData.push_back(vec4(1.0f, 0.0f, 0.0f, 0.0f));
	monster->ColorData.push_back(vec4(1.0f, 0.0f, 0.0f, 0.0f));
	monster->ColorData.push_back(vec4(1.0f, 0.0f, 0.0f, 0.0f));
	
	monster->UVData.push_back(vec2(0.0f, 0.0f));
	monster->UVData.push_back(vec2(1.0f, 0.0f));
	monster->UVData.push_back(vec2(1.0f, 1.0f));
	monster->UVData.push_back(vec2(0.0f, 1.0f));
	
	monster->IndicesData.push_back(0);
	monster->IndicesData.push_back(1);
	monster->IndicesData.push_back(3);
	
	monster->IndicesData.push_back(1);
	monster->IndicesData.push_back(2);
	monster->IndicesData.push_back(3);
	
	monster->Initialize();

	//wall
	wall = unique_ptr<Model>(new Model());
	wall->VertexData.push_back(vec3(-1.0f, -1.0f, -2.0f));
	wall->VertexData.push_back(vec3(1.0f, -1.0f, -2.0f));
	wall->VertexData.push_back(vec3(1.0f, 1.0f, -2.0f));
	wall->VertexData.push_back(vec3(-1.0f, 1.0f, -2.0f));

	wall->ColorData.push_back(vec4(1.0f, 0.0f, 0.0f, 0.0f));
	wall->ColorData.push_back(vec4(1.0f, 0.0f, 0.0f, 0.0f));
	wall->ColorData.push_back(vec4(1.0f, 0.0f, 0.0f, 0.0f));

	wall->UVData.push_back(vec2(0.0f, 0.0f));
	wall->UVData.push_back(vec2(1.0f, 0.0f));
	wall->UVData.push_back(vec2(1.0f, 1.0f));
	wall->UVData.push_back(vec2(0.0f, 1.0f));

	wall->IndicesData.push_back(0);
	wall->IndicesData.push_back(1);
	wall->IndicesData.push_back(3);
	
	wall->IndicesData.push_back(1);
	wall->IndicesData.push_back(2);
	wall->IndicesData.push_back(3);


	//hero
	hero = unique_ptr<Model>(new Model());
	hero->VertexData.push_back(vec3(-1.0f, -1.0f, -2.0f));
	hero->VertexData.push_back(vec3( 1.0f, -1.0f, -2.0f));
	hero->VertexData.push_back(vec3( 1.0f,  1.0f, -2.0f));
	hero->VertexData.push_back(vec3(-1.0f,  1.0f, -2.0f));

	hero->ColorData.push_back(vec4(1.0f, 0.0f, 0.0f,0.0f));
	hero->ColorData.push_back(vec4(1.0f, 0.0f, 0.0f,0.0f));
	hero->ColorData.push_back(vec4(1.0f, 0.0f, 0.0f,0.0f));

	hero->UVData.push_back(vec2(0.0f, 0.0f));
	hero->UVData.push_back(vec2(1.0f, 0.0f));
	hero->UVData.push_back(vec2(1.0f, 1.0f));
	hero->UVData.push_back(vec2(0.0f, 1.0f));

	hero->IndicesData.push_back(0);
	hero->IndicesData.push_back(1);
	hero->IndicesData.push_back(3);

	hero->IndicesData.push_back(1);
	hero->IndicesData.push_back(2);
	hero->IndicesData.push_back(3);

	hero->wentin1  = false;
	hero->wentin2  = false;
	hero->wentin3  = false;
	hero->wentin4  = false;
	hero->wentin5  = false;
	hero->wentin6  = false;
	hero->wentin7  = false;
	hero->wentin8  = false;
	hero->wentin9  = false;
	hero->wentin10 = false;
	hero->Score = 0;
	hero->MxPosition = 0;
	hero->MzPosition = 0;

	
	hero->Initialize();


	myTriangle = unique_ptr<Model>(new Model());
	myTriangle->VertexData.push_back(vec3(-1.0f, -1.0f, 0.0f));
	myTriangle->VertexData.push_back(vec3(1.0f, -1.0f, 0.0f));
	myTriangle->VertexData.push_back(vec3( 0.0f,  1.0f, 0.0f));

	myTriangle->ColorData.push_back(vec4(1.0f, 0.0f, 0.0f,0.0f));
	myTriangle->ColorData.push_back(vec4(0.0f, 1.0f, 0.0f,0.0f));
	myTriangle->ColorData.push_back(vec4(0.0f, 0.0f, 1.0f,0.0f));

	myTriangle->Initialize();


	//drawing a square.
	floor = unique_ptr<Model>(new Model());
	floor->VertexData.push_back(vec3(-1.0f, -1.0f, 0.0f));
	floor->VertexData.push_back(vec3( 1.0f, -1.0f, 0.0f));
	floor->VertexData.push_back(vec3( 1.0f,  1.0f, 0.0f));
	floor->VertexData.push_back(vec3(-1.0f,  1.0f, 0.0f));
	
	floor->ColorData.push_back(vec4(1.0f, 1.0f, 1.0f,1.0f));
	floor->ColorData.push_back(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	floor->ColorData.push_back(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	floor->ColorData.push_back(vec4(1.0f, 1.0f, 1.0f, 1.0f));

	floor->UVData.push_back(vec2(0.0f, 0.0f));
	floor->UVData.push_back(vec2(1.0f, 0.0f));
	floor->UVData.push_back(vec2(1.0f, 1.0f));
	floor->UVData.push_back(vec2(0.0f, 1.0f));

	floor->IndicesData.push_back(0);
	floor->IndicesData.push_back(1);
	floor->IndicesData.push_back(3);

	floor->IndicesData.push_back(1);
	floor->IndicesData.push_back(2);
	floor->IndicesData.push_back(3);
	floor->Initialize();



	//////////////////////////////////////////////////////////////////////////
	//////////////////// loading and initalizing textures ////////////////////
	//////////////////////////////////////////////////////////////////////////
	skyboxTexture = unique_ptr<Texture>(new Texture("bricks.jpg", 2));

	monsterFrontTexture = unique_ptr<Texture>(new Texture("front.png", 4));
	monsterBackTexture = unique_ptr<Texture>(new Texture("foxback.png", 5));
	monsterTopTexture = unique_ptr<Texture>(new Texture("top.png", 6));
	monsterLeftTexture = unique_ptr<Texture>(new Texture("left.png", 7));
	monsterRightTexture = unique_ptr<Texture>(new Texture("right.png", 8));
	
	
	heroFrontTexture  = unique_ptr<Texture>(new Texture("dudeface.png", 4));
	heroBackTexture   = unique_ptr<Texture>(new Texture("dudeback.png", 5));
	heroTopTexture    = unique_ptr<Texture>(new Texture("top.png", 6));
	heroLeftTexture   = unique_ptr<Texture>(new Texture("dudeforward.png", 7));
	heroRightTexture  = unique_ptr<Texture>(new Texture("dudebackward.png", 8));
	heroBottomTexture = unique_ptr<Texture>(new Texture("bottom.png", 9));
	floortex = unique_ptr<Texture>(new Texture("wooden.jpg", 2));

	
	//wall texture
	wallTexture = unique_ptr<Texture>(new Texture("wall.jpg", 4));


	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "SimpleTransformWithColor.vertexshader", "MultiColor.fragmentshader" );
	
	//////////////////////////////////////////////////////////////////////////
	mRenderingModeID = glGetUniformLocation(programID,"RenderingMode");
	//////////////////////////////////////////////////////////////////////////

	
	//////////////////////////////////// Transformations ////////////////////////////////////////
	// Get a handle for our "MVP" uniform the holder we created in the vertex shader)
	// GLint glGetUniformLocation(GLuint program​, const GLchar *name​);
	// program:  Specifies the program objec(t to be queried.
	// name: Points to a null terminated string containing the name of the uniform variable whose location is to be queried. 
	MatrixID = glGetUniformLocation(programID, "MVP");
	
	//////////////////////////////////////////////////////////////////////////

	// Projection matrix : 
	myCamera->SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,100.0f);

	// View matrix : 
	myCamera->Reset(
		0.0f, 0.5f, 4.0f,
		0.0f, 0.5f, 0.0f,
		0.0f, 1.0f, 0.0f
	);

	
	triangle1M  = translate(-1.0f, -0.05f, 1.0f)  * rotate(-30.0f, vec3(0,1,0)) * scale(0.1f, 0.1f, 0.1f);
	triangle2M  = translate(-1.0f, -0.05f,-0.75f) * rotate(30.0f, vec3(0,1,0)) * scale(0.1f, 0.1f, 0.1f);
	triangle3M  = translate(+1.0f, -0.00f, 1.0f)  * rotate(-30.0f, vec3(0,1,0)) * scale(0.1f, 0.1f, 0.1f);
	triangle4M  = translate(+1.0f, -0.05f,-0.75f) * rotate(30.0f, vec3(0,1,0)) * scale(0.1f, 0.1f, 0.1f);
	triangle5M  = translate(+1.0f, -0.05f, -0.75f)* rotate(30.0f, vec3(0, 1, 0)) * scale(0.1f, 0.1f, 0.1f);
	triangle6M  = translate( 0.5f, -0.05f, 0.0f)  * rotate(-30.0f, vec3(0, 1, 0)) * scale(0.1f, 0.1f, 0.1f);
	triangle7M  = translate(-0.5f, -0.05f, -0.5f) * rotate(30.0f, vec3(0, 1, 0)) * scale(0.1f, 0.1f, 0.1f);
	triangle8M  = translate(-1.0f, -0.00f, 1.0f)  * rotate(-30.0f, vec3(0, 1, 0)) * scale(0.1f, 0.1f, 0.1f);
	triangle9M  = translate(+1.0f, -0.05f, -0.75f) * rotate(30.0f, vec3(0, 1, 0)) * scale(0.1f, 0.1f, 0.1f);
	triangle10M = translate(+0.5f, -0.05f, +0.75f)* rotate(30.0f, vec3(0, 1, 0)) * scale(0.1f, 0.1f, 0.1f);
		
		
		

	//skybox
	skyboxBM = translate(0.0f, 0.0f, -6.0f) * rotate(0.0f, vec3(1, 0, 0)) * scale(6.0f, 6.0f,0.0f);
	skyboxFM = translate(0.0f, 0.0f, 6.0f) * rotate(0.0f, vec3(1, 0, 0)) * scale(6.0f, 6.0f, 0.0f);
	skyboxRM = translate(6.0f, 0.0f, 0.0f) * rotate(90.0f, vec3(0, 1, 0)) * scale(6.0f, 6.0f, 0.0f);
	skyboxLM = translate(-6.0f, 0.0f, 0.0f) * rotate(90.0f, vec3(0, 1, 0)) * scale(6.0f, 6.0f, 0.0f);
	skyboxTM = translate(0.0f, 6.0f, 0.0f) * rotate(90.0f, vec3(1, 0, 0)) * scale(6.0f, 6.0f, 0.0f);
	skyboxBTM = translate(0.0f, -6.0f, 0.0f) * rotate(90.0f, vec3(1, 0, 0)) * scale(6.0f, 6.0f, 0.0f);

	//heroFM = translate(0.0f, 0.15f, 0.0f) * rotate(0.0f, vec3(0, 1, 0)) * scale(0.25f, 0.25f, 0.25f);
	heroFM = translate(0.0f, 0.0f, 0.0f) * rotate(0.0f, vec3(0, 1, 0)) * scale(0.1f, 0.1f, 0.1f);

	//monster
	monsterFM  = translate(-0.5f, 0.0f, 0.0f) * rotate(0.0f, vec3(0, 1, 0)) * scale(0.1f, 0.1f, 0.1f);
	monsterBM  = translate(-0.5f, 0.0f, -0.2f) * rotate(0.0f, vec3(0, 1, 0)) * scale(0.1f, 0.1f, 0.1f);
	monsterRM  = translate(-0.4f, 0.0f, -0.1f)* rotate(90.0f, vec3(0, 1, 0)) * scale(0.1f, 0.1f, 0.1f);
	monsterLM  = translate(-0.6f, 0.0f, -0.1f)* rotate(-90.0f, vec3(0, 1, 0)) * scale(0.1f, 0.1f, 0.1f);
	monsterTM  = translate(0.0f, 0.1f, -0.1f)* rotate(90.0f, vec3(1, 0, 0)) * scale(0.1f, 0.1f, 0.1f);
	monsterBTM = translate(0.0f, -0.1f, -0.1f)*  rotate(90.0f, vec3(1, 0, 0)) * scale(0.1f, 0.1f, 0.1f);

	//wall transformation
	wallRM = translate(-1.5f, 0.0f, 0.0f)  * rotate(90.0f, vec3(0, 1, 0)) * scale(1.0f, 0.15f, 1.0f);
	wallBM = translate(-1.55f, 0.0f, -1.0f) * rotate(0.0f, vec3(0, 1, 0)) * scale(0.05f, 0.15f, 1.0f);
	wallFM = translate(-1.55f, 0.0f, +1.0f) * rotate(0.0f, vec3(0, 1, 0)) * scale(0.05f, 0.15f, 1.0f);
	wallLM = translate(-1.6f, 0.0f,  0.0f) * rotate(90.0f, vec3(0, 1, 0)) * scale(1.0f, 0.15f, 1.0f);
	wallTM = translate(-1.55f, 0.15f, 0.0f) * rotate(90.0f, vec3(1, 0, 0)) * scale(0.05f, 1.0f, 1.0f);
	
	
	floorM = translate(0.0f, -0.1f, -0.0f)* scale(3.0f,3.0f,3.0f)*rotate(90.0f,vec3(1.0f,0.0f,0.0f));
	
	cal_time = false;
	timestart= false;
	duration = 0;
    
}

void Renderer::Draw()
{		
		// Use our shadersh
		glUseProgram(programID);

		//send the rendering mode to the shader.
		mRenderingMode = RenderingMode::TEXTURE_ONLY;
		glUniform1i(mRenderingModeID,mRenderingMode);

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		mat4 VP = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix();
		
		if (heroF && !heroB && !heroR && !heroL) 
		{
			//front side of the hero
			heroFrontTexture->Bind();
		}

		if (!heroF && heroB && !heroR && !heroL) 
		{
			//back side of the hero
			heroBackTexture->Bind();
		}

		if (!heroF && !heroB && heroR && !heroL) 
		{
			//right side of the hero
			heroRightTexture->Bind();
		}

		if (!heroF && !heroB && !heroR && heroL) 
		{
			//left side of the hero
			heroLeftTexture->Bind();
		}

		//Hero
		herofrontMVP = VP * heroFM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &herofrontMVP[0][0]);
		hero->Draw();

		//the floor
		floortex->Bind();
		mat4 floorMVP = VP * floorM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &floorMVP[0][0]);
		floor->Draw();
	

		//right
		wallTexture->Bind();
		mat4 wallRmvp = VP * wallRM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &wallRmvp[0][0]);
		wall->Draw();
		
		//back
		wallTexture->Bind();
		mat4 wallBmvp = VP * wallBM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &wallBmvp[0][0]);
		wall->Draw();

		//wallFM
		wallTexture->Bind();
		mat4 wallfmvp = VP * wallFM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &wallfmvp[0][0]);
		wall->Draw();
		
		wallTexture->Bind();
		mat4 walllmvp = VP * wallLM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &walllmvp[0][0]);
		wall->Draw();

		//wallTM
		wallTexture->Bind();
		mat4 walltmvp = VP * wallTM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &walltmvp[0][0]);
		wall->Draw();


		
//Skybox
#pragma region Skybox
		
		skyboxTexture->Bind();
		
		mat4 skyMVPback = VP * skyboxBM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &skyMVPback[0][0]);
		skybox->Draw();

	
		mat4 skyMVPRight = VP * skyboxRM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &skyMVPRight[0][0]);
		skybox->Draw();

		
		mat4 skyMVPLeft = VP * skyboxLM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &skyMVPLeft[0][0]);
		skybox->Draw();

		
		mat4 skyMVPTop = VP * skyboxTM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &skyMVPTop[0][0]);
		skybox->Draw();

		
		mat4 skyMVPBottom = VP * skyboxBTM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &skyMVPBottom[0][0]);
		skybox->Draw();

		mat4 skyMVPfront = VP * skyboxFM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &skyMVPfront[0][0]);
		skybox->Draw();




#pragma endregion

#pragma region triangle
		//1st triangle
		mat4 triangle1MVP = VP * triangle1M;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &triangle1MVP[0][0]);
		myTriangle->Draw();

		//3rd triangle
		mat4 triangle3MVP = VP * triangle3M;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &triangle3MVP[0][0]);
		myTriangle->Draw();

		//4th triangle
		mat4 triangle4MVP = VP * triangle4M;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &triangle4MVP[0][0]);
		myTriangle->Draw();


		////5th triangle
		//if (duration > 15 )
		//{
		//	mat4 triangle5MVP = VP * triangle5M;
		//	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &triangle5MVP[0][0]);
		//	myTriangle->Draw();
		//}
		triangle6MVP = VP * triangle6M;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &triangle6MVP[0][0]);
		if (duration > 6)
		{
			
			myTriangle->Draw();
		}


		//if (duration > 20)
		//{
		//	mat4 triangle7MVP = VP * triangle7M;
		//	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &triangle7MVP[0][0]);
		//	myTriangle->Draw();
		//
		//
		//	mat4 triangle8MVP = VP * triangle8M;
		//	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &triangle8MVP[0][0]);
		//	myTriangle->Draw();
		//}
		//
		//if (duration > 25  || duration >40 )
		//{
		//	mat4 triangle9MVP = VP * triangle9M;
		//	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &triangle9MVP[0][0]);
		//	myTriangle->Draw();
		//
		//
		//	mat4 triangle10MVP = VP * triangle10M;
		//	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &triangle10MVP[0][0]);
		//	myTriangle->Draw();
		//}

#pragma endregion

		//monster
		if (monsF == true && monsB == false && monsR == false && monsL == false) {
			monsterFrontTexture->Bind();
		}
		else if (monsF == false && monsB == false && monsR == false && monsL == true) {
			monsterLeftTexture->Bind();
		}
		else if (monsF == false && monsB == false && monsR == true && monsL == false) {
			monsterRightTexture->Bind();
		}

		monsterMVPFront = VP * monsterFM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &monsterMVPFront[0][0]);
		monster->Draw();

		////////////////////// change the rendering mode to blend textures ////////////////////// ASK HERE
		mRenderingMode = RenderingMode::BLEND;
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glUniform1i(mRenderingModeID,mRenderingMode);


		mRenderingMode = RenderingMode::TEXTURE_ONLY;
		glUniform1i(mRenderingModeID,mRenderingMode);

		if (timestart)
		{

			start = std::clock();
			timestart = false;
			cal_time = true;
		}

		if (cal_time)
		{
			duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "Duration = " << duration << endl;
		}
}

void Renderer::Cleanup()
{
    glDeleteProgram(programID);
}

void Renderer::Update()
{	
	mat4 rotationMat = rotate((float)0.5,vec3(0.0,1.0,0.0));

	triangle1M = triangle1M * rotationMat;
	triangle3M = triangle3M * rotationMat;
	triangle4M = triangle4M * rotationMat;

	above = below = onRight = onleft = false;


	if (monsterMVPFront[3][0] > herofrontMVP[3][0])
	{
		onleft = true;
	}

	else  if (monsterMVPFront[3][0] < herofrontMVP[3][0])
	{
		onRight = true;
	}

	 if (monsterMVPFront[3][2] < herofrontMVP[3][2])
	{
		below = true;
	}

	else if (monsterMVPFront[3][2] > herofrontMVP[3][2])
	{
		above = true;
	}
	
	if ((ceil((monsterMVPFront[3][2] * 10)) / 10) == (ceil((herofrontMVP[3][2] * 10)) / 10) && (ceil((monsterMVPFront[3][0] * 10)) / 10) == (ceil((herofrontMVP[3][0] * 10)) / 10))
	{
		cout << "you are DEAD GAME OVER ";
		cout << "\n\n Final Score: " << hero->Score << "\n\n\n";
		done = true;
	}

	if (duration < 5)
	{
		//level 1
	}

	else if (duration < 10)
	{
		//level 2
		if (onleft)
		{
			monsterFM = monsterFM * translate(-0.01f, 0.0f, 0.0f);
			monsF = false, monsB = false, monsR = false, monsL =true;
		}

		if (onRight)
		{
			monsterFM = monsterFM * translate(0.01f, 0.0f, 0.0f);
			monsF = false, monsB = false, monsR =true, monsL = false;
		}

		if (below)
		{
			monsterFM = monsterFM * translate(0.00f, 0.0f, -0.01f);
		}
		if (above)
		{
			monsterFM = monsterFM * translate(0.0f, 0.0f, 0.01f);
			
			monsF = true, monsB = false, monsR = false, monsL = false;
		}

		
	}

	else if(true)
	{
		//level 3
		if (onleft)
		{
			monsterFM = monsterFM * translate(-0.02f, 0.0f, 0.0f);
			monsF = false, monsB = false, monsR = false, monsL = true;
		}

		if (onRight)
		{
			monsterFM = monsterFM * translate(0.02f, 0.0f, 0.0f);
			monsF = false, monsB = false, monsR = true, monsL = false;
		}

		if (below)
		{
			monsterFM = monsterFM * translate(0.00f, 0.0f, -0.02f);
		}

		if (above)
		{
			monsterFM = monsterFM * translate(0.0f, 0.0f, 0.02f);
			monsF = true, monsB = false, monsR = false, monsL = false;
		}
	}
}

void Renderer::HandleKeyboardInput(int key)
{
	if (hero->MxPosition >= 610 || hero->MxPosition <= -610 || hero->MzPosition >= 610 || hero->MzPosition <= -610)
	{
		heroFM = heroFM    	* translate(0.0f, -2.0f, 0.0f);
		printf("you are out GAME OVER %d %d \n", hero->MxPosition, hero->MzPosition);
		printf("\n Final Score %d \n\n\n", hero->Score);
		done = true;
	}
	

	if ((triangle6MVP[3][2] - herofrontMVP[3][2] < 0.01) && (triangle6MVP[3][2] - herofrontMVP[3][2] > -0.01) && (triangle6MVP[3][0] - herofrontMVP[3][0] < 0.01) && (triangle6MVP[3][0] - herofrontMVP[3][0] > -0.01))
	{
		triangle6M = triangle6M * glm::translate(10.0f, 10.0f, 0.0f);
		printf("triangle6M \n ");
		if (!hero->wentin6)
		{
			hero->wentin6 = true;
			hero->Score++;
			printf("\n\n CURRENT SCORE %d \n\n\n", hero->Score);
			PlaySound(TEXT("recycle.wav"), NULL, SND_FILENAME | SND_ASYNC);
			

		}
	}

	if (hero->MxPosition <= -190 && hero->MxPosition >= -220 && hero->MzPosition <= -240 && hero->MzPosition >= -255)
	{
		triangle1M = triangle1M * glm::translate(10.0f, 0.0f, 0.0f);
		//printf("Current location %d %d \n", hero->MxPosition, hero->MzPosition);
		if (!hero->wentin1)
		{
			hero->wentin1 = true;
			hero->Score++;
			printf("CURRENT SCORE %d \n\n\n", hero->Score);
			
			PlaySound(TEXT("recycle.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
	}

	if (hero->MzPosition <= -210 && hero->MzPosition >= -240 && hero->MxPosition >= 190 && hero->MxPosition <= 220)
	{
		triangle3M = triangle3M * glm::translate(10.0f, 0.0f, 0.0f);
		if (!hero->wentin3)
		{
			hero->wentin3 = true;
			hero->Score++;
			printf("CURRENT SCORE %d \n\n\n", hero->Score);
			PlaySound(TEXT("recycle.wav"), NULL, SND_FILENAME | SND_ASYNC);

		}
	}

	if (hero->MzPosition <=115  && hero->MzPosition >= 90 && hero->MxPosition >= 190 && hero->MxPosition <= 220)
	{
		triangle4M = triangle4M * glm::translate(10.0f, 0.0f, 0.0f);
		if (!hero->wentin4)
		{
			hero->wentin4 = true;
			hero->Score++;
			printf("CURRENT SCORE %d \n\n\n", hero->Score);
			PlaySound(TEXT("recycle.wav"), NULL, SND_FILENAME | SND_ASYNC);

		}
	}

	//printf("Renderer::KEY = %d \n",key);
	switch (key) 
	{

	case GLFW_KEY_ENTER:
	 {
		timestart = true;

		 break;
	 }
	case GLFW_KEY_UP:
		heroF = false, heroB = true, heroR = false, heroL = false;
		if (hero->MxPosition <= -279 && hero->MxPosition >= -344 && hero->MzPosition == -249)
		{
			break;
		}
		heroFM = heroFM * translate( 0.00f, 0.00f,-0.05f);

		hero->MzPosition++;

		myCamera->Walk(0.005f);
		break;


	case GLFW_KEY_DOWN:
		heroF = true, heroB = false, heroR = false, heroL = false;
		if (hero->MxPosition <= -279 && hero->MxPosition >= -344 && hero->MzPosition == 181)
		{
			break;
		}
		heroFM = heroFM * translate(0.00f, 0.00f, 0.05f);
	
		myCamera->Walk(-0.005f);

		//printf("keepPLaying: %d %d \n", hero->MxPosition, hero->MzPosition);
		hero->MzPosition--;
		break;


	case GLFW_KEY_LEFT:
		heroF = false, heroB = false, heroR = false, heroL = true;
		if (hero->MxPosition == -279 && hero->MzPosition <= 181 && hero->MzPosition >= -249)
		{
			break;
		}
		heroFM = heroFM * translate(-0.050f, 0.00f, 0.00f); 

		myCamera->Strafe(-0.005f);

		hero->MxPosition--;
		break;


	case GLFW_KEY_RIGHT:
		heroF = false, heroB = false, heroR = true, heroL = false;
		if (hero->MxPosition == -344 && hero->MzPosition <= 181 && hero->MzPosition >= -249)
		{
			break;
		}
		heroFM = heroFM * translate(0.050f, 0.00f, 0.00f); 

		myCamera->Strafe(0.005f);
		hero->MxPosition++;
		break;
	
	case GLFW_KEY_W:
		
		myCamera->Walk(0.5);
		break;
		//Moving backword
	case GLFW_KEY_S:
		myCamera->Walk(-0.5);
		break;
		// Moving right
	case GLFW_KEY_D:
		myCamera->Strafe(0.1);
		break;

		// Moving left
	case GLFW_KEY_A:
		myCamera->Strafe(-0.1);
		break;

		// Moving up
	case GLFW_KEY_SPACE:
	case GLFW_KEY_R:
		myCamera->Fly(0.1);
		break;

		// Moving down
	case GLFW_KEY_LEFT_CONTROL:
	case GLFW_KEY_F:
		myCamera->Fly(-0.1);
		break;

	default:
		break;
	}


	myCamera->UpdateViewMatrix();
}

void Renderer::HandleMouse(double deltaX,double deltaY)
{
	//printf("Renderer::MOUSE = %f , %f \n",deltaX,deltaY);
	
	myCamera->Yaw(deltaX);
	myCamera->Pitch(deltaY);
	myCamera->UpdateViewMatrix();

}