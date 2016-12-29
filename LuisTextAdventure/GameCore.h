#pragma once
#include <string>
#include <vector>

namespace TextGame
{
	struct PlayerState
	{
		bool WantsToExit;
		bool WantsToLook;
		int CurrentRoomIndex;
		std::string DesiredExit;
		bool HasKey;
		bool WantsToGetKey;
	};

	struct GameEventData {
		bool HasLeftOwnCell;
		bool HasAcquiredFirstKey;
		bool HasReachedLobby;
		bool HasEscaped;
	};

	struct RoomExitData
	{
		std::string Name;
		int DestinationRoomIndex;
		bool IsLocked;
	};

	struct RoomData
	{
		std::string Name;
		std::string Description;
		std::vector<RoomExitData> Exits;
		bool HasKey;
	};

	struct WorldState
	{
		std::vector<RoomData> Rooms;
	};

	void InitializeGame(PlayerState& playerState, WorldState& worldState);
	void GetInput(PlayerState& playerState, const WorldState& worldState);
	void RenderGame(const PlayerState& playerState, const WorldState& worldState);
	void UpdateGame(PlayerState& playerState, WorldState& worldState);
	void CleanupGame(PlayerState& playerState, WorldState& worldState);
	void PlayerMove(PlayerState& playerState, int newRoomIndex);
}