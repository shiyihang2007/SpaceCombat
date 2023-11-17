
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

// clang-format off
#include <glad/glad.h>
#include <glm/glm.hpp>
// clang-format on

#include "sprite_renderer.h"
#include "texture.h"

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject {
  public:
	// object state
	glm::vec2 Position, Size, Velocity;
	glm::vec3 Color;
	float Rotation;
	// render state
	Texture2D Sprite;
	// constructor(s)
	GameObject();
	GameObject(
		glm::vec2 pos, glm::vec2 size, Texture2D sprite,
		glm::vec3 color = glm::vec3(1.0F),
		glm::vec2 velocity = glm::vec2(0.0F, 0.0F),
		void (*update)(GameObject *self, float dt, unsigned int window_width,
					   unsigned int window_height) =
			[](GameObject *self, float dt, unsigned int window_width,
			   unsigned int window_height) {});
	// update
	void (*update)(GameObject *self, float dt, unsigned int window_width,
				   unsigned int window_height);
	// draw sprite
	virtual void Draw(SpriteRenderer &renderer);
};

#endif
