#pragma once

#include "Include.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Renderer.h"

#include "Test.h"

#include "LeafGeneration.h"
#include "RidgeGeneration.h"
#include "Leaf.h"
#include "Branch.h"

namespace test
{
	class TestTreeSpaceColonisation : public Test
	{
	public:
		TestTreeSpaceColonisation();
		
		void Build();
		void Ridge();

		void Grow();
		void Draw();
		//void SetSeed(int seed);

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

		float max_distance = 600 * 600;
		float min_distance = 10;
		float branch_length = 10;
		int tree_number = 4;
		//int tree_number = 2;

		float root_array[8] = { 0.0f, -600.0f, 0.0f, 600.0f, -600.0f, 0.0f, 600.0f, 0.0f };
		//float root_array[4] = { 0.0f, -600.0f, 600.0f, 0.0f };

	private:

		int window_width = 600;
		int window_height = 600;
		//int branch_direction;
		bool finish;

		std::vector<glm::vec2> random_leaves;
		std::vector<glm::vec2> random_ridges;
		std::vector<glm::vec2> ridges;
		std::vector<Leaf> leaves;
		//std::vector<float> position;
		std::vector<std::shared_ptr<Branch>> branches;

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer1;
		std::unique_ptr<VertexBuffer> m_VertexBuffer2;
		std::unique_ptr<VertexBuffer> m_VertexBuffer3;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};
}
