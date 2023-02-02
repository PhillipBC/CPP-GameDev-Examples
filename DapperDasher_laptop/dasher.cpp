#include "raylib.h"

// define custom data type 
struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

// function to check if scarfy is on ground
bool isOnGround(AnimData data, int windowHeight)
{   
    // return true or false
    return data.pos.y >= windowHeight - data.rec.height;
}

// function to update animation frame
AnimData updateAnimData(AnimData data, float dT, int maxFrame)
{
    // max frame should be length(sprite)-1
    // update running time
    data.runningTime += dT;

    // update animation frame
    if (data.runningTime >= data.updateTime)
    {
        data.rec.x = data.frame * data.rec.width;
        // update frame counter by 1, and loop back to 0 at end
        data.frame = (data.frame + 1) % maxFrame;
        // reset counter
        data.runningTime = 0.0;
    }
    return data;
}

int main()
{
    // Window dimensions
    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;
    //const int win_width{512};
    //const int win_height{380};

    // Open the window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dasher Dapper!");

    // acceleration due to gravity (pixels/second)/second
    const int gravity{1'000};
    // jumpy velocity (pixels/second)
    const int jumpVel{-600};

    // nebula stuff
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png"); // 8 x 8 grid of squares (800x800)
    const int num_neb{3};
    /*
    AnimData nebData{
        {0.0, 0.0, nebula.width / 8, nebula.height / 8},                  // Rectangle rec
        {windowDimensions[1] + nebData.rec.width, windowDimensions[1] - nebData.rec.height}, // Vector2 pos
        0,                                                                // int frame
        1.0 / 12.0,                                                       // float updateTime
        0.0                                                               // float running time
    };
    AnimData neb2Data{
        {0.0, 0.0, nebula.width / 8, nebula.height / 8},                                     // Rectangle rec
        {windowDimensions[1] + 300 + nebData.rec.width, windowDimensions[1] - nebData.rec.height}, // Vector2 pos
        0,                                                                                   // int frame
        1.0 / 16.0,                                                                          // float updateTime
        0.0                                                                                  // float running time
    };
    */

    // Array of nebulae 
    AnimData nebulae[num_neb]{};
    // initialize each nebula 
    for (int i = 0; i < num_neb; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width / 8;
        nebulae[i].rec.height = nebula.height / 8;
        //nebulae[i].pos.x = 0.0; different for each one
        nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;

        nebulae[i].pos.x = windowDimensions[0] + (i * 300);
    }

    /*
    // nebulae[0].pos.x = windowDimensions[0];
    // nebulae[1].pos.x = windowDimensions[0] + 300;
    /
    /
    // rectangle dims
    / Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    // neb sprite position
    / Vector2 nebPos{win_width + nebRec.width, win_height - nebRec.height};

    // nebula animation variables
    / int nebFrame{0};
    / const float nebUpdateTime{1.0/12.0};
    / float nebRunningTime{0.0};
    */

    float finishLine{nebulae[num_neb-1].pos.x+20};

    // nebula X velocity (pixels/second)
    int nebVel{-200};

    // compound data types (from raylib)
    // sprite textures
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData; // custom data type
    // Rectangle
    scarfyData.rec.width = scarfy.width / 6; // 1/6th of the sprite sheet
    scarfyData.rec.height = scarfy.height;       // height of sprite sheet
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    // Position
    scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2; // place center of scarfy in center of windows
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;       // place bottom of scarfy on bottom of window
    // frame & times
    scarfyData.frame = 0; // animation frame (counter)
    scarfyData.updateTime = 1.0 / 12.0; // how many times to update the frame per sec.
    scarfyData.runningTime = 0;         // How much time has passed since last update

    // sprite dimensions
    /* No longer necessary after custom data type
    / Rectangle scarfyRec;
    / scarfyRec.width = scarfy.width/6; // 1/6th of the sprite sheet
    / scarfyRec.height = scarfy.height; // height of sprite sheet
    / scarfyRec.x = 0; // initial position
    / scarfyRec.y = 0;

    // sprite position
    / Vector2 scarfyPos;
    / scarfyPos.x = win_width/2 - scarfyRec.width/2; // place center of scarfy in center of windows
    / scarfyPos.y = win_height - scarfyRec.height; // place bottom of scarfy on bottom of window

    // animation frame (counter)
    / int frame{0};
    // how many times to update the frame per sec.
    / const float updateTime{1.0/12.0}; 
    // How much time has passed since last update
    / float runningTime{0.0};
    */

    int velocity{0}; // starts not moving (pixels/second)
    bool isInAir{false}; // starts on the ground
    bool collision{false}; // collision detection

    // load background texture
    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};
    // midground & foreground
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float mgX{};
    float fgX{};

    // Sets the refresh rate of the window
    SetTargetFPS(60);

    // while the window has not closed
    while (!WindowShouldClose())
    {
        // delta time
        const float dT{GetFrameTime()};

        // start drawing
        BeginDrawing();
        // set a white background
        ClearBackground(WHITE);

        // move background by 20 pixels/sec
        bgX -= (20 * dT);
        if (bgX <= -background.width*2) // 2 for the scale
        {
            bgX = 0.0;
        }
        mgX -= (40 * dT);
        if (mgX <= -midground.width * 2) // 2 for the scale
        {
            mgX = 0.0;
        }
        fgX -= (80 * dT);
        if (fgX <= -foreground.width * 2) // 2 for the scale
        {
            fgX = 0.0;
        }

        // Draw background file
        Vector2 bg1Pos{bgX, 0.0};                           // background position
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE); // scaled up by 2 to fit the window
        Vector2 bg2Pos{bgX + background.width*2, 0.0};      // background dupe position (2* for scale)
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE); // scaled up by 2 to fit the window
        // Draw midground file
        Vector2 mg1Pos{mgX, 0.0};                           // midground position
        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);  // scaled up by 2 to fit the window
        Vector2 mg2Pos{mgX + midground.width * 2, 0.0};     // midground dupe position (2* for scale)
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);  // scaled up by 2 to fit the window
        // Draw foreground file
        Vector2 fg1Pos{fgX, 0.0};                           // foreground position
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE); // scaled up by 2 to fit the window
        Vector2 fg2Pos{fgX + foreground.width * 2, 0.0};     // foreground dupe position (2* for scale)
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE); // scaled up by 2 to fit the window

        // ground check (call function)
        if (isOnGround(scarfyData, windowDimensions[1]))
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // update velocity (gravity)
            velocity += gravity*dT;
            isInAir = true;
        }
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // update nebulae positions
        for (int i = 0; i < num_neb; i++)
        {
            nebulae[i].pos.x += nebVel * dT;
        }
        // update finish line
        finishLine += nebVel * dT;

        /*// update nebula X position
        nebulae[0].pos.x += nebVel * dT;
        // update 2nd nebula X position
        nebulae[1].pos.x += nebVel * dT;
        */
        // update scarfy Y position
        scarfyData.pos.y += velocity * dT;

        // update scarfy animation frame
        if (!isInAir)
        {
            /*
            // update running time
            scarfyData.runningTime += dT;

            // update animation frame
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                // update frame counter by 1, and loop back to 0 at end
                scarfyData.frame = (scarfyData.frame + 1) % 5;
                // reset counter
                scarfyData.runningTime = 0.0;
            }
            */
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }

        for (int i = 0; i < num_neb; i++)
        {
            // update Nebula animation frame
            /*
            nebulae[i].runningTime += dT;
            if (nebulae[i].runningTime >= nebulae[0].updateTime)
            {
                nebulae[i].runningTime = 0.0;
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame = (nebulae[i].frame + 1) % 8;
            }
            */
            nebulae[i] = updateAnimData(nebulae[i], dT, 8);
        }

        for (AnimData nebula : nebulae)
        {
            float pad{50}; // removing white space around nebulae
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2*pad,
                nebula.rec.height - 2*pad
            };
            Rectangle scarfyRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height
            };
            if (CheckCollisionRecs(nebRec,scarfyRec))
            {
                collision = true;
            }
        }
        if (collision)
        {
            DrawText("GAME OVER!", windowDimensions[0]/4, windowDimensions[1]/2, 40, RED);
        }
        else if (scarfyData.pos.x >= finishLine)
        {
            DrawText("YOU WIN!", windowDimensions[0] / 4, windowDimensions[1] / 2, 40, RED);
        }
        else
        {
            for (int i = 0; i < num_neb; i++)
            {
                // Draw Nebulae
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }

            /*
            // update Nebula animation frame
            nebulae[0].runningTime+= dT;
            if (nebulae[0].runningTime >= nebulae[0].updateTime)
            {
                nebulae[0].runningTime = 0.0;
                nebulae[0].rec.x = nebulae[0].frame* nebulae[0].rec.width;
                nebulae[0].frame = (nebulae[0].frame+ 1) % 8;
            }
            // update 2nd Nebula animation fram
            nebulae[1].runningTime += dT;
            if (nebulae[1].runningTime >= nebulae[1].updateTime)
            {
                nebulae[1].runningTime = 0.0;
                nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
                nebulae[1].frame = (nebulae[1].frame + 1) % 8;
            }
            // Draw nebula
            DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);
            // Draw 2nd nebula
            DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, WHITE);
            */
            // Draw scarfy
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        }

        // end drawing
        EndDrawing();
    }
    // need to unload textures
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
}