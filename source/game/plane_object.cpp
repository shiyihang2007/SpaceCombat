#include "game/plane_object.h"
#include "game/game_object.h"


auto PlaneUpdate(GameObject *base, float dt, unsigned int window_width,
				 unsigned int window_height) -> void {
	// 运动
	constexpr float WALL_FORCE = 7.0F;
	auto self = reinterpret_cast<PlaneObject *>(base);
	self->Position += self->Velocity * dt;
	self->Position += self->Velocity * dt;
	self->Velocity *= PlaneObject::ENVIROMENT_F;
	// then check if outside window bounds and if so,
	// transport to the otherside of window
	if (self->Position.x + self->Size.x < 0.0F) {
		// self->Velocity.x = -self->Velocity.x;
		self->Position.x = static_cast<float>(window_width);
	}
	else if (self->Position.x > static_cast<float>(window_width)) {
		// self->Velocity.x = -self->Velocity.x;
		self->Position.x = 0 - self->Size.x;
	}
	else if (self->Position.x < 0.0F) {
		self->Velocity += glm::vec2(1.0, 0) * WALL_FORCE;
	}
	else if (self->Position.x + self->Size.x >
			 static_cast<float>(window_width)) {
		self->Velocity += glm::vec2(-1.0, 0) * WALL_FORCE;
	}
	// if (self->Position.y < 0.0F) {
	// 	self->Velocity += glm::vec2(0, 1.0) * WALL_FORCE;
	// }
	if (self->Position.y + self->Size.y > static_cast<float>(window_height)) {
		self->Velocity += glm::vec2(0, -1.0) * WALL_FORCE;
	}
	// 无敌帧
	self->ultraTick = self->ultraTick > 0 ? self->ultraTick - dt : 0;
}

PlaneObject::PlaneObject() : health(defaultHealth), ultraTick(0) {}

PlaneObject::PlaneObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite,
						 glm::vec3 color, glm::vec2 velocity)
	: GameObject(pos, size, sprite, color, velocity, PlaneUpdate),
	  health(defaultHealth), ultraTick(0) {}

auto PlaneObject::Move(float dt, glm::vec2 deltaVelocity) -> glm::vec2 {
	// move the plane
	this->Velocity += deltaVelocity * dt * VELOCITY;
	return this->Position;
}

void PlaneObject::Reset(glm::vec2 position, glm::vec2 velocity) {
	this->Position = position;
	this->Velocity = velocity;
}
