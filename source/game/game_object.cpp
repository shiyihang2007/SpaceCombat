
#include "game/game_object.h"

GameObject::GameObject()
	: Position(0.0F, 0.0F), Size(1.0F, 1.0F), Velocity(0.0F),
	  Color(1.0F), Rotation(0.0F) {}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size,
					   Texture2D sprite, glm::vec3 color,
					   glm::vec2 velocity, float rotation)
	: Position(pos), Size(size), Velocity(velocity), Color(color),
	  Rotation(rotation), Sprite(sprite) {}

void GameObject::Draw(SpriteRenderer &renderer) {
	renderer.DrawSprite(this->Sprite, this->Position, this->Size,
						this->Rotation, this->Color);
}

void GameObject::Update(float dt, unsigned int window_width,
						unsigned int window_height) {}
