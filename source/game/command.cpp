#include "game/command.h"

#include "game/plane_object.h"
#include "glm/detail/type_vec.hpp"
#include <cmath>

void MoveLeftCommand::Execute(GameObject *Actor, float dt) {
	PlaneObject *Obj = reinterpret_cast<PlaneObject *>(Actor);
	Obj->Move(dt, glm::vec2(-1.0F, 0.0F));
}
void MoveRightCommand::Execute(GameObject *Actor, float dt) {
	PlaneObject *Obj = reinterpret_cast<PlaneObject *>(Actor);
	Obj->Move(dt, glm::vec2(1.0F, 0.0F));
}
void MoveTopCommand::Execute(GameObject *Actor, float dt) {
	PlaneObject *Obj = reinterpret_cast<PlaneObject *>(Actor);
	Obj->Move(dt, glm::vec2(0.0F, -1.0F));
}
void MoveBottomCommand::Execute(GameObject *Actor, float dt) {
	PlaneObject *Obj = reinterpret_cast<PlaneObject *>(Actor);
	Obj->Move(dt, glm::vec2(0.0F, 1.0F));
}

void FireCommand::Execute(GameObject *Actor, float dt) {
	PlaneObject *Obj = reinterpret_cast<PlaneObject *>(Actor);
	if (Obj->fireColdDown > 0) {
		Obj->fireColdDown = Obj->fireColdDown - dt;
	}
	else {
		Obj->fireColdDown = 0.3F;
		Obj->weapon->Spawn(
			glm::vec2(Obj->Position.x + Obj->Size.x * 0.5F,
					  Obj->Position.y + Obj->Size.y * 0.5F),
			glm::vec2(std::cos(Obj->Rotation),
					  std::sin(Obj->Rotation)) *
				30.0F);
	}
}
