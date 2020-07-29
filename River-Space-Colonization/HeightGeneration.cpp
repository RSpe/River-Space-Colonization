#include "HeightGeneration.h"

const std::vector<glm::vec2> HeightGeneration::create_base_heights(int window_width, int window_height, int min_x_point, int max_x_point, int min_y_point, int max_y_point)
{
	//unsigned int pbo;

	//glGenBuffers(1, &pbo);

	std::vector<glm::vec2> height_map;
	//GLenum *hello[1000];

	//int count_255 = 0;
	//int count_1 = 0;
	//int count_0 = 0;

	//int pixels[1000];

	//glReadBuffer(GL_FRONT);
	//glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo);
	//glReadPixels(0, 0, window_width - 50, window_height - 50, GL_BGRA, GL_UNSIGNED_BYTE, 0);
	//glMapBuffer(GL_PIXEL_PACK_BUFFER, hello);

	//for (int y = 0; y < window_height - 50; ++y)
	//{
	//	for (int x = 0; x < window_width - 50; ++x)
	//	{
	//		std::cout << pbo << std::endl;
	//	}
	//}
	//for (int y = 0; y < window_height - 50; ++y)
	//{
	//	for (int x = 0; x < window_width - 50; ++x)
	//	{
	//		unsigned char colour[3];

	//		//glFlush();
	//		//glReadBuffer(GL_DEPTH);
	//		glReadPixels(0, 0, window_width - 50, window_height - 50, GL_BGRA, GL_UNSIGNED_BYTE, 0);
	//		std::cout << (int)colour[0] << (int)colour[1] << (int)colour[2] << std::endl;
	//		//if (colour[0] == 255.0f && colour[1] == 255.0f && colour[2] == 255.0f)
	//		//{
	//		//	height_map.push_back(0);
	//		//	
	//		//}
	//		//else if (colour[0] == 0.001f && colour[1] == 1.0f && colour[2] == 0.5f)
	//		//{
	//		//	height_map.push_back(1);
	//		//}
	//	}
	//}
	//unsigned int fbo;
	//glGenFramebuffers(1, &fbo);
	//glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glReadBuffer(GL_FRONT);

	GLfloat pixels[50][50][3];

	int read_point_x = (window_width / 2) - (max_x_point / 2);
	int read_point_y = (window_height / 2) - (max_y_point / 2);

	glReadPixels(read_point_x, read_point_y, max_x_point, max_y_point, GL_RGB, GL_FLOAT, &pixels);

	//std::cout << sizeof(pixels) / sizeof(float) << std::endl;
	//int count_y = 0;
	//int count_x = 1;

	for (int i = max_y_point - 1; i > 0 ; --i)
	{
		for (int j = 0; j < max_x_point; ++j)
		{
			if (j < max_x_point - 1)
			{
				std::cout << pixels[i][j - 1][0] << " ";
			}
			else
			{
				std::cout << pixels[i][j][0] << std::endl;
			}
			
		}
	}


	return height_map;
}