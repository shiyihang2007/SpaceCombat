#ifndef WEAPON_H
#define WEAPON_H

#include "game/bullet_object.h"

#include <vector>

class Weapon {
  public:
	explicit Weapon(BulletObject *prototype)
		: BulletObjectPrototype(prototype) {}
	virtual ~Weapon();

	virtual auto Spawn(glm::vec2 position, glm::vec2 velocity)
		-> BulletObject *;

	void update(float dt, unsigned int window_width,
				unsigned int window_height);

	BulletObject *BulletObjectPrototype;
	std::vector<BulletObject *> BulletObjects;
};

class NullWeapon : public Weapon {
  public:
	NullWeapon() : Weapon(nullptr) {}
	auto Spawn(glm::vec2 position, glm::vec2 velocity)
		-> BulletObject * override {
		return nullptr;
	}
};

extern NullWeapon nullWeapon;

#endif
