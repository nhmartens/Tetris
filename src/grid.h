#pragma once
#include <vector>
#include <raylib.h>
#include "colors.h"

class Grid
{
public:
    Grid();
    void Initialize();
    void Print();
    void Draw();
    bool IsCellOutside(int row, int col);
    int grid[20][10];
    bool IsCellEmpty(int row, int col);
    int ClearFullRows();
    int numRows;
    int numCols;

private:
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);
    int cellSize;
    std::vector<Color> colors;
};
