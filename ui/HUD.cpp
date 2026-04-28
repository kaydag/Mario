#include "../ui/HUD.h"

#define TEX_HUD 20
#define HUD_COINS_X 353.0f
#define HUD_COINS_Y 38.0f
#define HUD_SCORE_X 165.0f
#define HUD_SCORE_Y 19.0f
#define HUD_TIME_X 334.0f
#define HUD_TIME_Y 19.0f
#define HUD_PMETER_X 165.0f 
#define HUD_PMETER_Y 37.0f

HUD* HUD::__instance = NULL;

HUD::HUD()
{
    // Khởi tạo thời gian 300 và bộ đếm 0
    time = 300;
    timeAccumulator = 0;
}

HUD* HUD::GetInstance()
{
    if (__instance == NULL) __instance = new HUD();
    return __instance;
}

void HUD::LoadSprites()
{
    Sprites* sprites = Sprites::GetInstance();

    sprites->Add(3000, 0, 0, 640, 75, TEX_HUD); // 3000: Nền HUD trống

    sprites->Add(1000, 649, 75, 668, 91, TEX_HUD); // Cắt số 0
    sprites->Add(1001, 669, 75, 688, 91, TEX_HUD); // Cắt số 1
    sprites->Add(1002, 689, 75, 708, 91, TEX_HUD); // Cắt số 2
    sprites->Add(1003, 709, 75, 728, 91, TEX_HUD); // Cắt số 3
    sprites->Add(1004, 729, 75, 748, 91, TEX_HUD); // Cắt số 4
    sprites->Add(1005, 749, 75, 768, 91, TEX_HUD); // Cắt số 5
    sprites->Add(1006, 769, 75, 788, 91, TEX_HUD); // Cắt số 6
    sprites->Add(1007, 789, 75, 808, 91, TEX_HUD); // Cắt số 7
    sprites->Add(1008, 809, 75, 828, 91, TEX_HUD); // Cắt số 8
    sprites->Add(1009, 829, 75, 848, 91, TEX_HUD); // Cắt số 9

    sprites->Add(3010, 932, 76, 951, 92, TEX_HUD); // 3010: Mũi tên sáng (màu trắng)
    sprites->Add(3011, 953, 76, 988, 92, TEX_HUD); // 3011: Chữ P sáng (nhấp nháy)
}

void HUD::Update(DWORD dt)
{
    // Cập nhật giảm thời gian
    if (time > 0)
    {
        timeAccumulator += dt;
        if (timeAccumulator >= 1000) // Đủ 1000ms = 1 giây
        {
            time--;
            timeAccumulator = 0; // Trả bộ đếm về 0 để đếm giây tiếp theo
        }
    }
}

void HUD::Render()
{
    Sprites* sprites = Sprites::GetInstance();

    // Vẽ nền HUD
    if (sprites->Get(3000)) sprites->Get(3000)->Draw(0.0f, 0.0f);

    DrawScore(0);
    DrawCoins(0);

    // Gọi hàm vẽ thời gian bằng biến time nội bộ
    DrawTime(time);
}

void HUD::DrawString(std::string text, float x, float y)
{
    float currentX = x;
    float charWidth = 19.0f; // Chiều rộng 1 số là 19px theo đúng ảnh cắt

    for (char c : text)
    {
        // Chỉ xử lý nếu ký tự là số (0-9)
        if (c >= '0' && c <= '9')
        {
            int spriteId = 1000 + (c - '0');
            Sprite* sprite = Sprites::GetInstance()->Get(spriteId);

            if (sprite)
            {
                sprite->Draw(currentX, y);
            }
        }

        // Dịch X sang phải để vẽ số tiếp theo
        currentX += charWidth;
    }
}

void HUD::DrawCoins(int coins)
{
    std::string str = std::to_string(coins);
    while (str.length() < 2) str = "0" + str; // Đệm đủ 2 số

    DrawString(str, HUD_COINS_X, HUD_COINS_Y);
}

void HUD::DrawScore(int score)
{
    std::string str = std::to_string(score);
    while (str.length() < 7) str = "0" + str; // Đệm đủ 7 số

    DrawString(str, HUD_SCORE_X, HUD_SCORE_Y);
}

void HUD::DrawTime(int t)
{
    std::string str = std::to_string(t);
    while (str.length() < 3) str = "0" + str; // Đệm đủ 3 số

    DrawString(str, HUD_TIME_X, HUD_TIME_Y);
}