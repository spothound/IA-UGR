#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H
#include <list>
#include<queue>
#include<set>
#include "comportamientos/comportamiento.hpp"
#include<iostream>
using namespace std;

class ComportamientoJugador : public Comportamiento{

public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){

        // Inicializar Variables de Estado
        fil = col = 99;
        brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
        ultimaAccion = actIDLE;
        girar_derecha = false;
        situado = false;



        estoy_ejecutando_plan =false;
        error_plan =false;

        ultimo_objeto = -1 ;
        tiempo = 0 ;

        for(int i = 0 ; i < 5 ; i ++){
            lotengo[i] = false;
        }
        nobjetos = 0 ;
        puerta_abierta = 0;
        tirar = 0;
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);

    int interact(Action accion, int valor);


    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}



private:

    int paseo = 0 ;
    int puerta_abierta ;
    Action accion ;
    int nobjetos ;
    int memoria[100][100];
    int memoriaAUX[200][200];
    char mapaAUX[200][200];
    char superficie[100][100];
    char superficieAUX[200][200];



    struct Estado{
        int fila;
        int columna;
        int orientacion;

        bool operator==(const Estado & a){
            return(fila == a.fila and columna == a.columna) ;
        }
        bool operator==(const Estado & a)const{
            return(fila == a.fila and columna == a.columna) ;
        }

        bool operator<(const Estado & a){
            if(fila < a.fila)
                return true ;
            else{
                if(fila == a.fila)
                    return(columna < a.columna);
                else
                    return false ;
            }
        }
        bool operator<(const Estado & a)const{
            if(fila < a.fila)
                return true ;
            else{
                if(fila == a.fila)
                    return(columna < a.columna);
                else
                    return false ;
            }
        }

        friend std::ostream & operator<<(std::ostream& os, const Estado & out){
            os << "\n" << out.fila
               << ", " << out.columna
               << " -- " << out.orientacion ;
            return os ;
        }
    };



    struct estadoHash{
        std::size_t operator()(const Estado& pos) const {
            int x, y,z;
            x = pos.fila ; y = pos.columna ; z = pos.orientacion ;
            return x * 1812433253 + 1001*y + z;
        }
    };

    set<Estado> objetivos ;

    bool breadth_first_search(Estado inicio, Estado objetivo);

    vector<Estado> Vecinos(Estado id) ;

    bool lotengo[5] ;

    int NuevosVisibles(char dir);
    int tirar;
    int avanza, izquierda, derecha;
    char encimade, delante ;
    int tiempo;
    char miobj;
    char frente ;
    char supd ;
    int objeto_tirar ;

    int ultimo_objeto ;


    // Declarar Variables de Estado
    int fil, col, brujula;
    Action ultimaAccion;
    bool girar_derecha;
    bool situado;

    // Para el plan
    bool estoy_ejecutando_plan;
    bool error_plan;
    list <Action> plan;


    bool hayObstaculoDelante(const vector<unsigned char> & terreno,
                             const vector<unsigned char> & superficie);
    bool A_estrella_search(Estado inicio, Estado objetivo);
    void Reiniciar();
    void Pulgarcito();
    bool SuperarObstaculo();
    bool PuedoPisar(char c);
    bool PuedoPisar(Estado actual, Estado objetivo);
    bool PuedoPisar(char actual, char c);
    bool PuedoPisar(Estado id) ;
    void DecisionesNoMovimiento();
    pair<int,int> Posicion(int pasos, char direccion);
    pair<int,int> Posicion(int pasos, char direccion,Estado origen);
    void Giro();
    void situar(int fil, int col);
    void Cartografiar(Sensores sensores);
    void situar(Sensores sensores);
    void NoPisarAlante();
    bool MejorGiroIzquierda();
    int Distancia(pair<int,int> pos1, pair<int,int> pos2);
    double heuristica(Estado a, Estado b);
    void Objetivo(int fil, int col);
    int Distancia(Estado origen, Estado destino);
    Estado getObjetivo();
};

#endif
