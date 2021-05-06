#ifndef BAR_H
#define BAR_H

class Bar
{   
protected:
    float _length;
    float _start_pos_x;
    float _curr_pos_y;
public:
    void VerticalUpdate();
    float GetLength() {return _length;}
    float GetCurrentHeight() {return _curr_pos_y;}
    void SetCurrentHeight(float h) {_curr_pos_y = h;}
    float GetStartPos() {return _start_pos_x;}
    float GetEndPos() {return _start_pos_x + _length;}
};

// The normal bar which is stationary
class Normalbar : public Bar
{
public:
    Normalbar(float length, float start_pos){
        _length = length; _start_pos_x = start_pos;};
};

// The bar which moves horizontally
class Movingbar : public Bar
{
private:
    float _speed{10};

public:
    Movingbar(float length, float start_pos){
                _length = length; _start_pos_x = start_pos; };
};

// The bar which causes blood drop if the kid end up on it
class Damagebar : public Bar
{
private:
    float _damage_per_second{1};
public:
    Damagebar(float length, float start_pos){
        _length = length; _start_pos_x = start_pos;};
};

#endif  