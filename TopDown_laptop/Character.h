// checking to see if already imported
#ifndef CHARACTER_H // if not defined
#define CHARACTER_H // define it

#include "raylib.h"
#include "BaseCharacter.h"

// inherits publicly from BaseCharacter
class Character : public BaseCharacter
{
// puiblic variables
public:
    // everything is inherited from BaseCharacter now
    Character(int winWidth, int winHeight);
    //Vector2 getWorldPos() { return worldPos; } // no semicolon needed for function
    //void setScreenPos(int winWidth, int winHeight); // replaced 
    virtual void tick(float dT) override; // override of parent version
    virtual Vector2 getScreenPos() override;
    //void tick(float dT);
    //void undoMovement();
    //Rectangle getCollisionRec();
    //

// private variables
private:
    int windowWidth{};
    int windowHeight{};

    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    /*
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

    float scale{4.0f}; // scale up texture
    */
    //
};

#endif // end if