#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Horse.h"
#include "Queen.h"
#include "King.h"
#include <cmath>
#include <QMessageBox>
#include <QTextStream>
#include <QTime>
#include <QDir>
#include <QFile>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->frame->adjustSize();
    //inicializamos el edittext donde se muestra la nomenclaura de los movimientos
    ui->mov_blancas->setFontPointSize(11);
    ui->mov_blancas->setReadOnly(true);
    ui->mov_negras->setFontPointSize(11);
    ui->mov_negras->setReadOnly(true);

    //inicializamos el tablero las fichas e imagenes
    inicializarBoard();
    inicializarFichas();
    show_image_pieces();

    //a cada boton le mandamos que accion realizar con el metoso connect
    connect(ui->guardar, SIGNAL(clicked()), this, SLOT(save()));
    connect(ui->nueva_partida, SIGNAL(clicked()), this, SLOT(nueva_partida()));
     connect(ui->tiempo, SIGNAL(clicked()), this, SLOT(temporizador_time()));

    //como todo casillero es un boton le asignamos la accion hacerclick()
    for(unsigned i= 0; i < 8 ; i++){
        for(unsigned j=0; j < 8; j++){
             connect(Tablero[i][j].boton, SIGNAL(clicked()), this, SLOT(hacerclick()));
        }
    }

}
void MainWindow::hacerclick()
{
    //primero evalua si se hizo el primer clcik
   if(click_x1 == 10 && click_y1 == 10){
       hacerclick_first();
   }else{
       hacerclick_second();
   }
   // cambiar ficha por peon en casod e que un peon sea coronado
   change_pawn();
   //muestra las imagenes de la ficha en el tablero
   show_image_pieces();
}


void MainWindow::save()
{
    //almacena un archivo txt donde estan los movimientos de las fichas
    //en la direcciond el proyecto con el nombre game+dia+hora.txt
    QString dir = QDir::currentPath();
    QString hours ="  "+QDate::currentDate().toString()+ " "+ QTime::currentTime().toString("hh mm ss");
    QString path = dir + "/game"+ hours+".txt";
    QFile file(path);
    if(! file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Error", "Error de creacion");
    }
    std::cout << path.toStdString() << std::endl;
    QTextStream out(&file);

    QString jugadas = "Jugador 01 \n" + ui->mov_blancas->toPlainText();
    jugadas = jugadas + "\n" + "Jugador 02 \n" + ui->mov_negras->toPlainText();
    out << jugadas;
    file.flush();
    file.close();
    QMessageBox::warning(this, "Ajedrez","El archivo fue correctamente almacenado");
}

void MainWindow::aumentar()
{
    //funcion para el cronometro por cada segundo que pase  reduce el tiempo
    //en -1 segundo y lo muestra en la interfaz
    //si cuando el tiempo es 00 00 00 el juego finaliza y muestra el mensaje de ganador
    //descativa los botones para no hacer mas movimientos
    ui->cronometro->setText(chrono.toString("hh mm ss"));
    QString c =chrono.toString("hh mm ss");
    if(c == "00 00 00"){
        QMessageBox msgBox(this);
        if(jugador%2 == 0){
           msgBox.setText("Tiempo finalizado, ganador jugador 2");
        }else{
           msgBox.setText("Tiempo finalizado, ganador jugador 1");
        }
        msgBox.exec();

        not_set_chequeable();
        for(unsigned i= 0; i < 8 ; i++){
            for(unsigned j=0; j < 8; j++){
                 disconnect(Tablero[i][j].boton, SIGNAL(clicked()), this, SLOT(hacerclick()));
            }
        }
        end_game = true;
        timer->stop();
    }
    chrono = chrono.addSecs(-1);
}

void MainWindow::temporizador_time()
{
    //activa la variable active_chronometer en inicia el cronometro a que
    // realice la funcion aumentar();
    active_chronometer=true;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(aumentar()));
    timer->start(1000);
}

