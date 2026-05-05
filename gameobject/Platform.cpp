#include "Platform.h"
#include "../animation/Animations.h"

Platform::Platform(float x, float y, float width, float height, int animationId)
    : GameObject(x, y)
{
    this->width = width;
    this->height = height;
    this->animationId = animationId;
    this->isStatic = true;
}

void Platform::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x;
    top = y;
    right = x + this->width;
    bottom = y + this->height;
}

void Platform::Render()
{

    Animation* ani = Animations::GetInstance()->Get(this->animationId);
    if (ani != NULL) ani->Render(x, y);
}