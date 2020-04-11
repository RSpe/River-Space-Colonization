#pragma once

#include "TestTreeSpaceColonisation.h"

class Branch
{
	public:
		Branch(glm::vec2 pos, glm::vec2 parent_pos, glm::vec2 dir);
		glm::vec2 get_position() const;
		glm::vec2 get_parent() const;
		glm::vec2 get_direction() const;
	private:
		glm::vec2 position;
		glm::vec2 parent_position;
		glm::vec2 direction;
};

