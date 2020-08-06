#pragma once

#include "Include.h"

class Branch
{
	public:
		Branch(glm::vec2 par, glm::vec2 pos, glm::vec2 dir, float height);

		glm::vec2 get_position() const;
		glm::vec2 get_parent() const;
		void set_parent(glm::vec2 new_parent);
		int get_parent_index();
		void set_parent_index(int index);
		glm::vec2 get_direction() const;
		void set_direction(glm::vec2 new_direction);
		float get_count() const;
		void increment_count(int count);
		float get_height() const;
		void reset();

	private:
		glm::vec2 parent_position;
		glm::vec2 position;
		glm::vec2 direction;
		float current_height;

		float counter;
		glm::vec2 original_direction;
		int parent_index;
};

