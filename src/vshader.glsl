#version 430

in vec4 vPosition;
in vec2 texCoord;
//in vec3 vNormal;

varying vec2 tex;

// uniform mat4 uModelViewMatrix;
// uniform mat3 normalMatrix;
uniform mat4 viewMatrix;

void main (void) 
{
  gl_Position = viewMatrix * vPosition;
  tex = texCoord;
}
