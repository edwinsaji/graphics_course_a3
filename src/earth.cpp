#include "earth.hpp"
#include "texture.hpp"


void earth::create_vertices (float _radius = 1.0f)
{
	radius = _radius;


	float PI = glm::pi<float>();
	//we will assume radius of 1 for this sphere. 

	float lats,longs;

	// float slices=(180/(float(Lats)*10))/2;
	// float sectors=(180/(float(Longs)*10))/2;

	float slices = 2.0 * PI/float(no_of_lats);
	float sectors = PI / float(no_of_longs);

	float l;

	for (lats = 0.0; lats <= PI; lats+=sectors)  
	{
		for(longs = 0.0; longs <= 2.0*PI; longs+=slices)
		{
			float x = radius * sin(lats) * cos(longs);
			float y = radius * sin(lats) * sin(longs);
			float z = radius * cos(lats);
			glm::vec4 pt(x, y, z, 1.0);

			vertices.push_back(pt);
			texture.push_back( glm::vec2( 1.0-longs/(2*PI) , lats/PI ) );


			if(lats+sectors>PI)
				l=PI;
			else
				l=lats+sectors;


			x = radius * sin(l) * cos(longs);
			y = radius * sin(l) * sin(longs);
			z = radius * cos(l);
			pt =glm::vec4(x, y, z, 1.0);

			vertices.push_back(pt);
			texture.push_back( glm::vec2( 1.0-longs/(2*PI) , l/PI ) );


		}
	}

	std::cout<<"\n"<<indices.size()<<"\n"<<texture.size()<<"\n"<<vertices.size()<<"\n";

}


void earth::init_buffers(GLuint _shaderProgram)
{
	shaderProgram = _shaderProgram;

	//creating vao
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);

	//vertex coordinates
	glGenBuffers (1, &vbo);
  	glBindBuffer (GL_ARRAY_BUFFER, vbo);
  	glBufferData (GL_ARRAY_BUFFER, vertices.size()*sizeof (glm::vec4), vertices.data(), GL_STATIC_DRAW);

  	GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	glEnableVertexAttribArray( vPosition );
	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	//texture coordinates
	glGenBuffers (1, &texture_id);
  	glBindBuffer (GL_ARRAY_BUFFER, texture_id);
  	glBufferData (GL_ARRAY_BUFFER, texture.size()*sizeof (glm::vec2), texture.data(), GL_STATIC_DRAW);

  	GLuint texCoord = glGetAttribLocation( shaderProgram, "texCoord" );
	glEnableVertexAttribArray( texCoord );
	glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

 //  	// Generate a buffer for the indices
	// glGenBuffers(1, &index);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	//load texture
	texture_id = LoadTexture("../textures/highres.bmp",16200,8100);

}

void earth::draw()
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glBindVertexArray(vao);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	//glDrawElements(GL_TRIANGLES, indices.size() , GL_UNSIGNED_INT, 0);
	glDrawArrays( GL_TRIANGLE_STRIP, 0,  vertices.size() ) ;
}