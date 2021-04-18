#pragma once

// LocalPlayer class is our player

class Vector3;
class LocalPlayer
{
private:
	LocalPlayer();

public:
	// Return base address to our player
	static LocalPlayer* Get();
	
	// Get xyz coordinates of where are our player is
	Vector3* GetOrigin();
	
	// Viewoffset is the distance from your body to your head.
	// This gets the position of the camera, which will be needed
	// to calculate the vector from where the bullets shoot from
	Vector3* GetViewOffset();

	// Return player health
	int* GetHealth();

	// Return team ID
	int* GetTeam();

	// Function will snap our player's aiming position to the target's head
	void AimAt(Vector3* target);

	// Calculate the distance between our player's origin
	// and the target's origin
	float GetDistance(Vector3* target);
};