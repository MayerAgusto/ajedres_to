#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"

class Pawn: public Piece
{
public:
    Pawn();
    //se especifica en la clase Bishop.h y Bishop.cpp
    void set_image() override;
    Movimientos move()override;
    Movimientos eat() override;
    std::string get_idetificador() override;

    ~Pawn(){/*std::cout<<"Pawn destroyed\n";*/}
};

#endif // PAWN_H
