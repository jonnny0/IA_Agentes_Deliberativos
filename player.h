#ifndef PLAYER_H
#define PLAYER_H

#include "environment.h"

class Player
{
public:
    Player(int jug);
    Environment::ActionType Think();
    void Perceive(const Environment &env);
private:
    //método encargado de aplicar minimax con poda alfa-beta a un estado
    double Poda_AlfaBeta(Environment &actual_, int jugador_, int nivel_actual, int PROFUNDIDAD_ALFABETA, double alpha, double beta, bool jugador_maximizador);

    //método que muestra por pantalla un estado
    void VerEstado(const Environment &estado);

    //método que devuelve una puntuación dependiendo del número de casillas pasado
    double Puntuar(int casillas);

    //métodos de comprobación que devuelven la puntuación si se pueden aplicar en esa dirección
    double ComprobarDerecha(const Environment &estado, int i, int j, int jug, int &casillas_positivas);
    double ComprobarIzquierda(const Environment &estado, int i, int j, int jug, int &casillas_positivas);
    double ComprobarArriba(const Environment &estado, int i, int j, int jug, int &casillas_positivas);
    double ComprobarAbajo(const Environment &estado, int i, int j, int jug, int &casillas_positivas);
    double ComprobarArribaDerecha(const Environment &estado, int i, int j, int jug, int &casillas_positivas);
    double ComprobarArribaIzquierda(const Environment &estado, int i, int j, int jug, int &casillas_positivas);
    double ComprobarAbajoDerecha(const Environment &estado, int i, int j, int jug, int &casillas_positivas);
    double ComprobarAbajoIzquierda(const Environment &estado, int i, int j, int jug, int &casillas_positivas);

    //método que recorre todo un estado, llamando a los métodos comprobar, para devolver a valoración
    double Evaluar(const Environment &estado, int jug);

    //método que llama minimax con un estado en concreto, éste llama a evaluar para cada jugador
    double Valoracion(const Environment &estado, int jugador);

    int jugador_;
    Environment actual_;
};
#endif
