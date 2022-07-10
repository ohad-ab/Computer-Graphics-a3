#version 330

in vec3 normal0;
in vec3 normal1;
in vec3 normal2;
in vec4 p;
uniform sampler2D sampler1;
uniform vec4 lightDirection;
uniform vec4 lightColor;

void main()
{
//	vec4 c = vec4(lightColor.rgb * abs(normal0),lightColor.a);
//	float cr = c.r *1000;
//	if (normal0.z>0)
	gl_FragColor = vec4(lightColor.r * abs(normal0),lightColor.a);
}
