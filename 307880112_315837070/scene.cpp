#define GLEW_STATIC
#include "GL/glew.h"
#include "scene.h"
#include <iostream>

static void printMat(const glm::mat4 mat)
{
	printf(" matrix: \n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("%f ", mat[j][i]);
		printf("\n");
	}
}

Scene::Scene()
{
	glLineWidth(5);

	pickedShape = -1;
	depth = 0;
	angle = 0;
	speed = 0.8f;
	direction = 1;
	isR = false;
	isL = false;
	isU = false;
	isD = false;
	isB = false;
	isF = false;
	isSpace = false;
	isZ = false;
	isA = false;
	isM = false;
}

void Scene::AddShapeFromFile(const std::string& fileName, int parent, unsigned int mode)
{
	chainParents.push_back(parent);
	shapes.push_back(new Shape(fileName, mode));
}

void Scene::AddShape(int type, int parent, unsigned int mode)
{
	chainParents.push_back(parent);
	shapes.push_back(new Shape(type, mode));
}

void Scene::AddShapeCopy(int indx, int parent, unsigned int mode)
{
	chainParents.push_back(parent);
	shapes.push_back(new Shape(*shapes[indx], mode));
}

int Scene::AddShader(const std::string& fileName)
{
	shaders.push_back(new Shader(fileName));
	return (shaders.size() - 1);
}

int  Scene::AddTexture(const std::string& textureFileName, int dim)
{
	textures.push_back(new Texture(textureFileName, dim));
	return(textures.size() - 1);
}

int Scene::AddTexture(int width, int height, unsigned char* data, int mode)
{
	textures.push_back(new Texture(width, height));

	switch (mode)
	{
	case COLOR:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //note GL_RED internal format, to save memory.
		break;
	case DEPTH:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, data);
		break;
	case STENCIL:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, data);
		break;
	default:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //note GL_RED internal format, to save memory.
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	return(textures.size() - 1);
}

int Scene::AddMaterial(unsigned int texIndices[], unsigned int slots[], unsigned int size)
{
	materials.push_back(new Material(texIndices, slots, size));
	return (materials.size() - 1);
}

void Scene::Draw(int shaderIndx, const glm::mat4& MVP, int viewportIndx, unsigned int flags) 
{
	glm::mat4 Normal = MakeTrans();

	int p = pickedShape;

	for (pickedShape = 0; pickedShape < shapes.size(); pickedShape++)
	{
		if (shapes[pickedShape]->Is2Render(viewportIndx))
		{
			glm::mat4 Model = Normal * shapes[pickedShape]->MakeTrans();

			if (shaderIndx > 0)
			{
				Update(MVP, Model, shapes[pickedShape]->GetShader());
				shapes[pickedShape]->Draw(shaders[shapes[pickedShape]->GetShader()], false);
			}
			else
			{ //picking
				Update(MVP, Model, 0);
				shapes[pickedShape]->Draw(shaders[0], true);
			}
		}
	}
	pickedShape = p;
}



void Scene::ShapeTransformation(int type, float amt)
{
	if (glm::abs(amt) > 1e-5)
	{
		switch (type)
		{
		case xTranslate:
			shapes[pickedShape]->MyTranslate(glm::vec3(amt, 0, 0), 0);
			break;
		case yTranslate:
			shapes[pickedShape]->MyTranslate(glm::vec3(0, amt, 0), 0);
			break;
		case zTranslate:
			shapes[pickedShape]->MyTranslate(glm::vec3(0, 0, amt), 0);
			break;
		case xRotate:
			shapes[pickedShape]->MyRotate(amt, glm::vec3(1, 0, 0), 0);
			break;
		case yRotate:
			shapes[pickedShape]->MyRotate(amt, glm::vec3(0, 1, 0), 0);
			break;
		case 6:
			shapes[pickedShape]->MyRotate(amt, glm::vec3(0, 1, 0), 0);
			break;
		case zRotate:
			shapes[pickedShape]->MyRotate(amt, glm::vec3(0, 0, 1), 0);
			break;
		default:
			break;
		}
	}

}

