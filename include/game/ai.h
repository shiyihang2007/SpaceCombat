#ifndef AI_H
#define AI_H

#include "game/game_object.h"

#include <random>

class AIBase {
  public:
	virtual ~AIBase() = default;
	virtual void Update(GameObject *self, GameObject *enemy,
						unsigned char *key, unsigned int Height,
						unsigned int Width, std::mt19937_64 &rnd) = 0;
};

class AISimple : public AIBase {
  public:
	AISimple() = default;

	void Update(GameObject *self, GameObject *enemy, unsigned char *key,
				unsigned int Height, unsigned int Width,
				std::mt19937_64 &rnd) override;
};

#endif
