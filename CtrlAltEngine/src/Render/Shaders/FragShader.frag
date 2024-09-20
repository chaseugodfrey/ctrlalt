// Fragment shader code goes here...
#version 450 core

//out vec3 vColor in vert shader is placed in location 0
//so to get that data here, location and type needs to match
//here, location index and in out qualifiers are used to identify the 2,
//else the names need to match

//layout (location=0) in vec3 vInterpolatedColor;
uniform vec3 uColor;

//front buffer is currently drawn
//back buffer is whr shader's data shld be placed
//GL_BACK_LEFT's color buffer index by default is 0, so thats where our data will be placed
layout (location=0) out vec4 fFragColor;

void main(){
    //Same thing, just convert it to a vec4 for color buffer
    fFragColor = vec4(uColor, 1.0);
}