bool Scene::Picking(unsigned char data[4])
{
		//pickedShape = -1;
	if (data[0] > 0)
	{
		pickedShape = data[0] - 1;
		for (int i = 0; i < 9; i++)
		{
			if (rubik[R[i]] == pickedShape)
			{
				queue.push(82);
				return true;
			}
		}
		queue.push(76);
		return true;
		//pickedShape = data[0] - 1;
		//glm::vec3 noramlx = glm::vec3(shapes[pickedShape]->MakeTrans()*glm::vec4(1, 0, 0, 0));
		////printf("normal %f\n", noraml.x);
		//if (round(noramlx.x) > 0)
		//{
		//	if (normals[pickedShape][0] < 0)
		//		queue.push(76);
		//	else
		//		queue.push(82);
		//}
		//else
		//{
		//	if (normals[pickedShape][0] < 0)
		//		queue.push(82);
		//	else
		//		queue.push(76);
		//}
		//return true;
	}
	if (data[1] > 0)
	{
		
		pickedShape = data[1] - 1;
		for (int i = 0; i < 9; i++)
		{
			if (rubik[U[i]] == pickedShape)
			{
				queue.push(85);
				return true;
			}
		}
		queue.push(68);
		return true;
		//glm::vec3 noramlx = glm::vec3(shapes[pickedShape]->MakeTrans()*glm::vec4(1, 0, 0, 0));
		//glm::vec3 noramly = glm::vec3(shapes[pickedShape]->MakeTrans()*glm::vec4(0, 1, 0, 0));
		//glm::vec3 noramlz = glm::vec3(shapes[pickedShape]->MakeTrans()*glm::vec4(0, 0, 1, 0));
		//if (round(noramly.y) > 0)
		//{
		//	if (normals[pickedShape][1] < 0)
		//		queue.push(68);
		//	else
		//		queue.push(85);
		//}
		//else if(round(noramly.x) > 0)
		//{
		//	if (normals[pickedShape][0] < 0)
		//		queue.push(85);
		//	else
		//		queue.push(68);
		//}
		//return true;
	}
	if (data[2] > 0)
	{
		pickedShape = data[2] - 1;
		for (int i = 0; i < 9; i++)
		{
			if (rubik[F[i]] == pickedShape)
			{
				queue.push(70);
				return true;
			}
		}
		queue.push(66);
		return true;
		//pickedShape = data[2] - 1;
		//glm::vec3 noramlz = glm::vec3(shapes[pickedShape]->MakeTrans()*glm::vec4(0, 0, 1, 0));
		//if (round(noramlz.z) > 0)
		//{
		//	if (normals[pickedShape][2] < 0)
		//		queue.push(66);
		//	else
		//		queue.push(70);
		//}
		//else
		//{
		//	if (normals[pickedShape][2] < 0)
		//		queue.push(70);
		//	else
		//		queue.push(66);
		//}
		//return true;
	}
		//for (int i = 0; i < 27; i++)
		//{
		//	glm::mat4 Model = shapes[i]->MakeTrans();
		//	glm::vec3 x = glm::vec3(Model* glm::vec4(glm::vec3(1, 0, 0), 0.0));
		//	glm::vec3 y = glm::vec3(Model* glm::vec4(glm::vec3(0, 1, 0), 0.0));
		//	glm::vec3 z = glm::vec3(Model* glm::vec4(glm::vec3(0, 0, 1), 0.0));
		//	glm::vec3 a = glm::vec3((i+1), 0, 0)*glm::abs(x);
		//	glm::vec3 b = glm::vec3((i+1), 0, 0)*glm::abs(y);
		//	glm::vec3 c = glm::vec3((i+1), 0, 0)*glm::abs(z);
		//	if (a.x == data[0])
		//	{
		//		rotateWall(a.x - 1, x.x);
		//		return true;
		//	}
		//	else if (b.y == data[1])
		//	{
		//		rotateWall(b.y - 1, y.y);
		//		return true;
		//	}
		//	else if (c.z == data[2])
		//	{
		//		rotateWall(c.z - 1, z.z);
		//		return true;
		//	}
		//		printf("%d x %f %f %f\n",i, a.x , a.y, a.z);
		//		printf("y %f %f %f\n", b.x , b.y, b.z);
		//		printf("z %f %f %f\n",c.x , c.y, c.z);
		//}
		
		return false;
		//WhenPicked();	
}
//void Scene::WhenPicked() {
//
//}
//return coordinates in global system for a tip of arm position is local system 
void Scene::MouseProccessing(int button, int xrel, int yrel)
{
	//if (pickedShape == -1)
	//{
	if (button == 1)
	{
		//pickedShape = 0;
		//ShapeTransformation(xTranslate, xrel / 80.0f);
		//pickedShape = 1;
		MyTranslate(glm::vec3(-xrel / 80.0f, 0, 0), 0);
		MyTranslate(glm::vec3(0, yrel / 80.0f, 0), 0);
		WhenTranslate();
	}
	else
	{
		//pickedShape = 0;
		//ShapeTransformation(yRotate, xrel / 2.0f);
		//pickedShape = 1;
		MyRotate(-xrel / 2.0f, glm::vec3(0, 1, 0), 0);
		MyRotate(-yrel / 2.0f, glm::vec3(1, 0, 0), 1);
		WhenRotate();
	}
	//}

}
void Scene::ScrollProccessing(double xoffset, double yoffset)
{
	pickedShape = 0;
	shapes[pickedShape]->MyScale(glm::vec3(2, 2, 2));

}
void Scene::KeyProccessing(int button)
{
	queue.push(button);
	//if (button == 82)
	//{
	//	isR = true;
	//}
	//if (button == 85)
	//	isU = true;
}
bool Scene::processR()
{
	float toadd = speed;

	float oldangle = angle;
	angle += speed;
	if (abs(angle) > 90.0f) {

		toadd = 90.f - oldangle;
		angle = 90.0f;

	}
	if (direction == -1)
		toadd = -toadd;
		//i wanna add the missing last part this is the angle 
	pickedShape = rubik[2];
	ShapeTransformation(xRotate, toadd);
	pickedShape = rubik[5];
	ShapeTransformation(xRotate, toadd);
	pickedShape = rubik[8];
	ShapeTransformation(xRotate, toadd);
	pickedShape = rubik[11];
	ShapeTransformation(xRotate, toadd);
	pickedShape = rubik[14];
	ShapeTransformation(xRotate, toadd);
	pickedShape = rubik[17];
	ShapeTransformation(xRotate, toadd);
	pickedShape = rubik[20];
	ShapeTransformation(xRotate, toadd);
	pickedShape = rubik[23];
	ShapeTransformation(xRotate, toadd);
	pickedShape = rubik[26];
	ShapeTransformation(xRotate, toadd);
	
	if (angle == 90)
	{
		updateCube(82);
		return true;
	}
	return false;
}
bool Scene::processU()
{
	float toadd = speed;

	float oldangle = angle;
	angle += speed ;
	if (angle > 90.0f) {

		toadd = 90.f - oldangle;
		angle = 90.0f;

	}
	if (direction == -1)
		toadd = -toadd;
	//i wanna add the missing last part this is the angle 
	pickedShape = rubik[0];
	ShapeTransformation(yRotate, toadd);
	pickedShape = rubik[1];
	ShapeTransformation(yRotate, toadd);
	pickedShape = rubik[2];
	ShapeTransformation(yRotate, toadd);
	pickedShape = rubik[9];
	ShapeTransformation(yRotate, toadd);
	pickedShape = rubik[10];
	ShapeTransformation(yRotate, toadd);
	pickedShape = rubik[11];
	ShapeTransformation(yRotate, toadd);
	pickedShape = rubik[18];
	ShapeTransformation(yRotate, toadd);
	pickedShape = rubik[19];
	ShapeTransformation(yRotate, toadd);
	pickedShape = rubik[20];
	ShapeTransformation(yRotate, toadd);
	if (angle == 90)
	{
		updateCube(85);
		return true;
	}
	return false;
}

