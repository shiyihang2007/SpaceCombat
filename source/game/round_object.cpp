
#include "game/round_object.h"

RoundObject::RoundObject() : Radius(12.5F) {}

RoundObject::RoundObject(glm::vec2 pos, float radius, glm::vec2 velocity,
						 Texture2D sprite)
	: GameObject(pos, glm::vec2(radius * 2.0F, radius * 2.0F), sprite,
				 glm::vec3(1.0F), velocity),
	  Radius(radius) {}

auto RoundObject::Move(float dt, unsigned int window_width) -> glm::vec2 {
	// move the object
	this->Position += this->Velocity * dt;
	// then check if outside window bounds and if so, reverse velocity and
	// restore at correct position
	if (this->Position.x <= 0.0F) {
		this->Velocity.x = -this->Velocity.x;
		this->Position.x = 0.0F;
	}
	else if (this->Position.x + this->Size.x >=
			 static_cast<float>(window_width)) {
		this->Velocity.x = -this->Velocity.x;
		this->Position.x = static_cast<float>(window_width) - this->Size.x;
	}
	if (this->Position.y <= 0.0F) {
		this->Velocity.y = -this->Velocity.y;
		this->Position.y = 0.0F;
	}
	return this->Position;
}

// resets the ball to initial Stuck Position (if ball is outside window bounds)
void RoundObject::Reset(glm::vec2 position, glm::vec2 velocity) {
	this->Position = position;
	this->Velocity = velocity;
}
