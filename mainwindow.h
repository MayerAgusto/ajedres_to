#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "CBoton.h"
#include <QLabel>
#include <QTime>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void inicializarBoard();
    void inicializarFichas(const std::shared_ptr<Piece>& ficha, unsigned int a, unsigned int b, unsigned int gamer);
    void inicializarFichas();


    unsigned int get_valor_selected_x();
    unsigned int get_valor_selected_y(unsigned int x);
    void set_chequeable();
    void not_set_chequeable();
    bool has_piece(unsigned int x, unsigned int y);
    void print_boton(unsigned int x, unsigned int y);

    void hacerclick_first();
    void hacerclick_second();
    void eat(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
    void move(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
    void show_image_pieces();
    void change_pawn();
    void show_message(unsigned int x, unsigned int y, unsigned int gamer);

    bool valid_eat(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
    bool valid_move(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
    void write_movement(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
    bool check(unsigned int gamer);
    bool checkmate();
    QString get_char(unsigned int i);


public slots:
    void hacerclick();
    void save();

    void aumentar();
    void temporizador_time();

    void nueva_partida();


private:
    Ui::MainWindow *ui;

public:
    //tablero donde se encuentran las fichas
    std::vector<std::vector<CBoton>> Tablero;
    //vectores donde se almacenan las imagenes de las fichas comidas blancas y negras
    std::vector<QLabel*> death_white;
    std::vector<QLabel*> death_black;
    //variables para capturar la posicion del primer click
    unsigned int click_x1{10};
    unsigned int click_y1{10};
    //variables para capturar la posicion del segundo click
    unsigned int click_x2{0};
    unsigned int click_y2{0};
    //variable que indica el jugador  jugador%2 = 0 (blancas) jugador%2=1 (negras)
    unsigned int jugador{0};
    //variables que indica la posicion donde agregar las imagenes de las fichas muertas
    unsigned int index_white{0};
    unsigned int index_black{0};
    //valor inicial del cronometro
    QTime chrono{0, 1, 30};
    //puntero que realiza una accion cada 1 segundo
    QTimer *timer;
    //variable que evalua si termino la partida por limite de tiempo
    // o por jaque mate
    bool end_game =false;
    //variable que indica si el cronometro esta activo
    bool active_chronometer=false;
    //posicion del rey  para evaluar el jaque mate
    unsigned int king_x{0};
    unsigned int king_y{0};

};
#endif // MAINWINDOW_H
