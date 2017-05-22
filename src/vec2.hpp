#ifndef VEC2_HPP
#define VEC2_HPP

template <class T>
struct Vec2
{
public:
    Vec2() {x = 0; y = 0;}
    Vec2(T initX, T initY): x(initX), y(initY) {}
    Vec2(const Vec2& other) {*this = other;}

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
