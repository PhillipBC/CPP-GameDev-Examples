#include "Enemy.h"
#include "raymath.h"

// inherits variables from BaseCharacter, don't initialize them in 
Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    
    width = texture.width / maxFrames;
    height = texture.height;
}

void Enemy::tick(float dT)
{   
    // -> lets you call functions of the object whos pointer we are using
    screenPos = Vector2Subtract(worldPos, target->getWorldPos());
    BaseCharacter::tick(dT);
    /*
    // store position before movement
    worldPosLastFrame = worldPos;

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
}
/*
    void Enemy::undoMovement()
    {
        worldPos = worldPosLastFrame;
    }

    Rectangle Enemy::getCollisionRec()
    {
        return Rectangle{
            screenPos.x,
            screenPos.y,
            width * scale,
            height * scale
        };
    }
*/
