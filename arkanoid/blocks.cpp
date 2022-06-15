#include "blocks.h"
#include "paddle.h"

void Bonus::update() {
    rectangle_shape.move(velocity);
    if (y() > window_height)
        lost = true;
}

void MovingBlock::update() {
    rectangle_shape.move(velocity);

    if (getLeftSide() < 0 || getRightSide() > window_width)
        velocity.x = -velocity.x;
}

void MovingBlock::BlocksCollision(Block& static_block) {
    if (!isColliding(static_block, *this)) return;
    velocity.x = -velocity.x;
}


void Bonus::paddleCollision(Paddle& player_paddle) {
    if (!isColliding(player_paddle, *this)) return;
    taken = true;
}