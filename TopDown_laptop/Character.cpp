#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) :
    windowWidth(winWidth),
    windowHeight(winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;

    // center of the screen
    //screenPos = {
        // better casting function -> does type checking
    //    static_cast<float>(winWidth) / 2.0f - scale * (0.5f * width),
    //    static_cast<float>(winHeight) / 2.0f - scale * (0.5f * height)};
}

Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)
    };
}

// fully qualifying the function to the class Character
/*void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        (float)winWidth / 2.0f - 4.0f * (0.5f * width),
        (float)winHeight / 2.0f - 4.0f * (0.5f * height)};
}
*/

void Character::tick(float dT)
{
    // store position before movement
    //worldPosLastFrame = worldPos;

    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0; // left
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0; // right
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0; // up
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0; // down

    BaseCharacter::tick(dT);
    // direction vector
    //Vector2 direction{}; // init as 0 in all directions
    // replaced in BaseCharacter class by velocity vector

    // if direction is non-zero
    /*  
        if (Vector2Length(direction) != 0.0)
        {
            // move map by the opposite of direction to simulate movement
            // set worldPos = worldPos + direction (and normalize and scale by the speed)
            worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
            // simple if else statement
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            texture = run;
        }
        else
        {
            // not moving
            texture = idle;
        }
    */
    /*
    // update animation frame
    runningTime += dT;
    if (runningTime >= updateTime)
    {
        frame = (frame + 1) % maxFrames; // next frame in sprite
        runningTime = 0.f;               // reset running time
    }

    // draw the character
    // if facing left, flip the rectangle
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
    */
    

    // weapon stuff
    Vector2 origin{}; // origin of weapon texture
    Vector2 offset{}; // offset
    float rotation{}; // for swinging sword
    if (rightLeft > 0.f)
    {
        origin = {0.f, weapon.height * scale};
        offset = {35.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = 35.f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = -35.f;
    }
    
    // draw the sword
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    DrawRectangleLines(
        weaponCollisionRec.x,
        weaponCollisionRec.y,
        weaponCollisionRec.width,
        weaponCollisionRec.height,
        RED
    );
}

/*
void Character::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle Character::getCollisionRec()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale
    };
}
*/