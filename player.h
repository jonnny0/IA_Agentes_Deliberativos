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
    //m�todo encargado de aplicar minimax con poda alfa-beta a un estado
    double Poda_AlfaBeta(Environment &actual_, int jugador_, int nivel_actual, int PROFUNDIDAD_ALFABETA, double alpha, double beta, bool jugador_maximizador);

    //m�todo que muestra por pantalla un estado
    void VerEstado(const Environment &estado);

    //m�todo que devuelve una puntuaci�n dependiendo del n�mero de casillas pasado
    double Puntuar(int casillas);

    //m�todos de comprobaci�n que devuelven la puntuaci�n si se pueden aplicar en esa direcci�n
    double ComprobarDerecha(const Environment &estado, int i, int j, int jug, int &casillas_positivas);
    double ComprobarIzquierda(const Environment &estado, int i, int j, int jug, int &casillas_positivas);
    double ComprobarArriba(const Environment &estado, int i, int j, int jug, int &casillas_positivas);
    double ComprobarAbajo(const Environment &estado, int i, int j, int jug, int &casillas_positivas);
    double ComprobarArribaDerecha(const Environment &estado, int i, int j, int jug, int &casillas_positivas);
    double ComprobarArribaIzquierda(const Environment &estado, int i, int j, int jug, int &casillas_positivas);
    double ComprobarAbajoDerecha(const Environment &estado, int i, int j, int jug, int &casillas_positivas);
    double ComprobarAbajoIzquierda(const Environment &estado, int i, int j, int jug, int &casillas_positivas);

    //m�todo que recorre todo un estado, llamando a los m�todos comprobar, para devolver a valoraci�n
    double Evaluar(const Environment &estado, int jug);

    //m�todo que llama minimax con un estado en concreto, �ste llama a evaluar para cada jugador
    double Valoracion(const Environment &estado, int jugador);

    int jugador_;
    Environment actual_;
};
#endif
