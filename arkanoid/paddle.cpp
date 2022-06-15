#include "paddle.h"

void Paddle::update() {
    rectangle_shape.move(velocity);

    if (Keyboard::isKeyPressed(Keyboard::Key::A) && getLeftSide() > 0)
        velocity.x = -paddle_velocity;
    else if (Keyboard::isKeyPressed(Keyboard::Key::D) && getRightSide() < window_width)
        velocity.x = paddle_velocity;
    else
        velocity.x = 0;
}