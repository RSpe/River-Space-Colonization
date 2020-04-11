#pragma once

#include "Include.h"

class Leaf
{
	public:
		Leaf(glm::vec2 pos);

		glm::vec2 get_position() const;
		void set_reached();
		bool get_reached() const;

	private:
		std::vector<glm::vec2> leaves;
		glm::vec2 position;

		bool reached;
};

