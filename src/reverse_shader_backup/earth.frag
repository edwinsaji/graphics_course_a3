#version 430

uniform sampler2D u_texture;



in vec4 PositionForFragmentShader;
in vec3 vNormalFragment;
in vec2 texCoordFragment;

out vec4 color;





in vec3 v_groundCol, v_attenuation;



void main()
{

 
    

    vec4 outCol;

    outCol = vec4(v_groundCol + texture( u_texture , texCoordFragment).rgb * v_attenuation , 1.0);


    //overwrite nan with debug color
    if ( ( outCol != outCol ) )
        outCol = vec4( 1.0, 0.0, 1.0, 1.0 );


    color = outCol ;


}


