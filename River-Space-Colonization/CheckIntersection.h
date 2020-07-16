#pragma once

#include "Include.h"

class CheckIntersection
{
public:
	static const bool check_intersection(glm::vec2 p1, glm::vec2 p2, glm::vec2 q1, glm::vec2 q2);
private:
	static int orientation(glm::vec2 p, glm::vec2 q, glm::vec2 r);
	static bool onSegment(glm::vec2 p, glm::vec2 q, glm::vec2 r);
};


