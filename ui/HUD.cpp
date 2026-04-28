#include "HUD.h"

#define TEX_HUD 20

HUD* HUD::__instance = NULL;

HUD::HUD()
{
    score = 0;
    coins = 0;
    time = 300;
}

void HUD::LoadSprites()
{
    Sprites* sprites = Sprites::GetInstance();

	sprites->Add(3000, 0, 0, 640, 95, TEX_HUD); //3000: Nền HUD
}

HUD* HUD::GetInstance()
{
    if (__instance == NULL) __instance = new HUD();
    return __instance;
}

void HUD::Update(DWORD dt)
{
    // Logic đếm ngược thời gian
}

void HUD::DrawNumber(int number, float x, float y)
{
    std::string strNum = std::to_string(number);
    float currentX = x;
    float charWidth = 16.0f;

    for (char c : strNum)
    {
        int digit = c - '0';
        int spriteId = 1000 + digit; // Yêu cầu ID 1000-1009 là các số 0-9

        Sprite* sprite = Sprites::GetInstance()->Get(spriteId);
        if (sprite)
        {
            sprite->Draw(currentX, y);
        }
        currentX += charWidth;
    }
}

void HUD::Render()
{
    Sprites* sprites = Sprites::GetInstance();
    float yPos = 450.0f;

    if (sprites->Get(3000)) sprites->Get(3000)->Draw(0.0f, 0.0f);

    DrawNumber(score, 20.0f, yPos);   // Điểm
    DrawNumber(coins, 300.0f, yPos);  // Xu
    DrawNumber(time, 550.0f, yPos);   // Thời gian
}