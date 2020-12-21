#ifndef CBOTON_H
#define CBOTON_H
#include <QPushButton>
#include "Piece.h"
#include <memory>

class CBoton
{
public:
    CBoton();
    ~CBoton(){};
    // funcion que sirve para asignar una pieza al objeto cboton
    void set_pieza(const std::shared_ptr<Piece>& p);
    // cambia el valor a 1, valida el cboton
    void set_valid(){validador = 1;};
    // cambia el valor a 0, inicializa a su estado por defecto
    void empty_valid(){validador=0;};
    //retorna la variable validador
    unsigned int get_valid(){return validador;};
    //elimina la pieza
    void delete_pieza(){pieza = nullptr;}
    // retorna la pieza;
    std::shared_ptr<Piece> get_pieza();

//nuestra clase va a tener un objeto de la clase boton
// una pieza inicializada en nulo
// y un int validador este int sirve para validar si el movimiento de la ficha
//seleccionada es valida
public:
    QPushButton *boton = nullptr;
    std::shared_ptr<Piece> pieza = nullptr;
    unsigned int validador{0};

};

#endif // CBOTON_H
