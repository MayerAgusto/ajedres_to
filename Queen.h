#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

class Queen:public Piece
{
public:
    Queen();
    //se especifica en la clase Bishop.h y Bishop.cpp
    void set_image() override;
    Movimientos move()override;
    Movimientos eat() override;
    std::string get_idetificador() override;

    ~Queen(){/*std::cout<<"Pawn destroyed\n";*/}
};

#endif // QUEEN_H
