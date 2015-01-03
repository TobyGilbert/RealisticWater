#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;


out vec3 position;
out vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;
//float gl_ClipDistance[1];

void main(){

   //gl_ClipDistance[0] = dot(modelMatrix * vec4(vertexPosition, 1.0), vec4(0.0, 1.0, 0.0, 0.0));
   normal = normalize(normalMatrix * vertexNormal);
   position = vec3(modelViewMatrix * vec4(vertexPosition, 1.0));
   gl_Position = modelViewProjectionMatrix * vec4(vertexPosition,1.0);
}
