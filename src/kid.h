#ifndef KID_H
#define KID_H

#include "bar.h"

enum Direction{kLeft, kRight};

class kid
{
private:
    float _speed;
    float _blood{10};
    int _grid_width;
    int _grid_height;
    bool _on_bar{true};

public:
    bool _alive{true};
    float _pos_x;
    float _pos_y;

    kid(float speed, float x, float y, int w, int h)
        :_speed(speed), _pos_x(x), _pos_y(y), 
        _grid_width(w), _grid_height(h) {};
    float GetBlood() {return _blood;};
    void ReduceBlood(float time);
    void UpdatePosition();
    bool FallOnBar();
};

#endif