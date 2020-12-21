#ifndef KING_H
#define KING_H
#include "Piece.h"

class King: public Piece
{
public:
    King();
     //se especifica en la clase Bishop.h y Bishop.cpp
    void set_image() override;
    Movimientos move()override;
    Movimientos eat() override;
    std::string get_idetificador() override;

    ~King(){/*std::cout<<"Pawn destroyed\n";*/}
};

#endif // KING_H
