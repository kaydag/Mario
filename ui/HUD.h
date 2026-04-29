#pragma once
#include <string>
#include <Windows.h>
#include "../render/Sprites.h"

class HUD
{
private:
    static HUD* __instance;

    int time;
    DWORD timeAccumulator;

    DWORD pMeterBlinkTime;
    bool isPMeterBlinkVisible;

    int currentPMeter;
    int currentPlayer;
    int currentScore; // Thêm biến lưu điểm
    int currentCoins; // Thêm biến lưu xu

    void DrawString(std::string text, float x, float y);

public:
    HUD();
    static HUD* GetInstance();
    void LoadSprites();

    void Update(DWORD dt);
    void Render();

    void DrawCoins(int coins);
    void DrawScore(int score);
    void DrawTime(int time);
    void DrawPMeter(int powerLevel);
    void DrawPlayerIcon(int player);

    // Các hàm để bên logic truyền dữ liệu vào
    void SetPMeter(int level) { currentPMeter = level; }
    void SetPlayer(int player) { currentPlayer = player; }
    void SetScore(int score) { currentScore = score; }
    void SetCoins(int coins) { currentCoins = coins; }
};