bool Scene::processL()
{
	float toadd = speed;

	float oldangle = angle;
	angle += speed;
	if (angle > 90.0f) {

		toadd = 90.f - oldangle;
		angle = 90.0f;

	}
	if (direction == -1)
		toadd = -toadd;
	pickedShape = rubik[0];
	ShapeTransformation(xRotate, toadd);
	pickedShape = rubik[3];
	ShapeTransformation(xRotate, toadd);
	pickedShape = rubik[6];
	ShapeTransformation(xRotate, toadd);
	pickedShape = rubik[9];
	ShapeTransformation(xRotate, toadd);
	pickedShape = rubik[12];
	ShapeTransformation(xRotate, toadd);
	pickedShape = rubik[15];
	ShapeTransformation(xRotate, toadd);
	pickedShape = rubik[18];
	ShapeTransformation(xRotate, toadd);
	pickedShape = rubik[21];
	ShapeTransformation(xRotate, toadd);
	pickedShape = rubik[24];
	ShapeTransformation(xRotate, toadd);
	if (angle == 90)
	{
		updateCube(76);
		return true;
	}
	return false;
}

bool Scene::processD()
{
	float toadd = speed;

	float oldangle = angle;
	angle += speed;
	if (angle > 90.0f) {

		toadd = 90.f - oldangle;
		angle = 90.0f;

	}
	if (direction == -1)
		toadd = -toadd;
	//i wanna add the missing last part this is the angle 
	pickedShape = rubik[6];
	ShapeTransformation(yRotate, toadd);
	pickedShape = rubik[7];
	ShapeTransformation(yRotate, toadd);
	pickedShape = rubik[8];
	ShapeTransformation(yRotate, toadd);
	pickedShape = rubik[15];
	ShapeTransformation(yRotate, toadd);
	pickedShape = rubik[16];
	ShapeTransformation(yRotate, toadd);
	pickedShape = rubik[17];
	ShapeTransformation(yRotate, toadd);
	pickedShape = rubik[24];
	ShapeTransformation(yRotate, toadd);
	pickedShape = rubik[25];
	ShapeTransformation(yRotate, toadd);
	pickedShape = rubik[26];
	ShapeTransformation(yRotate, toadd);
	if (angle == 90)
	{
		updateCube(68);
		return true;
	}
	return false;
}

