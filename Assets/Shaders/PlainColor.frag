// Fragment shader code goes here...
#version 450 core

//---------------Input

//---------------Uniform
uniform vec4 uColor;

//---------------Output
layout (location=0) out vec4 fFragColor;

void main(){
	fFragColor = uColor;
}