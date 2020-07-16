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
#include "CheckIntersection.h"

namespace test
{
	class TestTreeSpaceColonisation : public Test
	{
	public:

		TestTreeSpaceColonisation();
		
		void Build();
		//void Ridge();

		void Grow();
		void Draw();
		//void SetSeed(int seed);

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

		int leaves_to_generate = 150;

		float max_distance = 100;
		float min_distance = 0.01;
		float branch_length = 0.02;
		float min_x_point = -500;
		float max_x_point = 500;
		float min_y_point = -500;
		float max_y_point = 500;
		int tree_number = 2;
		int ridge_number = 3;
		int ridge_definition = 4;
		double set_seed = 1000000;

		int check_leaf_change = 0;
		int check_branch_change = 0;
		int no_change_count = 0;

	private:

		int window_width = 600;
		int window_height = 600;

		bool finish;

		std::vector<glm::vec2> random_leaves;
		std::vector<glm::vec2> random_roots;
		std::vector<std::vector<glm::vec2>> random_ridges;
		std::vector<glm::vec2> random_ridges_1d;
		std::vector<glm::vec2> ridges;
		std::vector<Leaf> leaves;
		std::vector<std::shared_ptr<Branch>> branches;
		
		std::vector<glm::vec2> branch_pos;

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer1;
		std::unique_ptr<VertexBuffer> m_VertexBuffer2;
		std::unique_ptr<VertexBuffer> m_VertexBuffer3;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};
}
