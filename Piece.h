#ifndef PIECE_H
#define PIECE_H


class Piece
{
public:
    Piece();
    void setPos(unsigned int pox, unsigned int posy);
    virtual void move()=0;
    virtual ~Piece(){};
private:
    unsigned int x{1};
    unsigned int y{1};
    unsigned int jugador{0};

};

#endif // PIECE_H
