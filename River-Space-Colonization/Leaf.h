#pragma once

#include "TestTreeSpaceColonisation.h"

class Leaf
{
	public:
		Leaf(glm::vec2 pos);
		glm::vec2 get_position() const;

	private:
		std::vector<glm::vec2> leaves;
		glm::vec2 position;
};

