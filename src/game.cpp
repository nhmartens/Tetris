#include "game.h"
#include "colors.h"
#include <random>

Game::Game()
{
    grid = Grid();
    blocks = {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;

}

Block Game::GetRandomBlock()
{
    if (blocks.empty()){
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;

}

std::vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);
    DrawPreviewBlock(11, 11);
    switch(nextBlock.id)
    {
        case 3:
            nextBlock.Draw(255, 290);
            break;
        case 4:
            nextBlock.Draw(255, 280);
            break;
        default:
            nextBlock.Draw(270, 270);
            break;
    }
}

void Game::HandleInput()
{
    static double lastInputTime = GetTime();
    double currentTime = GetTime();

    int keyPressed = GetKeyPressed();
    if(gameOver && keyPressed != 0){
        gameOver = false;
        Reset();
    }

    if (keyPressed != 0) {
        lastInputTime = currentTime;
        switch(keyPressed){
            case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            UpdateScore(0,1);
            break;
        case KEY_UP:
            RotateBlock();
            break;
        }
    }
    else {
        if (currentTime - lastInputTime >= 0.09) {
            if (IsKeyDown(KEY_LEFT)) {
                MoveBlockLeft();
            }
            if (IsKeyDown(KEY_RIGHT)) {
                MoveBlockRight();
            }
            if (IsKeyDown(KEY_DOWN)) {
                MoveBlockDown();
                UpdateScore(0, 1);
            }
            lastInputTime = currentTime;
        }
    if (keyPressed == KEY_UP) {
        RotateBlock();
    }
    }


}


void Game::MoveBlockLeft()
{
    if(!gameOver) {
        currentBlock.Move(0, -1);
        if(IsBlockOutside()|| BlockFits() == false){
            currentBlock.Move(0, 1);
    }

    }
}

void Game::MoveBlockRight()
{
    if(!gameOver) {
        currentBlock.Move(0, 1);
        if(IsBlockOutside()|| BlockFits() == false){
            currentBlock.Move(0, -1);
        }

    }
}

void Game::MoveBlockDown()
{
    if(!gameOver) {
        currentBlock.Move(1, 0);
        if(IsBlockOutside() || BlockFits() == false){
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item: tiles) {
        grid.grid[item.row][item.col] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if(BlockFits() == false) {
        gameOver = true;

    }

    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    UpdateScore(rowsCleared, 0);
}

bool Game::IsBlockOutside(int rowsDown)
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item: tiles){
        if (grid.IsCellOutside((item.row + rowsDown), item.col)) {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    if(!gameOver) {
        currentBlock.Rotate();
        if(IsBlockOutside()|| BlockFits() == false) {
            currentBlock.UndoRotation();
        }
    }

}

bool Game::BlockFits(int rowsDown)
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item: tiles) {
        if (grid.IsCellEmpty(item.row + rowsDown, item.col) == false) {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int LinesCleared, int moveDownPoints)
{
    switch(LinesCleared)
    {
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score += 500;
            break;
        default:
            break;
    }
    score += moveDownPoints;


}
void Game::DrawPreviewBlock(int offsetX, int offsetY)
{
    int numRowsDown = 0;
    std::vector<Position> tiles = currentBlock.GetCellPositions();

    for (int i = 1; i < grid.numRows; ++i) {
        if (!BlockFits(i) || IsBlockOutside(i)) {
            numRowsDown = i-1;
            break;
        }
    }
    if(numRowsDown > 0){
        currentBlock.DrawPreview(numRowsDown, offsetX, offsetY);
    }
}
