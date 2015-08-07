#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf=9999999999.0, menosinf=-9999999999.0;

int EnteroGlobal = 0;

// Constructor
Player::Player(int jug)
{
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment & env)
{
    actual_=env;
}

double Puntuacion(int jugador, const Environment &estado)
{
    double suma=0;

    for (int i=0; i<7; i++)
        for (int j=0; j<7; j++)
        {
            if (estado.See_Casilla(i,j)==jugador)
            {
                if (j<3)
                    suma += j;
                else
                    suma += (6-j);
            }
        }

    return suma;
}


// Funcion de valoracion para testear Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador)
{
    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
        return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
        return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
        return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
        return Puntuacion(jugador,estado);
}

// ------------------- Los tres metodos anteriores no se pueden modificar


//método para poder ver un estado
void Player::VerEstado(const Environment &estado)
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            cout << estado.See_Casilla(i,j) << "| ";
        }
        cout << endl << "--------------------" << endl;
    }
}


//devuelvo la puntuación dependiendo del número de casillas pasado
double Player::Puntuar(int casillas)
{
    if (casillas == 0)
    {
        return 0;
    }
    else if (casillas == 1)
    {
        return 1;
    }
    else if (casillas == 2)
    {
        return 1000;
    }
    else if (casillas == 3)
    {
        return 100000;
    }
    else
    {
        return masinf;
    }
}


//compruebo en esta dirección, si no se sale y hay espacio para poder ganar
double Player::ComprobarDerecha(const Environment &estado, int i, int j, int jug, int &casillas_positivas)
{
    double total_positivos = 0;
    int oponente;

    if (jug == 1)
    {
        oponente = 2;
    }
    else
    {
        oponente = 1;
    }

    if((j+3)<7) //comprobacion derecha
    {
        if((int)estado.See_Casilla(i, j+1)!=oponente)
        {
            if((int)estado.See_Casilla(i, j+1)==jug)
            {
                casillas_positivas++;
            }
            if ((int)estado.See_Casilla(i, j+2)!=oponente)
            {
                if ((int)estado.See_Casilla(i, j+2)==jug)
                {
                    casillas_positivas++;
                }
                if ((int)estado.See_Casilla(i, j+3)!=oponente)
                {
                    if ((int)estado.See_Casilla(i, j+3)==jug)
                    {
                        casillas_positivas++;
                    }
                }
                else if((int)estado.See_Casilla(i, j+3)==oponente)
                {
                    total_positivos -= 1000;
                    casillas_positivas=0;
                }
            }
            else if((int)estado.See_Casilla(i, j+2)==oponente)
            {
                total_positivos -= 100;
                casillas_positivas=0;
            }
        }
        else if((int)estado.See_Casilla(i, j+1)==oponente)
        {
            total_positivos -= 10;
            casillas_positivas=0;
        }
        total_positivos += Puntuar(casillas_positivas);
        casillas_positivas=0;
    }
    return total_positivos;
}


//compruebo en esta dirección, si no se sale y hay espacio para poder ganar
double Player::ComprobarIzquierda(const Environment &estado, int i, int j, int jug, int &casillas_positivas)
{
    double total_positivos = 0;
    int oponente;

    if (jug == 1)
    {
        oponente = 2;
    }
    else
    {
        oponente = 1;
    }

    if((j-3)>0) //comprobacion izquierda
    {
        if((int)estado.See_Casilla(i, j-1)!=oponente)
        {
            if((int)estado.See_Casilla(i, j-1)==jug)
            {
                casillas_positivas++;
            }
            if ((int)estado.See_Casilla(i, j-2)!=oponente)
            {
                if ((int)estado.See_Casilla(i, j-2)==jug)
                {
                    casillas_positivas++;
                }
                if ((int)estado.See_Casilla(i, j-3)!=oponente)
                {
                    if ((int)estado.See_Casilla(i, j-3)==jug)
                    {
                        casillas_positivas++;
                    }
                }
                else if((int)estado.See_Casilla(i, j-3)==oponente)
                {
                    total_positivos -= 1000;
                    casillas_positivas=0;
                }
            }
            else if((int)estado.See_Casilla(i, j-2)==oponente)
            {
                total_positivos -= 100;
                casillas_positivas=0;
            }
        }
        else if((int)estado.See_Casilla(i, j-1)==oponente)
        {
            total_positivos -= 10;
            casillas_positivas=0;
        }
        total_positivos += Puntuar(casillas_positivas);
        casillas_positivas=0;
    }
    return total_positivos;
}


