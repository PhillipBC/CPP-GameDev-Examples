#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
// puiblic variables
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    //Vector2 getWorldPos() {return worldPos;}
    virtual void tick(float dT) override;
    //void undoMovement();
    //Rectangle getCollisionRec();
    void setTarget(Character* character){ target = character; };
    //

// private variables
private:
    Character* target;
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