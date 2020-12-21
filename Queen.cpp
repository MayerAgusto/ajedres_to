#include "Queen.h"

Queen::Queen()
{

}

void Queen::set_image()
{
    if(gamer == 0){
        image = "://queen1.png";
    } else{
        image ="://queen.png";
    }
}

Movimientos Queen::move()
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
    //------------------------------------------------
    std::vector<Coordenada> mov_1_1;
    int l = 1;
    for(int i= (pos_y+1); i < 8; ++i){
        Coordenada a{pos_x+l,i};
        if(a.es_valida()){
            mov_1_1.emplace_back(a);

        }
        l++;
    }
    std::vector<Coordenada> mov_2_1;
    l=1;
    for(int i= (pos_y-1); i >=0 && i < 8; i--){
        Coordenada a{(pos_x-l),i};
        if(a.es_valida()){
            mov_2_1.emplace_back(a);

        }
        l++;
    }

    l=1;
    std::vector<Coordenada> mov_3_1;
    for(int i= (pos_x+1); i <8; ++i){
        Coordenada a{i,(pos_y-l)};
        if(a.es_valida()){
            mov_3_1.emplace_back(a);

        }
        l++;
    }
    l=1;
    std::vector<Coordenada> mov_4_1;
    for(int i= (pos_x-1); i >=0 && i < 8; --i){
        Coordenada a{i,(pos_y+l)};
        if(a.es_valida()){
            mov_4_1.emplace_back(a);
        }
        l++;
    }
    if(mov_1_1.size()!= 0){
        aux.add_fila_movimientos(mov_1_1);
    }
    if(mov_2_1.size()!= 0){
        aux.add_fila_movimientos(mov_2_1);
    }
    if(mov_3_1.size()!= 0){
        aux.add_fila_movimientos(mov_3_1);
    }
    if(mov_4_1.size()!= 0){
         aux.add_fila_movimientos(mov_4_1);
    }
    //------------------------------------------------
    return aux;
}

Movimientos Queen::eat()
{
    Movimientos aux = move();
    return aux;
}

std::string Queen::get_idetificador()
{
    identificador ="D";
    return identificador;
}
