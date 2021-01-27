/*
	THIS FILE IS A PART OF RDR 2 SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2019
*/

#include "script.h"
#include <string>
#include <vector>
#include <ctime>
#include "keyboard.h"



Hash joaat(const char* button)
{
	return MISC::GET_HASH_KEY(button);
}

void TeleHorse()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Ped mount;
	mount = PLAYER::_GET_SADDLE_HORSE_FOR_PLAYER(PLAYER::PLAYER_ID());
	//Ped mount = PED::_GET_LAST_MOUNT(playerPed);
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(playerPed, true, true);
	float ground;


	//A few sets of possible horse teleport locations
	srand(time(NULL));
	int choice = rand() % 6 + 1; //rand is used to make sure the location is random
	int distance = 50;
	if (choice == 1)
	{
		pos.x = pos.x - distance;
	}
	else if (choice == 2)
	{
		pos.y = pos.y - distance;
	}
	else if (choice == 3)
	{
		pos.x = pos.x - distance;
		pos.y = pos.y - distance;
	}
	else if (choice == 4)
	{
		pos.x = pos.x + distance;
		pos.y = pos.y + distance;
	}
	else if (choice == 5)
	{
		pos.x = pos.x + distance;
	}
	else if (choice == 6)
	{
		pos.y = pos.y + distance;
	}

	//Finds the ground elevation at the specified coordinates
	pos.z = pos.z + 100;
	if (MISC::GET_GROUND_Z_FOR_3D_COORD(pos.x, pos.y, pos.z, &ground, 0))
	{
		pos.z = ground;
	}


	if ((PED::IS_PED_ON_MOUNT(playerPed) == false))
	{
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(mount, pos.x, pos.y, pos.z, false, false, false);
		TASK::TASK_GO_TO_ENTITY(mount, playerPed, 70000, 4.0f, 100, 100, 0);
	}
}




bool IsHorseFar() //Checks if the horse is too far to hear the player's whistle
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Ped mount;
	mount = PLAYER::_GET_SADDLE_HORSE_FOR_PLAYER(PLAYER::PLAYER_ID());
	//mount = PED::_GET_LAST_MOUNT(playerPed);
	
	Vector3 myPos = ENTITY::GET_ENTITY_COORDS(playerPed, true, true);
	Vector3 mountPos = ENTITY::GET_ENTITY_COORDS(mount, true, true);
	

	float distance = MISC::GET_DISTANCE_BETWEEN_COORDS(myPos.x,myPos.y, myPos.z, mountPos.x, mountPos.y, mountPos.z, true);
	
	if (distance >= 204.771469) // Out of whistle range distance
		return true;
	else
		return false;

}



void update()
{
	if (IsKeyJustUp(0x48) || PAD::IS_CONTROL_JUST_PRESSED(0, joaat("INPUT_FRONTEND_UP")))
	{
		if (IsHorseFar() == true)
		{
			TeleHorse();
		}
	}
}

void main()
{		
	while (true)
	{
		update();
		WAIT(0);
	}
}

void ScriptMain()
{	
	srand(GetTickCount());
	main();
}
