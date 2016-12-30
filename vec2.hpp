#ifndef VEC2_HPP
#define VEC2_HPP

struct Vec2
{
public:
    Vec2() {x = 0; y = 0;}
    Vec2(int initX, int initY): x(initX), y(initY) {}

    int x, y;

    bool operator==(const Vec2& otherVec) {return (this->x == otherVec.x && this->y == otherVec.y) ? true : false;}
    Vec2 operator+(const Vec2& vec2) const{return Vec2(this->x + vec2.x, this->y + vec2.y);}
    Vec2 operator-(const Vec2& vec2) const {return Vec2(this->x - vec2.x, this->y - vec2.y);}
    Vec2& operator=(const Vec2& vec2)
    {
        this->x = vec2.x;
        this->y = vec2.y;

        return *this;
    }
};

#endif
