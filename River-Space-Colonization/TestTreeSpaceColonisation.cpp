#include "TestTreeSpaceColonisation.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator

namespace test
{
	struct Branch {
		float positionx;
		float positiony;
		float parent;
		float directionx;
		float directiony;
	};

	TestTreeSpaceColonisation::TestTreeSpaceColonisation()
	{
		Leaf();

		float positions[200];
		std::copy(leaves.begin(), leaves.end(), positions);

		float posx = window_width / 2;
		float posy = window_height / 2;
		float directx = 0;
		float directy = -1;

		Branch root = { posx, posy, 0, directx, directy };

		


		
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 100 * 2 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_Shader = std::make_unique<Shader>("River.shader");
		m_Shader->Bind();
		/* Have to call uniforms after a shader is bound */
		m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	}

	TestTreeSpaceColonisation::~TestTreeSpaceColonisation()
	{

	}

	void TestTreeSpaceColonisation::SetSeed(int seed)
	{
		given_seed = seed;
	}

	void TestTreeSpaceColonisation::Leaf()
	{
		/* Range of vertex values that can be drawn */
		int low = -1;
		int high = 1;

		srand(given_seed);

		for (int i = 0; i < 100; i++)
		{
			float leaf_position_width = low + static_cast<float>(rand())/(static_cast<float>(RAND_MAX/(high - low)));
			float leaf_position_height = low + static_cast<float>(rand())/(static_cast<float>(RAND_MAX/(high - low)));
			leaves.push_back(leaf_position_width);
			leaves.push_back(leaf_position_height);
		}
	}

	//void TestTreeSpaceColonisation::Branch(float posx, float posy, float parent, float direction) 
	//{


	//}

	void TestTreeSpaceColonisation::OnUpdate(float deltaTime)
	{

	}

	void TestTreeSpaceColonisation::OnRender()
	{
		GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_Shader->Bind();
		m_VAO->Bind();

		GLCall(glPointSize(3));
		GLCall(glDrawArrays(GL_POINTS, 0, 100));

	}

	void TestTreeSpaceColonisation::OnImGuiRender()
	{

	}

}