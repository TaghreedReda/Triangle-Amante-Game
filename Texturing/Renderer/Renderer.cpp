#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>

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
	//myCamera = unique_ptr<FPCamera>(new FPCamera());
	myCamera = unique_ptr<EulerCamera>(new EulerCamera());

	//collectables
	//
	//
	collectables = unique_ptr<Model>(new Model());

	collectables->VertexData.push_back(vec3(-1.0f, -1.0f, 0.0f));
	collectables->VertexData.push_back(vec3( 1.0f, -1.0f, 0.0f));
	collectables->VertexData.push_back(vec3( 1.0f,  1.0f, 0.0f));
	collectables->VertexData.push_back(vec3(-1.0f,  1.0f, 0.0f));
	
	//*
	collectables->ColorData.push_back(vec4(1.0f, 0.0f, 0.0f,1.0f));
	collectables->ColorData.push_back(vec4(1.0f, 0.0f, 0.0f,1.0f));
	collectables->ColorData.push_back(vec4(1.0f, 0.0f, 0.0f,1.0f));
	
	collectables->UVData.push_back(vec2(0.0f, 0.0f));
	collectables->UVData.push_back(vec2(1.0f, 0.0f));
	collectables->UVData.push_back(vec2(1.0f, 1.0f));
	collectables->UVData.push_back(vec2(0.0f, 1.0f));
	
	collectables->IndicesData.push_back(0);
	collectables->IndicesData.push_back(1);
	collectables->IndicesData.push_back(3);
	
	collectables->IndicesData.push_back(1);
	collectables->IndicesData.push_back(2);
	collectables->IndicesData.push_back(3);
	collectables->Initialize();



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
	hero->Initialize();


	myTriangle = unique_ptr<Model>(new Model());
	myTriangle->VertexData.push_back(vec3(-1.0f, -1.0f, 0.0f));
	myTriangle->VertexData.push_back(vec3(1.0f, -1.0f, 0.0f));
	myTriangle->VertexData.push_back(vec3( 0.0f,  1.0f, 0.0f));

	myTriangle->ColorData.push_back(vec4(1.0f, 0.0f, 0.0f,1.0f));
	myTriangle->ColorData.push_back(vec4(0.0f, 1.0f, 0.0f,1.0f));
	myTriangle->ColorData.push_back(vec4(0.0f, 0.0f, 1.0f,1.0f));

	myTriangle->UVData.push_back(vec2(+0.5f,+0.5f));
	myTriangle->UVData.push_back(vec2(2.0f,0.0f));
	myTriangle->UVData.push_back(vec2(0.0f,2.0f));
	myTriangle->Initialize();

	//drawing a square.
	floor = unique_ptr<Model>(new Model());

	floor->VertexData.push_back(vec3(-1.0f, -1.0f, 0.0f));
	floor->VertexData.push_back(vec3( 1.0f, -1.0f, 0.0f));
	floor->VertexData.push_back(vec3( 1.0f,  1.0f, 0.0f));
	floor->VertexData.push_back(vec3(-1.0f,  1.0f, 0.0f));
	
	floor->ColorData.push_back(vec4(0.0f, 0.0f, 0.0f,1.0f));
	floor->ColorData.push_back(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	floor->ColorData.push_back(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	floor->ColorData.push_back(vec4(0.0f, 0.0f, 0.0f, 1.0f));

	floor->UVData.push_back(vec2(0.0f, 0.0f));
	floor->UVData.push_back(vec2(1.0f, 0.0f));
	floor->UVData.push_back(vec2(1.0f, 1.0f));
	floor->UVData.push_back(vec2(0.0f, 1.0f));

	//first triangle.
	floor->IndicesData.push_back(0);
	floor->IndicesData.push_back(1);
	floor->IndicesData.push_back(3);

	//second triangle.
	floor->IndicesData.push_back(1);
	floor->IndicesData.push_back(2);
	floor->IndicesData.push_back(3);

	floor->Initialize();

	//skybox->VertexData.push_back();

	//////////////////////////////////////////////////////////////////////////
	// loading and initalizing textures.
	////////////////////////////////////////////////////
	
	mTexture1 = unique_ptr<Texture>(new Texture("1.png",0));
	mTexture2 = unique_ptr<Texture>(new Texture("2.png",1));

	//collectablesTexture = unique_ptr<Texture>(new Texture("cookie.png", 2));

	heroFrontTexture = unique_ptr<Texture>(new Texture("dudeface.png", 4));
	heroBackTexture = unique_ptr<Texture>(new Texture("dudeback.png", 5));
	heroTopTexture = unique_ptr<Texture>(new Texture("top.png", 6));
	heroLeftTexture = unique_ptr<Texture>(new Texture("dudeforward.png", 7));
	heroRightTexture = unique_ptr<Texture>(new Texture("dudebackward.png", 8));
	heroBottomTexture = unique_ptr<Texture>(new Texture("bottom.png", 9));
	//////////////////////////////////////////////////////////////////////////
	bkgtex = unique_ptr<Texture>(new Texture("space.jpg", 10));
	floortex= unique_ptr<Texture>(new Texture("wooden.jpg", 2)); //
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "SimpleTransformWithColor.vertexshader", "MultiColor.fragmentshader" );
	
	//////////////////////////////////////////////////////////////////////////
	mRenderingModeID = glGetUniformLocation(programID,"RenderingMode");
	//////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Transformations
	////////////////////
	// Get a handle for our "MVP" uniform the holder we created in the vertex shader)
	// GLint glGetUniformLocation(GLuint program​, const GLchar *name​);
	// program:  Specifies the program objec(t to be queried.
	// name: Points to a null terminated string containing the name of the uniform variable whose location is to be queried. 
	MatrixID = glGetUniformLocation(programID, "MVP");
	
	//////////////////////////////////////////////////////////////////////////

	// Projection matrix : 
	myCamera->SetPerspectiveProjection(65.0f,4.0f/3.0f,0.1f,100.0f);

	// View matrix : 
	myCamera->Reset(
		0.0f, 1.0f, 4.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	);
	//myCamera->Fly(-0.3);
	//////////////////////
	hero->MxPosition = 0;
	hero->MzPosition = 0;

	triangle1M  = translate(-1.0f, -0.0f, 1.0f) * rotate(-30.0f, vec3(0,1,0)) * scale(0.3f, 0.3f, 0.3f);
	triangle2M  = translate(-1.0f, -0.0f,-0.75f) * rotate(30.0f, vec3(0,1,0)) * scale(0.3f, 0.3f, 0.3f);
	triangle3M  = translate(+1.0f, -0.00f, 1.0f) * rotate(-30.0f, vec3(0,1,0)) * scale(0.3f,0.3f,0.3f);
	triangle4M  = translate(+1.0f, -0.00f,-0.75f) * rotate(30.0f, vec3(0,1,0)) * scale(0.3f, 0.3f, 0.3f);
	
	collectablesFM = translate(0.0f, 0.0f, 0.0f) * rotate(0.0f, vec3(1, 0, 0)) * scale(0.05f, 0.05f, 0.05f);
	collectablesBM = translate(0.0f, 0.0f, -0.1f) * rotate(0.0f, vec3(1, 0, 0)) * scale(0.05f, 0.05f, 0.05f);
	collectablesRM = translate(0.05f, 0.0f, -0.05f) * rotate(90.0f, vec3(0, 1, 0)) * scale(0.05f, 0.05f, 0.05f);
	collectablesLM = translate(-0.05f, 0.0f, -0.05f) * rotate(90.0f, vec3(0, 1, 0)) * scale(0.05f, 0.05f, 0.05f);
	collectablesTM = translate(0.0f, 0.05f, -0.05f) * rotate(90.0f, vec3(1, 0, 0)) * scale(0.05f, 0.05f, 0.05f);


	heroFM = translate(0.0f, 0.105f, 0.0f) * rotate(0.0f, vec3(0, 1, 0)) * scale(0.25f, 0.25f, 0.25f);
	//heroFM = translate(0.0f, 0.0f, 0.0f) * rotate(0.0f, vec3(0, 1, 0)) * scale(0.1f, 0.1f, 0.1f);
	heroBM = translate(0.0f,  0.0f, -0.2f) * heroFM;
	heroRM = translate(0.1f,  0.0f, -0.1f)	* rotate(90.0f, vec3(0, 1, 0)) * scale(0.1f, 0.1f, 0.1f);  
	heroLM = translate(-0.1f, 0.0f, -0.1f)	* rotate(-90.0f, vec3(0, 1, 0)) * scale(0.1f, 0.1f, 0.1f); 
	heroTM = translate(0.0f,  0.1f, -0.1f)	* rotate(90.0f, vec3(1, 0, 0)) * scale(0.1f, 0.1f, 0.1f);  
	heroBtM= translate(0.0f, -0.1f, -0.1f)*  rotate(90.0f, vec3(1, 0, 0)) * scale(0.1f, 0.1f, 0.1f); 


	floorM = translate(0.0f, -0.1f, -0.0f)* scale(6.0f,3.0f,3.0f)*rotate(90.0f,vec3(1.0f,0.0f,0.0f));
   
	upM = translate(0.0f, 2.5f, 0.0f)* scale(6.0f, 3.0f, 3.0f)*rotate(90.0f, vec3(1.0f, 0.0f, 0.0f));

	backgroundM= translate(0.0f, 2.5f, -3.0f)* scale(6.0f, 3.0f, 0.0f)*rotate(180.0f, vec3(1.0f, 0.0f, 0.0f));
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
		
		if (heroF && !heroB && !heroR && !heroL) {
			//front side of the hero
			heroFrontTexture->Bind();
		}
		if (!heroF && heroB && !heroR && !heroL) {
			//back side of the hero
			heroBackTexture->Bind();
		}
		if (!heroF && !heroB && heroR && !heroL) {
			//right side of the hero
			heroRightTexture->Bind();
		}
		if (!heroF && !heroB && !heroR && heroL) {
			//left side of the hero
			heroLeftTexture->Bind();
		}

		 herofrontMVP = VP * heroFM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &herofrontMVP[0][0]);
			hero->Draw();
	

		//back side of the hero
		heroBackTexture->Bind();
		heroMVPBack = VP * heroBM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &heroMVPBack[0][0]);
		//hero->Draw();


		//right side of the hero
		heroRightTexture->Bind();
	    heroMVPRight = VP * heroRM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &heroMVPRight[0][0]);
		//hero->Draw();


		//left side of the hero
		heroLeftTexture->Bind();
		heroMVPLeft = VP * heroLM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &heroMVPLeft[0][0]);
		//hero->Draw();


		//top side of the hero
		heroTopTexture->Bind();
		mat4 heroMVPTop = VP * heroTM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &heroMVPTop[0][0]);
		//hero->Draw();


		//bottom side of the hero
		heroBottomTexture->Bind();
		mat4 heroMVPbottom = VP * heroBtM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &heroMVPbottom[0][0]);
		//hero->Draw();

		////collectables front
		//collectablesTexture->Bind();
		//mat4 collecFMVP = VP * collectablesFM;
		//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &collecFMVP[0][0]);
		//collectables->Draw();

		////collectables back
		//collectablesTexture->Bind();
		//mat4 collecBMVP = VP * collectablesBM;
		//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &collecBMVP[0][0]);
		//collectables->Draw();

		////collectables right
		//collectablesTexture->Bind();
		//mat4 collecRMVP = VP * collectablesRM;
		//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &collecRMVP[0][0]);
		//collectables->Draw();


		////collectables right
		//collectablesTexture->Bind();
		//mat4 collecLMVP = VP * collectablesLM;
		//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &collecLMVP[0][0]);
		//collectables->Draw();
		//
		////collectables top
		//collectablesTexture->Bind();
		//mat4 collecTMVP = VP * collectablesTM;
		//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &collecTMVP[0][0]);
		//collectables->Draw();

		mRenderingMode = RenderingMode::NO_TEXTURE;
		glUniform1i(mRenderingModeID, mRenderingMode);


		mTexture1->Bind();
		//1st triangle
		mat4 triangle1MVP =   VP * triangle1M; 
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &triangle1MVP[0][0]);
		myTriangle->Draw();

		

		//3rd triangle
		mat4 triangle3MVP = VP * triangle3M;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &triangle3MVP[0][0]);
		myTriangle->Draw();

		
		//2nd triangle
		mTexture2->Bind();
		mat4 triangle2MVP = VP * triangle2M;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &triangle2MVP[0][0]);
		myTriangle->Draw();
		

		//////////////////////////////////////////////////////////////////////////
		// change the rendering mode to blend textures.
		mRenderingMode = RenderingMode::TEXTURE_ONLY;
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glUniform1i(mRenderingModeID,mRenderingMode);
		//4th triangle
		mat4 triangle4MVP =   VP * triangle4M; 
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &triangle4MVP[0][0]);
		myTriangle->Draw();


		mRenderingMode = RenderingMode::TEXTURE_ONLY;
		glUniform1i(mRenderingModeID,mRenderingMode);

		//background
		bkgtex->Bind();
		mat4 backgroundMVP = VP * backgroundM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &backgroundMVP[0][0]);
		floor->Draw();

		//above
		mat4 upMVP = VP * upM;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &upMVP[0][0]);
		floor->Draw();


		//the floor
		floortex->Bind();
		mat4 floorMVP =  VP * floorM; 
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &floorMVP[0][0]);
		floor->Draw();

		

}

