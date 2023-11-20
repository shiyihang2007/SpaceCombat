#include "game/game.h"
#include "game/ai.h"
#include "game/ai_plane_object.h"
#include "game/command.h"
#include "game/game_object.h"
#include "game/level_loader.h"
#include "game/plane_object.h"
#include "game/round_object.h"

#include "resource_manager.h"
#include "sprite_renderer.h"

#include "spdlog/spdlog.h"

#include <cmath>
#include <filesystem>
#include <iostream>
#include <random>
#include <vector>


// Game-related State data
SpriteRenderer *Renderer;

// 控制飞机图像缩放
float PlaneSpriteScale;

// Initial velocity of the player plane
float controlScale = 1.0F;

// Initial Velocity of the Background (Stars)
float backgroundYPosition = 0.0F;
const float backgroundYVelocity = 30.0F;

// colors
const glm::vec3 PLAYER_COLOR(0.0F, 0.5F, 1.0F);
const glm::vec3 ENEMY_COLOR(1.0F, 0.0F, 0.0F);

Game::Game(unsigned int width, unsigned int height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height),
	  rnd(std::random_device{}()) {}

Game::~Game() { delete Renderer; }

void Game::Init() {
	// load shaders
	ResourceManager::LoadShader("./shader/sprite.vert",
								"./shader/sprite.frag", nullptr,
								"sprite");
	// configure shaders
	glm::mat4 projection = glm::ortho(
		0.0F, static_cast<float>(this->Width),
		static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image",
														  0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection",
													projection);
	// set render-specific controls
	Renderer =
		new SpriteRenderer(ResourceManager::GetShader("sprite"));
	// load textures
	ResourceManager::LoadTexture("./texture/awesomeface.png", true,
								 "plane_basic");
	ResourceManager::LoadTexture("./texture/stars.png", true,
								 "background");
	// 设置缩放
	PlaneSpriteScale = 0.03F;
	// load Commands
	for (auto &command : this->Key2Commands) {
		command = &nullCommand;
	}
	this->Key2Commands[GLFW_KEY_A] = &moveLeftCommand;
	this->Key2Commands[GLFW_KEY_D] = &moveRightCommand;
	this->Key2Commands[GLFW_KEY_W] = &moveTopCommand;
	this->Key2Commands[GLFW_KEY_S] = &moveBottomCommand;
	Commands[CommandType::MoveLeft] = &moveLeftCommand;
	Commands[CommandType::MoveRight] = &moveRightCommand;
	Commands[CommandType::MoveTop] = &moveTopCommand;
	Commands[CommandType::MoveBottom] = &moveBottomCommand;
	// load Player
	auto t = ResourceManager::GetTexture("plane_basic");
	glm::vec2 playerSize =
		glm::vec2(t.Width, t.Height) * PlaneSpriteScale;
	glm::vec2 playerPos = glm::vec2(
		static_cast<float>(this->Width) / 2.0F - playerSize.x / 2.0F,
		static_cast<float>(this->Height) - playerSize.y);
	this->Player =
		new PlaneObject(playerPos, playerSize, t, PLAYER_COLOR);
	// load Levels
	auto FindLevels = [this](auto self, std::string path) -> void {
		for (auto const &dirEntry :
			 std::filesystem::recursive_directory_iterator{path}) {
			if (dirEntry.is_directory()) {
				self(self, dirEntry.path());
			}
			else {
				this->Levels.push_back(dirEntry.path());
				LevelLoader::LoadLevel(dirEntry.path().c_str(),
									   dirEntry.path().c_str());
			}
		}
	};
	FindLevels(FindLevels, "./level");
	this->CurrentLevel = 0;
	spdlog::info("level count: {}", this->Levels.size());
	for (const auto &level : this->Levels) {
		spdlog::info(" - {}", level);
	}
	this->LoadLevel();
	this->LoadWave();
}

void Game::Update(float dt) {
	this->Player->update(this->Player, dt, this->Width,
						 this->Height);
	for (auto *i : this->Enemies) {
		i->update(i, dt, this->Width, this->Height);
	}
	backgroundYPosition += dt * backgroundYVelocity;
	backgroundYPosition =
		backgroundYPosition > static_cast<float>(this->Height)
			? backgroundYPosition - static_cast<float>(this->Height)
			: backgroundYPosition;
	this->DoCollisions();
	this->CheckLevel();
}

auto Game::InputHandle(unsigned char *keys)
	-> std::vector<Command *> {
	std::vector<Command *> res;
	for (int i = 0; i < 1024; ++i) {
		if (keys[i] != 0U) {
			res.emplace_back(this->Key2Commands[i]);
			// std::cerr << "key pressed: " << i << "\n";
		}
	}
	return res;
}

// This part of code should be refactor someday.
void Game::ProcessInput(float dt) {
	auto res = this->InputHandle(Keys);
	for (auto *i : res) {
		if (i == nullptr) {
			spdlog::warn("Invalid command.");
			continue;
		}
		i->Execute(this->Player, dt);
	}

	for (auto *i : Enemies) {
		auto res = i->Ai->Update(i, Player, Commands, this->Height,
								 this->Width, this->rnd);
		for (auto *j : res) {
			if (j == nullptr) {
				spdlog::warn("Invalid command.");
				continue;
			}
			j->Execute(i, dt);
		}
	}
}

