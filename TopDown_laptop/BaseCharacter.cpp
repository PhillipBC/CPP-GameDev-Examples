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
        getScreenPos().x,
        getScreenPos().y,
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

    if (Vector2Length(velocity) != 0.0)
    {
        // move map by the opposite of direction to simulate movement
        // set worldPos = worldPos + direction (and normalize and scale by the speed)
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        // simple if else statement
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        // not moving
        texture = idle;
    }
    velocity = {};

    // draw the character
    // if facing left, flip the rectangle
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}