bool Scene::processB()
{
	float toadd = speed;

	float oldangle = angle;
	angle += speed;
	if (angle > 90.0f) {

		toadd = 90.f - oldangle;
		angle = 90.0f;

	}
	if (direction == -1)
		toadd = -toadd;
	pickedShape = rubik[18];
	ShapeTransformation(zRotate, toadd);
	pickedShape = rubik[19];
	ShapeTransformation(zRotate, toadd);
	pickedShape = rubik[20];
	ShapeTransformation(zRotate, toadd);
	pickedShape = rubik[21];
	ShapeTransformation(zRotate, toadd);
	pickedShape = rubik[22];
	ShapeTransformation(zRotate, toadd);
	pickedShape = rubik[23];
	ShapeTransformation(zRotate, toadd);
	pickedShape = rubik[24];
	ShapeTransformation(zRotate, toadd);
	pickedShape = rubik[25];
	ShapeTransformation(zRotate, toadd);
	pickedShape = rubik[26];
	ShapeTransformation(zRotate, toadd);
	if (angle == 90)
	{
		updateCube(66);
		return true;
	}
	return false;
}

bool Scene::processF()
{
	float toadd = speed;

	float oldangle = angle;
	angle += speed;
	if (angle > 90.0f) {

		toadd = 90.f - oldangle;
		angle = 90.0f;

	}
	if (direction == -1)
		toadd = -toadd;
	pickedShape = rubik[0];
	ShapeTransformation(zRotate, toadd);
	pickedShape = rubik[1];
	ShapeTransformation(zRotate, toadd);
	pickedShape = rubik[2];
	ShapeTransformation(zRotate, toadd);
	pickedShape = rubik[3];
	ShapeTransformation(zRotate, toadd);
	pickedShape = rubik[4];
	ShapeTransformation(zRotate, toadd);
	pickedShape = rubik[5];
	ShapeTransformation(zRotate, toadd);
	pickedShape = rubik[6];
	ShapeTransformation(zRotate, toadd);
	pickedShape = rubik[7];
	ShapeTransformation(zRotate, toadd);
	pickedShape = rubik[8];
	ShapeTransformation(zRotate, toadd);
	if (angle == 90)
	{
		updateCube(70);
		return true;
	}
	return false;
}

