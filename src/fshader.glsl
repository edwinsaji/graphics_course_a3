#version 430


out vec4 frag_color;

uniform sampler2D texture;

varying vec2 tex;

void main () 
{
      frag_color = texture2D(texture, tex);
      //frag_color = vec4(1.0f,0.0f,0.0f,1.0f);		
}
