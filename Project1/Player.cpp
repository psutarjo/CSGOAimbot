#pragma once
#include <Windows.h>
#include <cstdint>

#include "Player.h"
#include "Vector3.h"
#include "offsets.h"

Player* Player::GetPlayer(int index)
{
	static uint32_t moduleBase = (uint32_t)GetModuleHandle("client.dll");
	static uint32_t entityList = moduleBase + dwEntityList;
	
	return (Player*)(entityList + index * 0x10); 
}

int* Player::GetMaxPlayer() {
	static uint32_t moduleBase = (uintptr_t)GetModuleHandle("engine.dll");
	return (int*)(*(uint32_t*)(moduleBase + dwClientState) + dwClientState_MaxPlayer);
}

Vector3* Player::GetOrigin() {
	return (Vector3*)(*(uintptr_t*)this + m_vecOrigin);
}

Vector3* Player::GetViewOffset() {
	return (Vector3*)(*(uintptr_t*)this + m_vecViewOffset);
}

Vector3* Player::GetBonePos(int boneID) {
	uint32_t boneMatrix = *(uint32_t*)(*(uint32_t*)this + m_dwBoneMatrix);
	static Vector3 bonePos;
	bonePos.x = *(float*)(boneMatrix + 0x30 * boneID + 0x0C);
	bonePos.y = *(float*)(boneMatrix + 0x30 * boneID + 0x1C);
	bonePos.z = *(float*)(boneMatrix + 0x30 * boneID + 0x2C);
	return &bonePos;
}

int* Player::GetHealth()
{
	return (int*)(*(uint32_t*)this + m_iHealth);
}

int* Player::GetTeam()
{
	return (int*)(*(uint32_t*)this + m_iTeamNum);
}