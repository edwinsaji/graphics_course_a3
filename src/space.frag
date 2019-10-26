#version 430


in vec4 PositionForFragmentShader;
//in vec3 vNormalFragment;
in vec2 texCoordFragment;

uniform sampler2D u_texture;


in vec4 temp_color;

out vec4 color;

void main()
{
	



    color = vec4(temp_color.rgb * texture(u_texture, texCoordFragment).rgb , 1.0f);

    //color = vec4(1.0,1.0,1.0,1.0);
  

    // //temp_color.a = 0.0;

    // color = temp_color;// + vec4(0.5,0.5,0.5,0.0);

}