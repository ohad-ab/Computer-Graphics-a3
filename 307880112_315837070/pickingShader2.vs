#version 330

attribute vec3 position;
attribute vec3 color;
attribute vec3 normal;
attribute vec2 texCoords;

uniform mat4 MVP;
//uniform mat4 Proj;
//uniform mat4 View;
uniform mat4 Normal;
uniform mat4 Model;
uniform mat4 N;

out vec3 normal0;
//out vec3 normal1;
//out vec3 normal2;
out vec4 p;
void main()
{
	//normal1 = vec3(N* vec4(normal, 0.0));
	normal0 = vec3(Normal* vec4(normal, 0.0));
	//normal2 = normal;
	gl_Position = MVP * Model* vec4(position, 1.0);
}