//compruebo en esta dirección, si no se sale y hay espacio para poder ganar
double Player::ComprobarArriba(const Environment &estado, int i, int j, int jug, int &casillas_positivas)
{
    double total_positivos = 0;
    int oponente;

    if (jug == 1)
    {
        oponente = 2;
    }
    else
    {
        oponente = 1;
    }

    if((i-3)>0)//comprobacion arriba
    {
        if((int)estado.See_Casilla(i-1, j)!=oponente)
        {
            if((int)estado.See_Casilla(i-1, j)==jug)
            {
                casillas_positivas++;
            }
            if ((int)estado.See_Casilla(i-2, j)!=oponente)
            {
                if ((int)estado.See_Casilla(i-2, j)==jug)
                {
                    casillas_positivas++;
                }
                if ((int)estado.See_Casilla(i-3, j)!=oponente)
                {
                    if ((int)estado.See_Casilla(i-3, j)==jug)
                    {
                        casillas_positivas++;
                    }
                }
                else if((int)estado.See_Casilla(i-3, j)==oponente)
                {
                    total_positivos -= 1000;
                    casillas_positivas=0;
                }
            }
            else if((int)estado.See_Casilla(i-2, j)==oponente)
            {
                total_positivos -= 100;
                casillas_positivas=0;
            }
        }
        else if((int)estado.See_Casilla(i-1, j)==oponente)
        {
            total_positivos -= 10;
            casillas_positivas=0;
        }
        total_positivos += Puntuar(casillas_positivas);
        casillas_positivas=0;
    }
    return total_positivos;
}


//compruebo en esta dirección, si no se sale y hay espacio para poder ganar
double Player::ComprobarAbajo(const Environment &estado, int i, int j, int jug, int &casillas_positivas)
{
    double total_positivos = 0;
    int oponente;

    if (jug == 1)
    {
        oponente = 2;
    }
    else
    {
        oponente = 1;
    }

    if((i+3)<7) //comprobacion abajo
    {

        if((int)estado.See_Casilla(i+1, j)!=oponente)
        {
            if((int)estado.See_Casilla(i+1, j)==jug)
            {
                casillas_positivas++;
            }

            if ((int)estado.See_Casilla(i+2, j)!=oponente)
            {
                if ((int)estado.See_Casilla(i+2, j)==jug)
                {
                    casillas_positivas++;
                }
                if ((int)estado.See_Casilla(i+3, j)!=oponente)
                {
                    if ((int)estado.See_Casilla(i+3, j)==jug)
                    {
                        casillas_positivas++;
                    }
                }
                else if((int)estado.See_Casilla(i+3, j)==oponente)
                {
                    total_positivos -= 1000;
                    casillas_positivas=0;
                }
            }
            else if((int)estado.See_Casilla(i+2, j)==oponente)
            {
                total_positivos -= 100;
                casillas_positivas=0;
            }
        }
        else if((int)estado.See_Casilla(i+1, j)==oponente)
        {
            total_positivos -= 10;
            casillas_positivas=0;
        }
        total_positivos += Puntuar(casillas_positivas);
        casillas_positivas=0;
    }
    return total_positivos;
}


