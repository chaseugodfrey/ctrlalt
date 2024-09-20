// Vertex shader code goes here...
//everything is string literal
//defines current openGL Vers, gives error if dosent match
#version 450 core

//use slot 0 of vao, and according to the way it has been specified to read from vbo,
//put the data into aVertexPosition in the form of vec2
//likewise for aVertexColor

layout (location=0) in vec2 aVertexPosition;
//layout (location=1) in vec3 aVertexColor;

//vert shader will output a vec3 color
//layout (location=0) out vec3 vColor;

//object's 3x3 matrix transform
uniform mat3 uModel_to_NDC;

void main(){
    //in a vertex shader, gl_Position MUST be defined by something else compiler error
    //gl_Position should store vert pos as clip coord
    //first make current vtx position as a vec3, so it can be multiplied by mat3x3
    //then convert the result vec3 into a vec 2 ndc coord
    //then convert vec2 ndc coord into vec 4 clip coord with z-axis 0 and homogeneos coord 1
    
    gl_Position = vec4(vec2(uModel_to_NDC * vec3(aVertexPosition, 1.0)), 0.0, 1.0);
    //gl_Position = vec4(aVertexPosition, 0.0, 1.0);
    //vColor      = aVertexColor;
}