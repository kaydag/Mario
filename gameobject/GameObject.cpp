#include <vector>

#include <d3dx10.h>
#include "GameObject.h"
#include "debug.h"
#include "Game.h"

CGameObject::CGameObject()
{
	this->x = 0;
	this->y = 0;

	this->vx = 0;
	this->vy = 0;

	this->nx = 1;

	this->state = -1;

	this->isDeleted = false; 

	this->texture = NULL; 
}
CGameObject::CGameObject(float x, float y, LPTEXTURE texture)
{
	this->x = x;
	this->y = y;
	this->texture = texture;

	this->vx = 0;
	this->vy = 0;

	this->nx = 1;

	this->state = -1;

	this->isDeleted = false;

}

void CGameObject::RenderBoundingBox()
{

}
CGameObject::~CGameObject()
{

}



