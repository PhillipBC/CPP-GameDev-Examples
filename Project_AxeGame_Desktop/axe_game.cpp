#include "raylib.h"

int main()
{
    // Window dimensions
    int width{500};
    int height{300};
    // Open the window
    InitWindow(width, height, "Phillip's Window");

    // Circle coordinates
    int circle_x{width/2};
    int circle_y{height/2};
    int circle_r{10};

    // circles boundaries for collision detection
    int l_circle_x{circle_x - circle_r};
    int r_circle_x{circle_x + circle_r};
    int u_circle_y{circle_y - circle_r};
    int b_circle_y{circle_y + circle_r};

    // Rectangle coordinates
    int posX{300};
    int posY{0};
    int rec_w{50};
    int rec_h{50};

    // rectangle boundaries for collision detection
    int l_axe_x{posX};
    int r_axe_x{posX+rec_w};
    int b_axe_y{posY+rec_h};
    int u_axe_y{posY};

    int direction{5}; // how many pixels the square moves by per refresh

    // Boolean to determine whether the circle has collided with the axe
    bool CollWithAxe = 
                    (b_axe_y >= u_circle_y) && 
                    (u_axe_y <= b_circle_y) && 
                    (r_axe_x >= l_circle_x) && 
                    (l_axe_x <= r_circle_x);
    //

    // Sets the refresh rate of the window 
    SetTargetFPS(60);

    // while the window has not closed
    while (WindowShouldClose() != true)
    {
        BeginDrawing();
        // set a white background
        ClearBackground(WHITE);
        
        // if the circle and axe have collided
        if (CollWithAxe)
        {
            DrawText("GAME OVER", 200, 200, 20, RED);
        }
        else
        {    
        // Game logic begins

        // update egdes for collision detection
        // circle edges
        l_circle_x = circle_x - circle_r;
        r_circle_x = circle_x + circle_r;
        u_circle_y = circle_y - circle_r;
        b_circle_y = circle_y + circle_r;
        // axe edges
        l_axe_x = posX;
        r_axe_x = posX + rec_w;
        u_axe_y = posY;
        b_axe_y = posY + rec_h; 
        
        // check if axe has collided with circle
        CollWithAxe =
            (b_axe_y >= u_circle_y) &&
            (u_axe_y <= b_circle_y) &&
            (r_axe_x >= l_circle_x) &&
            (l_axe_x <= r_circle_x);
        //
        // draw the circle and rectangle in this frame
        DrawCircle(circle_x, circle_y, circle_r, BLUE);
        DrawRectangle(posX,posY, rec_w, rec_h, RED);

        posY+=direction; // axe moves up (or down)
        if (posY > height-rec_h || posY < 0)
        {
            // if the axe reaches the top (or the bottom) we reverse the dircetion
            direction = -direction;
        }
        // take user input to move the circle
        // set so the circle cannot leave the window
        if (IsKeyDown(KEY_D) && circle_x + circle_r < width)
        {
            circle_x +=1;
        }
        if (IsKeyDown(KEY_D) && IsKeyDown(KEY_LEFT_SHIFT) && circle_x + circle_r < width)
        {
            circle_x +=2;
        }
        if (IsKeyDown(KEY_A) && circle_x - circle_r > 0)
        {
            circle_x -=1;
        }
        if (IsKeyDown(KEY_A) && IsKeyDown(KEY_LEFT_SHIFT) && circle_x - circle_r > 0)
        {
            circle_x -=2;
        }
        if (IsKeyDown(KEY_S) && circle_y + circle_r < height)
        {
            circle_y +=1;
        }
        if (IsKeyDown(KEY_S) && IsKeyDown(KEY_LEFT_SHIFT) && circle_y + circle_r < height)
        {
            circle_y +=2;
        }
        if (IsKeyDown(KEY_W) && circle_y - circle_r > 0)
        {
            circle_y -=1;
        }
        if (IsKeyDown(KEY_W) && IsKeyDown(KEY_LEFT_SHIFT) && circle_y - circle_r > 0)
        {
            circle_y -=2;
        }

        // Game logic ends
        }
        EndDrawing();
    }
    

}