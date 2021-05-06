#include "kid.h"
#include <iostream>

void Kid::FallOnBar(std::deque<Normalbar> &_normalbar_group,
                    std::deque<Movingbar> &_movingbar_group,
                    std::deque<Damagebar> &_damagebar_group){
    // Check if kid y position matches any normalbar
    for (auto bar : _normalbar_group){
        if (abs(bar.GetCurrentHeight() - _pos_y) < 1 && 
            bar.GetStartPos() <= _pos_x && 
            bar.GetEndPos() >= _pos_x){
            _current_bar = normal;
            return;
        }
    }
    for (auto bar : _movingbar_group){
        if (abs(bar.GetCurrentHeight() - _pos_y) < 1 && 
            bar.GetStartPos() <= _pos_x && 
            bar.GetEndPos() >= _pos_x){
            _current_bar = moving;
            return;
        }
    }
    for (auto bar : _damagebar_group){
        if (abs(bar.GetCurrentHeight() - _pos_y) < 1 && 
            bar.GetStartPos() <= _pos_x && 
            bar.GetEndPos() >= _pos_x){
            _current_bar = damaging;
            return;
        }
    }
    _current_bar = none;
    _pos_y += kFallingSpeed;
}
