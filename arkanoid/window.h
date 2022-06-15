#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
constexpr int window_width{ 800 }, window_height{ 600 }, top_window_line{ 30 };
;

template <class T1, class T2>
bool isColliding(T1& objA, T2& objB)
{
    return objA.getRightSide() >= objB.getLeftSide() &&
        objA.getLeftSide() <= objB.getRightSide() &&
        objA.getBottomSide() >= objB.getTopSide() &&
        objA.getTopSide() <= objB.getBottomSide();
}