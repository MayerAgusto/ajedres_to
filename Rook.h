#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

class Rook: public Piece
{
public:
    Rook();
    //se especifica en la clase Bishop.h y Bishop.cpp
    void set_image() override;
    Movimientos move()override;
    Movimientos eat() override;
   std::string get_idetificador() override;

    ~Rook(){/*std::cout<<"Pawn destroyed\n";*/}
};

#endif // ROOK_H
