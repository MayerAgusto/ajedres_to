#ifndef MOVIMIENTOS_H
#define MOVIMIENTOS_H
#include <vector>
#include "Coordenada.h"

//la clase movimientos almacenan los movimientos de la ficha
// las cordenadas del tablero donde la ficha pueda moverse
//almacena un vector de coordenadas,
// por ejemplo almacena un vector de movimientos a la izquierda
// por ejemplo almacena un vector de movimientos a la derecha
// por ejemplo almacena un vector de movimientos a la arriba
//todos esos vectores se almacenan en esta clase
class Movimientos
{
public:
    Movimientos();
    ~Movimientos(){};
    void add_fila_movimientos(std::vector<Coordenada> a);

public:
    std::vector<std::vector<Coordenada>> mov;

};

#endif // MOVIMIENTOS_H
