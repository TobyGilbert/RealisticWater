#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 texCoords;

uniform mat4 MVP;
uniform float uniTime;
out vec2 TexCoords;

out float time;
out vec4 pos;

void main()
{
  vec4 vertex = vec4(vertexPosition, 1.0);

  gl_Position = MVP * vec4(vertexPosition, 1.0);

  vec4 newPos = vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0);
  pos = MVP * newPos;

  TexCoords = texCoords;
  time = uniTime / 20000.0;
}
