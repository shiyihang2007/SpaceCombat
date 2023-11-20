
#ifndef PLANEOBJECT_H
#define PLANEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game/weapon.h"
#include "game_object.h"

#include "sprite_renderer.h"
#include "texture.h"

class PlaneObject : public GameObject {
  public:
	static constexpr int defaultHealth = 1;
	// 环境常数
	float velocity = 200.0F; // pixel per second
	static constexpr float ENVIROMENT_F = 0.95F;

	uint health;
	float ultraTick;
	float fireColdDown;

	Weapon *weapon;

	// constructor(s)
	PlaneObject();

	PlaneObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite,
				glm::vec3 color = glm::vec3(1.0F),
				glm::vec2 velocity = glm::vec2(0.0F),
				float rotation = 0.0F, Weapon *weapon = &nullWeapon,
				uint health = defaultHealth, uint ultraTick = 0U);
	// moves the plane (at any specify facing),
	// transport it to the otherside
	// while it go out the window (expect top and bottom);
	auto Move(float dt, glm::vec2 facing) -> glm::vec2;
	// resets the plane to original state with given position and
	// velocity
	void Reset(glm::vec2 position, glm::vec2 velocity);

	void Update(float dt, unsigned int window_width,
				unsigned int window_height) override;

	void Draw(SpriteRenderer &renderer) override;
};

#endif
