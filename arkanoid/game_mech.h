#include <SFML/Graphics.hpp>
#include <iostream>
#include "ball.h"
#include "blocks.h"
#include "paddle.h"

using namespace std;
using namespace sf;

template <class T1, class T2>
bool isIntersecting(T1& objA, T2& objB)
{
    return objA.getRightSide() >= objB.getLeftSide() &&
        objA.getLeftSide() <= objB.getRightSide() &&
        objA.getBottomSide() >= objB.getTopSide() &&
        objA.getTopSide() <= objB.getBottomSide();
}

void testCollision(Paddle& paddle_, Ball& ball_)
{
    if (!isIntersecting(paddle_, ball_)) return;

    ball_.velocity.y = -ball_.ball_velocity;
    if (ball_.x() < paddle_.x())
        ball_.velocity.x = -ball_.ball_velocity;
    else
        ball_.velocity.x = ball_.ball_velocity;
}

void testCollision(Block& brick_, Ball& ball_)
{
    if (!isIntersecting(brick_, ball_)) return;

    if (brick_.num_lives != INFINITE_BLOCK)
        --brick_.num_lives;

    double overlapLeft{ ball_.getRightSide() - brick_.getLeftSide() };
    double overlapRight{ brick_.getRightSide() - brick_.getLeftSide() };
    double overlapTop{ ball_.getBottomSide() - brick_.getTopSide() };
    double overlapBottom{ brick_.getBottomSide() - brick_.getTopSide() };

    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    double minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
    double minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

    if (abs(minOverlapX) < abs(minOverlapY))
        ball_.velocity.x = ballFromLeft ? -ball_.ball_velocity : ball_.ball_velocity;
    else
        ball_.velocity.y = ballFromTop ? -ball_.ball_velocity : ball_.ball_velocity;

}