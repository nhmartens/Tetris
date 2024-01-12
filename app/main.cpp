#include <raylib.h>
#include "game.h"
#include <string>
#include <cstring>
#include "colors.h"

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(500, 620, "raylib Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("./Font/monogram.ttf", 64, 0, 0);

    Game game = Game();

    while(WindowShouldClose()==false)
    {
        game.HandleInput();
        if(EventTriggered(0.3)){
            game.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        if (game.gameOver) {
            DrawTextEx(font, "GAME OVER", {320, 450}, 30, 2, WHITE);
            DrawTextEx(font, "Press key to restart", {324, 500}, 14, 2, WHITE);
        }
        DrawRectangleRounded({320,55,170,60}, 0.3, 6, lightBlue);

        std::string Score = std::to_string(game.score);
        const char* scoreText = Score.c_str();
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);



        DrawTextEx(font, scoreText, {320+(170-textSize.x)/2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320,215,170,180}, 0.3, 6, lightBlue);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
