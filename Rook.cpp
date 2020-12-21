#include "Rook.h"

Rook::Rook()
{

}

void Rook::set_image()
{
    if(gamer == 0){
        image = "://rook1.png";
    } else{
        image ="://rook.png";
    }
}

Movimientos Rook::move()
{
    Movimientos aux;
    std::vector<Coordenada> mov_1;
    for(int i= (pos_y+1); i < 8; ++i){
        Coordenada a{pos_x,i};
        if(a.es_valida()){
            mov_1.emplace_back(a);

        }
    }
    std::vector<Coordenada> mov_2;
    for(int i= (pos_y-1); i >=0 && i < 8; i--){
        Coordenada a{pos_x,i};
        if(a.es_valida()){
            mov_2.emplace_back(a);

        }
    }

    std::vector<Coordenada> mov_3;
    for(int i= (pos_x+1); i <8; ++i){
        Coordenada a{i,pos_y};
        if(a.es_valida()){
            mov_3.emplace_back(a);

        }
    }
    std::vector<Coordenada> mov_4;
    for(int i= (pos_x-1); i >=0 && i < 8; --i){
        Coordenada a{i,pos_y};
        if(a.es_valida()){
            mov_4.emplace_back(a);

        }
    }
    if(mov_1.size()!= 0){
        aux.add_fila_movimientos(mov_1);
    }
    if(mov_2.size()!= 0){
        aux.add_fila_movimientos(mov_2);
    }
    if(mov_3.size()!= 0){
        aux.add_fila_movimientos(mov_3);
    }
    if(mov_4.size()!= 0){
         aux.add_fila_movimientos(mov_4);
    }


    return aux;
}

Movimientos Rook::eat()
{
    Movimientos aux = move();
    return aux;
}

std::string Rook::get_idetificador()
{
    identificador ="T";
    return identificador;

}
