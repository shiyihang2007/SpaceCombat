#ifndef AI_PLANE_OBJECT_H
#define AI_PLANE_OBJECT_H

#include "game/ai.h"
#include "game/plane_object.h"

class AIPlaneObject : public PlaneObject {
  public:
	AIBase *Ai;
	AIPlaneObject() : Ai(nullptr) {}
	AIPlaneObject(AIBase *Ai, glm::vec2 pos, glm::vec2 size,
				  Texture2D sprite,
				  glm::vec3 color = glm::vec3(1.0F),
				  glm::vec2 velocity = glm::vec2(0.0F),
				  float rotation = 0.0F,
				  Weapon *weapon = &nullWeapon,
				  uint health = defaultHealth, uint ultraTick = 0U)
		: Ai(Ai), PlaneObject(pos, size, sprite, color, velocity,
							  rotation, weapon, health, ultraTick) {}
};

#endif
