#pragma once

#include "Player.h"
#include "LocalPlayer.h"

#include <stdint.h>

Player* GetClosestEnemy()
{
	LocalPlayer* localPlayer = LocalPlayer::Get();

	float closestDistance = 1000000;
	int closestDistanceIndex = -1;

	// Iterate through all players in the game
	for (int i = 1; i < *Player::GetMaxPlayer(); i++) {
		Player* currentPlayer = Player::GetPlayer(i);

		// Skip if the player is ourself or if the pointer is invalid
		if(!currentPlayer ||  !(*(uint32_t*)currentPlayer) || (uint32_t)currentPlayer == (uint32_t)localPlayer)
		{
			continue;
		}
		// Skip if the player is on our team
		if (*currentPlayer->GetTeam() == *localPlayer->GetTeam()) {
			continue;
		}
		// Skip if the player is dead
		if (*currentPlayer->GetHealth() < 1 || *localPlayer->GetHealth() < 1) {
			continue;
		}
		// Calculate distance between player and target, and return the index in the entity list of the target
		float currentDistance = localPlayer->GetDistance(currentPlayer->GetOrigin());
		if (currentDistance < closestDistance) {
			closestDistance = currentDistance;
			closestDistanceIndex = i;
		}
	}
	if (closestDistanceIndex == -1) {
		return NULL;
	}
	return Player::GetPlayer(closestDistanceIndex);
}

void Run()
{
	Player* closestEnemy = GetClosestEnemy();

	if (closestEnemy)
	{
		// Explanation for why we use bone ID of 8 is contained in the slides
		LocalPlayer::Get()->AimAt(closestEnemy->GetBonePos(8));
	}
}