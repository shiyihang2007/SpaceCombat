#include "game/plane_object.h"
#include "game/game_object.h"
#include "game/weapon.h"

PlaneObject::PlaneObject()
	: weapon(&nullWeapon), health(defaultHealth), ultraTick(0) {}

PlaneObject::PlaneObject(glm::vec2 pos, glm::vec2 size,
						 Texture2D sprite, glm::vec3 color,
						 glm::vec2 velocity, float rotation,
						 Weapon *weapon, uint health, uint ultraTick)
	: GameObject(pos, size, sprite, color, velocity, rotation),
	  weapon(weapon), health(health), ultraTick(ultraTick) {}

void PlaneObject::Update(float dt, unsigned int window_width,
						 unsigned int window_height) {
	// 运动
	constexpr float WALL_FORCE = 7.0F;
	this->Position += this->Velocity * dt;
	this->Velocity *= PlaneObject::ENVIROMENT_F;
	// 传送
	if (this->Position.x + this->Size.x < 0.0F) {
		// this->Velocity.x = -this->Velocity.x;
		this->Position.x = static_cast<float>(window_width);
	}
	else if (this->Position.x > static_cast<float>(window_width)) {
		// this->Velocity.x = -this->Velocity.x;
		this->Position.x = 0 - this->Size.x;
	}
	else if (this->Position.x < 0.0F) {
		this->Velocity += glm::vec2(1.0, 0) * WALL_FORCE;
	}
	else if (this->Position.x + this->Size.x >
			 static_cast<float>(window_width)) {
		this->Velocity += glm::vec2(-1.0, 0) * WALL_FORCE;
	}
	// if (this->Position.y < 0.0F) {
	// 	this->Velocity += glm::vec2(0, 1.0) * WALL_FORCE;
	// }
	if (this->Position.y + this->Size.y >
		static_cast<float>(window_height)) {
		this->Velocity += glm::vec2(0, -1.0) * WALL_FORCE;
	}
	// 无敌帧
	this->ultraTick = this->ultraTick > 0 ? this->ultraTick - dt : 0;
	// 武器
	this->weapon->update(dt, window_width, window_height);
}

auto PlaneObject::Move(float dt, glm::vec2 deltaVelocity)
	-> glm::vec2 {
	// move the plane
	this->Velocity += deltaVelocity * dt * this->velocity;
	return this->Position;
}

void PlaneObject::Reset(glm::vec2 position, glm::vec2 velocity) {
	this->Position = position;
	this->Velocity = velocity;
}

void PlaneObject::Draw(SpriteRenderer &renderer) {
	renderer.DrawSprite(this->Sprite, this->Position, this->Size,
						this->Rotation, this->Color);
	for (auto *i : this->weapon->BulletObjects) {
		i->Draw(renderer);
	}
}
