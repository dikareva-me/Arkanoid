#pragma once
#include "window.h"
#include "blocks.h"

constexpr double paddle_width{ 60.f }, paddle_height{ 20.f }, paddle_velocity{ 6.f };
constexpr int paddle_offset{ 50 };

class Paddle : public Rectangle
{
public:
    virtual ~Paddle() = default;
    Paddle(double x, double y) {
        rectangle_shape.setPosition(x, y);
        rectangle_shape.setSize({ paddle_width, paddle_height });
        rectangle_shape.setFillColor(Color::Red);
        rectangle_shape.setOrigin(paddle_width / 2.f, paddle_height / 2.f);
    }
    void update();

protected:
    Vector2f velocity;
};
