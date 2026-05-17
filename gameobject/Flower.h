#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_FLOWER 110
#define FLOWER_WIDTH 12
#define FLOWER_BBOX_WIDTH  12
#define FLOWER_BBOX_HEIGHT 20

class CFlower : public CGameObject {
public:
	CTulip(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};