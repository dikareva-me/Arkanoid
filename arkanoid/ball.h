#pragma once
#include "window.h"
#include "paddle.h"

constexpr double ball_radius{ 10.f };
constexpr double default_velocity{ 6.f };


class Ball
{
public:
    CircleShape ball_shape;
    double abs_velocity = default_velocity;
    Vector2f velocity{ -abs_velocity, -abs_velocity };
    virtual ~Ball() = default;
    Ball(double x, double y, Color ball_color, bool is_bonus_ball) {
        ball_shape.setPosition(x, y);
        ball_shape.setRadius(ball_radius);
        ball_shape.setFillColor(ball_color);
        ball_shape.setOrigin(ball_radius, ball_radius);
        can_die = is_bonus_ball;
    }

    void update();

    double x() { return ball_shape.getPosition().x; }
    double y() { return ball_shape.getPosition().y; }
    double getLeftSide() { return x() - ball_shape.getRadius(); }
    double getRightSide() { return x() + ball_shape.getRadius(); }
    double getTopSide() { return y() - ball_shape.getRadius(); }
    double getBottomSide() { return y() + ball_shape.getRadius(); }
    void checkCollision(Paddle& paddle);
    void checkCollision(Ball& other_ball);
    void checkCollision(Block& block);

    bool can_die = false;
    bool is_dead = false;
};

class BonusBall : public Ball {
public:
    BonusBall(double x, double y) : Ball(x, y, Color::Blue, true) {}
    virtual ~BonusBall() = default;

};