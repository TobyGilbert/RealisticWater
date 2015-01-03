#version 400

out vec4 fragColour;

in vec2 TexCoords;

uniform sampler2D reflect;
uniform sampler2D refract;

void main(){
  fragColour = texture(refract, TexCoords);// + texture(refract, TexCoords);
}

