#ifndef AI_H
#define AI_H

#include "game/command.h"
#include "game/game_object.h"

#include <random>
#include <unordered_map>
#include <vector>

class AIBase {
  public:
	virtual ~AIBase() = default;
	virtual auto
	Update(GameObject *self, GameObject *enemy,
		   std::unordered_map<CommandType, Command *> cmds,
		   unsigned int Height, unsigned int Width,
		   std::mt19937_64 &rnd) -> std::vector<Command *> = 0;
};

class AISimple : public AIBase {
  public:
	AISimple() = default;

	auto Update(GameObject *self, GameObject *enemy,
				std::unordered_map<CommandType, Command *> cmds,
				unsigned int Height, unsigned int Width,
				std::mt19937_64 &rnd)
		-> std::vector<Command *> override;
};

#endif
