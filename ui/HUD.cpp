#include "HUD.h"

#define TEX_HUD 20
#define HUD_COINS_X 353.0f
#define HUD_COINS_Y 38.0f
#define HUD_SCORE_X 165.0f
#define HUD_SCORE_Y 19.0f
#define HUD_TIME_X 334.0f
#define HUD_TIME_Y 19.0f
#define HUD_PMETER_X 165.0f 
#define HUD_PMETER_Y 38.0f

// Khai báo tọa độ vẽ Icon M/L
#define HUD_ICON_X 52.0f 
#define HUD_ICON_Y 19.0f 

// Khai báo tọa độ vẽ 3 ô thẻ bài (Bạn tự căn chỉnh lại cho khớp khung vuông)
#define HUD_CARD_1_X 426.0f
#define HUD_CARD_2_X 482.0f
#define HUD_CARD_3_X 538.0f
#define HUD_CARD_Y   14.0f

HUD* HUD::__instance = NULL;

HUD::HUD()
{
    time = 300;
    timeAccumulator = 0;

    pMeterBlinkTime = 0;
    isPMeterBlinkVisible = true;

    currentPMeter = 0;
    currentPlayer = 1;
    currentScore = 0;
    currentCoins = 0;

    // Ban đầu 3 ô thẻ đều trống rỗng
    cards[0] = 0;
    cards[1] = 0;
    cards[2] = 0;
}

HUD* HUD::GetInstance()
{
    if (__instance == NULL) __instance = new HUD();
    return __instance;
}

void HUD::LoadSprites()
{
    Sprites* sprites = Sprites::GetInstance();

    sprites->Add(3000, 0, 0, 640, 75, TEX_HUD); // Nền HUD trống

    sprites->Add(1000, 649, 75, 668, 91, TEX_HUD);
    sprites->Add(1001, 669, 75, 688, 91, TEX_HUD);
    sprites->Add(1002, 689, 75, 708, 91, TEX_HUD);
    sprites->Add(1003, 709, 75, 728, 91, TEX_HUD);
    sprites->Add(1004, 729, 75, 748, 91, TEX_HUD);
    sprites->Add(1005, 749, 75, 768, 91, TEX_HUD);
    sprites->Add(1006, 769, 75, 788, 91, TEX_HUD);
    sprites->Add(1007, 789, 75, 808, 91, TEX_HUD);
    sprites->Add(1008, 809, 75, 828, 91, TEX_HUD);
    sprites->Add(1009, 829, 75, 848, 91, TEX_HUD);

    sprites->Add(3010, 932, 76, 951, 92, TEX_HUD); // Mũi tên sáng
    sprites->Add(3011, 953, 76, 988, 92, TEX_HUD); // Chữ P sáng

    // Sprite cho chữ M và L
    sprites->Add(3012, 601, 86, 639, 102, TEX_HUD); // 3012: Chữ M
    sprites->Add(3013, 601, 103, 639, 119, TEX_HUD); // 3013: Chữ L

    // Sprite cho 3 Thẻ bài (Bạn điền tọa độ cắt ảnh nhé)
    sprites->Add(3014, 1025, 83, 1068, 130, TEX_HUD); // 3014: Nấm
    sprites->Add(3015, 1081, 83, 1124, 130, TEX_HUD); // 3015: Hoa
    sprites->Add(3016, 1137, 83, 1180, 130, TEX_HUD); // 3016: Sao
}

void HUD::Update(DWORD dt)
{
    if (time > 0)
    {
        timeAccumulator += dt;
        if (timeAccumulator >= 1000)
        {
            time--;
            timeAccumulator = 0;
        }
    }

    pMeterBlinkTime += dt;
    if (pMeterBlinkTime >= 150)
    {
        isPMeterBlinkVisible = !isPMeterBlinkVisible;
        pMeterBlinkTime = 0;
    }

    // ==========================================
    // CODE TEST: TỰ ĐỘNG THÊM THẺ BÀI RANDOM MỖI 2 GIÂY
    // ==========================================
    static DWORD testCardTimer = 0;
    static int testCardStep = 0;

    testCardTimer += dt;
    if (testCardTimer >= 2000) // Mỗi 2000ms (2 giây)
    {
        testCardStep++;

        if (testCardStep >= 1 && testCardStep <= 3)
        {
            // Random ra số 1, 2 hoặc 3
            int randomItem = (rand() % 3) + 1;
            cards[testCardStep - 1] = randomItem; // Gán item vào ô tương ứng (0, 1, 2)
        }
        else if (testCardStep == 4)
        {
            // Reset xóa sạch thẻ
            cards[0] = 0;
            cards[1] = 0;
            cards[2] = 0;
            testCardStep = 0; // Bắt đầu lại chu trình
        }

        testCardTimer = 0; // Reset đồng hồ đếm
    }
}

