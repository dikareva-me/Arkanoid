#pragma once
#include "window.h"
constexpr double block_width{ 60.f }, block_height{ 20.f };
constexpr int count_blocksX{ 11 }, count_blocksY{ 4 };
constexpr int infinite_block{ 4 }, max_lives{ 3 };

class Paddle;

class Rectangle
{
public:
    RectangleShape rectangle_shape;

    virtual ~Rectangle() = default;
    float x() { return rectangle_shape.getPosition().x; }
    float y() { return rectangle_shape.getPosition().y; }
    float getLeftSide() { return x() - rectangle_shape.getSize().x / 2.f; }
    float getRightSide() { return x() + rectangle_shape.getSize().x / 2.f; }
    float getTopSide() { return y() - rectangle_shape.getSize().y / 2.f; }
    float getBottomSide() { return y() + rectangle_shape.getSize().y / 2.f; }
};

enum class BonusType {
    NONE,
    MOVING_BLOCK,
    SECOND_BALL
};

class Block : public Rectangle
{
public:
    virtual ~Block() = default;
    Block(double x, double y, int lives, Color block_color, BonusType bonus) {
        rectangle_shape.setPosition(x, y);
        rectangle_shape.setSize({ block_width, block_height });
        rectangle_shape.setOrigin(block_width / 2.f, block_height / 2.f);
        num_lives = lives;
        rectangle_shape.setFillColor(block_color);
        bonus_type = bonus;
    }

    BonusType bonus_type;
    int num_lives = 1;
};

class MovingBlock : public Block {
public:
    MovingBlock(double x, double y): Block(x, y, 3, Color::Cyan, BonusType::MOVING_BLOCK){}
    virtual ~MovingBlock() = default;
    void update();
    void BlocksCollision(Block& static_block);
    Vector2f velocity{ 5.f, 0.f };
};

class Bonus : public Rectangle
{
public:
    Vector2f velocity{ 0.f, 5.f };
    BonusType bonus_type;
    double block_pos_x;
    double block_pos_y;
    Bonus(double x, double y, BonusType bonus) {
        rectangle_shape.setPosition(x, y);
        rectangle_shape.setSize({ block_width / 2, block_height });
        rectangle_shape.setOrigin(block_width / 4.f, block_height / 2.f);
        rectangle_shape.setFillColor(Color::Magenta);
        bonus_type = bonus;
        block_pos_x = x;
        block_pos_y = y;
    }
    void update();
    void paddleCollision(Paddle& player_paddle);
    virtual ~Bonus() = default;

    bool lost = false;
    bool taken = false;
};