
#include "game/bullet_object.h"

#include "spdlog/spdlog.h"

void BulletObject::Update(float dt, unsigned int window_width,
						  unsigned int window_height) {
	this->Position += this->Velocity * dt;
	// spdlog::debug(
	// 	"BulletObject::Update velocity: ({},{}) position: ({},{})",
	// 	this->Velocity.x, this->Velocity.y, this->Position.x,
	// 	this->Position.y);
}
