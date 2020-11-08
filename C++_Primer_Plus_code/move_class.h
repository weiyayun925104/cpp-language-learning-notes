#pragma once
#ifndef MOVE_CLASS_H_
#define MOVE_CLASS_H_


class Move
{
private:
    mutable double x;
    mutable double y;
public:
    Move() {};
    ~Move() {};
    Move(double a = 0, double b = 0);
    void show_move() const;

    Move add(const Move &m) const;
    void reset(double a = 0, double b = 0);
};

#endif
