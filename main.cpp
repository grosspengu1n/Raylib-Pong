#include "raylib.h"
#include <iostream>

using namespace std;

const int screenWidth = 800;
const int screenHeight = 450;
const int paddleWidth = 20;
const int paddleHeight = 100;
const int ballSize = 20;

Vector2 leftPaddlePos = { 20, screenHeight / 2 - paddleHeight / 2 };
Vector2 rightPaddlePos = { screenWidth - 20 - paddleWidth, screenHeight / 2 - paddleHeight / 2 };
Vector2 ballPos = { screenWidth / 2 - ballSize / 2, screenHeight / 2 - ballSize / 2 };
Vector2 ballSpeed = { 5, 5 };



int leftScore = 0;
int rightScore = 0;
bool isTwoPlayerMode = false;
bool menuOn = true;




Color HexToColor(const char* hex)
{
    unsigned int hexValue;
    if (sscanf_s(hex, "#%x", &hexValue) != 1)
    {
        return WHITE;
    }

    Color color;
    color.r = (hexValue >> 16) + 0xFF;
    color.g = (hexValue >> 8) + 0xFF;
    color.b = hexValue + 0xFF;
    color.a = 255;

    return color;
}

void DrawMenu()
{
    DrawText("PONG GAME", screenWidth / 4, screenHeight / 4, 50, HexToColor("#79F2E6"));
    DrawText("Press (1) for Singleplayer", screenWidth / 4, screenHeight / 2 - 40, 30, HexToColor("#7630D9"));
    DrawText("Press (2) for Co-op", screenWidth / 4, screenHeight / 2, 30, HexToColor("#F06BF2"));
}

int main()
{
    InitWindow(screenWidth, screenHeight, "Pong Game");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ONE))
        {
            menuOn = false;
            isTwoPlayerMode = false;
            leftPaddlePos = { 20, screenHeight / 2 - paddleHeight / 2 };
            rightPaddlePos = { screenWidth - 20 - paddleWidth, screenHeight / 2 - paddleHeight / 2 };
            ballPos = { screenWidth / 2 - ballSize / 2, screenHeight / 2 - ballSize / 2 };
            ballSpeed = { 5, 5 };
            leftScore = 0;
            rightScore = 0;
        }
        else if (IsKeyPressed(KEY_TWO))
        {
            menuOn = false;
            isTwoPlayerMode = true;
            leftPaddlePos = { 20, screenHeight / 2 - paddleHeight / 2 };
            rightPaddlePos = { screenWidth - 20 - paddleWidth, screenHeight / 2 - paddleHeight / 2 };
            ballPos = { screenWidth / 2 - ballSize / 2, screenHeight / 2 - ballSize / 2 };
            ballSpeed = { 5, 5 };
            leftScore = 0;
            rightScore = 0;
        }
        if (IsKeyPressed(KEY_X))
        {
            menuOn = true;
        }
        if (IsKeyDown(KEY_W) && leftPaddlePos.y > 0)
            leftPaddlePos.y -= 5;
        if (IsKeyDown(KEY_S) && leftPaddlePos.y < screenHeight - paddleHeight)
            leftPaddlePos.y += 5;


        if (!isTwoPlayerMode)
        {
            if (ballPos.y + ballSize / 2 < rightPaddlePos.y + paddleHeight / 2)
            {
                if (rightPaddlePos.y > 0)
                    rightPaddlePos.y -= 5;
            }
            else if (ballPos.y + ballSize / 2 > rightPaddlePos.y + paddleHeight / 2)
            {
                if (rightPaddlePos.y < screenHeight - paddleHeight)
                    rightPaddlePos.y += 5;
            }
        }
        else
        {
            if (IsKeyDown(KEY_UP) && rightPaddlePos.y > 0)
                rightPaddlePos.y -= 5;
            if (IsKeyDown(KEY_DOWN) && rightPaddlePos.y < screenHeight - paddleHeight)
                rightPaddlePos.y += 5;
        }

        ballPos.x += ballSpeed.x;
        ballPos.y += ballSpeed.y;


        if (CheckCollisionRecs({ ballPos.x, ballPos.y, ballSize, ballSize }, { leftPaddlePos.x, leftPaddlePos.y, paddleWidth, paddleHeight }) ||
            CheckCollisionRecs({ ballPos.x, ballPos.y, ballSize, ballSize }, { rightPaddlePos.x, rightPaddlePos.y, paddleWidth, paddleHeight }))
        {
            ballSpeed.x = -ballSpeed.x;
        }


        if (ballPos.y <= 0 || ballPos.y + ballSize >= screenHeight)
        {
            ballSpeed.y = -ballSpeed.y;
        }


        if (ballPos.x <= 0)
        {
            rightScore++;
            ballPos = { screenWidth / 2 - ballSize / 2, screenHeight / 2 - ballSize / 2 };
        }
        else if (ballPos.x + ballSize >= screenWidth)
        {
            leftScore++;
            ballPos = { screenWidth / 2 - ballSize / 2, screenHeight / 2 - ballSize / 2 };
        }


        BeginDrawing();

        ClearBackground(HexToColor("#010626"));

        if (!menuOn || (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_TWO)))
        {
            for (int i = 0; i < screenHeight; i += 20)
            {
                DrawRectangle(screenWidth / 2 - 1, i, 3, 10, HexToColor("#79F2E6"));
            }
            DrawText(TextFormat("%d", leftScore), screenWidth / 4, 20, 30, HexToColor("#7630D9"));
            DrawText(TextFormat("%d", rightScore), screenWidth * 3 / 4 - MeasureText(TextFormat("%d", rightScore), 30), 20, 30, HexToColor("#F06BF2"));

            DrawRectangleRec({ leftPaddlePos.x, leftPaddlePos.y, paddleWidth, paddleHeight }, HexToColor("#7630D9"));
            DrawRectangleRec({ rightPaddlePos.x, rightPaddlePos.y, paddleWidth, paddleHeight }, HexToColor("#F06BF2"));
            DrawRectangleRec({ ballPos.x, ballPos.y, ballSize, ballSize }, HexToColor("#79F2E6"));
        }
        else
        {
            DrawMenu();
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}