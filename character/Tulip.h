#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_TULIP 110
#define TULIP_WIDTH 12
#define TULIP_BBOX_WIDTH  12
#define TULIP_BBOX_HEIGHT 20

class CTulip : public CGameObject {
public:
	CTulip(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};