//compruebo en esta dirección, si no se sale y hay espacio para poder ganar
double Player::ComprobarArribaDerecha(const Environment &estado, int i, int j, int jug, int &casillas_positivas)
{
    double total_positivos = 0;
    int oponente;

    if (jug == 1)
    {
        oponente = 2;
    }
    else
    {
        oponente = 1;
    }
    if((i-3)>0 && (j+3)<7)//comprobacion arriba derecha
    {

        if((int)estado.See_Casilla(i-1, j+1)!=oponente)
        {
            if((int)estado.See_Casilla(i-1, j+1)==jug)
            {
                casillas_positivas++;
            }

            if ((int)estado.See_Casilla(i-2, j+2)!=oponente)
            {
                if ((int)estado.See_Casilla(i-2, j+2)==jug)
                {
                    casillas_positivas++;
                }
                if ((int)estado.See_Casilla(i-3, j+3)!=oponente)
                {
                    if ((int)estado.See_Casilla(i-3, j+3)==jug)
                    {
                        casillas_positivas++;
                    }
                }
                else if((int)estado.See_Casilla(i-3, j+3)==oponente)
                {
                    total_positivos -= 1000;
                    casillas_positivas=0;
                }
            }
            else if((int)estado.See_Casilla(i-2, j+2)==oponente)
            {
                total_positivos -= 100;
                casillas_positivas=0;
            }
        }
        else if((int)estado.See_Casilla(i-1, j+1)==oponente)
        {
            total_positivos -= 10;
            casillas_positivas=0;
        }
        total_positivos += Puntuar(casillas_positivas);
        casillas_positivas=0;
    }
    return total_positivos;
}


//compruebo en esta dirección, si no se sale y hay espacio para poder ganar
double Player::ComprobarArribaIzquierda(const Environment &estado, int i, int j, int jug, int &casillas_positivas)
{
    double total_positivos = 0;
    int oponente;

    if (jug == 1)
    {
        oponente = 2;
    }
    else
    {
        oponente = 1;
    }
    if((j-3)>0 && (i-3)>0)//comprobacion arriba izquierda
    {

        if((int)estado.See_Casilla(i-1, j-1)!=oponente)
        {
            if((int)estado.See_Casilla(i-1, j-1)==jug)
            {
                casillas_positivas++;
            }

            if ((int)estado.See_Casilla(i-2, j-2)!=oponente)
            {
                if ((int)estado.See_Casilla(i-2, j-2)==jug)
                {
                    casillas_positivas++;
                }
                if ((int)estado.See_Casilla(i-3, j-3)!=oponente)
                {
                    if ((int)estado.See_Casilla(i-3, j-3)==jug)
                    {
                        casillas_positivas++;
                    }
                }
                else if((int)estado.See_Casilla(i-3, j-3)==oponente)
                {
                    total_positivos -= 1000;
                    casillas_positivas=0;
                }
            }
            else if((int)estado.See_Casilla(i-2, j-2)==oponente)
            {
                total_positivos -= 100;
                casillas_positivas=0;
            }
        }
        else if((int)estado.See_Casilla(i-1, j-1)==oponente)
        {
            total_positivos -= 10;
            casillas_positivas=0;
        }
        total_positivos += Puntuar(casillas_positivas);
        casillas_positivas=0;
    }
    return total_positivos;
}


//compruebo en esta dirección, si no se sale y hay espacio para poder ganar
double Player::ComprobarAbajoDerecha(const Environment &estado, int i, int j, int jug, int &casillas_positivas)
{
    double total_positivos = 0;
    int oponente;

    if (jug == 1)
    {
        oponente = 2;
    }
    else
    {
        oponente = 1;
    }
    if((j+3)<7 && (i+3)<7)//comprobacion abajo derecha
    {
        if((int)estado.See_Casilla(i+1, j+1)!=oponente)
        {
            if((int)estado.See_Casilla(i+1, j+1)==jug)
            {
                casillas_positivas++;
            }

            if ((int)estado.See_Casilla(i+2, j+2)!=oponente)
            {
                if ((int)estado.See_Casilla(i+2, j+2)==jug)
                {
                    casillas_positivas++;
                }
                if ((int)estado.See_Casilla(i+3, j+3)!=oponente)
                {
                    if ((int)estado.See_Casilla(i+3, j+3)==jug)
                    {
                        casillas_positivas++;
                    }
                }
                else if((int)estado.See_Casilla(i+3, j+3)==oponente)
                {
                    total_positivos -= 1000;
                    casillas_positivas=0;
                }
            }
            else if((int)estado.See_Casilla(i+2, j+2)==oponente)
            {
                total_positivos -= 100;
                casillas_positivas=0;
            }
        }
        else if((int)estado.See_Casilla(i+1, j+1)==oponente)
        {
            total_positivos -= 10;
            casillas_positivas=0;
        }
        total_positivos += Puntuar(casillas_positivas);
        casillas_positivas=0;
    }
    return total_positivos;
}