void Game::Render() {
	if (this->State == GAME_ACTIVE) {
		// 滚动背景
		Renderer->DrawSprite(
			ResourceManager::GetTexture("background"),
			glm::vec2(0.0F, backgroundYPosition),
			glm::vec2(this->Width, this->Height), 0.0F);
		Renderer->DrawSprite(
			ResourceManager::GetTexture("background"),
			glm::vec2(0.0F,
					  backgroundYPosition - 1.0 * this->Height),
			glm::vec2(this->Width, this->Height), 0.0F);
		// 玩家
		this->Player->Draw(*Renderer);
		// 敌人
		// std::cerr << "=====\n";
		for (auto *i : this->Enemies) {
			i->Draw(*Renderer);
			// std::cerr << i->Position.x << " " << i->Position.y <<
			// "\n";
		}
	}
}

void Game::ResetPlayer() {}

// 碰撞方向
enum Direction { UP, RIGHT, DOWN, LEFT };

auto VectorDirection(glm::vec2 target) -> Direction {
	glm::vec2 compass[] = {
		glm::vec2(0.0F, 1.0F),	// 上
		glm::vec2(1.0F, 0.0F),	// 右
		glm::vec2(0.0F, -1.0F), // 下
		glm::vec2(-1.0F, 0.0F)	// 左
	};
	GLfloat max = 0.0F;
	GLuint best_match = -1;
	for (GLuint i = 0; i < 4; i++) {
		GLfloat dot_product =
			glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max) {
			max = dot_product;
			best_match = i;
		}
	}
	return static_cast<Direction>(best_match);
}

using Collision = std::tuple<GLboolean, Direction, glm::vec2>;

auto CheckCollision(const GameObject &one,
					const GameObject &two)
	-> GLboolean // AABB - AABB collision
{
	// x轴方向碰撞？
	bool collisionX =
		one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;
	// y轴方向碰撞？
	bool collisionY =
		one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;
	// 只有两个轴向都有碰撞时才碰撞
	return static_cast<GLboolean>(collisionX && collisionY);
}

auto CheckCollision(const RoundObject &one,
					const GameObject &two)
	-> Collision // AABB - Circle collision
{
	// 获取圆的中心
	glm::vec2 center(one.Position + one.Radius);
	// 计算AABB的信息（中心、半边长）
	glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x,
						  two.Position.y + aabb_half_extents.y);
	// 获取两个中心的差矢量
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents,
								   aabb_half_extents);
	// AABB_center加上clamped这样就得到了碰撞箱上距离圆最近的点closest
	glm::vec2 closest = aabb_center + clamped;
	// 获得圆心center和最近点closest的矢量并判断是否 length <= radius
	difference = closest - center;
	if (glm::length(difference) <= one.Radius) {
		return std::make_tuple(GL_TRUE, VectorDirection(difference),
							   difference);
	}
	return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
}

void Game::DoCollisions() {
	if (Player->ultraTick < 0.01) {
		for (auto *enemy : this->Enemies) {
			if (enemy->ultraTick > 0) {
				continue;
			}
			if (CheckCollision(GameObject(*Player),
							   GameObject(*enemy)) != 0U) {
				this->Player->health -= 1;
				this->Player->ultraTick += 0.1F;
				enemy->health -= 1;
				enemy->ultraTick += 0.1F;
			}
		}
	}
}

void Game::CheckLevel() {
	if (this->Player->health == 0) {
		// 如果血量掉光
		// 就重新开始这一关
		CurrentWave = 0;
	}
	for (auto it = this->Enemies.begin(); it != this->Enemies.end();
		 ++it) {
		if ((*it)->health == 0) {
			auto tmp = it;
			--it;
			this->Enemies.erase(tmp);
		}
	}
	if (this->Enemies.empty()) {
		++this->CurrentWave;
		if (this->CurrentWave == this->Waves.size()) {
			++this->CurrentLevel;
			// 最后一关无限出怪
			if (this->CurrentLevel == this->Levels.size()) {
				--this->CurrentLevel;
			}
			this->LoadLevel();
		}
		this->LoadWave();
	}
}

void Game::LoadLevel() {
	spdlog::debug("Current Level: {}", this->CurrentLevel);
	auto level =
		LevelLoader::GetLevel(Levels[this->CurrentLevel].c_str());
	this->Waves.clear();
	for (const auto &i : level) {
		this->Waves.emplace_back();
		spdlog::info("Wave [{}]: ", this->Waves.size() - 1);
		for (const auto &j : i) {
			auto t = ResourceManager::GetTexture(j.type);
			auto size =
				glm::vec2(t.Width, t.Height) * PlaneSpriteScale;
			auto pos = glm::vec2(
				j.position * static_cast<float>(this->Width) * 0.8F +
					static_cast<float>(size.x) * 0.5F +
					static_cast<float>(this->Width) * 0.1F,
				0.0F);
			spdlog::info("  - '{}'x{} at {} ({},{})", j.type,
						 j.count, j.position, pos.x, pos.y);
			for (int k = 0; k < j.count; ++k) {
				auto tpos = glm::vec2(
					pos.x - static_cast<float>(size.x) * 0.5F +
						std::uniform_real_distribution<float>(
							-size.x, size.x)(rnd),
					pos.y - static_cast<float>(k + 1) * size.y);
				this->Waves.back().emplace_back(
					&this->AiSimple, tpos, size, t, ENEMY_COLOR,
					glm::vec2(0.0, 30.0));
			}
		}
	}
	this->CurrentWave = 0;
}

void Game::LoadWave() {
	spdlog::debug("Current Wave: {}", this->CurrentWave);
	this->Enemies.clear();
	for (auto &i : Waves[CurrentWave]) {
		this->Enemies.push_back(&i);
		spdlog::debug("  - ({}, {})", i.Position.x, i.Position.y);
	}
	spdlog::debug("Total enemies: {}", this->Enemies.size());
}
