#include "King.h"

King::King()
{

}

void King::set_image()
{
    if(gamer == 0){
        image = "://king1.png";
    } else{
        image ="://king.png";
    }
}

Movimientos King::move()
{
    Movimientos aux;
    Coordenada a{pos_x,pos_y-1};
    Coordenada b{pos_x,pos_y+1};
    Coordenada a_especial{pos_x,pos_y-2};
    Coordenada b_especial{pos_x,pos_y+2};

    Coordenada c{pos_x-1,pos_y};
    Coordenada d{pos_x+1,pos_y};
    Coordenada a_1{pos_x+1,pos_y-1};
    Coordenada b_1{pos_x+1,pos_y+1};
    Coordenada c_1{pos_x-1,pos_y-1};
    Coordenada d_1{pos_x-1,pos_y+1};

    if(a.es_valida()){
        std::vector<Coordenada> mov_1;
        mov_1.emplace_back(a);
         if(a_especial.es_valida() && contador == 0){
             mov_1.emplace_back(a_especial);
         }
        aux.add_fila_movimientos(mov_1);
    }
    if(b.es_valida()){
        std::vector<Coordenada> mov_1;
        mov_1.emplace_back(b);
        if(b_especial.es_valida() && contador == 0){
            mov_1.emplace_back(b_especial);
        }
        aux.add_fila_movimientos(mov_1);
    }
    if(c.es_valida()){
        std::vector<Coordenada> mov_1;
        mov_1.emplace_back(c);
        aux.add_fila_movimientos(mov_1);
    }
    if(d.es_valida()){
        std::vector<Coordenada> mov_1;
        mov_1.emplace_back(d);
        aux.add_fila_movimientos(mov_1);
    }

    if(a_1.es_valida()){
        std::vector<Coordenada> mov_1;
        mov_1.emplace_back(a_1);
        aux.add_fila_movimientos(mov_1);
    }
    if(b_1.es_valida()){
        std::vector<Coordenada> mov_1;
        mov_1.emplace_back(b_1);
        aux.add_fila_movimientos(mov_1);
    }
    if(c_1.es_valida()){
        std::vector<Coordenada> mov_1;
        mov_1.emplace_back(c_1);
        aux.add_fila_movimientos(mov_1);
    }
    if(d_1.es_valida()){
        std::vector<Coordenada> mov_1;
        mov_1.emplace_back(d_1);
        aux.add_fila_movimientos(mov_1);
    }

    return aux;
}

Movimientos King::eat()
{
    Movimientos aux = move();

    Coordenada a{pos_x,pos_y-1};
    Coordenada b{pos_x,pos_y+1};
    Coordenada c{pos_x-1,pos_y};
    Coordenada d{pos_x+1,pos_y};

    Coordenada a_1{pos_x+1,pos_y-1};
    Coordenada b_1{pos_x+1,pos_y+1};
    Coordenada c_1{pos_x-1,pos_y-1};
    Coordenada d_1{pos_x-1,pos_y+1};

    if(a.es_valida()){
        std::vector<Coordenada> mov_1;
        mov_1.emplace_back(a);
        aux.add_fila_movimientos(mov_1);
    }
    if(b.es_valida()){
        std::vector<Coordenada> mov_1;
        mov_1.emplace_back(b);
        aux.add_fila_movimientos(mov_1);
    }
    if(c.es_valida()){
        std::vector<Coordenada> mov_1;
        mov_1.emplace_back(c);
        aux.add_fila_movimientos(mov_1);
    }
    if(d.es_valida()){
        std::vector<Coordenada> mov_1;
        mov_1.emplace_back(d);
        aux.add_fila_movimientos(mov_1);
    }

    if(a_1.es_valida()){
        std::vector<Coordenada> mov_1;
        mov_1.emplace_back(a_1);
        aux.add_fila_movimientos(mov_1);
    }
    if(b_1.es_valida()){
        std::vector<Coordenada> mov_1;
        mov_1.emplace_back(b_1);
        aux.add_fila_movimientos(mov_1);
    }
    if(c_1.es_valida()){
        std::vector<Coordenada> mov_1;
        mov_1.emplace_back(c_1);
        aux.add_fila_movimientos(mov_1);
    }
    if(d_1.es_valida()){
        std::vector<Coordenada> mov_1;
        mov_1.emplace_back(d_1);
        aux.add_fila_movimientos(mov_1);
    }

    return aux;
}

std::string King::get_idetificador()
{
    identificador ="R";
    return identificador;
}
