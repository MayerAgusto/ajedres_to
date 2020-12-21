#ifndef HORSE_H
#define HORSE_H
#include "Piece.h"

class Horse: public Piece
{
public:
    //se especifica en la clase Bishop.h y Bishop.cpp
    Horse();
    void set_image() override;
    Movimientos move()override;
    Movimientos eat() override;
   std::string get_idetificador() override;

    ~Horse(){/*std::cout<<"Pawn destroyed\n";*/}
};

#endif // HORSE_H
