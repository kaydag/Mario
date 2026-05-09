#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <d3dx10.h>
#include <vector>

#include "Animation.h"
#include "Animations.h"
#include "Texture.h"
#include "Sprites.h"
#include "Collision.h"

using namespace std; 
#define ID_TEX_BBOX -100

class CGameObject; 
typedef CGameObject* LPGAMEOBJECT;

class CGameObject
{
protected:
	float x;
	float y;

	float vx;
	float vy;

	int nx; //Direction 

	int state; 
	bool isDeleted; 
		LPTEXTURE texture;
public:
	void SetPosition(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	void SetSpeed(float vx, float vy)
	{
		this->vx = vx;
		this->vy = vy; 
	}
	
	void SetDirection(float nx)
	{
		this->nx = nx; 
	}
	int GetDirection()
	{
		return this->nx; 
	}

	int GetState()
	{
		return this->state;
	}
	void GetPosition(float& x, float& y)
	{
		x = this->x;
		y = this->y; 
	}
	void GetSpeed(float& vx, float& vy)
	{
		vx = this->vx; 
		vy = this->vy; 
	}
	virtual void Delete()
	{
		isDeleted = true;
	}
	bool IsDeleted()
	{
		return isDeleted; 
	}
	
	void RenderBoundingBox();

	CGameObject();
	CGameObject(float x = 0.0f, float y = 0.0f, LPTEXTURE texture = NULL);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0; 
	virtual void Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void Render() = 0;
	virtual void SetState(int state)
	{
		this->state = state;
	}

	virtual int IsCollidable()
	{
		return 0;
	}

	virtual void OnNoCollision(DWORD dt) {};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};
	virtual int IsBlocking() { return 1 };
	virtual int IsDirectionColliable (float nx, float ny)
	{
		return 1;
	}
	 virtual ~CGameObject();
	static bool IsDeleted (const LPGAMEOBJECT& o)
	{
		return o->IsDeleted(); 
	}
};

 
