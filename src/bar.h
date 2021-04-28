#ifndef BAR_H
#define BAR_H

class Bar
{   
protected:
    float _length;
    float _start_pos;

public:
    void VerticalUpdate();
};

// The normal bar which is stationary
class Normalbar : private Bar
{
public:
    Normalbar(float length, float start_pos){
        _length = length; _start_pos = start_pos;};
};

// The bar which moves horizontally
class Movingbar : private Bar
{
private:
    float _speed;

public:
    Movingbar(float length, float start_pos, float speed)
                :_speed(speed){
                _length = length; _start_pos = start_pos; };
};

// The bar which causes blood drop if the kid end up on it
class Damagebar : private Bar
{
private:
    float _damage_per_second;
public:
    Damagebar(float length, float start_pos, float damage)
        :_damage_per_second(damage){
        _length = length; _start_pos = start_pos;};
};

#endif  