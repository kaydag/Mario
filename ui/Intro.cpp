#include "Intro.h"

Intro::Intro()
{
    currentOption = 1;
    isDone = false;

    curtainY = 0.0f;
    curtainSpeed = 0.2f;
    isCurtainUp = false;

    // Tăng số này lên bằng hoặc lớn hơn chiều cao ảnh màn nhung của bạn
    curtainHeight = 600.0f;
}

void Intro::Update(DWORD dt)
{
    if (!isCurtainUp)
    {
        curtainY += curtainSpeed * dt;

        // Chỉ ẩn khi màn nhung đã trượt qua hết giới hạn curtainHeight
        if (abs(curtainY) > curtainHeight)
        {
            isCurtainUp = true;
        }
    }

    if (isCurtainUp)
    {
        if (GetAsyncKeyState(VK_UP) & 0x8000)
        {
            currentOption = 1;
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
        {
            currentOption = 2;
        }

        if ((GetAsyncKeyState(VK_RETURN) & 0x8000) || (GetAsyncKeyState(VK_SPACE) & 0x8000))
        {
            isDone = true;
        }
    }
}

void Intro::Render()
{
    Sprites* sprites = Sprites::GetInstance();

    if (sprites->Get(2001)) sprites->Get(2001)->Draw(170.0f, 275.0f); // Logo
    if (sprites->Get(2002)) sprites->Get(2002)->Draw(220.0f, 125.0f); // Text

    float cursorX = 185.0f;
    float cursorY = (currentOption == 1) ? 157.0f : 123.0f;
    if (sprites->Get(2003)) sprites->Get(2003)->Draw(cursorX, cursorY);

    if (!isCurtainUp)
    {
        if (sprites->Get(2000)) sprites->Get(2000)->Draw(0.0f, curtainY);
    }
}