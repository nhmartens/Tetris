#pragma once
#include <raylib.h>
#include <vector>

inline const Color darkGrey = {26, 31, 40, 255};
inline const Color green = {47, 230, 23, 255};
inline const Color red = {232, 18, 18, 255};
inline const Color orange = {226, 116, 17, 255};
inline const Color yellow = {237, 234, 4, 255};
inline const Color purple = {166, 0, 247, 255};
inline const Color cyan = {21, 204, 209, 255};
inline const Color blue = {13, 64, 216, 255};
inline const Color lightBlue = {59, 85, 162, 255};
inline const Color darkBlue = {44, 44, 127, 255};

constexpr std::vector<Color> GetCellColors()
{
    return {darkGrey, green, red, orange, yellow, purple, cyan, blue};
}
