#include "ball.h"

int player_score{ 0 };


void Ball::update() {
    ball_shape.move(velocity);

    if (getLeftSide() < 0)
        velocity.x = abs_velocity;
    else if (getRightSide() > window_width)
        velocity.x = -abs_velocity;

    if (getTopSide() < top_window_line)
        velocity.y = abs_velocity;
    else if (getBottomSide() > window_height) {
        velocity.y = -abs_velocity;
        if (!can_die)
            --player_score;
        else is_dead = true;
    }
}

void Ball::checkCollision(Paddle& paddle) {
    if (!isColliding(paddle, *this)) return;

    velocity.y = -velocity.y;

    if (x() < paddle.x())
        velocity.x = -abs_velocity;
    else
        velocity.x = abs_velocity;
}

template <class T1, class Ball>
Ball& solveCollision(T1& objA, Ball& ball) {
    double overlapLeft{ ball.getRightSide() - objA.getLeftSide() };
    double overlapRight{ objA.getRightSide() - ball.getLeftSide() };
    double overlapTop{ ball.getBottomSide() - objA.getTopSide() };
    double overlapBottom{ objA.getBottomSide() - ball.getTopSide() };

    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    double minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
    double minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

    if (abs(minOverlapX) < abs(minOverlapY))
        ball.velocity.x = ballFromLeft ? -ball.abs_velocity : ball.abs_velocity;
    else
        ball.velocity.y = ballFromTop ? -ball.abs_velocity : ball.abs_velocity;

    return ball;
    
}

void Ball::checkCollision(Block& block) {
    if (!isColliding(block, *this)) return;

    if (block.num_lives != infinite_block) {
        ++player_score;
        --block.num_lives;
    }
    *this = solveCollision(block, *this);
 
}


void Ball::checkCollision(Ball& other_ball) {
    if (!isColliding(other_ball, *this)) return;

    other_ball = solveCollision(*this, other_ball);
    *this = solveCollision(other_ball, *this);
}