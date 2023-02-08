#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale};
}

void BaseCharacter::tick(float dT)
{
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
}