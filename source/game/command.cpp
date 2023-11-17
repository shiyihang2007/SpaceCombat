#include "game/command.h"
#include "game/plane_object.h"
#include <iostream>

void MoveLeftCommand::Execute(GameObject *Actor, float dt) {
	// std::cerr << "MoveLeftCommand::Execute\n";
	PlaneObject *Obj = reinterpret_cast<PlaneObject *>(Actor);
	Obj->Move(dt, glm::vec2(-1.0F, 0.0F));
}

void MoveRightCommand::Execute(GameObject *Actor, float dt) {
	// std::cerr << "MoveRightCommand::Execute\n";
	PlaneObject *Obj = reinterpret_cast<PlaneObject *>(Actor);
	Obj->Move(dt, glm::vec2(1.0F, 0.0F));
}

void MoveTopCommand::Execute(GameObject *Actor, float dt) {
	// std::cerr << "MoveTopCommand::Execute\n";
	PlaneObject *Obj = reinterpret_cast<PlaneObject *>(Actor);
	Obj->Move(dt, glm::vec2(0.0F, -1.0F));
}

void MoveBottomCommand::Execute(GameObject *Actor, float dt) {
	// std::cerr << "MoveBottomCommand::Execute\n";
	PlaneObject *Obj = reinterpret_cast<PlaneObject *>(Actor);
	Obj->Move(dt, glm::vec2(0.0F, 1.0F));
}