void Scene::updateCube(int button)
{
	int temp;
	if (button == 82)
	{
		if (direction == 1)
		{
			temp = rubik[8];
			rubik[8] = rubik[2];
			rubik[2] = rubik[20];
			rubik[20] = rubik[26];
			rubik[26] = temp;
			temp = rubik[5];
			rubik[5] = rubik[11];
			rubik[11] = rubik[23];
			rubik[23] = rubik[17];
			rubik[17] = temp;
		}
		else
		{
			temp = rubik[8];
			rubik[8] = rubik[26];
			rubik[26] = rubik[20];
			rubik[20] = rubik[2];
			rubik[2] = temp;
			temp = rubik[5];
			rubik[5] = rubik[17];
			rubik[17] = rubik[23];
			rubik[23] = rubik[11];
			rubik[11] = temp;
		}
	}
	if (button == 85)
	{
		if (direction == 1)
		{
			temp = rubik[0];
			rubik[0] = rubik[18];
			rubik[18] = rubik[20];
			rubik[20] = rubik[2];
			rubik[2] = temp;
			temp = rubik[9];
			rubik[9] = rubik[19];
			rubik[19] = rubik[11];
			rubik[11] = rubik[1];
			rubik[1] = temp;
		}
		else
		{
			temp = rubik[0];
			rubik[0] = rubik[2];
			rubik[2] = rubik[20];
			rubik[20] = rubik[18];
			rubik[18] = temp;
			temp = rubik[9];
			rubik[9] = rubik[1];
			rubik[1] = rubik[11];
			rubik[11] = rubik[19];
			rubik[19] = temp;
		}
	}
	if (button == 76)
	{
		if (direction == 1)
		{
			temp = rubik[0];
			rubik[0] = rubik[18];
			rubik[18] = rubik[24];
			rubik[24] = rubik[6];
			rubik[6] = temp;
			temp = rubik[9];
			rubik[9] = rubik[21];
			rubik[21] = rubik[15];
			rubik[15] = rubik[3];
			rubik[3] = temp;
		}
		else
		{
			temp = rubik[0];
			rubik[0] = rubik[6];
			rubik[6] = rubik[24];
			rubik[24] = rubik[18];
			rubik[18] = temp;
			temp = rubik[9];
			rubik[9] = rubik[3];
			rubik[3] = rubik[15];
			rubik[15] = rubik[21];
			rubik[21] = temp;
		}
	}
	if (button == 68)
	{
		if (direction == 1)
		{
			temp = rubik[8];
			rubik[8] = rubik[6];
			rubik[6] = rubik[24];
			rubik[24] = rubik[26];
			rubik[26] = temp;
			temp = rubik[17];
			rubik[17] = rubik[7];
			rubik[7] = rubik[15];
			rubik[15] = rubik[25];
			rubik[25] = temp;
		}
		else
		{
			temp = rubik[8];
			rubik[8] = rubik[26];
			rubik[26] = rubik[24];
			rubik[24] = rubik[6];
			rubik[6] = temp;
			temp = rubik[17];
			rubik[17] = rubik[25];
			rubik[25] = rubik[15];
			rubik[15] = rubik[7];
			rubik[7] = temp;
		}
	}
	if (button == 66)
	{
		if (direction == 1)
		{
			temp = rubik[24];
			rubik[24] = rubik[18];
			rubik[18] = rubik[20];
			rubik[20] = rubik[26];
			rubik[26] = temp;
			temp = rubik[21];
			rubik[21] = rubik[19];
			rubik[19] = rubik[23];
			rubik[23] = rubik[25];
			rubik[25] = temp;
		}
		else
		{
			temp = rubik[24];
			rubik[24] = rubik[26];
			rubik[26] = rubik[20];
			rubik[20] = rubik[18];
			rubik[18] = temp;
			temp = rubik[21];
			rubik[21] = rubik[25];
			rubik[25] = rubik[23];
			rubik[23] = rubik[19];
			rubik[19] = temp;
		}
	}
	if (button == 70)
	{

		if (direction == 1)
		{
			temp = rubik[6];
			rubik[6] = rubik[0];
			rubik[0] = rubik[2];
			rubik[2] = rubik[8];
			rubik[8] = temp;
			temp = rubik[3];
			rubik[3] = rubik[1];
			rubik[1] = rubik[5];
			rubik[5] = rubik[7];
			rubik[7] = temp;
		}
		else {
			temp = rubik[6];
			rubik[6] = rubik[8];
			rubik[8] = rubik[2];
			rubik[2] = rubik[0];
			rubik[0] = temp;
			temp = rubik[3];
			rubik[3] = rubik[7];
			rubik[7] = rubik[5];
			rubik[5] = rubik[1];
			rubik[1] = temp;
		}
	}
}

void Scene::ZeroShapesTrans()
{
	for (unsigned int i = 0; i < shapes.size(); i++)
	{
		shapes[i]->ZeroTrans();
	}
}

void Scene::ReadPixel()
{
	glReadPixels(1, 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
}

void Scene::AddShapeViewport(int shpIndx,int viewPortIndx)
{
	shapes[shpIndx]->AddViewport(viewPortIndx);
}

void Scene::RemoveShapeViewport(int shpIndx, int viewPortIndx)
{
	shapes[shpIndx]->RemoveViewport(viewPortIndx);
}

void Scene::BindMaterial(Shader* s, unsigned int materialIndx)
{

	for (size_t i = 0; i < materials[materialIndx]->GetNumOfTexs(); i++)
	{
		materials[materialIndx]->Bind(textures, i);
		s->SetUniform1i("sampler" + std::to_string(i + 1), materials[materialIndx]->GetSlot(i));
	}
}

Scene::~Scene(void)
{
	for (Shape* shp : shapes)
	{
		delete shp;
	}

	for (Shader* sdr : shaders)
	{
		delete sdr;
	}
	for (Texture* tex : textures)
	{
		delete tex;
	}
	for (Material* mat : materials)
	{
		delete mat;
	}

}



