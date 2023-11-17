#ifndef AI_PLANE_OBJECT_H
#define AI_PLANE_OBJECT_H

#include "game/ai.h"
#include "game/plane_object.h"

class AIPlaneObject : public PlaneObject {
  public:
	AIBase *Ai;
	AIPlaneObject() : Ai(nullptr) {}
	AIPlaneObject(AIBase *Ai, glm::vec2 pos, glm::vec2 size, Texture2D sprite,
				  glm::vec3 color, glm::vec2 velocity)
		: Ai(Ai), PlaneObject(pos, size, sprite, color, velocity) {}
};

#endif
