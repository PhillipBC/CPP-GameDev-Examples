#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    // Window dimensions
    const int winWidth{384};
    const int winHeight{384};
    InitWindow(winWidth, winHeight, "Phil's Top Down");

    // load the map texture
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    // initialize map location
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};
    /*
        // movement speed
        float speed{4.0};
        // knight texture
        Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
        Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
        Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
        Vector2 knightPos{
            windowDimensions[0]/2.0f - 4.0f * (0.5f * (float)knight.width/6.0f),
            windowDimensions[1]/2.0f - 4.0f * (0.5f * (float)knight.height)
        };

        // 1 : facing right , -1 : facing left
        float rightLeft{1.f};

        // animation variables
        float runningTime{};
        int frame{};
        const int maxFrames{6};
        const float updateTime{1.f/12.f};
    */

    Character knight{winWidth, winHeight};
    //knight.setScreenPos(winWidth,winHeight); // replaced
    // load a single prop
    //Prop rock{Vector2{}, LoadTexture("nature_tileset/Rock.png")};
    // array of props
    Prop props[2]{
        Prop{Vector2{600.f,300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f,500.f}, LoadTexture("nature_tileset/Log.png")}
    };

    // create an enemy
    Enemy goblin{Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"), 
        LoadTexture("characters/goblin_run_spritesheet.png")
    };
    //goblin.setTarget(&knight); // done below

    // create another enemy
    Enemy slime{Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")
    };
    // array of enemy pointers
    Enemy* enemies[]{
        &goblin,
        &slime
    };

    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }
    
    //
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // delta time
        float dT{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
        // Render single prop
        //rock.Render(knight.getWorldPos());

        // Render props from array of props
        for (auto prop : props) // auto loops through array
        {
            prop.Render(knight.getWorldPos());
        }
        // if character is dead
        if (!knight.getAlive())
        {
            DrawText("GAME OVER!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue; // ignores the rest of loop iteration
        }
        else // character is alive
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5); // keep characters 0 to 5
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }
        
        // check map bounds
        knight.tick(dT);
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + winWidth > map.width * mapScale || 
            knight.getWorldPos().y + winHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }
        for (auto prop : props)
        {
            // if character and prop collide
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()),knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }
        
        //goblin.tick(dT);
        for (auto enemy : enemies)
        {
            enemy->tick(dT);
        }

        /*
            // direction vector
            Vector2 direction{}; // init as 0 in all directions

            if (IsKeyDown(KEY_A)) direction.x -= 1.0; // left
            if (IsKeyDown(KEY_D)) direction.x += 1.0; // right
            if (IsKeyDown(KEY_W)) direction.y -= 1.0; // up
            if (IsKeyDown(KEY_S)) direction.y += 1.0; // down

            // if direction is non-zero
            if (Vector2Length(direction) != 0.0)
            {   
                // move map by the opposite of direction to simulate movement
                // set mapPos = mapPos - direction (and normalize and scale by the speed)
                mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction),speed));

                // simple if else statement
                direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
                / *
                *if (direction.x < 0.f)
                *{
                *    rightLeft = -1.f
                *}
                *else
                *{
                *    rightLeft = 1.f
                *}
                * /
                knight = knight_run;
            }
            else
            {
                // not moving
                knight = knight_idle;
            }

            // draw the map
            DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

            //update animation frame
            runningTime += dT;
            if (runningTime >= updateTime)
            {
                frame = (frame + 1) % maxFrames; // next frame in sprite
                runningTime = 0.f; // reset running time
            }

            // draw the character
            // if facing left, flip the rectangle
            Rectangle source{frame * (float)knight.width / 6.f, 0.f, rightLeft * (float)knight.width / 6.f, (float)knight.height};
            Rectangle dest{knightPos.x, knightPos.y, 4.f * (float)knight.width/6.f, 4.f * (float)knight.height};
            DrawTexturePro(knight, source, dest, origin, 0.f, WHITE);
        */

       // if the sword is swung by pressing the mouse button
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // goblin.setAlive(false);
            for (auto enemy : enemies)
            {
                //if the weapon collision box collides with the goblin collision rec
                if(CheckCollisionRecs(enemy->getCollisionRec(),knight.getWeaponCollisionRec()))
                {
                    // kill the goblin
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}