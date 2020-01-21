#include <Game.h>

static bool flip;

float vertices[24] =
					{ -1.0f, -1.0f, 1.0f,
						1.0f, -1.0f, 1.0f,
						1.0f, 1.0f, 1.0f,
						-1.0f, 1.0f, 1.0f,

						-1.0f, -1.0f, -1.0f,
						1.0f, -1.0f, -1.0f,
						1.0f, 1.0f, -1.0f,
						-1.0f, 1.0f, -1.0f };

Vector3 m_points[] = { { vertices[0], vertices[1] , vertices[2] },
						{ vertices[3], vertices[4] , vertices[5] },
						{ vertices[6], vertices[7] , vertices[8] },
						{ vertices[9], vertices[10] , vertices[11] },
						{ vertices[12], vertices[13] , vertices[14] },
						{ vertices[15], vertices[16] , vertices[17] },
						{ vertices[18], vertices[19] , vertices[20] },
						{ vertices[21], vertices[22] , vertices[23] } };

Game::Game() : window(sf::VideoMode(800, 600), "OpenGL Cube VBO")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) {

		std::cout << "Game running..." << std::endl;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[3];
} Vertex;

Vertex vertex[8];
GLubyte triangles[36];

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	isRunning = true;
	glTranslatef(0.0f, 0.0f, -8.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);

	glewInit();

	/* Vertices counter-clockwise winding */

	vertex[0].coordinate[0] = vertices[0];
	vertex[0].coordinate[1] = vertices[1];
	vertex[0].coordinate[2] = vertices[2];

	vertex[1].coordinate[0] = vertices[3];
	vertex[1].coordinate[1] = vertices[4];
	vertex[1].coordinate[2] = vertices[5];

	vertex[2].coordinate[0] = vertices[6];
	vertex[2].coordinate[1] = vertices[7];
	vertex[2].coordinate[2] = vertices[8];

	vertex[3].coordinate[0] = vertices[9];
	vertex[3].coordinate[1] = vertices[10];
	vertex[3].coordinate[2] = vertices[11];

	vertex[4].coordinate[0] = vertices[12];
	vertex[4].coordinate[1] = vertices[13];
	vertex[4].coordinate[2] = vertices[14];

	vertex[5].coordinate[0] = vertices[15];
	vertex[5].coordinate[1] = vertices[16];
	vertex[5].coordinate[2] = vertices[17];



	vertex[6].coordinate[0] = vertices[18];
	vertex[6].coordinate[1] = vertices[19];
	vertex[6].coordinate[2] = vertices[20];

	vertex[7].coordinate[0] = vertices[21];
	vertex[7].coordinate[1] = vertices[22];
	vertex[7].coordinate[2] = vertices[23];


	vertex[0].color[0] = 0.1f;
	vertex[0].color[1] = 1.0f;
	vertex[0].color[2] = 0.0f;

	vertex[1].color[0] = 0.2f;
	vertex[1].color[1] = 1.0f;
	vertex[1].color[2] = 0.0f;

	vertex[2].color[0] = 0.3f;
	vertex[2].color[1] = 1.0f;
	vertex[2].color[2] = 0.0f;

	vertex[3].color[0] = 0.4f;
	vertex[3].color[1] = 1.0f;
	vertex[3].color[2] = 0.0f;

	vertex[4].color[0] = 0.5f;
	vertex[4].color[1] = 1.0f;
	vertex[4].color[2] = 0.0f;

	vertex[5].color[0] = 0.6f;
	vertex[5].color[1] = 1.0f;
	vertex[5].color[2] = 0.0f;

	vertex[6].color[0] = 0.8f;
	vertex[6].color[1] = 0.498039f;
	vertex[6].color[2] = 0.196078f;

	vertex[7].color[0] = 1.0f;
	vertex[7].color[1] = 1.0f;
	vertex[7].color[2] = 1.0f;

	vertex[8].color[0] = 1.0f;
	vertex[8].color[1] = 0.5f;
	vertex[8].color[2] = 0.0f;

	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;
	triangles[3] = 2;   triangles[4] = 3;   triangles[5] = 0;
	triangles[6] = 2;   triangles[7] = 6;   triangles[8] = 3;
	triangles[9] = 6;   triangles[10] = 7;   triangles[11] = 3;
	triangles[12] = 7;   triangles[13] = 6;   triangles[14] = 5;
	triangles[15] = 5;   triangles[16] = 4;   triangles[17] = 7;
	triangles[18] = 5;   triangles[19] = 0;   triangles[20] = 4;
	triangles[21] = 5;   triangles[22] = 1;   triangles[23] = 0;
	triangles[24] = 1;   triangles[25] = 5;   triangles[26] = 6;
	triangles[27] = 6;   triangles[28] = 2;   triangles[29] = 1;
	triangles[30] = 4;   triangles[31] = 0;   triangles[32] = 3;
	triangles[33] = 3;   triangles[34] = 7;   triangles[35] = 4;

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	controlCube();


	std::cout << "Update up" << std::endl;
}

void Game::render()
{
	std::cout << "Drawing" << std::endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glTranslatef(-8.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain 
		model compoents that are and are not to be drawn )	*/
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();

}

void Game::unload()
{
	std::cout << "Cleaning up" << std::endl;

	glDeleteBuffers(1, vbo);
}

void Game::controlCube()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::RotationX(rotationAngle) * m_points[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::RotationX(-rotationAngle) * m_points[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::RotationY(rotationAngle) * m_points[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::RotationY(-rotationAngle) * m_points[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::RotationZ(rotationAngle) * m_points[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::RotationZ(-rotationAngle) * m_points[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		for (int i = 0; i < 8; i++)
		{
			float temp = m_points[i].Z;
			m_points[i].Z = 1;
			m_points[i] = Matrix3::Translate(0, 0.001f) * m_points[i];

			m_points[i].Z = temp;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		for (int i = 0; i < 8; i++)
		{
			float temp = m_points[i].Z;
			m_points[i].Z = 1;
			m_points[i] = Matrix3::Translate(0, -0.001f) * m_points[i];

			m_points[i].Z = temp;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		for (int i = 0; i < 8; i++)
		{
			float temp = m_points[i].Z;
			m_points[i].Z = 1;
			m_points[i] = Matrix3::Translate(-0.001f, 0) * m_points[i];

			m_points[i].Z = temp;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		for (int i = 0; i < 8; i++)
		{
			float temp = m_points[i].Z;
			m_points[i].Z = 1;
			m_points[i] = Matrix3::Translate(0.001f, 0) * m_points[i];

			m_points[i].Z = temp;
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::Scale3D(100.05) * m_points[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3::Scale3D(99.95) * m_points[i];
		}
	}

	for (int i = 0, j = 0; i < 8, j < 24; i++)
	{
		vertex[i].coordinate[0] = m_points[i].X;
		j++;
		vertex[i].coordinate[1] = m_points[i].Y;
		j++;
		vertex[i].coordinate[2] = m_points[i].Z;
		j++;
	}
}
