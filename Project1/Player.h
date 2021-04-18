#pragma once

// This class represents any player including ourself

class Vector3;
class Player
{
private:
	Player();

public:
	// Returns the maximum number of players allowed in the game
	static int* GetMaxPlayer();
	
	// Return base address of the player at a given point in the entity list
	static Player* GetPlayer(int index);

	// Return player's health
	int* GetHealth();

	// Return player's team ID
	int* GetTeam();

	// Returns the XYZ coordinates of the player
	Vector3* GetOrigin();
	
	// Viewoffset is the distance from the player's distance to
	// the player's head. This gets the position of the camera
	// from the target's perspective, which will be used to calculate
	// the view angle from the target to the player
	Vector3* GetViewOffset();

	// Return the XYZ coordinates of a specific bone in the bone matrix
	// given the id
	Vector3* GetBonePos(int boneID);
};

