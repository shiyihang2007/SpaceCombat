
#include "game/weapon.h"
#include "game/bullet_object.h"

#include "spdlog/spdlog.h"

#include <vector>

Weapon::~Weapon() {
	for (auto &i : this->BulletObjects) {
		delete i;
	}
}

auto Weapon::Spawn(glm::vec2 position, glm::vec2 velocity)
	-> BulletObject * {
	this->BulletObjects.emplace_back(
		new BulletObject(*this->BulletObjectPrototype));
	this->BulletObjects.back()->Position = position;
	this->BulletObjects.back()->Velocity = velocity;
	return this->BulletObjects.back();
}

void Weapon::update(float dt, unsigned int window_width,
					unsigned int window_height) {
	for (auto &i : this->BulletObjects) {
		i->Update(dt, window_width, window_height);
	}
	for (auto it = this->BulletObjects.begin();
		 it != this->BulletObjects.end(); ++it) {
		auto &i = *it;
		if (i->Position.x > static_cast<float>(window_width) ||
			i->Position.x < 0 ||
			i->Position.y > static_cast<float>(window_height) ||
			i->Position.y < 0) {
			delete i;
			auto tmp = it;
			--it;
			this->BulletObjects.erase(tmp);
		}
	}
}

NullWeapon nullWeapon;
