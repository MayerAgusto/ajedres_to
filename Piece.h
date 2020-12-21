#ifndef PIECE_H
#define PIECE_H
#include <iostream>
#include <QString>
#include <vector>
#include "Movimientos.h"

class Piece
{
public:
    Piece();
    virtual ~Piece(){/*std::cout<<"Piece destroyed\n";*/}
    void set_gamer(unsigned int a){gamer=a;};// ficha blanca 0 ,  ficha negra 1
    unsigned int get_gamer(){return gamer;};
    //inicializa la posicion de la ficha
    void set_position(int x,int y){pos_x = x; pos_y = y;};
    //cambia la posicion de la ficha
    int get_position_x() const {return pos_x;};
    //cambia la posicion de la ficha
    int get_position_y() const {return pos_y;};
    //retorna la direccion de la imagen
    QString get_image()const {return image;};
    //cambia el contador de la ficha
    void piece_contador(){contador = contador+1;};
    //retorna un bool si esta el primer movimiento
    bool first_move(){bool id = true;if(contador != 0){id = false;}return id;};

    // las clases que tendran los fichas en general
    //se especifica en la clase Bishop.h y Bishop.cpp
    virtual void set_image() = 0;
    virtual Movimientos move() = 0;
    virtual Movimientos eat() = 0;
    virtual std::string get_idetificador()=0;

protected:
    //cada ficha va a tener un identificador sejemplo Queen(Q), King(K)
    std::string identificador{""};
    //cada ficha va a tener la url de la imagen de la ficha
    QString image;
    // gamer es el identificador de ficha blanca o ficha negra
    unsigned int gamer{0};
    // contabiliza el movimiento de una ficha
    unsigned int contador{0};
    // almacenan la corrdenada donde se ubica la ficha
    int pos_x{0};
    int pos_y{0};

};

#endif // PIECE_H
