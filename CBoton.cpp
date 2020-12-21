#include "CBoton.h"

CBoton::CBoton()
{

}

void CBoton::set_pieza(const std::shared_ptr<Piece>& p)
{
    pieza = p;
}

std::shared_ptr<Piece> CBoton::get_pieza()
{
    return pieza;
}


