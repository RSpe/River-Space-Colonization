#include "Branch.h"

Branch::Branch(glm::vec2 par, glm::vec2 pos, glm::vec2 dir)
{
	parent_position = par;
	position = pos;
	direction = dir;
	counter = 0;
	original_direction = dir;
	parent_index;
}

glm::vec2 Branch::get_position() const
{
	return this->position;
}

glm::vec2 Branch::get_parent() const
{
	return this->parent_position;
}

void Branch::set_parent(glm::vec2 new_parent)
{
	this->parent_position = new_parent;
}

int Branch::get_parent_index()
{
	return this->parent_index;
}

void Branch::set_parent_index(int index)
{
	this->parent_index = index;
}

glm::vec2 Branch::get_direction() const
{
	return this->direction;
}

void Branch::set_direction(glm::vec2 new_direction)
{
	this->direction = new_direction;
}

float Branch::get_count() const
{
	return this->counter;
}

void Branch::increment_count(int count)
{
	this->counter += count;
}

void Branch::reset() 
{
	set_direction(original_direction);
	this->counter = 0;
}