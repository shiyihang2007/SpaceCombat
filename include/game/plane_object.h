
#ifndef PLANEOBJECT_H
#define PLANEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "texture.h"

// RoundObject holds the state of the Rounded object inheriting
// relevant state data from GameObject.
// Contains some extra functionality specific to rounded object that
// were too specific for within GameObject alone.
class PlaneObject : public GameObject {
  public:
	static constexpr int defaultHealth = 1;
	// 环境常数
	static constexpr float VELOCITY = 200.0F; // pixel per second
	static constexpr float ENVIROMENT_F = 0.95F;
	uint health;
	float ultraTick;

	// constructor(s)
	PlaneObject();
	PlaneObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite,
				glm::vec3 color = glm::vec3(1.0F),
				glm::vec2 velocity = glm::vec2(0.0F, 0.0F));
	// moves the plane (at any specify facing),
	// transport it to the otherside
	// while it go out the window (expect top and bottom);
	auto Move(float dt, glm::vec2 facing) -> glm::vec2;
	// resets the plane to original state with given position and velocity
	void Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif
