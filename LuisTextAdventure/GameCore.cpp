#include "GameCore.h"
#include "CommandParser.h"
#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>

namespace TextGame
{
	RoomData CreateRoom(const std::string& inName, const std::string& inDescription)
	{
		RoomData roomData = {};
		roomData.Name = inName;
		roomData.Description = inDescription;
		roomData.HasKey = false;
		return roomData;
	}
	/*
	RoomData CreateLockedRoom(const std::string& inName, const std::string& inDescription, const std::string& inLocked) {
		RoomData roomData = {};
		roomData.Name = inName;
		roomData.Description = inDescription;
		roomData.Locked = inLocked;

		return roomData;
	}

	RoomData CreateItemRoom(const std::string& inName, const std::string& inDescription, const std::string& inLocked, const std::string& inItem) {
		RoomData roomData = {};
		roomData.Name = inName;
		roomData.Description = inDescription;
		roomData.Locked = inLocked;
		roomData.Item = inItem;

		return roomData;
	}
	*/
	RoomExitData CreateRoomExit(const std::string& inName, int inTargetIndex)
	{
		RoomExitData exitData = {};
		exitData.Name = inName;
		exitData.DestinationRoomIndex = inTargetIndex;
		exitData.IsLocked = false;
		return exitData;
	}
	
	GameEventData ThisGameEvent() {
		GameEventData gameData = {};
		gameData.HasAcquiredFirstKey = false;
		gameData.HasEscaped = false;
		gameData.HasLeftOwnCell = false;
		gameData.HasReachedLobby = false;
		return gameData;
	}

	void InitializeGame(PlayerState& playerState, WorldState& worldState)
	{
		playerState.WantsToLook = true;
		playerState.CurrentRoomIndex = 0;
		playerState.HasKey = false;

		printf("Your name is not important. Your mission, is to infiltrate the factory and retrieve valuable blueprints.\n");
		printf("Unfortunately, you were captured, and now reside in a cell on the outside of the factory perimeter.\n");
		printf("Luckily, you were able to get a good look at the prison as you were dragged inside.\n");
		printf("Approximately 10 rooms...and at least one locked door stand behind you and freedom.\n");
		printf("\n");

		//Initialize playerState and create room descriptions
		//*** Room Index 0 ***
		RoomData roomData = CreateRoom("MyCell", "The cell you were thrown in when you were taken to this prison.");
		roomData.HasKey = true;

		RoomExitData exitData = CreateRoomExit("cellhall", 1);
		exitData.IsLocked = true;
		roomData.Exits.push_back(exitData);

		worldState.Rooms.push_back(roomData);

		//*** Room Index 1 ***
		RoomData roomData2 = CreateRoom("CellHall", "A hallway containing three cells, with a door leading to the lobby of the prison.");
		roomData2.HasKey = false;

		RoomExitData exitData2 = CreateRoomExit("prisonlobby", 4);
		exitData2.IsLocked = true;

		roomData2.Exits.push_back(CreateRoomExit("mycell", 0));
		roomData2.Exits.push_back(CreateRoomExit("cell2", 2));
		roomData2.Exits.push_back(CreateRoomExit("cell3", 3));
		roomData2.Exits.push_back(exitData2);
		worldState.Rooms.push_back(roomData2);

		//*** Room Index 2 ***
		RoomData roomData3 = CreateRoom("Cell2", "The second cell in the hall of three. They must keep very few prisoners alive. There is a message etched into the wall\n\n 'Rob wuz here'\n\n wut\n");
		roomData3.Exits.push_back(CreateRoomExit("cellhall", 1));
		worldState.Rooms.push_back(roomData3);

		//*** Room Index 3 ***
		RoomData roomData4 = CreateRoom("Cell3", "The third cell. There's a pile of dirt and assorted items in the corner.");
		roomData4.HasKey = true;
		roomData4.Exits.push_back(CreateRoomExit("cellhall", 1));
		worldState.Rooms.push_back(roomData4);

		//*** Room Index 4 ***
		RoomData roomData5 = CreateRoom("PrisonLobby", "The lobby of the prison. Three doors to the front, one leading back to Cell Hall ");
		roomData5.Exits.push_back(CreateRoomExit("cellhall", 1));
		roomData5.Exits.push_back(CreateRoomExit("handoff", 5));
		roomData5.Exits.push_back(CreateRoomExit("thirdroom", 6));
		roomData5.Exits.push_back(CreateRoomExit("sideroom", 7));
		worldState.Rooms.push_back(roomData5);

		//*** Room Index 5 ***
		RoomData roomData6 = CreateRoom("Hand Off Area", "A small chamber with two doors on either side. One door looks to be only openable with another key. The other leads back to the prison lobby.");
		roomData6.Exits.push_back(CreateRoomExit("prisonlobby", 4));

		RoomExitData exitData6 = CreateRoomExit("courtyard", 8);
		exitData6.IsLocked = true;

		roomData6.Exits.push_back(exitData6);
		worldState.Rooms.push_back(roomData6);

		//*** Room Index 6 ***
		RoomData roomData7 = CreateRoom("Third Room", "A broom closet. Grafitti on the wall says 'Game created by Luis Brito'. \n Weird");
		roomData7.Exits.push_back(CreateRoomExit("prisonlobby", 4));
		worldState.Rooms.push_back(roomData7);

		//*** Room Index 7 ***
		RoomData roomData8 = CreateRoom("Side Room", "A room half the size of the lobby. Contains two levers, a desk, and another key. A note on the desk says \n 'This puzzle was not finished on time. Just take the key'");
		roomData8.HasKey = true;
		roomData8.Exits.push_back(CreateRoomExit("prisonlobby", 4));
		worldState.Rooms.push_back(roomData8);

		//*** Room Index 8 ***
		RoomData roomData9 = CreateRoom("Courtyard", "Empty grassy area outside of the prison. You can see that the prison was barely the size of a small barn. There is also a helicopter in the distance.");
		roomData9.Exits.push_back(CreateRoomExit("handoff", 5));
		roomData9.Exits.push_back(CreateRoomExit("helicopter", 9));
		worldState.Rooms.push_back(roomData9);

		//*** Room Index 9 ***
		RoomData roomData10 = CreateRoom("Helicopter", "The cockpit of a helicopter. The coordinates for your home are already punched in.");
		roomData10.Exits.push_back(CreateRoomExit("home", 10));
		worldState.Rooms.push_back(roomData10);

		//*** Room Index 10 ***
		RoomData roomData11 = CreateRoom("Home", "Your home. The place where you can get away and relax after a good adventure. There is a Helicopter in the front lawn.");
		//roomData10.Exits.push_back(CreateRoomExit("home", 10));
		worldState.Rooms.push_back(roomData11);
	}

