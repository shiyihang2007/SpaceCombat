#ifndef COMMAND_H
#define COMMAND_H

#include "game/game_object.h"
#include "game/plane_object.h"

class Command {
  public:
	virtual void Execute(GameObject *Actor, float dt) = 0;
	virtual ~Command() = default;
};

class NullCommand : public Command {
  public:
	void Execute(GameObject *Actor, float dt) override {}
};

class MoveLeftCommand : public Command {
  public:
	MoveLeftCommand() = default;
	void Execute(GameObject *Actor, float dt) override;
};
class MoveRightCommand : public Command {
  public:
	MoveRightCommand() = default;
	void Execute(GameObject *Actor, float dt) override;
};
class MoveTopCommand : public Command {
  public:
	MoveTopCommand() = default;
	void Execute(GameObject *Actor, float dt) override;
};
class MoveBottomCommand : public Command {
  public:
	MoveBottomCommand() = default;
	void Execute(GameObject *Actor, float dt) override;
};

enum CommandType { MoveLeft, MoveRight, MoveTop, MoveBottom };

#endif
