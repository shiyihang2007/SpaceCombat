
#ifndef GAME_H
#define GAME_H

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "game/ai.h"
#include "game/ai_plane_object.h"
#include "game/command.h"
#include "game/plane_object.h"

#include <random>
#include <vector>

// Represents the current state of the Game
enum GameState { GAME_ACTIVE, GAME_MENU, GAME_WIN };

// Game holds all Game-related state and functionality.
// Combines all Game-related data into a single class for
// easy access to each of the components and manageability.
class Game {
  public:
	// random generator
	std::mt19937_64 rnd;

	// Game state
	GameState State;
	GLboolean Keys[1024];
	GLuint Width, Height;

	// 玩家操控对象
	PlaneObject *Player;

	// 预先从硬盘加载列表
	std::vector<std::string> Levels;
	GLuint CurrentLevel;

	// 在关卡开始时再加载对象
	std::vector<std::vector<AIPlaneObject>> Waves;
	GLuint CurrentWave;

	std::vector<AIPlaneObject *> Enemies;

	// ai
	AISimple AiSimple;

	// 按键对应的命令
	Command *Key2Commands[1024];

	// 所有命令的实例
	NullCommand nullCommand;
	MoveLeftCommand moveLeftCommand;
	MoveRightCommand moveRightCommand;
	MoveTopCommand moveTopCommand;
	MoveBottomCommand moveBottomCommand;

	std::unordered_map<CommandType, Command *> Commands;

	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	~Game();

	// Initialize Game state (load all shaders/textures)
	void Init();

	// GameLoop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();

	auto InputHandle(GLboolean *keys) -> std::vector<Command *>;

	void DoCollisions();
	void CheckLevel();
	void LoadLevel();
	void LoadWave();

	// Reset
	void ResetPlayer();
};

#endif
