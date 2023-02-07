#include "Character.h"
#include "raymath.h"


Character::Character()
{
    width = texture.width / maxFrames;
    height = texture.height;
}

// fully qualifying the function to the class Character
void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        (float)winWidth / 2.0f - 4.0f * (0.5f * width),
        (float)winHeight / 2.0f - 4.0f * (0.5f * height)};
}

void Character::tick(float dT)
{
    // store position before movement
    worldPosLastFrame = worldPos;
    // direction vector
    Vector2 direction{}; // init as 0 in all directions

    if (IsKeyDown(KEY_A))
        direction.x -= 1.0; // left
    if (IsKeyDown(KEY_D))
        direction.x += 1.0; // right
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0; // up
    if (IsKeyDown(KEY_S))
        direction.y += 1.0; // down

    // if direction is non-zero
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
    Rectangle dest{screenPos.x, screenPos.y, 4.f * width, 4.f * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

void Character::undoMovement()
{
    worldPos = worldPosLastFrame;
}
