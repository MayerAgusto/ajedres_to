#include "Pawn.h"

Pawn::Pawn()
{

}

void Pawn::set_image()
{
   if(gamer == 0){
       image = "://pawn1.png";
   } else{
       image ="://pawn.png";
   }
}

Movimientos Pawn::move()
{
    Movimientos aux;
    if( gamer == 0){
        Coordenada a{(pos_x-1),pos_y};
        Coordenada a_especial{(pos_x-2),pos_y};
        if(a.es_valida()){
            std::vector<Coordenada> mov_1;
            mov_1.emplace_back(a);
            if(a_especial.es_valida() && contador == 0){
                 mov_1.emplace_back(a_especial);
            }
            aux.add_fila_movimientos(mov_1);
        }

    }
    if(gamer == 1){
        Coordenada a{(pos_x+1),pos_y};
        Coordenada a_especial{(pos_x+2),pos_y};
        if(a.es_valida()){
            std::vector<Coordenada> mov_1;
            mov_1.emplace_back(a);
            if(a_especial.es_valida() && contador == 0){
                 mov_1.emplace_back(a_especial);
            }
            aux.add_fila_movimientos(mov_1);
        }

    }
    return aux;
}


Movimientos Pawn::eat()
{
   Movimientos aux;
   if( gamer == 0){
       Coordenada a{(pos_x-1),(pos_y+1)};
       Coordenada b{(pos_x-1),(pos_y-1)};
       std::vector<Coordenada> mov_1;
       std::vector<Coordenada> mov_2;
       if(a.es_valida()){
           mov_1.emplace_back(a);
           aux.add_fila_movimientos(mov_1);
       }
       if(b.es_valida()){
           mov_2.emplace_back(b);
           aux.add_fila_movimientos(mov_2);
       }


   }
   if(gamer == 1){
       Coordenada a{(pos_x+1),(pos_y+1)};
       Coordenada b{(pos_x+1),(pos_y-1)};
       std::vector<Coordenada> mov_1;
       std::vector<Coordenada> mov_2;
       if(a.es_valida()){
           mov_1.emplace_back(a);
           aux.add_fila_movimientos(mov_1);
       }
       if(b.es_valida()){
           mov_2.emplace_back(b);
            aux.add_fila_movimientos(mov_2);
       }
   }
   return aux;
}

std::string Pawn::get_idetificador()
{
    identificador ="P";
    return identificador;
}
