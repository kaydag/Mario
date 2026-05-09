#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_PIPE 11
#define PIPE_WIDTH 20
#define GROUND_BBOX_WIDTH 40
#define GROUND_BBOX_HEIGHT 15

class CPipe : public CGameObject {
public:
	CPipe(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};