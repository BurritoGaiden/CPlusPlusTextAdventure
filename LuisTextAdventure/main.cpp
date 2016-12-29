#include <stdio.h>
#include "GameCore.h"

using namespace TextGame;

int main(int argc, char* argv[])
{
	PlayerState playerState = {};
	WorldState worldState = {};
	printf("\n");
	printf("The best Sneaking Adventure by Luis Brito\n\n");

	InitializeGame(playerState, worldState);

	while (!playerState.WantsToExit)
	{
		RenderGame(playerState, worldState);
		GetInput(playerState, worldState);
		UpdateGame(playerState, worldState);
	}

	CleanupGame(playerState, worldState);

	return 0;
}