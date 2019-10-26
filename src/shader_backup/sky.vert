#version 430




layout (location=0) in vec4 vPosition;
//layout (location=1) in vec3 vNormal;
//layout (location=2) in vec2 texCoord;


uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;
//uniform vec3 u_CameraPosition;//in WCS

out vec4 PositionForFragmentShader;
//out vec3 vNormalFragment;
//out vec2 texCoordFragment;



void main()
{
	PositionForFragmentShader = vPosition;
	

	gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vPosition;
}