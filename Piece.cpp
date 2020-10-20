#include "Piece.h"


Piece::Piece()
{



}

void Piece::setPos(unsigned int pox, unsigned int posy)
{
    if(pox >=1 && pox<=8){
        this->x = pox;
    }
    if(posy >=1 && posy<=8){
        this->y = posy;
    }
}
