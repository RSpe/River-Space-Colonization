#pragma once

#include "Include.h"

class Branch
{
	public:
		Branch(std::shared_ptr<Branch> par, glm::vec2 pos, glm::vec2 dir);

		glm::vec2 get_position() const;
		std::shared_ptr<Branch> get_parent() const;
		glm::vec2 get_direction() const;
		void set_direction(glm::vec2 new_direction);
		float get_count() const;
		void increment_count(int count);
		void reset();

	private:
		std::shared_ptr<Branch> parent;
		glm::vec2 position;
		glm::vec2 direction;

		float counter;
		glm::vec2 original_direction;
};

