#include "kid.h"
#include <iostream>
void Kid::UpdatePosition(){
    switch (_direction) {
    case Direction::kLeft:
      if (_pos_x - _speed >= 0 ){
        _pos_x -= _speed;
        std::cout<<_pos_x<<std::endl;
        break;
      }
      
    case Direction::kRight:
      // if (_pos_x + _speed <= _grid_width){
        _pos_x += _speed;
        std::cout<<_pos_x<<std::endl;
        break;
      // }
    }
}