//compruebo en esta dirección, si no se sale y hay espacio para poder ganar
double Player::ComprobarAbajoIzquierda(const Environment &estado, int i, int j, int jug, int &casillas_positivas)
{
    double total_positivos = 0;
    int oponente;

    if (jug == 1)
    {
        oponente = 2;
    }
    else
    {
        oponente = 1;
    }
    if((j-3)>0 && (i+3)<7) //comprobacion abajo izquierda
    {

        if((int)estado.See_Casilla(i+1, j-1)!=oponente)
        {
            if((int)estado.See_Casilla(i+1, j-1)==jug)
            {
                casillas_positivas++;
            }

            if ((int)estado.See_Casilla(i+2, j-2)!=oponente)
            {
                if ((int)estado.See_Casilla(i+2, j-2)==jug)
                {
                    casillas_positivas++;
                }
                if ((int)estado.See_Casilla(i+3, j-3)!=oponente)
                {
                    if ((int)estado.See_Casilla(i+3, j-3)==jug)
                    {
                        casillas_positivas++;
                    }
                }
                else if((int)estado.See_Casilla(i+3, j-3)==oponente)
                {
                    total_positivos -= 1000;
                    casillas_positivas=0;
                }
            }
            else if((int)estado.See_Casilla(i+2, j-2)==oponente)
            {
                total_positivos -= 100;
                casillas_positivas=0;
            }
        }
        else if((int)estado.See_Casilla(i+1, j-1)==oponente)
        {
            total_positivos -= 10;
            casillas_positivas=0;
        }
        total_positivos += Puntuar(casillas_positivas);
        casillas_positivas=0;
    }
    return total_positivos;
}

//evalúa un estado
double Player::Evaluar(const Environment &estado, int jug)
{
    int casillas_positivas = 0;
    double total_positivos = 0;
    int oponente;

    if (jug == 1)
    {
        oponente = 2;
    }
    else
    {
        oponente = 1;
    }

    //recorro todas las casillas
    for(int i=0; i<7; i++)
    {
        for(int j=0; j<7; j++)
        {
            //si es una casilla del jugador
            //recorro todas sus adyacentes llamando a sus métodos correspondientes
            //añado esos valores al valor a devolver
            if((int)estado.See_Casilla(i, j)==jug)
            {
                casillas_positivas++;
                total_positivos += ComprobarDerecha(estado, i, j, jug, casillas_positivas);
                total_positivos += ComprobarIzquierda(estado, i, j, jug, casillas_positivas);
                total_positivos += ComprobarArriba(estado, i, j, jug, casillas_positivas);
                total_positivos += ComprobarAbajo(estado, i, j, jug, casillas_positivas);
                total_positivos += ComprobarArribaDerecha(estado, i, j, jug, casillas_positivas);
                total_positivos += ComprobarArribaIzquierda(estado, i, j, jug, casillas_positivas);
                total_positivos += ComprobarAbajoDerecha(estado, i, j, jug, casillas_positivas);
                total_positivos += ComprobarAbajoIzquierda(estado, i, j, jug, casillas_positivas);
            }
            else if((int)estado.See_Casilla(i, j)==oponente)
            {
                total_positivos -= 1;
            }
        }
    }
    return total_positivos;
}


