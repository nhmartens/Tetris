#include "block.h"
#include "colors.h"

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    colOffset = 0;

}

void Block::Draw(int offsetX, int offsetY)
{
    std::vector<Position> tiles = GetCellPositions();
    for (Position item: tiles){
        DrawRectangle(item.col * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::DrawPreview(int rowsDown, int offsetX, int offsetY)
{
    std::vector<Position> tiles = GetCellPositions();
    for (Position item: tiles){
        DrawRectangleLines(item.col * cellSize + offsetX, (item.row + rowsDown) * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::Move(int rows, int cols)
{
    rowOffset += rows;
    colOffset += cols;
}

void Block::Rotate()
{
    rotationState++;
    if (rotationState == static_cast<int>(cells.size())){
        rotationState = 0;
    }
}

void Block::UndoRotation()
{
    rotationState--;
    if (rotationState == -1) {
        rotationState = cells.size() - 1;
    }
}

std::vector<Position> Block::GetCellPositions()
{
    std::vector<Position>& tiles = cells[rotationState];
    std::vector<Position> movedTiles;
    for (Position item: tiles){
        Position newPos = Position(item.row + rowOffset, item.col + colOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}
