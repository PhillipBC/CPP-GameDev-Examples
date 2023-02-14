// checking to see if already imported
#ifndef BASE_CHARACTER_H // if not defined
#define BASE_CHARACTER_H //define it

#include "raylib.h"

class BaseCharacter
{
// puiblic variables
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; } // no semicolon needed for function
    void undoMovement();
    Rectangle getCollisionRec();
    virtual void tick(float dT);
    // pure virtual function - function is only defined by children of parent class
    virtual Vector2 getScreenPos() = 0; 
    // this makes BaseCharacter an abstract class -> cant make an instance of this, only its children
    bool getAlive(){return alive;}
    void setAlive(bool isAlive){alive = isAlive;}
    //
//protected stuff
protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")}; // default texture used
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};    // idle texture
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};      // running texture
    //Vector2 screenPos{};                                                      // position on screen
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{}; // position on map

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

    Vector2 velocity{};

    // private variables
private:
    bool alive{true}; // boolean to determine if a character is alive
    //
};

#endif // end if