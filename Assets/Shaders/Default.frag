// Fragment shader code goes here...
#version 450 core

//---------------Input
//Get Texture coord
layout (location=1) in vec2 vInterpolatedTexture;

//---------------Uniform
//BlackBox Data structure thata represents a texture
//Requires that the uniform value that represents the image unit's format fits this sampler's format
uniform sampler2D uTex2d;
uniform vec3 uColor;

//---------------Output
//front buffer is currently drawn
//back buffer is whr shader's data shld be placed
//GL_BACK_LEFT's color buffer index by default is 0, so thats where our data will be placed
layout (location=0) out vec4 fFragColor;

void main(){
	//Get Texture Color
	fFragColor = texture(uTex2d, vInterpolatedTexture);
	//fFragColor = vec4(uTex2d, 0.0, 1.0);
	
	//Modulate texture with color param
	//fFragColor = fFragColor * vec4(uColor, 1.0);
}