#pragma once
#include "grid.h"
#include "blocks.h"
#include "colors.h"

class Game
{
public:
    Game();
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    bool gameOver;
    int score;


private:
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    void MoveBlockLeft();
    void MoveBlockRight();
    std::vector<Block> blocks;
    Grid grid;
    Block currentBlock;
    Block nextBlock;
    void LockBlock();
    bool IsBlockOutside(int rowsDown = 0);
    void RotateBlock();
    bool BlockFits(int rowsDown = 0);
    void Reset();
    void UpdateScore(int LinesCleared, int moveDownPoints);
    void DrawPreviewBlock(int offsetX, int offsetY);
};
