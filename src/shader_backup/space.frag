#version 430


in vec4 PositionForFragmentShader;
//in vec3 vNormalFragment;
in vec2 texCoordFragment;

uniform sampler2D u_texture;

//===============================================


uniform vec3  u_CameraPos;      // The camera's current position
uniform vec3  u_LightDir;       // The direction vector to the light source

uniform vec3  u_InvWavelength;  // 1 / pow(wavelength, 4) for the red, green, and blue channels
uniform float u_OuterRadius;    // The outer (atmosphere) radius
uniform float u_InnerRadius;    // The inner (planetary) radius
uniform float u_KrESun;         // Kr * ESun 
uniform float u_KmESun;         // Km * ESun
uniform float u_Kr4PI;          // Kr * 4 * PI
uniform float u_Km4PI;          // Km * 4 * PI
uniform float u_Scale;          // 1 / (u_OuterRadius - u_InnerRadius)
uniform float u_ScaleDepth;     // The scale depth (i.e. the altitude at which the atmosphere's average density is found)
uniform float u_ScaleOverScaleDepth; // u_Scale / u_ScaleDepth

uniform float u_g;

const int   SAMPLES_N = 5;
const float SAMPLES_F = 5.0;

//Kr is rayleigh scattering constant
//Km is mie scattering constant
//Esun is sun brightness constant
//u_g is the g factor for mie scattering

//==================================================================
float ONAS_CalcCamDistanceFromPlanetOrigin()
{
    return length( u_CameraPos );
}

//==================================================================
void ONAS_CalcRayFromCamera(
            vec3 pos,
            out vec3 out_raySta,
            out vec3 out_rayDir )
{
    out_raySta = u_CameraPos;
    out_rayDir = normalize( pos - out_raySta );
}

//==================================================================
void ONAS_CalcRayFromCameraLen(
            vec3 pos,
            out vec3  out_raySta,
            out vec3  out_rayDir,
            out float out_rayLen )
{
    out_raySta = u_CameraPos;

    vec3 raySta_to_pos = pos - out_raySta;

    out_rayLen = length( raySta_to_pos );
    out_rayDir = raySta_to_pos / out_rayLen;
}

//==================================================================
bool ONAS_IsGoodScaleParam( float cosA )
{
    return (1.0 - cosA) < 1.3;
}

//==================================================================
float ONAS_Scale( float cosA )
{
    float x = max( 1.0 - cosA, 0.0 );

    return
        u_ScaleDepth *
            exp( -0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))) );
}

//==================================================================
// http://http.developer.nvidia.com/GPUGems2/elementLinks/0256equ01.jpg
float ONAS_CalcMiePhase( float cosA, float g )
{
    float g2 = g * g;

    float a = 1.0 - g2;
    float b = 2.0 + g2;

    float c = 1.0 + cosA * cosA;
    float d = pow( 1.0 + g2 - 2.0 * g * cosA, 1.5 );

    return (3.0 / 2.0) * a / b * c / d;
}

//==================================================================
// NOTE: assumes that rayDir is normalized
// NOTE: using radius squared
float ONAS_CalcRaySphereClosestInters(
                vec3 raySta,
                vec3 rayDir,
                vec3 sphereC,
                float sphereRSqr )
{
    float B = 2.0 * dot( raySta, rayDir ) - dot( rayDir, sphereC );

    vec3 raySta_to_sphereC = sphereC - raySta;

    float C = dot( raySta_to_sphereC, raySta_to_sphereC ) - sphereRSqr;

    float det = max( 0.0, B*B - 4.0 * C );

    return 0.5 * ( -B - sqrt( det ) );
}

//=================================================================sw

out vec4 color;

void main()
{
	vec3 pos = PositionForFragmentShader.xyz;

    vec3 raySta;
    vec3 rayDir;
    ONAS_CalcRayFromCamera( pos, raySta, rayDir );

    vec3 start = raySta;

    if ( length( u_CameraPos ) >= u_OuterRadius )
    {
        // Calculate the farther intersection of the ray with the outer atmosphere
        // (which is the far point of the ray passing through the atmosphere)
        float near = ONAS_CalcRaySphereClosestInters(
                            raySta,
                            rayDir,
                            vec3(0.0, 0.0, 0.0),
                            u_OuterRadius * u_OuterRadius );

        start += rayDir * near;
    }

    // Calculate attenuation from the camera to the top of the atmosphere toward the vertex
    float height = length(start);
    float useOuterRadius = ONAS_CalcCamDistanceFromPlanetOrigin();
    float depth = exp( u_ScaleOverScaleDepth * (u_InnerRadius - useOuterRadius) );
    float angle = dot(rayDir, start) / height;
    float scatter = depth * ONAS_Scale( angle );
    vec4 temp_color = vec4 (exp(-scatter * (u_InvWavelength * u_Kr4PI + u_Km4PI)) , 1.0f );

    temp_color *= texture(u_texture, texCoordFragment);

    color = temp_color// + vec4(0.5,0.5,0.5,0.0)
    ;

}