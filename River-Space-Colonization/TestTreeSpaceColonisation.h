#pragma once

#include "Include.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
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
		~TestTreeSpaceColonisation();

		void SetSeed(int seed);

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

		int max_dist = 500;
		int min_dist = 10;
	private:

		int window_width = 640;
		int window_height = 480;
		int branch_direction;

		std::vector<glm::vec2> random_leaves;
		std::vector<Leaf> leaves;
		//std::vector<float> position;
		std::vector<std::shared_ptr<Branch>> branches;

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};
}
