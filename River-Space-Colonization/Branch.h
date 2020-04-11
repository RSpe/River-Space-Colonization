#pragma once

#include "Include.h"

class Branch
{
	public:
		Branch(std::shared_ptr<Branch> par, glm::vec2 pos, glm::vec2 dir);
		glm::vec2 get_position() const;
		std::shared_ptr<Branch> get_parent() const;
		glm::vec2 get_direction() const;
	private:
		glm::vec2 position;
		std::shared_ptr<Branch> parent;
		glm::vec2 direction;
};

