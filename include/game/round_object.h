
#ifndef ROUNDOBJECT_H
#define ROUNDOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "texture.h"

// RoundObject holds the state of the Rounded object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to rounded object that
// were too specific for within GameObject alone.
class RoundObject : public GameObject {
  public:
	float Radius;
	// constructor(s)
	RoundObject();
	RoundObject(glm::vec2 pos, float radius, glm::vec2 velocity,
				Texture2D sprite);
	// moves the ball,
	// keeping it constrained within the window bounds (except bottom edge);
	// returns new position
	auto Move(float dt, unsigned int window_width) -> glm::vec2;
	// resets the ball to original state with given position and velocity
	void Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif
