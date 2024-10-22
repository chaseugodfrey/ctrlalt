// Fragment shader code goes here...
#version 450 core

//---------------Input
layout (location=1) in vec2 vInterpolatedTexture;

//---------------Uniform
uniform sampler2D uTex2d;
//---------------Output
layout (location=0) out vec4 fFragColor;

void main(){
	fFragColor = texture(uTex2d, vInterpolatedTexture);
}