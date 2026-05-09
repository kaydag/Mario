#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_GROUND 10
#define GROUND_WIDTH 1
#define GROUND_BBOX_WIDTH 1
#define GROUND_BBOX_HEIGHT 1

class CGround : public CGameObject {
public:
	CGround(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};