void HUD::Render()
{
    Sprites* sprites = Sprites::GetInstance();

    if (sprites->Get(3000)) sprites->Get(3000)->Draw(0.0f, 0.0f);

    DrawScore(currentScore);
    DrawCoins(currentCoins);
    DrawTime(time);
    DrawPMeter(currentPMeter);
    DrawPlayerIcon(currentPlayer);

    // Gọi hàm vẽ 3 thẻ bài
    DrawCards();
}

void HUD::DrawString(std::string text, float x, float y)
{
    float currentX = x;
    float charWidth = 19.0f;

    for (char c : text)
    {
        if (c >= '0' && c <= '9')
        {
            int spriteId = 1000 + (c - '0');
            Sprite* sprite = Sprites::GetInstance()->Get(spriteId);

            if (sprite)
            {
                sprite->Draw(currentX, y);
            }
        }
        currentX += charWidth;
    }
}

void HUD::DrawCoins(int coins)
{
    std::string str = std::to_string(coins);
    while (str.length() < 2) str = "0" + str;

    DrawString(str, HUD_COINS_X, HUD_COINS_Y);
}

void HUD::DrawScore(int score)
{
    std::string str = std::to_string(score);
    while (str.length() < 7) str = "0" + str;

    DrawString(str, HUD_SCORE_X, HUD_SCORE_Y);
}

void HUD::DrawTime(int t)
{
    std::string str = std::to_string(t);
    while (str.length() < 3) str = "0" + str;

    DrawString(str, HUD_TIME_X, HUD_TIME_Y);
}

void HUD::DrawPMeter(int powerLevel)
{
    Sprites* sprites = Sprites::GetInstance();
    float currentX = HUD_PMETER_X;
    float arrowWidth = 19.0f;

    for (int i = 0; i < 6; i++)
    {
        if (powerLevel > i)
        {
            if (sprites->Get(3010)) sprites->Get(3010)->Draw(currentX, HUD_PMETER_Y);
        }
        currentX += arrowWidth;
    }

    currentX += 1.0f;

    if (powerLevel >= 7)
    {
        if (isPMeterBlinkVisible)
        {
            if (sprites->Get(3011)) sprites->Get(3011)->Draw(currentX, HUD_PMETER_Y);
        }
    }
}

void HUD::DrawPlayerIcon(int player)
{
    Sprites* sprites = Sprites::GetInstance();

    if (player == 1)
    {
        if (sprites->Get(3012)) sprites->Get(3012)->Draw(HUD_ICON_X, HUD_ICON_Y);
    }
    else if (player == 2)
    {
        if (sprites->Get(3013)) sprites->Get(3013)->Draw(HUD_ICON_X, HUD_ICON_Y);
    }
}

void HUD::DrawCards()
{
    Sprites* sprites = Sprites::GetInstance();
    float cardX[3] = { HUD_CARD_1_X, HUD_CARD_2_X, HUD_CARD_3_X };

    for (int i = 0; i < 3; i++)
    {
        int spriteId = 0;

        if (cards[i] == 1) spriteId = 3014;      // Nấm
        else if (cards[i] == 2) spriteId = 3015; // Hoa
        else if (cards[i] == 3) spriteId = 3016; // Sao

        // Nếu có ID hợp lệ thì vẽ ra ô tương ứng
        if (spriteId != 0 && sprites->Get(spriteId))
        {
            sprites->Get(spriteId)->Draw(cardX[i], HUD_CARD_Y);
        }
    }
}