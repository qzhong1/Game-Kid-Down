#ifndef KID_H
#define KID_H

#include "bar.h"
#include <deque>

enum Direction{kLeft, kRight};
enum BarType {normal, moving, damaging, none};
constexpr std::size_t kFallingSpeed{5};

class Kid
{
private:
    
    float _blood{10};
    int _grid_width;
    int _grid_height;
    bool _on_bar{true};
    BarType _current_bar;

public:
    bool _alive{true};
    float _pos_x;
    float _pos_y{0};
    Direction _direction;
    float _speed{10};
    
    Kid(int w, int h)
        :_grid_width(w), _grid_height(h){};
    
    float GetBlood() {return _blood;};
    void ReduceBlood(float time);
    void FallOnBar(std::deque<Normalbar> &_normalbar_group,
                   std::deque<Movingbar> &_movingbar_group,
                   std::deque<Damagebar> &_damagebar_group);
};

#endif