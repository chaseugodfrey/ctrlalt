// Vertex shader code goes here...
//everything is string literal
//defines current openGL Vers, gives error if dosent match
#version 450 core

//---------------Input
layout (location=0) in vec2 aVertexPosition;
layout (location=1) in vec2 aVertexTexture;

//---------------Uniform
//object's 3x3 matrix transform
uniform mat3 uModel_to_NDC;

//---------------Output
//Pass texture coord to frag shader
layout (location=1) out vec2 vTexture;



void main(){
    	gl_Position 	= vec4(vec2(uModel_to_NDC * vec3(aVertexPosition, 1.0)), 0.0, 1.0);
	vTexture	= aVertexTexture;

    //gl_Position = vec4(aVertexPosition, 0.0, 1.0);
    //vColor      = aVertexColor;
}