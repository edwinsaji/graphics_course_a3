

class ONAS_state
{

public:



	constexpr static float INNER_RAD_TO_OUTER_SCALE = 1.025f;

	float m_Kr      =  0.0025f; // Rayleigh scattering constant
	float m_Km      =  0.0010f; // Mie scattering constant
	float m_ESun    =  20.0f;   // Sun brightness constant
	float m_g       = -0.990f;  // The Mie phase asymmetry factor
								// the g-factor for rayleigh scattering is taken as zero (check!!) 

	float m_InnerRadius        = 1.0f;
	float m_OuterRadius        = 1.0f * INNER_RAD_TO_OUTER_SCALE;
	float m_Wavelength[3]      = {0,0,0};
	float m_RayleighScaleDepth = 0;
	float m_MieScaleDepth      = 0;

	float lightDir[3];

	ONAS_state()
    {
    	m_InnerRadius = 1.0f;

        m_Wavelength[0] = 0.650f;		// 650 nm for red
        m_Wavelength[1] = 0.570f;		// 570 nm for green
        m_Wavelength[2] = 0.475f;		// 475 nm for blue

        m_RayleighScaleDepth = 0.25f;
        m_MieScaleDepth = 0.1f;
    }

};