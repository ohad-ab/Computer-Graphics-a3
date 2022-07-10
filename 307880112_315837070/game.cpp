#include "game.h"
#include <iostream>
#include "GL/glew.h"
#include <random>
static void printMat(const glm::mat4 mat)
{
	std::cout<<" matrix:"<<std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout<< mat[j][i]<<" ";
		std::cout<<std::endl;
	}
}

Game::Game() : Scene()
{
}

//Game::Game(float angle ,float relationWH, float near, float far) : Scene(angle,relationWH,near,far)
//{ 	
//}

void Game::Init()
{		
	unsigned int texIDs[3] = { 0 , 1, 0};
	unsigned int slots[3] = { 0 , 1, 0 };
	
	AddShader("../res/shaders/pickingShader2");	
	AddShader("../res/shaders/basicShader");
	//AddShader("../res/shaders/basicShader");
	
	AddTexture("../res/textures/plane.png",2);
	//AddTexture("../res/textures/grass.bmp", 2);
	//TextureDesine(800, 800);
	AddMaterial(texIDs,slots, 1);
	//AddMaterial(texIDs+1,slots+1, 2);
	AddShape(Cube, -1, TRIANGLES);
	rubik[13] = 0;
	SetShapeShader(0, 1);
	for (int i = 1; i < 27; i++)
	{
		AddShapeCopy(0, -1, TRIANGLES);
		SetShapeShader(i, 1);

	}

	pickedShape = 1;
	ShapeTransformation(xTranslate, -2);
	rubik[12] = 1;
	normals[pickedShape][0] = -1;
	pickedShape = 2;
	ShapeTransformation(xTranslate, 2);
	rubik[14] = 2;
	pickedShape = 3;
	ShapeTransformation(yTranslate, 2);
	rubik[10] = 3;
	pickedShape = 4;
	ShapeTransformation(yTranslate, 2);
	ShapeTransformation(xTranslate, 2);
	rubik[11] = 4;
	pickedShape = 5;
	ShapeTransformation(yTranslate, 2);
	ShapeTransformation(xTranslate, -2);
	rubik[9] = 5;
	normals[pickedShape][0] = -1;
	pickedShape = 6;
	ShapeTransformation(yTranslate, -2);
	rubik[16] = 6;
	normals[pickedShape][1] = -1;
	pickedShape = 7;
	ShapeTransformation(yTranslate, -2);
	ShapeTransformation(xTranslate, 2);
	rubik[17] = 7;
	normals[pickedShape][1] = -1;
	pickedShape = 8;
	ShapeTransformation(yTranslate, -2);
	ShapeTransformation(xTranslate, -2);
	rubik[15] = 8;
	normals[pickedShape][1] = -1;
	normals[pickedShape][0] = -1;
	pickedShape = 9;
	ShapeTransformation(zTranslate, 2);
	rubik[4] = 9;
	pickedShape = 10;
	ShapeTransformation(xTranslate, -2);
	ShapeTransformation(zTranslate, 2);
	rubik[3] = 10;
	normals[pickedShape][0] = -1;
	pickedShape = 11;
	ShapeTransformation(xTranslate, 2);
	ShapeTransformation(zTranslate, 2);
	rubik[5] = 11;
	pickedShape = 12;
	ShapeTransformation(yTranslate, 2);
	ShapeTransformation(zTranslate, 2);
	rubik[1] = 12;
	pickedShape = 13;
	ShapeTransformation(yTranslate, 2);
	ShapeTransformation(xTranslate, 2);
	ShapeTransformation(zTranslate, 2);
	rubik[2] = 13;
	pickedShape = 14;
	ShapeTransformation(yTranslate, 2);
	ShapeTransformation(xTranslate, -2);
	ShapeTransformation(zTranslate, 2);
	rubik[0] = 14;
	normals[pickedShape][0] = -1;
	pickedShape = 15;
	ShapeTransformation(yTranslate, -2);
	ShapeTransformation(zTranslate, 2);
	rubik[7] = 15;
	normals[pickedShape][1] = -1;
	pickedShape = 16;
	ShapeTransformation(yTranslate, -2);
	ShapeTransformation(xTranslate, 2);
	ShapeTransformation(zTranslate, 2);
	normals[pickedShape][1] = -1;
	rubik[8] = 16;
	pickedShape = 17;
	ShapeTransformation(yTranslate, -2);
	ShapeTransformation(xTranslate, -2);
	ShapeTransformation(zTranslate, 2);
	normals[pickedShape][1] = -1;
	normals[pickedShape][0] = -1;
	rubik[6] = 17;
	pickedShape = 18;
	ShapeTransformation(zTranslate, -2);
	rubik[22] = 18;
	normals[pickedShape][2] = -1;
	pickedShape = 19;
	ShapeTransformation(xTranslate, -2);
	ShapeTransformation(zTranslate, -2);
	normals[pickedShape][0] = -1;
	normals[pickedShape][2] = -1;
	rubik[21] = 19;
	pickedShape = 20;
	ShapeTransformation(xTranslate, 2);
	ShapeTransformation(zTranslate, -2);
	rubik[23] = 20;
	normals[pickedShape][2] = -1;
	pickedShape = 21;
	ShapeTransformation(yTranslate, 2);
	ShapeTransformation(zTranslate, -2);
	rubik[19] = 21;
	normals[pickedShape][2] = -1;
	pickedShape = 22;
	ShapeTransformation(yTranslate, 2);
	ShapeTransformation(xTranslate, 2);
	ShapeTransformation(zTranslate, -2);
	normals[pickedShape][2] = -1;
	rubik[20] = 22;
	pickedShape = 23;
	ShapeTransformation(yTranslate, 2);
	ShapeTransformation(xTranslate, -2);
	ShapeTransformation(zTranslate, -2);
	normals[pickedShape][0] = -1;
	normals[pickedShape][2] = -1;
	rubik[18] = 23;
	pickedShape = 24;
	ShapeTransformation(yTranslate, -2);
	ShapeTransformation(zTranslate, -2);
	rubik[25] = 24;
	normals[pickedShape][1] = -1;
	normals[pickedShape][2] = -1;
	pickedShape = 25;
	ShapeTransformation(yTranslate, -2);
	ShapeTransformation(xTranslate, 2);
	ShapeTransformation(zTranslate, -2);
	rubik[26] = 25;
	normals[pickedShape][1] = -1;
	normals[pickedShape][2] = -1;
	pickedShape = 26;
	ShapeTransformation(yTranslate, -2);
	ShapeTransformation(xTranslate, -2);
	ShapeTransformation(zTranslate, -2);
	rubik[24] = 26;
	normals[pickedShape][0] = -1;
	normals[pickedShape][1] = -1;
	normals[pickedShape][2] = -1;

	//pickedShape = 2;
	//ShapeTransformation(xTranslate, 2);
	//pickedShape = 2;
	//ShapeTransformation(xTranslate, 2);
	//pickedShape = 2;
	//ShapeTransformation(xTranslate, 2);
	/*pickedShape = 1;
	ShapeTransformation(xTranslate, 1);
	SetShapeMaterial(1, 1);
	pickedShape = -1;

	pickedShape = 2;
	SetShapeMaterial(2, 2);
	pickedShape = -1;*/
	
	//ReadPixel(); //uncomment when you are reading from the z-buffer
}

