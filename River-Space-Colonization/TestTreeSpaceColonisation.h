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
#include "HeightGeneration.h"

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

		int leaves_to_generate = 25;

		float max_distance = 100;
		float min_distance = 0.01;
		float branch_length = 0.02;
		float min_x_point = -100;
		float max_x_point = 100;
		float min_y_point = -100;
		float max_y_point = 100;
		int tree_number = 2;
		int ridge_number = 2;
		int ridge_definition = 4;
		double set_seed = 100000000;

		std::vector<float> leaf_colour = { 0.1f, 0.2f, 0.3f, 1.0f };
		std::vector<float> tree_colour = { 0.0f, 1.0f, 1.0f, 1.0f };
		std::vector<float> ridge_colour = { 1.0f, 0.0f, 0.0f, 1.0f };

	private:

		static const int window_width = 600;
		static const int window_height = 600;

		int check_leaf_change;
		int check_branch_change;
		int no_change_count = 0;

		bool finish;
		int generate_height_map = 0;

		std::vector<int> height_map;
		std::vector<glm::vec2> location_map;
		//float height_map[window_width * window_height] = {0};

		std::vector<glm::vec2> random_leaves;
		std::vector<glm::vec2> random_roots;
		std::vector<std::vector<glm::vec2>> random_ridges;
		std::vector<glm::vec2> random_ridges_1d;
		std::vector<glm::vec2> leaf_pos;
		std::vector<glm::vec2> ridges;
		std::vector<Leaf> leaves;
		std::vector<std::shared_ptr<Branch>> branches;
		
		std::vector<glm::vec2> branch_pos;
		std::vector<float> branch_height;

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer1;
		std::unique_ptr<VertexBuffer> m_VertexBuffer2;
		std::unique_ptr<VertexBuffer> m_VertexBuffer3;
		std::unique_ptr<VertexBuffer> m_VertexBuffer4;
		std::unique_ptr<VertexBuffer> m_VertexBuffer5;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

		//std::vector<float> height_map;
	};
}
