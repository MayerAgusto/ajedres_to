#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class Bishop: public Piece
{
public:
    Bishop(); 
    //la funcion asigna la url de la imagen segun la ficha
    void set_image() override;
    //la funcion move() retorna un objeto con los movimiento validos
    // para moverse de la ficha
    Movimientos move()override;
    //la funcion move() retorna un objeto con los movimiento validos para comer
    // de la ficha
    Movimientos eat() override;
    //retorna un indentificador de la ficha ver mas en Bishop.cpp
    std::string get_idetificador() override;

    ~Bishop(){/*std::cout<<"Pawn destroyed\n";*/}
};

#endif // BISHOP_H
