//Shader that is plain and only deals with position, and shader color variable

//defines current openGL Vers, gives error if dosent match
#version 450 core

//---------------Input
layout (location=0) in vec2 aVertexPosition;

//---------------Uniform
//object's 3x3 matrix transform
uniform mat3 uModel_to_NDC;

//---------------Output




void main(){
    gl_Position = vec4(vec2(uModel_to_NDC * vec3(aVertexPosition, 1.0)), 0.0, 1.0);
}