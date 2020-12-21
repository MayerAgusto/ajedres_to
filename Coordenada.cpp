#include "Coordenada.h"

Coordenada::Coordenada()
{

}

Coordenada::Coordenada(int a, int b): x{a},y{b}
{

}

int Coordenada::get_value_x() const
{
    return x;
}
int Coordenada::get_value_y() const
{
    return y;
}

void Coordenada::set_value_x(int a)
{
    x=a;
}

void Coordenada::set_value_y(int b)
{
    y=b;
}

bool Coordenada::es_valida()
{
    bool aux = false;
    if((x>= 0 && x<8) && (y>=0 && y<8)){
        aux = true;
    }
    return aux;
}
bool operator==(const Coordenada& a, const Coordenada& b){
    if((a.x == b.x) && (a.y== b.y)){
        return true;
    }
    return false;
}
bool operator!=(const Coordenada& a, const Coordenada& b){
    return !(a==b);
}