	void PlayerMove(PlayerState& playerState, int newRoomIndex) {
		playerState.CurrentRoomIndex = newRoomIndex;
		playerState.WantsToLook = true;	
	}

	void GetInput(PlayerState& playerState, const WorldState& worldState)
	{
		playerState.WantsToLook = false;
		playerState.WantsToGetKey = false;
		playerState.DesiredExit = "";

		printf("What do you do?\n");
		printf("> ");
		TextAdventureCommand command = ParseAdventureCommand();

		if (command.CommandType == CommandType_QUIT)
		{
			playerState.WantsToExit = true;
		}
		else if (command.CommandType == CommandType_LOOK)
		{
			playerState.WantsToLook = true;
		}
		else if (command.CommandType == CommandType_GO)
		{
			playerState.DesiredExit = command.Parameter;
		}
		else if (command.CommandType == CommandType_GET)
		{
			if (command.Parameter == "key") {
				playerState.WantsToGetKey = true;
			}
		}
		/*
		else if (command.CommandType == CommandType_SLEEP)
		{
		
		}*/
		else if (command.CommandType == CommandType_HELP)
		{
			printf("Command List: look, quit, go [place], get keys, sleep\n");
		}

		if(command.CommandType == CommandType_NONE)
		{
			printf("I don't understand\n");
		}
		printf("\n");

	}

	void RenderGame(const PlayerState& playerState, const WorldState& worldState)
	{
		if (playerState.WantsToLook)
		{
			const RoomData& currentRoom = worldState.Rooms[playerState.CurrentRoomIndex];

			printf("===============================================\n\n");
			printf("LOCATION: %s\n", currentRoom.Name.c_str());
			printf("%s\n\n", currentRoom.Description.c_str());

			if (currentRoom.HasKey) {
				printf("A glimmering, key like object can be seen in the corner\n");
			}
			printf("\n");
			printf("EXITS:\n");
			for (int i = 0; i < currentRoom.Exits.size(); i++)
			{
				printf("%s\n", currentRoom.Exits[i].Name.c_str());
			}

			if (currentRoom.Name == "Home") {
				printf("Your adventure is complete. AMERICA IS SAFE. You may now *QUIT*\n");
			}

			printf("\n");
			printf("INVENTORY:\n");
			if (playerState.HasKey) {
				printf("key\n");
			}
			printf("\n");
		}
	}

	void UpdateGame(PlayerState& playerState, WorldState& worldState)
	{
		RoomData& currentRoom = worldState.Rooms[playerState.CurrentRoomIndex];
		if (playerState.DesiredExit != "")
		{
			bool HasFoundExit = false;
			for (int i = 0; i < currentRoom.Exits.size(); i++)
			{
				if (playerState.DesiredExit == currentRoom.Exits[i].Name)
				{
					if (currentRoom.Exits[i].IsLocked) {
						if (playerState.HasKey) {
							PlayerMove(playerState, currentRoom.Exits[i].DestinationRoomIndex);
							playerState.HasKey = false;
							currentRoom.Exits[i].IsLocked = false;
						}
						else {
							printf("The door is locked...\n");
						}
					}
					else {
						PlayerMove(playerState, currentRoom.Exits[i].DestinationRoomIndex);
					}
					HasFoundExit = true;
				}
			}

			if(!HasFoundExit)
			{
				printf("I can't find that exit\n");
			}
		}

		if (playerState.WantsToGetKey) {
			if (playerState.HasKey) {
				printf("Key already in INVENTORY\n");
			}
			else {
				if (currentRoom.HasKey) {
					playerState.HasKey = true;
					currentRoom.HasKey = false;
					printf("Key Acquired\n");
				}
				else {
					printf("No key to be seen\n");
				}
			}			
		}
	}

	void CleanupGame(PlayerState& playerState, WorldState& worldState)
	{
		
	}
}
