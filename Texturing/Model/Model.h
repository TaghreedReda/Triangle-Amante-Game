#ifndef Model_h__
#define Model_h__

#include <glm/glm.hpp>
#include <vector>
#include <gl\glew.h>
class Model
{
	//VAO
	GLuint mVertexArrayObjectID;
	
	//VBOs
	GLuint mVertexDataBufferID;
	GLuint mColorDataBufferID;
	GLuint mIndicesDataBufferID;
	GLuint mUVDataBufferID;


	/*std::vector<glm::vec3> mNormalData;
	std::vector<glm::vec2> mUVData;*/
public:
	glm::vec3 mPosition;
	glm::vec3 mUp;
	glm::vec3 mRight;
	glm::vec3 mDirection;
	glm::mat4 mViewMatrix;
	glm::mat4 mProjectionMatrix;

	//to know current location.
#pragma region new_stuff

	int MxPosition;
	int MzPosition;

	//monster.
	bool reachedHero;
	
	//hero
	bool wentin1;
	bool wentin2;
	bool wentin3;
	bool wentin4;
	bool wentin5;
	bool wentin6;
	bool wentin7;
	bool wentin8;
	bool wentin9;
	bool wentin10;

	//games
	int Score;

#pragma endregion

	Model();
	~Model();

	std::vector<glm::vec3> VertexData;
	std::vector<glm::vec4> ColorData;
	std::vector<unsigned short> IndicesData;
	std::vector<glm::vec2> UVData;

	 void Initialize();
	 void Draw();
	 void Walk(float dist);
	 void Cleanup();

};
#endif // Model_h__