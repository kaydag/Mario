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
    int currentScore;
    int currentCoins;

    // Mảng lưu 3 thẻ bài (0: Trống, 1: Nấm, 2: Hoa, 3: Sao)
    int cards[3];

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
    void DrawCards(); // Hàm vẽ 3 thẻ bài

    // Các hàm để bên logic truyền dữ liệu vào
    void SetPMeter(int level) { currentPMeter = level; }
    void SetPlayer(int player) { currentPlayer = player; }
    void SetScore(int score) { currentScore = score; }
    void SetCoins(int coins) { currentCoins = coins; }

    // Set loại thẻ (0: Trống, 1: Nấm, 2: Hoa, 3: Sao)
    void SetCard(int slot, int cardType) {
        if (slot >= 0 && slot < 3) cards[slot] = cardType;
    }

    //Xóa sạch 3 thẻ sau khi ăn đủ 3 cái
    void ClearCards() {
        cards[0] = 0;
        cards[1] = 0;
        cards[2] = 0;
    }
};