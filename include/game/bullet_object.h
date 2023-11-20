#ifndef WEAPON_OBJECT_H
#define WEAPON_OBJECT_H

#include "game/game_object.h"

class BulletObject : public GameObject {
  public:
	BulletObject(glm::vec2 size, Texture2D sprite)
		: GameObject(glm::vec2(0.0F), size, sprite) {}
	virtual ~BulletObject() = default;

	void Update(float dt, unsigned int window_width,
				unsigned int window_height) override;
};

#endif
