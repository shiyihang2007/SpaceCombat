
#include "game/ai.h"
#include "game/command.h"

#include <algorithm>
#include <cstring>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

auto AISimple::Update(
	GameObject *self, GameObject *enemy,
	std::unordered_map<CommandType, Command *> cmds,
	unsigned int Height, unsigned int Width, std::mt19937_64 &rnd)
	-> std::vector<Command *> {
	std::vector<Command *> commands;

	// don't move out of screen
	if (self->Position.y < static_cast<float>(Height) * 0.1F) {
		commands.push_back(cmds[CommandType::MoveBottom]);
	}

	// keep a distance from the enemy
	constexpr float distanceMax = 0.8F;
	constexpr float distanceMin = 0.3F;
	if (enemy->Position.y - self->Position.y >
		static_cast<float>(Height) * distanceMax) {
		commands.push_back(cmds[CommandType::MoveBottom]);
	}
	if (enemy->Position.y - self->Position.y <
		static_cast<float>(Height) * -distanceMax) {
		commands.push_back(cmds[CommandType::MoveTop]);
	}
	if (enemy->Position.y - self->Position.y <
			static_cast<float>(Height) * distanceMin &&
		enemy->Position.y - self->Position.y >
			static_cast<float>(Height) * 0.0F) {
		commands.push_back(cmds[CommandType::MoveTop]);
	}
	if (enemy->Position.y - self->Position.y >
			static_cast<float>(Height) * -distanceMin &&
		enemy->Position.y - self->Position.y <
			static_cast<float>(Height) * 0.0F) {
		commands.push_back(cmds[CommandType::MoveBottom]);
	}
	// No need for x distance
	/*
	if (enemy->Position.x - self->Position.x >
		static_cast<float>(Width) * distanceMax) {
		commands.push_back(cmds[CommandType::MoveRight]);
	}
	if (enemy->Position.x - self->Position.x <
		static_cast<float>(Width) * -distanceMax) {
		commands.push_back(cmds[CommandType::MoveLeft]);
	}
	if (enemy->Position.x - self->Position.x <
			static_cast<float>(Width) * distanceMin &&
		enemy->Position.x - self->Position.x >
			static_cast<float>(Width) * 0.0F) {
		commands.push_back(cmds[CommandType::MoveLeft]);
	}
	if (enemy->Position.x - self->Position.x >
			static_cast<float>(Width) * -distanceMin &&
		enemy->Position.x - self->Position.x <
			static_cast<float>(Width) * 0.0F) {
		commands.push_back(cmds[CommandType::MoveRight]);
	}
	*/

	// random walk
	if (commands.empty()) {
		if (fabs(self->Velocity.x) > 0.1F &&
			std::uniform_int_distribution<>(0, 1)(rnd) != 0) {
			if (self->Velocity.x < 0.0F) {
				commands.push_back(cmds[CommandType::MoveLeft]);
			}
			else if (self->Velocity.x > 0.0F) {
				commands.push_back(cmds[CommandType::MoveRight]);
			}
		}
		else {
			commands.push_back(
				cmds[std::uniform_int_distribution<>(0, 1)(rnd) == 0
						 ? CommandType::MoveLeft
						 : CommandType::MoveRight]);
		}
		if (fabs(self->Velocity.y) > 0.1F &&
			std::uniform_int_distribution<>(0, 1)(rnd) != 0) {
			if (self->Velocity.y < 0.0F) {
				commands.push_back(cmds[CommandType::MoveTop]);
			}
			else if (self->Velocity.y > 0.0F) {
				commands.push_back(cmds[CommandType::MoveBottom]);
			}
		}
		else {
			commands.push_back(
				cmds[std::uniform_int_distribution<>(0, 1)(rnd) == 0
						 ? CommandType::MoveTop
						 : CommandType::MoveBottom]);
		}
	}

	// fire
	if (std::abs(self->Position.x - enemy->Position.x) <
		static_cast<float>(Width) * 0.3F) {
		commands.push_back(cmds[CommandType::Fire]);
	}

	std::sort(commands.begin(), commands.end());
	commands.erase(std::unique(commands.begin(), commands.end()),
				   commands.end());
	return commands;
}
