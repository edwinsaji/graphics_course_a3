#version 430


in vec4 PositionForFragmentShader;
//in vec3 vNormalFragment;
in vec2 texCoordFragment;

uniform sampler2D u_texture;


in vec4 temp_color;

out vec4 color;

void main()
{
	



    color = temp_color * texture(u_texture, texCoordFragment);

    // //temp_color.a = 0.0;

    // color = temp_color;// + vec4(0.5,0.5,0.5,0.0);

}