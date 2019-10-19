

	void earth::create_vertices (float _radius = 1.0f)
{
	radius = _radius;

	//we will assume radius of 1 for this sphere. 

	//initial top most point will be north pole
	glm::vec4 north_pole(0.0f,0.0f,radius,1.0f);
	glm::vec4 south_pole(0.0f,0.0f,-radius,1.0f);

	vertices.push_back( north_pole );
	texture.push_back ( glm::vec2(0.0f,0.0f) ); //remember the picture is sorta upside down

	//we know it is a plate caree projection ...

	for(unsigned int lat=1 ; lat < no_of_lats ; ++lat )
	{
		for (unsigned int longit = 0; longit < no_of_longs ; ++longit)
		{
			float theta = lat * ( glm::pi<float>() / no_of_lats );


			float phi = 2 * longit * ( glm::pi<float>() / no_of_longs );


			vertices.push_back( glm::vec4( radius*glm::sin(theta)*glm::cos(phi), radius*glm::sin(theta)*glm::cos(phi) , radius*glm::cos(theta) , 1.0f ) );
			texture.push_back( glm::vec2( ((float)longit) / no_of_longs , ((float)lat) / no_of_lats ) );
		}
	}

	vertices.push_back( south_pole );
	texture.push_back( glm::vec2(0.0f,1.0f) );


	//now making the index buffer for use with GL_triangles

	//indices.push_back(0);
	//lat=1 is a special case

	for(unsigned int longit = 0; longit < no_of_longs-1 ; ++longit)
	{	
		indices.push_back(0);//north_pole
		indices.push_back( longit + 1); //this will give longitudinal points on the first latitude
		indices.push_back( longit + 1 +1);
	} 

	//last case for first longitude
	indices.push_back(0);
	indices.push_back( no_of_longs-1 + 1 );
	indices.push_back( 0 + 1);



	for(int lat=1 ; lat < no_of_lats-1 ; ++lat )
	{
		unsigned int lat0_offset = 1 + (lat-1)*no_of_longs ;
		unsigned int lat1_offset = 1 + (lat)*no_of_longs;

		for(int longit = 0; longit < no_of_longs-1 ; ++longit)
		{
			

			indices.push_back( lat0_offset + longit );
			indices.push_back( lat1_offset + longit );
			indices.push_back( lat1_offset + longit +1);

			indices.push_back( lat1_offset + longit +1 );
			indices.push_back( lat0_offset + longit );
			indices.push_back( lat0_offset + longit +1);
		} 

		indices.push_back( lat0_offset + no_of_longs-1 );
		indices.push_back( lat1_offset + no_of_longs-1 );
		indices.push_back( lat1_offset + 0);

		indices.push_back( lat1_offset + 0 );
		indices.push_back( lat0_offset + no_of_longs-1 );
		indices.push_back( lat0_offset + 0);

	}


	{
		unsigned int lat0_offset = 1 + ( no_of_lats-1 -1)*no_of_longs ;
		unsigned int lat1_offset = 1 + ( no_of_lats-1 )*no_of_longs;

		for(unsigned int longit = 0; longit < no_of_longs-1 ; ++longit)
		{	
			indices.push_back(lat1_offset);//southpole
			indices.push_back(lat0_offset + longit);
			indices.push_back(lat0_offset + longit +1 );

		} 

		//last case
		indices.push_back(lat1_offset);//southpole
		indices.push_back(lat0_offset + no_of_longs-1);
		indices.push_back(lat0_offset + 0);

	}

	std::cout<<"\n"<<indices.size()<<"\n"<<texture.size()<<"\n"<<vertices.size()<<"\n";

}