void MainWindow::nueva_partida()
{
    //funcion para realizar una nueva partida
    //elimina las fichas
    jugador = 0;
    for(int l = 2; l < 6;++l ){
        for(int r= 0; r <8; ++r){
            if(has_piece(l,r)){
                Tablero[l][r].delete_pieza();
            }
        }
    }
    //inicializa las fihas en la posicion inicial
    inicializarFichas();
    //muestra las fichas en la interfaz
    show_image_pieces();
    //vuelve a conectar las acciones en cada boton
    if(end_game == true){
        for(unsigned i= 0; i < 8 ; i++){
            for(unsigned j=0; j < 8; j++){
                 connect(Tablero[i][j].boton, SIGNAL(clicked()), this, SLOT(hacerclick()));
            }
        }
    }
     end_game = false;
    //-------elimina las imagenes de las fichas comidas
    QPixmap pix;
    index_white=0;
    index_black=0;
    for(unsigned r= 0; r < death_white.size(); ++r){
        death_white[r]->setPixmap(pix);
    }
    for(unsigned r= 0; r < death_black.size(); ++r){
        death_black[r]->setPixmap(pix);
    }

    //----elimina los movimientos de las fichas
    ui->mov_blancas->setText("");
    ui->mov_negras->setText("");
    //------pausa e inicializa el cronometro
    if(active_chronometer){
        timer->stop();
        active_chronometer=false;
        chrono.setHMS(0,1,30);
        ui->cronometro->setText(chrono.toString("hh mm ss"));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::inicializarFichas(const std::shared_ptr<Piece>& ficha, unsigned int a, unsigned int b, unsigned int gamer)
{
    //recibe una ficha y la ubica en la posicion establecida
    ficha->set_gamer(gamer);
    ficha->set_image();
    ficha->set_position(a,b);
    Tablero[a][b].set_pieza(ficha);
}

//la funcion busca la posicion x de la accion click
// es decir el boton seleccionado por el usuario
unsigned int MainWindow::get_valor_selected_x()
{
 unsigned int valor_x=0;
 for(unsigned i = 0; i < Tablero.size(); ++i){
     for(unsigned j=0 ; j < Tablero[i].size(); ++j){
         if(Tablero[i][j].boton->isChecked()){
             valor_x = i;
             break;
         }
     }
 }
 return valor_x;
}

//la funcion busca la posicion y de la accion click
// es decir el boton seleccionado por el usuario
unsigned int MainWindow::get_valor_selected_y(unsigned int x)
{
    unsigned int valor_y=0;
        for(unsigned i = 0; i < Tablero[x].size(); ++i){
            if(Tablero[x][i].boton->isChecked()){
                valor_y = i;
                break;
            }
        }
    return valor_y;
}

//hace que los botones puedan ser seleccionados
void MainWindow::set_chequeable()
{
    for(int i=0; i <8; i++){
        for(int j=0; j<8;++j){
            Tablero[i][j].boton->setCheckable(true);
        }
    }
}
//hace que los botones no puedan ser seleccionados
void MainWindow::not_set_chequeable()
{
    for(int i=0; i <8; i++){
        for(int j=0; j<8;++j){
            Tablero[i][j].boton->setCheckable(false);
        }
    }
}

//funcion que evalua si en una posicion dada hay una ficha
bool MainWindow::has_piece(unsigned int x, unsigned int y)
{
    if(Tablero[x][y].get_pieza() == nullptr){
        return false;
    }
    return true;
}

//cunado se hace click en una ficha la funcion print_boton
//cambia el color de los casilleros verde: para mostrar al usuario
//los casilleros donde se puede mover la ficha y
//rojo en los casilleros donde la ficha puede comer a otra ficha
void MainWindow::print_boton(unsigned int x, unsigned int y)
{
    Movimientos a;
    a = Tablero[x][y].get_pieza()->move();
    unsigned int sub_x=0;
    unsigned int sub_y=0;
    for(unsigned i = 0; i < a.mov.size(); i++){
        for(unsigned j = 0; j < a.mov[i].size();++j){
            sub_x = a.mov[i][j].get_value_x();
            sub_y = a.mov[i][j].get_value_y();
            if(has_piece(sub_x,sub_y) != true){
                Tablero[sub_x][sub_y].set_valid();
                Tablero[sub_x][sub_y].boton->setStyleSheet("QPushButton{background-color: green;}");
            }else{
                break;
            }
        }
    }

    Movimientos comer;
    comer = Tablero[x][y].get_pieza()->eat();
       for(unsigned i = 0; i < comer.mov.size(); i++){
           for(unsigned j = 0; j < comer.mov[i].size();++j){
               sub_x = comer.mov[i][j].get_value_x();
               sub_y = comer.mov[i][j].get_value_y();
              if(has_piece(sub_x,sub_y)){
                  if(Tablero[click_x1][click_y1].get_pieza()->get_gamer() == Tablero[sub_x][sub_y].get_pieza()->get_gamer()){
                      break;
                  }

                  if(Tablero[click_x1][click_y1].get_pieza()->get_gamer() != Tablero[sub_x][sub_y].get_pieza()->get_gamer()){
                      Tablero[sub_x][sub_y].set_valid();
                      Tablero[sub_x][sub_y].boton->setStyleSheet("QPushButton{background-color: red;}");
                      break;
                  }
              }
           }
       }
}

//esta funcion ubica la posicion del primer clcik
//si esta tiene una ficha lama a la funcion para mostrar
//los movimientos disponibles de la ficha
void MainWindow::hacerclick_first()
{
    unsigned int val_x = get_valor_selected_x();
    unsigned int val_y = get_valor_selected_y(val_x);
       if(has_piece(val_x,val_y)){
           if(Tablero[val_x][val_y].get_pieza()->get_gamer() == 0 && jugador%2 == 0){
               click_x1 = val_x;
               click_y1 = val_y;
               print_boton(click_x1,click_y1);
           }
           if(Tablero[val_x][val_y].get_pieza()->get_gamer() == 1 && jugador%2 == 1){
               click_x1 = val_x;
               click_y1 = val_y;
               print_boton(click_x1,click_y1);
           }
       }
       not_set_chequeable();
       set_chequeable();
}

//esta funcion evalua si el segundo click se realizo
// si hizo click en un casillero vacio realiza la accion de mover
// si hizo click en un casillero con una ficha enemiga
//realiza la accion de comer
//tambien realiza las acciones de jake y jake mate
// y las acciones de enroque
void MainWindow::hacerclick_second()
{
        unsigned int val_x = get_valor_selected_x();
        unsigned int val_y = get_valor_selected_y(val_x);
        click_x2 = val_x;
        click_y2 = val_y;
        if(has_piece(val_x,val_y) == true && Tablero[val_x][val_y].get_valid() == 1){
            bool flag = valid_eat(click_x1,click_y1, click_x2,click_y2);
            if(flag == true){
                write_movement(click_x1,click_y1, click_x2,click_y2);
                eat(click_x1,click_y1, click_x2,click_y2);
                   Tablero[click_x2][click_y2].get_pieza()->set_position(click_x2,click_y2);
                   Tablero[click_x2][click_y2].get_pieza()->piece_contador();
                   chrono.setHMS(0,1,30);
                   jugador++;
            }else{
                QMessageBox msgBox(this);
                msgBox.setText("Movimiento no valido, su rey esta en peligro");
                msgBox.exec();
            }

        } if(has_piece(val_x,val_y) == false && Tablero[val_x][val_y].get_valid() == 1){
            bool flag = valid_move(click_x1,click_y1, click_x2,click_y2);
            if(flag == true){
                move(click_x1,click_y1, click_x2,click_y2);
            }else{
                QMessageBox msgBox(this);
                msgBox.setText("Movimiento no valido, su rey esta en peligro");
                msgBox.exec();
            }
        }

        click_x1 = 10;
        click_y1 = 10;
        click_x2 = 0;
        click_y2 = 0;

        show_image_pieces();
        if(check(jugador%2)){
            if(checkmate()==true){
                //si hay un jaque mate ya no permite realizar movimientos
                //muestra un mensaje
                //e ingresa la nomenclautra en el texto de movimientos
                end_game = true;
                not_set_chequeable();
                for(unsigned i= 0; i < 8 ; i++){
                    for(unsigned j=0; j < 8; j++){
                         disconnect(Tablero[i][j].boton, SIGNAL(clicked()), this, SLOT(hacerclick()));
                    }
                }
                if(jugador%2 == 1){
                    QString aux =ui->mov_blancas->toPlainText();
                    aux = aux+"++" + "\n" + "1 - 0";
                    ui->mov_blancas->setText(aux);
                }else{
                    QString aux =ui->mov_negras->toPlainText();
                    aux = aux +"++" +"\n"+ "0 - 1";
                    ui->mov_negras->setText(aux);
                }

                QMessageBox msgBox(this);
                msgBox.setText("Jaque Mate, fin del juego");
                msgBox.exec();
                jugador = 0;

            }else{
                //si el segundo click ocaciona un jake se muestra un mensaje
                if(jugador%2 == 1){
                    QString aux =ui->mov_blancas->toPlainText();
                    aux = aux+"+";
                    ui->mov_blancas->setText(aux);
                }else{
                    QString aux =ui->mov_negras->toPlainText();
                    aux = aux +"+";
                    ui->mov_negras->setText(aux);
                }
                QMessageBox msgBox(this);
                msgBox.setText("El rey esta en jaque");
                msgBox.exec();
            }
        }
    //-------------------------------------------------------------
    not_set_chequeable();
    set_chequeable();

    // eliminar los cambios de color
    for(unsigned i=0; i < 8; i++){
        for (unsigned j = 0; j < 8 ; j++){
            if( (i+j)%2 == 0){
                Tablero[i][j].boton->setStyleSheet("QPushButton{background-color: rgb(236, 211, 184);}");
            }else{
                Tablero[i][j].boton->setStyleSheet("QPushButton{background-color:  rgb(151, 84, 31);}");
            }
        }
    }
    // eliminar los movimientos disponibles
    for(unsigned i=0; i < 8; i++){
        for (unsigned j = 0; j < 8 ; j++){
            Tablero[i][j].empty_valid();
        }
    }
}

//realiza la accion de comer ficha
void MainWindow::eat(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
    auto pieza = Tablero[x1][y1].get_pieza();
    QPixmap pix(Tablero[x2][y2].get_pieza()->get_image());

    if(pieza->get_gamer() == 0){
        death_white[index_white]->setPixmap(pix);
        index_white++;
    }else{
        death_black[index_black]->setPixmap(pix);
        index_black++;
    }

    Tablero[x1][y1].delete_pieza();
    Tablero[x2][y2].delete_pieza();
    Tablero[x2][y2].set_pieza(pieza);
}

//realiza la accion de movimientos
//tambien realiza movimientos especiales como enroque corto y largo
void MainWindow::move(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
    int val = y2-y1;
    std::string val_king = Tablero[x1][y1].get_pieza()->get_idetificador();
    bool first_move = Tablero[x1][y1].get_pieza()->first_move();

    if(std::abs(val)==2 && val_king =="R" && first_move){
        if(val > 0){
            if(has_piece(x1,7)== true){
                std::string val_tower =Tablero[x1][7].get_pieza()->get_idetificador();
                if(val_tower == "T"){

                    auto tower =  Tablero[x1][7].get_pieza();
                    tower->set_position(x1,5);
                    Tablero[x1][7].delete_pieza();
                    Tablero[x1][5].set_pieza(tower);
                    chrono.setHMS(0,1,30);
                    jugador++;

                    auto pieza = Tablero[x1][y1].get_pieza();
                    Tablero[x1][y1].delete_pieza();
                    Tablero[x2][y2].set_pieza(pieza);

                    Tablero[click_x2][click_y2].get_pieza()->set_position(click_x2,click_y2);
                    Tablero[click_x2][click_y2].get_pieza()->piece_contador();

                    if(pieza->get_gamer() == 0){
                        QString aux =ui->mov_blancas->toPlainText();
                        aux = aux +"\n" +"0 - 0";
                        ui->mov_blancas->setText(aux);
                    }else{
                        QString aux =ui->mov_negras->toPlainText();
                        aux = aux +"\n" +"0 - 0";
                        ui->mov_negras->setText(aux);
                    }
                }
            }
        }else{
            if(has_piece(x1,0)== true && has_piece(x1,1)== false){
                std::string val_tower =Tablero[x1][0].get_pieza()->get_idetificador();
                if(val_tower == "T"){
                    auto tower =  Tablero[x1][0].get_pieza();
                    tower->set_position(x1,3);
                    Tablero[x1][0].delete_pieza();
                    Tablero[x1][3].set_pieza(tower);
                    chrono.setHMS(0,1,30);
                    jugador++;

                    auto pieza = Tablero[x1][y1].get_pieza();
                    Tablero[x1][y1].delete_pieza();
                    Tablero[x2][y2].set_pieza(pieza);

                    Tablero[click_x2][click_y2].get_pieza()->set_position(click_x2,click_y2);
                    Tablero[click_x2][click_y2].get_pieza()->piece_contador();

                    if(pieza->get_gamer() == 0){
                        QString aux =ui->mov_blancas->toPlainText();
                        aux = aux +"\n" +"0 - 0 - 0";
                        ui->mov_blancas->setText(aux);
                    }else{
                        QString aux =ui->mov_negras->toPlainText();
                        aux = aux +"\n" +"0 - 0 - 0";
                        ui->mov_negras->setText(aux);
                    }

                }
            }
        }

    }else{
        write_movement(click_x1,click_y1, click_x2,click_y2);
        auto pieza = Tablero[x1][y1].get_pieza();
        Tablero[x1][y1].delete_pieza();
        Tablero[x2][y2].set_pieza(pieza);
        Tablero[click_x2][click_y2].get_pieza()->set_position(click_x2,click_y2);
        Tablero[click_x2][click_y2].get_pieza()->piece_contador();
        chrono.setHMS(0,1,30);
        jugador++;
    }
}

//muestra las imagenes de las fichas dentro de los casilleros
void MainWindow::show_image_pieces()
{
    for(unsigned i = 0; i < 8; i++){
        for(unsigned j =0; j < 8; j++){
            if(has_piece(i,j)){
                Tablero[i][j].boton->setIcon(QIcon(Tablero[i][j].pieza->get_image()));
                Tablero[i][j].boton->setIconSize(QSize(60,60));
            }else{
                Tablero[i][j].boton->setIcon(QIcon());
                Tablero[i][j].boton->setIconSize(QSize(60,60));
            }
        }
    }
}

//evalua si hay un peon que requiera la ccion de coronacion
void MainWindow::change_pawn()
{
    for(int i = 0; i <8; i++){
        if(has_piece(0,i)){
            std::string get_ident =Tablero[0][i].get_pieza()->get_idetificador();
            if(get_ident== "P"){
               show_message(0, i, Tablero[0][i].get_pieza()->get_gamer());
            }
        }
        if(has_piece(7,i)){
            std::string get_ident =Tablero[7][i].get_pieza()->get_idetificador();
            if(get_ident== "P"){
               show_message(7, i, Tablero[7][i].get_pieza()->get_gamer());
            }
        }
    }
}

//muestra un mensaje para que el usuario pueda coronar un peon
// realiza el cambio de ficha seleccionada
void MainWindow::show_message(unsigned int x,unsigned int y,unsigned int gamer)
{
    QMessageBox messageBox(this);

    messageBox.setText("Escoja una nueva pieza: ");
    QAbstractButton *Q =messageBox.addButton(tr("Reyna"), QMessageBox::ActionRole);
    QAbstractButton *T =messageBox.addButton(tr("Torre"), QMessageBox::ActionRole);
    QAbstractButton *C =messageBox.addButton(tr("Caballo"), QMessageBox::ActionRole);
    QAbstractButton *A =messageBox.addButton(tr("Alfil"), QMessageBox::ActionRole);
    messageBox.exec();
    if (messageBox.clickedButton() == Q) {
        std::shared_ptr<Piece> queen = std::make_unique<Queen>();
        Tablero[x][y].delete_pieza();
        inicializarFichas(queen,x,y,gamer);
        if(gamer == 0){
            QString aux =ui->mov_blancas->toPlainText();
            aux = aux+"=Q";
            ui->mov_blancas->setText(aux);
        }else{
            QString aux =ui->mov_negras->toPlainText();
            aux = aux+"=Q";
            ui->mov_negras->setText(aux);
        }
    }
    if (messageBox.clickedButton() == T) {
        std::shared_ptr<Piece> torre = std::make_unique<Rook>();
        Tablero[x][y].delete_pieza();
        inicializarFichas(torre,x,y,gamer);
        if(gamer == 0){
            QString aux =ui->mov_blancas->toPlainText();
            aux = aux+"=T";
            ui->mov_blancas->setText(aux);
        }else{
            QString aux =ui->mov_negras->toPlainText();
            aux = aux+"=T";
            ui->mov_negras->setText(aux);
        }
    }
    if (messageBox.clickedButton() == C) {
        std::shared_ptr<Piece> horse = std::make_unique<Horse>();
        Tablero[x][y].delete_pieza();
        inicializarFichas(horse,x,y,gamer);
        if(gamer == 0){
            QString aux =ui->mov_blancas->toPlainText();
            aux = aux+"=C";
            ui->mov_blancas->setText(aux);
        }else{
            QString aux =ui->mov_negras->toPlainText();
            aux = aux+"=C";
            ui->mov_negras->setText(aux);
        }
    }
    if (messageBox.clickedButton() == A) {
        std::shared_ptr<Piece> alfil = std::make_unique<Bishop>();
        Tablero[x][y].delete_pieza();
        inicializarFichas(alfil,x,y,gamer);
        if(gamer == 0){
            QString aux =ui->mov_blancas->toPlainText();
            aux = aux+"=A";
            ui->mov_blancas->setText(aux);
        }else{
            QString aux =ui->mov_negras->toPlainText();
            aux = aux+"=A";
            ui->mov_negras->setText(aux);
        }
    }
}

//funcion que evalua si la accion de comer porvoca un jaque del rival
// en caso de darse se muestra el mensaje de alerta
//recibe la posicion de la ficha y la posicion del movimiento siguiente
bool MainWindow::valid_eat(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
    bool flag = true;
    unsigned int gamer = Tablero[x1][y1].get_pieza()->get_gamer();

    auto piece_1 = Tablero[x1][y1].get_pieza();
    auto piece_2 = Tablero[x2][y2].get_pieza();


    //auto pieza = Tablero[x1][y1].get_pieza();
    Tablero[x1][y1].delete_pieza();
    Tablero[x2][y2].delete_pieza();
    Tablero[x2][y2].set_pieza(piece_1);

    unsigned int sub_x=0;
    unsigned int sub_y=0;

    for(unsigned k=0; k<8;++k){
        for(unsigned l= 0; l<8; ++l){
            if(has_piece(k,l)== true){
                if(Tablero[k][l].get_pieza()->get_gamer() != gamer){
                    Movimientos comer;
                    comer = Tablero[k][l].get_pieza()->eat();
                    for(unsigned i = 0; i < comer.mov.size(); i++){
                        for(unsigned j = 0; j < comer.mov[i].size();++j){
                            sub_x = comer.mov[i][j].get_value_x();
                            sub_y = comer.mov[i][j].get_value_y();
                           if(has_piece(sub_x,sub_y)){
                               if(Tablero[sub_x][sub_y].get_pieza()->get_gamer() != gamer){
                                   break;
                               }
                               if(Tablero[sub_x][sub_y].get_pieza()->get_gamer() == gamer){
                                   if(Tablero[sub_x][sub_y].get_pieza()->get_idetificador() =="R"){
                                       flag = false;
                                       Tablero[x1][y1].set_pieza(piece_1);
                                       Tablero[x2][y2].delete_pieza();
                                       Tablero[x2][y2].set_pieza(piece_2);
                                       return flag;
                                   }
                                   break;
                               }
                           }
                        }
                    }
                }
            }
        }
    }
    //------------------------------------------------
    Tablero[x1][y1].set_pieza(piece_1);
    Tablero[x2][y2].delete_pieza();
    Tablero[x2][y2].set_pieza(piece_2);
    return flag;
}

//funcion que evalua si la accion de mover porvoca un jaque del rival
// en caso de darse se muestra el mensaje de alerta
//recibe la posicion de la ficha y la posicion del movimiento siguiente
bool MainWindow::valid_move(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
    bool flag = true;
    unsigned int gamer = Tablero[x1][y1].get_pieza()->get_gamer();

    auto piece = Tablero[x1][y1].get_pieza();
    Tablero[x1][y1].delete_pieza();
    Tablero[x2][y2].set_pieza(piece);
    //----------------
    unsigned int sub_x=0;
    unsigned int sub_y=0;

    for(unsigned k=0; k<8;++k){
        for(unsigned l= 0; l<8; ++l){
            if(has_piece(k,l)== true){
                if(Tablero[k][l].get_pieza()->get_gamer() != gamer){
                    Movimientos comer;
                    comer = Tablero[k][l].get_pieza()->eat();
                    for(unsigned i = 0; i < comer.mov.size(); i++){
                        for(unsigned j = 0; j < comer.mov[i].size();++j){
                            sub_x = comer.mov[i][j].get_value_x();
                            sub_y = comer.mov[i][j].get_value_y();
                           if(has_piece(sub_x,sub_y)){
                               if(Tablero[sub_x][sub_y].get_pieza()->get_gamer() != gamer){
                                   break;
                               }
                               if(Tablero[sub_x][sub_y].get_pieza()->get_gamer() == gamer){
                                   if(Tablero[sub_x][sub_y].get_pieza()->get_idetificador() =="R"){
                                       flag = false;
                                       Tablero[x2][y2].delete_pieza();
                                       Tablero[x1][y1].set_pieza(piece);
                                       return flag;
                                   }
                                   break;
                               }
                           }
                        }
                    }
                }
            }
        }
    }
    //-------------------
    Tablero[x2][y2].delete_pieza();
    Tablero[x1][y1].set_pieza(piece);
    return flag;
}

//funcion que que realiza la nomenclaura de las acciones dentro del tablero
// como comer o moveer para ello requiere del indentificador
// de cada fichas la posicion acutal y del siguiente movimiento
void MainWindow::write_movement(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
    QString message;
    if(has_piece(x2,y2)== false){
        if(Tablero[x1][y1].get_pieza()->get_idetificador()!="P"){
            std::string id = Tablero[x1][y1].get_pieza()->get_idetificador();
            message = message +QString::fromStdString(id);
        }
        std::string number = std::to_string(8-x2);
        message =message + get_char(y2) + QString::fromStdString(number);

    }else{
        if(Tablero[x1][y1].get_pieza()->get_idetificador()!="P"){
            std::string id = Tablero[x1][y1].get_pieza()->get_idetificador();
            message =message+ QString::fromStdString(id);
        }else{
            message = message +get_char(y1);
        }
        message = message +"x";
        std::string number = std::to_string(8-x2);
        message =message + get_char(y2) + QString::fromStdString(number);
    }

    if(Tablero[x1][y1].get_pieza()->get_gamer() ==0){
       QString aux =ui->mov_blancas->toPlainText();
       aux = aux +"\n" +message;
       ui->mov_blancas->setText(aux);
    }else{
       QString aux = ui->mov_negras->toPlainText();
       aux = aux +"\n" +message;
       ui->mov_negras->setText(aux);
    }
}

// evalu si el rey esta en jaque, recibe como parametro
//al jugador
bool MainWindow::check(unsigned int gamer)
{
    bool jaque = false;
   //-------------------------
    unsigned int sub_x=0;
    unsigned int sub_y=0;
    for(unsigned k=0; k<8;++k){
        for(unsigned l= 0; l<8; ++l){
            if(has_piece(k,l)== true){
                if(Tablero[k][l].get_pieza()->get_gamer() != gamer){
                    Movimientos comer;
                    comer = Tablero[k][l].get_pieza()->eat();
                    for(unsigned i = 0; i < comer.mov.size(); i++){
                        for(unsigned j = 0; j < comer.mov[i].size();++j){
                            sub_x = comer.mov[i][j].get_value_x();
                            sub_y = comer.mov[i][j].get_value_y();
                           if(has_piece(sub_x,sub_y)){
                               if(Tablero[sub_x][sub_y].get_pieza()->get_gamer() != gamer){
                                   break;
                               }
                               if(Tablero[sub_x][sub_y].get_pieza()->get_gamer() == gamer){
                                   if(Tablero[sub_x][sub_y].get_pieza()->get_idetificador() =="R"){
                                       jaque = true;
                                       king_x=sub_x;
                                       king_y = sub_y;
                                       return jaque;
                                   }
                                   break;
                               }
                           }
                        }
                    }
                }
            }
        }
    }
    //------------------------
    return jaque;
}

//evalua si hay el rey esta en jaque mate
bool MainWindow::checkmate()
{
    bool flag = true;
    Movimientos move;
    move = Tablero[king_x][king_y].get_pieza()->move();
    unsigned int gamer = Tablero[king_x][king_y].get_pieza()->get_gamer();

    unsigned int sub_x=0;
    unsigned int sub_y=0;

    for(unsigned i = 0; i < move.mov.size(); i++){
        for(unsigned j = 0; j < move.mov[i].size();++j){
            sub_x = move.mov[i][j].get_value_x();
            sub_y = move.mov[i][j].get_value_y();

            if(has_piece(sub_x,sub_y)){
                if(Tablero[sub_x][sub_y].get_pieza()->get_gamer() != gamer){
                    flag = flag && !valid_eat(king_x,king_y,sub_x,sub_y);
                }
            }else{
                flag = flag && !valid_move(king_x,king_y,sub_x,sub_y);
            }
        }
     }
    return flag;
}

// funcion que ayuda a la nomenclautra del tablero
// erecibe el indice de la columna y retorna el caracter correspondiente
QString MainWindow::get_char(unsigned int i)
{
    QString c;
    switch(i){
    case 0:
        c = "a";
        break;
    case 1:
        c = "b";
        break;
    case 2:
        c = "c";
        break;
    case 3:
        c = "d";
        break;
    case 4:
        c = "e";
        break;
    case 5:
        c = "f";
        break;
    case 6:
        c = "g";
        break;
    case 7:
        c = "h";
        break;
    }
    return c;
}

//funcion que crea las fichas del ajedrez
// la posicion de cada fichas inicial y si son fichas blancas  o negras
void MainWindow::inicializarFichas()
{
    std::shared_ptr<Piece> torre_w = std::make_unique<Rook>();
    std::shared_ptr<Piece> horse_w = std::make_unique<Horse>();
    std::shared_ptr<Piece> alfil_w = std::make_unique<Bishop>();
    std::shared_ptr<Piece> queen_w = std::make_unique<Queen>();
    std::shared_ptr<Piece> king_w = std::make_unique<King>();
    std::shared_ptr<Piece> alfil_1w = std::make_unique<Bishop>();
    std::shared_ptr<Piece> horse_1w = std::make_unique<Horse>();
    std::shared_ptr<Piece> torre_1w = std::make_unique<Rook>();

    std::shared_ptr<Piece> peon_1w = std::make_unique<Pawn>();
    std::shared_ptr<Piece> peon_2w = std::make_unique<Pawn>();
    std::shared_ptr<Piece> peon_3w = std::make_unique<Pawn>();
    std::shared_ptr<Piece> peon_4w = std::make_unique<Pawn>();
    std::shared_ptr<Piece> peon_5w = std::make_unique<Pawn>();
    std::shared_ptr<Piece> peon_6w = std::make_unique<Pawn>();
    std::shared_ptr<Piece> peon_7w = std::make_unique<Pawn>();
    std::shared_ptr<Piece> peon_8w = std::make_unique<Pawn>();

    std::shared_ptr<Piece> torre_b = std::make_unique<Rook>();
    std::shared_ptr<Piece> horse_b = std::make_unique<Horse>();
    std::shared_ptr<Piece> alfil_b = std::make_unique<Bishop>();
    std::shared_ptr<Piece> queen_b = std::make_unique<Queen>();
    std::shared_ptr<Piece> king_b = std::make_unique<King>();
    std::shared_ptr<Piece> alfil_1b = std::make_unique<Bishop>();
    std::shared_ptr<Piece> horse_1b = std::make_unique<Horse>();
    std::shared_ptr<Piece> torre_1b = std::make_unique<Rook>();

    std::shared_ptr<Piece> peon_1b = std::make_unique<Pawn>();
    std::shared_ptr<Piece> peon_2b = std::make_unique<Pawn>();
    std::shared_ptr<Piece> peon_3b = std::make_unique<Pawn>();
    std::shared_ptr<Piece> peon_4b = std::make_unique<Pawn>();
    std::shared_ptr<Piece> peon_5b = std::make_unique<Pawn>();
    std::shared_ptr<Piece> peon_6b = std::make_unique<Pawn>();
    std::shared_ptr<Piece> peon_7b = std::make_unique<Pawn>();
    std::shared_ptr<Piece> peon_8b = std::make_unique<Pawn>();

    inicializarFichas(torre_w,7,0,0);
    inicializarFichas(horse_w,7,1,0);
    inicializarFichas(alfil_w,7,2,0);
    inicializarFichas(queen_w,7,3,0);
    inicializarFichas(king_w,7,4,0);
    inicializarFichas(alfil_1w,7,5,0);
    inicializarFichas(horse_1w,7,6,0);
    inicializarFichas(torre_1w,7,7,0);

    inicializarFichas(peon_1w,6,0,0);
    inicializarFichas(peon_2w,6,1,0);
    inicializarFichas(peon_3w,6,2,0);
    inicializarFichas(peon_4w,6,3,0);
    inicializarFichas(peon_5w,6,4,0);
    inicializarFichas(peon_6w,6,5,0);
    inicializarFichas(peon_7w,6,6,0);
    inicializarFichas(peon_8w,6,7,0);

    inicializarFichas(torre_b,0,0,1);
    inicializarFichas(horse_b,0,1,1);
    inicializarFichas(alfil_b,0,2,1);
    inicializarFichas(queen_b,0,3,1);
    inicializarFichas(king_b,0,4,1);
    inicializarFichas(alfil_1b,0,5,1);
    inicializarFichas(horse_1b,0,6,1);
    inicializarFichas(torre_1b,0,7,1);

    inicializarFichas(peon_1b,1,0,1);
    inicializarFichas(peon_2b,1,1,1);
    inicializarFichas(peon_3b,1,2,1);
    inicializarFichas(peon_4b,1,3,1);
    inicializarFichas(peon_5b,1,4,1);
    inicializarFichas(peon_6b,1,5,1);
    inicializarFichas(peon_7b,1,6,1);
    inicializarFichas(peon_8b,1,7,1);
}


// funcion que inicializa el tablero asigna un boton a cada casilleros
// de la clase CBOTON y un QLabel para cada arreglo donde se muestran
// las fichas negras y blancas
void MainWindow::inicializarBoard()
{

    for(int i= 0; i < 8 ;++i){
        std::vector<CBoton> aux;
        for(int j=0; j <8; ++j){
            CBoton ex;
            aux.emplace_back(ex);
        }
        Tablero.emplace_back(aux);
    }

    Tablero[0][0].boton =ui->tab11;
    Tablero[0][1].boton = ui->tab12;
    Tablero[0][2].boton = ui->tab13;
    Tablero[0][3].boton = ui->tab14;
    Tablero[0][4].boton = ui->tab15;
    Tablero[0][5].boton = ui->tab16;
    Tablero[0][6].boton = ui->tab17;
    Tablero[0][7].boton = ui->tab18;

    Tablero[1][0].boton = ui->tab21;
    Tablero[1][1].boton = ui->tab22;
    Tablero[1][2].boton = ui->tab23;
    Tablero[1][3].boton = ui->tab24;
    Tablero[1][4].boton = ui->tab25;
    Tablero[1][5].boton = ui->tab26;
    Tablero[1][6].boton = ui->tab27;
    Tablero[1][7].boton = ui->tab28;

    Tablero[2][0].boton = ui->tab31;
    Tablero[2][1].boton = ui->tab32;
    Tablero[2][2].boton = ui->tab33;
    Tablero[2][3].boton = ui->tab34;
    Tablero[2][4].boton = ui->tab35;
    Tablero[2][5].boton = ui->tab36;
    Tablero[2][6].boton = ui->tab37;
    Tablero[2][7].boton = ui->tab38;

    Tablero[3][0].boton = ui->tab41;
    Tablero[3][1].boton = ui->tab42;
    Tablero[3][2].boton = ui->tab43;
    Tablero[3][3].boton = ui->tab44;
    Tablero[3][4].boton = ui->tab45;
    Tablero[3][5].boton = ui->tab46;
    Tablero[3][6].boton = ui->tab47;
    Tablero[3][7].boton = ui->tab48;

    Tablero[4][0].boton = ui->tab51;
    Tablero[4][1].boton = ui->tab52;
    Tablero[4][2].boton = ui->tab53;
    Tablero[4][3].boton = ui->tab54;
    Tablero[4][4].boton = ui->tab55;
    Tablero[4][5].boton = ui->tab56;
    Tablero[4][6].boton = ui->tab57;
    Tablero[4][7].boton = ui->tab58;

    Tablero[5][0].boton = ui->tab61;
    Tablero[5][1].boton = ui->tab62;
    Tablero[5][2].boton = ui->tab63;
    Tablero[5][3].boton = ui->tab64;
    Tablero[5][4].boton = ui->tab65;
    Tablero[5][5].boton = ui->tab66;
    Tablero[5][6].boton = ui->tab67;
    Tablero[5][7].boton = ui->tab68;

    Tablero[6][0].boton = ui->tab71;
    Tablero[6][1].boton = ui->tab72;
    Tablero[6][2].boton = ui->tab73;
    Tablero[6][3].boton = ui->tab74;
    Tablero[6][4].boton = ui->tab75;
    Tablero[6][5].boton = ui->tab76;
    Tablero[6][6].boton = ui->tab77;
    Tablero[6][7].boton = ui->tab78;

    Tablero[7][0].boton = ui->tab81;
    Tablero[7][1].boton = ui->tab82;
    Tablero[7][2].boton = ui->tab83;
    Tablero[7][3].boton = ui->tab84;
    Tablero[7][4].boton = ui->tab85;
    Tablero[7][5].boton = ui->tab86;
    Tablero[7][6].boton = ui->tab87;
    Tablero[7][7].boton = ui->tab88;

    set_chequeable();

    death_white.emplace_back(ui->w01);
    death_white.emplace_back(ui->w02);
    death_white.emplace_back(ui->w03);
    death_white.emplace_back(ui->w04);
    death_white.emplace_back(ui->w05);
    death_white.emplace_back(ui->w06);
    death_white.emplace_back(ui->w07);
    death_white.emplace_back(ui->w08);
    death_white.emplace_back(ui->w09);
    death_white.emplace_back(ui->w10);
    death_white.emplace_back(ui->w11);
    death_white.emplace_back(ui->w12);
    death_white.emplace_back(ui->w13);
    death_white.emplace_back(ui->w14);
    death_white.emplace_back(ui->w15);

    death_black.emplace_back(ui->b01);
    death_black.emplace_back(ui->b02);
    death_black.emplace_back(ui->b03);
    death_black.emplace_back(ui->b04);
    death_black.emplace_back(ui->b05);
    death_black.emplace_back(ui->b06);
    death_black.emplace_back(ui->b07);
    death_black.emplace_back(ui->b08);
    death_black.emplace_back(ui->b09);
    death_black.emplace_back(ui->b10);
    death_black.emplace_back(ui->b11);
    death_black.emplace_back(ui->b12);
    death_black.emplace_back(ui->b13);
    death_black.emplace_back(ui->b14);
    death_black.emplace_back(ui->b15);
}
