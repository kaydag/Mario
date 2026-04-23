#include "Intro.h"

#define TEX_INTRO 30

void Intro::LoadSprites()
{
    Sprites* sprites = Sprites::GetInstance();

    sprites->Add(2000, 8, 19, 648, 434, TEX_INTRO);    // 2000: Nền màn nhung đỏ
    sprites->Add(2004, 8, 434, 648, 499, TEX_INTRO);   // 2004: Sàn caro
    sprites->Add(2001, 653, 19, 1293, 312, TEX_INTRO); // 2001: Logo Super Mario
    sprites->Add(2002, 411, 601, 611, 651, TEX_INTRO); // 2002: Chữ 1 Player / 2 Player
    sprites->Add(2003, 388, 601, 409, 620, TEX_INTRO); // 2003: Con trỏ (Nấm)

    // THÊM: ID 2005 cho nền màu mới. Hãy sửa lại toạ độ (left, top, right, bottom) cho khớp với ảnh của bạn.
    sprites->Add(2005, 1300, 19, 1940, 434, TEX_INTRO);     // 2005: Nền màu mới
}

Intro::Intro()
{
    currentOption = 1;
    isDone = false;

    curtainY = 60.0f;
    curtainSpeed = 0.2f;
    isCurtainUp = false;
    curtainHeight = 500.0f;

    logoY = 500.0f;
    logoSpeed = 0.2f;
    isLogoDown = false;
}

void Intro::Update(DWORD dt)
{
    if (!isCurtainUp)
    {
        curtainY += curtainSpeed * dt;

        if (abs(curtainY) > curtainHeight)
        {
            isCurtainUp = true;
        }
    }
    else if (!isLogoDown)
    {
        logoY -= logoSpeed * dt;

        if (logoY <= 175.0f)
        {
            logoY = 175.0f;
            isLogoDown = true;
        }
    }
    else
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

    // NẾU LOGO ĐÃ HẠ XUỐNG XONG
    if (isLogoDown)
    {
        // 1. Vẽ nền màu mới ở vị trí ban đầu của màn nhung (Y = 60.0f)
        if (sprites->Get(2005)) sprites->Get(2005)->Draw(0.0f, 60.0f);

        // 2. Vẽ lại sàn caro lên trên nền mới
        if (sprites->Get(2004)) sprites->Get(2004)->Draw(0.0f, 0.0f);

        // 3. Hiện Text và Con trỏ
        if (sprites->Get(2002)) sprites->Get(2002)->Draw(220.0f, 100.0f);

        float cursorX = 185.0f;
        float cursorY = (currentOption == 1) ? 132.0f : 98.0f;
        if (sprites->Get(2003)) sprites->Get(2003)->Draw(cursorX, cursorY);

        // GHI CHÚ: Cố tình KHÔNG vẽ ID 2001 (Logo) và ID 2000 (Nền nhung) để xóa chúng khỏi màn hình.
    }
    // NẾU LOGO CHƯA XUỐNG XONG HOẶC MÀN NHUNG ĐANG KÉO
    else
    {
        // Vẽ sàn caro dưới cùng
        if (sprites->Get(2004)) sprites->Get(2004)->Draw(0.0f, 0.0f);

        // Vẽ Logo đang rơi
        if (sprites->Get(2001)) sprites->Get(2001)->Draw(0.0f, logoY);

        // Vẽ màn nhung đè lên trên cùng 
        if (!isCurtainUp)
        {
            if (sprites->Get(2000)) sprites->Get(2000)->Draw(0.0f, curtainY);
        }
    }
}