void Game::Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx)
{
	Shader *s = shaders[shaderIndx];
	int r = ((pickedShape+1) & 0x000000FF) >>  0;
	int g = ((pickedShape+1) & 0x0000FF00) >>  8;
	int b = ((pickedShape+1) & 0x00FF0000) >> 16;
	if (shapes[pickedShape]->GetMaterial() >= 0 && !materials.empty())
		BindMaterial(s, shapes[pickedShape]->GetMaterial());
	//textures[0]->Bind(0);
	s->Bind();
	glm::mat4 shapeModel = shapes[pickedShape]->MakeTrans();
	if (shaderIndx != 0)
	{
		s->SetUniformMat4f("MVP", MVP);
		s->SetUniformMat4f("Normal", Model);
		//s->SetUniformMat4f("Normal", shapeModel);
		//s->SetUniformMat4f("Model", Model);
		//s->SetUniformMat4f("N", shapes[pickedShape]->MakeTrans());
	}
	else
	{
		s->SetUniformMat4f("MVP", MVP);
		s->SetUniformMat4f("Normal", shapeModel);
		s->SetUniformMat4f("Model", Model);
		s->SetUniformMat4f("N", shapes[pickedShape]->MakeTrans());
	}
	s->SetUniform1i("sampler1", materials[shapes[pickedShape]->GetMaterial()]->GetSlot(0));
	if(shaderIndx!=2)
		s->SetUniform1i("sampler2", materials[shapes[pickedShape]->GetMaterial()]->GetSlot(1));
	s->SetUniform4f("lightColor", r/255.0f, g/255.0f, b/255.0f, 0.0f);
	s->Unbind();
}

void Game::WhenRotate()
{
}

void Game::WhenTranslate()
{
}

void Game::Motion()
{
	int button = 0;
	if(!queue.empty())
		button = queue.front();
	if (button == 82)
	{
		if (processR()){
			angle = 0;
			isR = false;
			queue.pop();
			}
	}
	if (button == 85)
	{
		if (processU()) {
			angle = 0;
			queue.pop();
		}
	}
	if (button == 76)
	{
		if (processL()) {
			angle = 0;
			queue.pop();
		}
	}
	if (button == 68)
	{
		if (processD()) {
			angle = 0;
			queue.pop();
		}
	}
	if (button == 66)
	{
		if (processB()) {
			angle = 0;
			queue.pop();
		}
	}
	if (button == 70)
	{
		if (processF()) {
			angle = 0;
			queue.pop();
		}
	}
	if (button == 90)
	{
		speed += 0.3;
		queue.pop();
	}if (button == 65)
	{
		if(speed>0.3)
			speed -= 0.3;
		queue.pop();
	}
	else if(button == 77)
	{
		int numbers[] = { 82, 85, 76, 68, 66, 70 };
		int length = sizeof(numbers) / sizeof(int);
		for (int i = 0; i < 10; i++)
		{
			int randomNumber = numbers[rand() % length];
			queue.push(randomNumber);
		}
		queue.pop();
	}
	if (button == 32)
	{
		direction = -direction;
		queue.pop();
	}
}

unsigned int Game::TextureDesine(int width, int height)
{
	unsigned char* data = new unsigned char[width * height * 4];
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			data[(i * height + j) * 4] = (i + j) % 256;
			data[(i * height + j) * 4 + 1] = (i + j * 2) % 256;
			data[(i * height + j) * 4 + 2] = (i * 2 + j) % 256;
			data[(i * height + j) * 4 + 3] = (i * 3 + j) % 256;
		}
	}
	textures.push_back(new Texture(width, height));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //note GL_RED internal format, to save 
	glBindTexture(GL_TEXTURE_2D, 0);
	delete[] data;
	return(textures.size() - 1);
}

Game::~Game(void)
{

}
