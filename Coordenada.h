#ifndef COORDENADA_H
#define COORDENADA_H


//la clase cordenada va a juntar las cordenadas de nuestro tablero
// las posiciones x e y del tablero son almacenadas en esta clase
//cada pieza va atener su cordenada
class Coordenada
{
public:
    Coordenada();
    ~Coordenada(){};
    Coordenada(int a,int b);
    int get_value_x() const;
    int get_value_y() const;
    void set_value_x( int a);
    void set_value_y( int b);
    //la funcion es_valida() valida si los valores x e y que se ingresa
    // son mayores a 0 y menor a 8;
    bool es_valida();
    friend bool operator==(const Coordenada& a, const Coordenada& b);
    friend bool operator!=(const Coordenada& a, const Coordenada& b);

private:
    int x{0};
    int y{0};
};

#endif // COORDENADA_H
