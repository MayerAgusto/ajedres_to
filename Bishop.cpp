#include "Bishop.h"

Bishop::Bishop()
{

}
//se carga la direccion de la imagen de la ficha dependiendo si es negra o blanca dependiendo
// si es ficha negra o blanca
void Bishop::set_image()
{
    if(gamer == 0){
        image = "://bishop1.png";
    } else{
        image ="://bishop.png";
    }

}
//en la funcion mover con un elemento de la clase move
//se almacenan los movimientos dependiendo de la ficha
//los movimiento spueden ser movimiento a la derecha, izquiera, arriba o abajo
Movimientos Bishop::move()
{
    Movimientos aux;
    std::vector<Coordenada> mov_1;
     int l = 1;
    for(int i= (pos_y+1); i < 8; ++i){
        Coordenada a{pos_x+l,i};
        if(a.es_valida()){
            mov_1.emplace_back(a);

        }
        l++;
    }
    std::vector<Coordenada> mov_2;
    l=1;
    for(int i= (pos_y-1); i >=0 && i < 8; i--){
        Coordenada a{(pos_x-l),i};
        if(a.es_valida()){
            mov_2.emplace_back(a);

        }
        l++;
    }

    l=1;
    std::vector<Coordenada> mov_3;
    for(int i= (pos_x+1); i <8; ++i){
        Coordenada a{i,(pos_y-l)};
        if(a.es_valida()){
            mov_3.emplace_back(a);

        }
        l++;
    }
    l=1;
    std::vector<Coordenada> mov_4;
    for(int i= (pos_x-1); i >=0 && i < 8; --i){
        Coordenada a{i,(pos_y+l)};
        if(a.es_valida()){
            mov_4.emplace_back(a);
        }
        l++;
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

//en la funcion eat con un elemento de la clase move
//se almacenan los movimientos que puede comer dependiendo de la ficha
//este movimiento puede ser igual a como se mueve la ficha o requiere
// movimientos especiales

Movimientos Bishop::eat()
{

    Movimientos aux;
    std::vector<Coordenada> mov_1;
    int l = 1;
    for(int i= (pos_y+1); i < 8; ++i){
        Coordenada a{pos_x+l,i};
        if(a.es_valida()){
            mov_1.emplace_back(a);

        }
        l++;
    }
    std::vector<Coordenada> mov_2;
    l=1;
    for(int i= (pos_y-1); i >=0 && i < 8; i--){
        Coordenada a{(pos_x-l),i};
        if(a.es_valida()){
            mov_2.emplace_back(a);

        }
        l++;
    }

    l=1;
    std::vector<Coordenada> mov_3;
    for(int i= (pos_x+1); i <8; ++i){
        Coordenada a{i,(pos_y-l)};
        if(a.es_valida()){
            mov_3.emplace_back(a);

        }
        l++;
    }
    l=1;
    std::vector<Coordenada> mov_4;
    for(int i= (pos_x-1); i >=0 && i < 8; --i){
        Coordenada a{i,(pos_y+l)};
        if(a.es_valida()){
            mov_4.emplace_back(a);
        }
        l++;
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

std::string Bishop::get_idetificador()
{
    identificador ="A";
    return identificador;
}