void Renderer::Cleanup()
{
    glDeleteProgram(programID);
}

void Renderer::Update(double deltaTime)
{
	double triangle1RotationSpeed = 0.06;
	double trianglesRotationAngle = triangle1RotationSpeed*deltaTime;
	mat4 rotationMat = rotate((float)trianglesRotationAngle,vec3(0.0,1.0,0.0));
	//triangle1M = triangle1M * rotationMat;
	//triangle2M = triangle2M * rotationMat;
	//triangle3M = triangle3M * rotationMat;
	//triangle4M = triangle4M * rotationMat;
	//double squareRotationSpeed = 0.2;
	//double squareRotationAngle = squareRotationSpeed*deltaTime;
	//floorM =  rotate((float)squareRotationAngle,vec3(0.0,1.0,0.0))* floorM ;
}

void Renderer::HandleKeyboardInput(int key)
{
	//printf("Renderer::KEY = %d \n",key);

	/*if (heroFM[3][2] - triangle3M[3][2] ==-0.001)
	{
		triangle3M = triangle3M * translate(2.0f, 0.0f, 0.0f);
		printf("triangle4M \n ");
	}*/
	switch (key) 
	{
	case GLFW_KEY_UP:

		cout << "Hero x = " << heroFM[3][0] << " T3 X = " << triangle3M[3][0]<<endl
			<< "Hero z = " << heroFM[3][2] << " T3 z = " << triangle3M[3][2] << endl;
		heroFM = heroFM * translate( 0.00f, 0.00f,-0.05f);
		heroF = false, heroB = true, heroR = false, heroL = false;
		hero->MzPosition++;
		/*heroBM = heroBM * translate( 0.00f, 0.00f,-0.25f);
		heroRM = heroRM * translate( 0.25f, 0.00f, 0.00f);
		heroLM = heroLM * translate(-0.25f, 0.00f, 0.00f);
		heroTM = heroTM * translate( 0.00f,-0.25f, 0.00f);
		heroBtM=heroBtM * translate( 0.00f,-0.25f, 0.00f);*/
		

		//printf("keepPLaying: %d %d \n", hero->MxPosition, hero->MzPosition);
		
		//544 floor max size
		if (hero->MxPosition >= 544 || hero->MxPosition <= -544 || hero->MzPosition >= 544 || hero->MzPosition <= -544)
		{
			printf("you are out GAME OVER %d %d \n", hero->MxPosition, hero->MzPosition);
			done = true;
		}

		//static collision
		/*if (heroFM[3][2]== triangle3M[3][2]|| heroFM[3][0] == triangle3M[3][0])
		{
		        triangle3M = triangle3M * translate(10.0f, 0.0f, 0.0f);
			printf("triangle4M \n ");
		}*/

		myCamera->Walk(0.005f);
		break;


	case GLFW_KEY_DOWN:
		cout << "Hero x = " << heroFM[3][0] << " T3 X = " << triangle3M[3][0] << endl
			<< "Hero z = " << heroFM[3][2] << " T3 z = " << triangle3M[3][2] << endl;

		heroFM = heroFM * translate(0.00f, 0.00f, 0.05f);
		heroF = true, heroB = false, heroR = false, heroL = false;
		hero->MzPosition--;

		/*heroBM = heroBM * translate( 0.00f, 0.00f, 0.25f);
		heroRM = heroRM * translate(-0.25f, 0.00f, 0.00f);
		heroLM = heroLM * translate( 0.25f, 0.00f, 0.00f);
		heroTM = heroTM * translate( 0.00f, 0.25f, 0.00f);
		heroBtM=heroBtM * translate( 0.00f, 0.25f, 0.00f);*/
		
		//printf("keepPLaying: %d %d \n", hero->MxPosition, hero->MzPosition);

		if (hero->MxPosition >= 544 || hero->MxPosition <= -544 || hero->MzPosition >= 544 || hero->MzPosition <= -544)
		{
			//printf("you are out GAME OVER %d %d \n" , hero->MxPosition, hero->MzPosition);
			done = true;

		}
		

		myCamera->Walk(-0.005f);
		break;


	case GLFW_KEY_LEFT:
		cout << "Hero x = " << heroFM[3][0] << " T3 X = " << triangle3M[3][0] << endl
			<< "Hero z = " << heroFM[3][2] << " T3 z = " << triangle3M[3][2] << endl;

		heroFM = heroFM * translate(-0.050f, 0.00f, 0.00f); 
		heroF = false, heroB = false, heroR = false, heroL = true;

		/*heroBM = heroBM * translate(0.25f, 0.00f, 0.00f);
		heroRM = heroRM * translate(0.00f, 0.00f, 0.25f);
		heroLM = heroLM * translate(0.00f, 0.00f,-0.25f);
		heroTM = heroTM * translate(0.25f, 0.00f, 0.00f);
		heroBtM=heroBtM * translate(0.25f, 0.00f, 0.00f);*/
		myCamera->Strafe(-0.005f);
		//printf("keepPLaying: %d %d \n", hero->MxPosition, hero->MzPosition);

		hero->MxPosition--;
		if (hero->MxPosition >= 544 || hero->MxPosition <= -544 || hero->MzPosition >= 544 || hero->MzPosition <= -544)
		{
			//printf("you are out GAME OVER %d %d \n", hero->MxPosition, hero->MzPosition);
			done = true;

		}
		if (heroFM[3][2] == triangle3M[3][2] || heroFM[3][0] == triangle3M[3][0])
		{
			triangle3M = triangle3M * translate(10.0f, 0.0f, 0.0f);
			printf("triangle4M \n ");
		}
		break;


	case GLFW_KEY_RIGHT:
		cout << "Hero x = " << heroFM[3][0] << " T3 X = " << triangle3M[3][0] << endl
			<< "Hero z = " << heroFM[3][2] << " T3 z = " << triangle3M[3][2] << endl;

		heroFM = heroFM * translate(0.050f, 0.00f, 0.00f); 
		heroF = false, heroB = false, heroR = true, heroL = false;

		/*heroBM = heroBM * translate(-0.25f, 0.00f, 0.00f);
		heroRM = heroRM * translate(-0.00f, 0.00f,-0.25f);
		heroLM = heroLM * translate(-0.00f, 0.00f, 0.25f);
		heroTM = heroTM * translate(-0.25f, 0.00f, 0.00f);
		heroBtM=heroBtM * translate(-0.25f, 0.00f, 0.00f);*/
		myCamera->Strafe(0.005f);
		//printf("keepPLaying: %d %d \n", hero->MxPosition, hero->MzPosition);

		hero->MxPosition++;
		if (hero->MxPosition >= 544 || hero->MxPosition <= -544 || hero->MzPosition >= 544 || hero->MzPosition <= -544)
		{
			printf("you are out GAME OVER %d %d \n", hero->MxPosition, hero->MzPosition);
			done = true;
		}
		//z -215
		if (heroFM[3][2] == triangle3M[3][2] || heroFM[3][0] == triangle3M[3][0])
		{
			triangle3M = triangle3M * translate(10.0f, 0.0f, 0.0f);
			printf("triangle4M \n ");
		}
		break;
	
		//Moving forward
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
	//continue the remaining movements.

	myCamera->UpdateViewMatrix();
}

void Renderer::HandleMouse(double deltaX,double deltaY)
{
	printf("Renderer::MOUSE = %f , %f \n",deltaX,deltaY);
	
	myCamera->Yaw(deltaX);
	myCamera->Pitch(deltaY);
	myCamera->UpdateViewMatrix();

}
