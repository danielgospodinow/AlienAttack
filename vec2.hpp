#ifndef VEC2_HPP
#define VEC2_HPP

struct Vec2
{
public:
    Vec2() {x = 0; y = 0;}
    Vec2(int initX, int initY): x(initX), y(initY) {}
    int x, y;
};

#endif
