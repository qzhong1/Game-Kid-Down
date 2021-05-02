#ifndef KID_H
#define KID_H

#include "bar.h"

enum Direction{kLeft, kRight};

class Kid
{
private:
    float _speed{10};
    float _blood{10};
    int _grid_width;
    int _grid_height;
    bool _on_bar{true};

public:
    bool _alive{true};
    float _pos_x;
    float _pos_y;
    Direction _direction;

    Kid(int w, int h)
        :_grid_width(w), _grid_height(h){};
    
    float GetBlood() {return _blood;};
    void ReduceBlood(float time);
    void UpdatePosition();
    bool FallOnBar();
};

#endif