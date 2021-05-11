#ifndef KID_H
#define KID_H

#include "bar.h"
#include <deque>

constexpr std::size_t kKidHeight{40};
constexpr std::size_t kKidWidth{20};

enum Direction{kLeft, kRight};
enum BarType {normal, moving, damaging, none};
constexpr std::size_t kFallingSpeed{5};
constexpr std::size_t kBloodDecrement{1};
constexpr std::size_t kCarouselSpeed{1};

class Kid
{
private:
    
    float _blood{600};
    int _grid_width;
    int _grid_height;
    bool _on_bar{true};
    BarType _current_bar{none};

public:
    bool _alive{true};
    float _pos_x;
    float _pos_y{0};
    Direction _direction;
    float _speed{10};
    
    Kid(int w, int h)
        :_grid_width(w), _grid_height(h){};
    
    float GetBlood() {return _blood;};
    bool GetOnBar() {return _on_bar;}
    BarType GetBarType() {return _current_bar;}
    void ReduceBlood() {_blood -= kBloodDecrement;};
    void ResetBlood() {_blood = 600;}
    void MoveOnCarousel() {_pos_x -= kCarouselSpeed;};
    void FallOnBar(std::deque<Normalbar> &_normalbar_group,
                   std::deque<Movingbar> &_movingbar_group,
                   std::deque<Damagebar> &_damagebar_group);
};

#endif