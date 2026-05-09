#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_MUSHROOM 120
#define MUSHROOM_WIDTH 16
#define MUSHROOM_BBOX_WIDTH  25
#define MUSHROOM_BBOX_HEIGHT 16

class CMushroom : public CGameObject {
public:
	CMushroom(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};