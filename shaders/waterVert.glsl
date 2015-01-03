#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 texCoords;

uniform mat4 MVP;
out vec2 TexCoords;


void main(){
  TexCoords = texCoords;
  gl_Position = MVP * vec4(vertexPosition, 1.0);
}


