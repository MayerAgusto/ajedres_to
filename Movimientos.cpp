#include "Movimientos.h"

Movimientos::Movimientos()
{

}

void Movimientos::add_fila_movimientos(std::vector<Coordenada> a)
{
    mov.emplace_back(a);
}
