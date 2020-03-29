#pragma once

#include "Test.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <vector>
#include <ctime>
#include <random>

namespace test
{
	class TestTreeSpaceColonisation : public Test
	{
	public:
		TestTreeSpaceColonisation();
		~TestTreeSpaceColonisation();

		void SetSeed(int seed);

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		void Leaf();
		//void Branch(float posx, float posy, float parent, float direction);

		int window_width = 640;
		int window_height = 480;

		int given_seed = 1;
		int root;
		int branch_direction;

		std::vector<float> leaves;
		//std::vector<float> position;
		std::vector< std::vector<int> > branches;

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};
}
