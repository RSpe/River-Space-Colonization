#include "Branch.h"

Branch::Branch(std::shared_ptr<Branch> par, glm::vec2 pos, glm::vec2 dir)
{
	parent = par;
	position = pos;
	direction = dir;
	counter = 0;
	original_direction = dir;
}

glm::vec2 Branch::get_position() const
{
	return this->position;
}

std::shared_ptr<Branch> Branch::get_parent() const
{
	return this->parent;
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
	this->direction = this->original_direction;
	this->counter = 0;
}