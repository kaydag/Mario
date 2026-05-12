#include "Buff.h"
#include "../animation/Animations.h"

Buff::Buff(float x, float y)
    : GameObject(x, y)
{
    width = BUFF_WIDTH;
    height = BUFF_HEIGHT;

    vx = 0.0f;
    vy = 0.0f;

    isStatic = true;
	isDeleted = false;
}

void Buff::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x;
    top = y;
    right = x + width;
    bottom = y + height;
}

void Buff::Update(DWORD dt, vector<GameObject*>* coObjects)
{
}

void Buff::Render()
{
    Animation* ani = Animations::GetInstance()->Get(300);

    if (ani != NULL)
    {
        ani->Render(x, y);
    }
}