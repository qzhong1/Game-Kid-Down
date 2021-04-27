#ifndef BAR_H
#define BAR_H

class Bar
{
private:
    
public:
    float _length;
    float _start_pos;
};

enum Direction{kLeft, kRight};

class MovingBar : private Bar
{
private:
    float _speed;
    Direction _direction;
public:
    MovingBar(float length, float start_pos, float speed, Direction direction)
            :_speed(speed), _direction(direction)
            {_length = length; _start_pos = start_pos; };
};

#endif  