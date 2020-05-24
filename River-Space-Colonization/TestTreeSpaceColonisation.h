#pragma once

#include "Include.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Renderer.h"

#include "Test.h"

#include "Leaf.h"
#include "LeafGeneration.h"
#include "Branch.h"

namespace test
{
	class TestTreeSpaceColonisation : public Test
	{
	public:
		TestTreeSpaceColonisation();
		
		void Grow();
		void Build();
		void Draw();
		void SetSeed(int seed);

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

		float max_distance = 200;
		float min_distance = 10;
		float branch_length = 10;
	private:

		int window_width = 600;
		int window_height = 600;
		//int branch_direction;
		bool finish;

		std::vector<glm::vec2> random_leaves;
		std::vector<Leaf> leaves;
		//std::vector<float> position;
		std::vector<std::shared_ptr<Branch>> branches;

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer1;
		std::unique_ptr<VertexBuffer> m_VertexBuffer2;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};
}