//valora un estado
double Player::Valoracion(const Environment &estado, int jugador)
{
    double valor = 0;
    int oponente;

    if (jugador == 1)
    {
        oponente = 2;
    }
    else
    {
        oponente = 1;
    }

    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
        return masinf; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
        return menosinf; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
        return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
    {
        //evalúo el estado como jugador y como oponente
        valor += Evaluar(estado,jugador);
        valor -= Evaluar(estado,oponente);
    }

    return valor;
}


//aplico minimax con poda alfa-beta
double Player::Poda_AlfaBeta(Environment &actual_, int jugador_, int nivel_actual, int PROFUNDIDAD_ALFABETA, double alpha, double beta, bool jugador_maximizador)
{
    Environment V[7]; //V son los posibles estados
    int n_act;

    //si estoy en un nodo hoja o en un estado terminal
    if (nivel_actual == PROFUNDIDAD_ALFABETA || actual_.JuegoTerminado())
    {
        return Valoracion(actual_, jugador_);

    }
    else if (jugador_maximizador)
    {
        n_act = actual_.GenerateAllMoves(V);

        for (int i = 0; i < n_act; i++)
        {
            alpha = max(alpha, Poda_AlfaBeta(V[i], jugador_, nivel_actual+1, PROFUNDIDAD_ALFABETA, alpha, beta, false));

            if (beta <= alpha) //si se cruzan alfa y beta se poda
            {
                break;
            }
        }

        return alpha;
    }
    else
    {
        n_act = actual_.GenerateAllMoves(V);

        for (int i = 0; i < n_act; i++)
        {
            beta = min(beta, Poda_AlfaBeta(V[i], jugador_, nivel_actual+1, PROFUNDIDAD_ALFABETA, alpha, beta, true));

            if (beta <= alpha) //si se cruzan alfa y beta se poda
            {
                break;
            }
        }
        return beta;
    }
}


// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think()
{
    const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
    const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

    Environment::ActionType accion; // acción que se va a devolver
    bool aplicables[7]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
    // aplicables[0]==true si PUT1 es aplicable
    // aplicables[1]==true si PUT2 es aplicable
    // aplicables[2]==true si PUT3 es aplicable
    // aplicables[3]==true si PUT4 es aplicable
    // aplicables[4]==true si PUT5 es aplicable
    // aplicables[5]==true si PUT6 es aplicable
    // aplicables[6]==true si PUT7 es aplicable

    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha, beta; // Cotas de la poda AlfaBeta

    int n_act; //Acciones posibles en el estado actual


    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    cout << " Acciones aplicables ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<7; t++)
        if (aplicables[t])
            cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;


    alpha = menosinf;
    beta = masinf;
    Environment V[7];
    n_act = actual_.GenerateAllMoves(V); //genero los todos posibles movimientos de actual_ y los almaceno en V
    double valores[7]; //vector donde se almacenarán los valores devueltos por la función Posa_Alfabeta

    //para todos los posibles movientos
    for (int i = 0; i < n_act; i++)
    {
        //calculo su valor minimax usando poda alfa-beta y lo almaceno en valores
        valores[i] = Poda_AlfaBeta(V[i], jugador_, 1, PROFUNDIDAD_ALFABETA, alpha, beta, false);
        cout << "valores[" << i << "]: " << valores[i] << endl;
    }

    //asigno a mayor el valor más pequeño posible
    double mayor = menosinf-1;
    accion = static_cast< Environment::ActionType > (-1);

    //recorro los valores de los hijos del estado actual y si es mayor que el actual, actualizo accion
    for (int i = 0; i < n_act; i++)
    {
        if (valores[i]>mayor)
        {
            mayor = valores[i];
            accion = static_cast< Environment::ActionType > (V[i].Last_Action(jugador_));
        }
    }

    cout << "Valor MiniMax: " << mayor << "  Accion: " << actual_.ActionStr(accion) << endl;

    return accion;
}

