//
// Created by cvalenza on 8/28/16.
//

#ifndef OXYGINE_HW_GAME_H
#define OXYGINE_HW_GAME_H

#include "oxygine-framework.h"

using namespace oxygine;

DECLARE_SMART(Player, spPlayer);
DECLARE_SMART(Joystick, spJoystick);
DECLARE_SMART(EquipmentButton, spEquipmentButton);
DECLARE_SMART(Game, spGame);

class Game : public Actor {
	private:
		friend class Player;
		void doUpdate(const UpdateState& us);

		spPlayer player;
		spJoystick move;
		spJoystick look;
		spEquipmentButton slot1;
		spEquipmentButton slot2;
		spEquipmentButton slot3;
	public:
		Game();
		void setPlayerRHWeapon(std::string weap);
		void init();
};

#endif //OXYGINE_HW_GAME_H
