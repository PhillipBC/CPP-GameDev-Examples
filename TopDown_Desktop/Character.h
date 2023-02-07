#include "raylib.h"

class Character
{
// puiblic variables
public:
    Character();
    Vector2 getWorldPos() { return worldPos; } // no semicolon needed for function
    void setScreenPos(int winWidth, int winHeight);
    void tick(float dT);
    void undoMovement();
    //

// private variables
private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")}; // default texture used
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};    // idle texture
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};      // running texture
    Vector2 screenPos{};                                                      // position on screen
    Vector2 worldPos{};  
    Vector2 worldPosLastFrame{};                                                     // position on map

    // 1 : facing right , -1 : facing left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};

    float speed{4.f};
    float width{};
    float height{};

    //
};