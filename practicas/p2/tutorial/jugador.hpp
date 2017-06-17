#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H
#include <list>
#include "comportamientos/comportamiento.hpp"
using namespace std;

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      ultimaAccion = actIDLE;
      girar_derecha = false;
      bien_situado = false;
      tengo_regalo = false;

      estoy_ejecutando_plan =false;
      error_plan =false;
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);

    int interact(Action accion, int valor);


    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}



  private:

    struct estado{
    	int fila;
    	int columna;
    	int orientacion;
    };


    // Declarar Variables de Estado
    int fil, col, brujula;
    Action ultimaAccion;
    bool girar_derecha;
    bool bien_situado;
    bool tengo_regalo;

      // Para el plan
    bool estoy_ejecutando_plan;
    bool error_plan;
    list <Action> plan;


    void Reiniciar();
    bool pathFinding(const estado &origen, const estado &destino, list<Action> &plan);


};


#endif
