
// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

#include "game/ai.h"

#include <cstring>
#include <random>

void AISimple::Update(GameObject *self, GameObject *enemy, unsigned char *key,
					  unsigned int Height, unsigned int Width,
					  std::mt19937_64 &rnd) {
	if (self->Position.y < static_cast<float>(Height) * 0.1F) {
		key[GLFW_KEY_S] = 1;
	}

	if (enemy->Position.y - self->Position.y >
		static_cast<float>(Height) * 0.5F) {
		key[GLFW_KEY_S] = 1;
	}
	if (enemy->Position.y - self->Position.y <
		static_cast<float>(Height) * -0.5F) {
		key[GLFW_KEY_W] = 1;
	}
	if (enemy->Position.y - self->Position.y <
			static_cast<float>(Height) * 0.3F &&
		enemy->Position.y - self->Position.y >
			static_cast<float>(Height) * 0.0F) {
		key[GLFW_KEY_W] = 1;
	}
	if (enemy->Position.y - self->Position.y >
			static_cast<float>(Height) * -0.3F &&
		enemy->Position.y - self->Position.y <
			static_cast<float>(Height) * 0.0F) {
		key[GLFW_KEY_S] = 1;
	}

	if (enemy->Position.x - self->Position.x >
		static_cast<float>(Width) * 0.5F) {
		key[GLFW_KEY_D] = 1;
	}
	if (enemy->Position.x - self->Position.x <
		static_cast<float>(Width) * -0.5F) {
		key[GLFW_KEY_A] = 1;
	}
	if (enemy->Position.x - self->Position.x <
			static_cast<float>(Width) * 0.3F &&
		enemy->Position.x - self->Position.x >
			static_cast<float>(Width) * 0.0F) {
		key[GLFW_KEY_A] = 1;
	}
	if (enemy->Position.x - self->Position.x >
			static_cast<float>(Width) * -0.3F &&
		enemy->Position.x - self->Position.x <
			static_cast<float>(Width) * 0.0F) {
		key[GLFW_KEY_D] = 1;
	}
}
