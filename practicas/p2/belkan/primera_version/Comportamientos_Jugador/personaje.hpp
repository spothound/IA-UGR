#ifndef COMPORTAMIENTOPERSONAJE_H
#define COMPORTAMIENTOPERSONAJE_H

#include "comportamientos/comportamiento.hpp"

class ComportamientoPersonaje : public Comportamiento{

  public:
    ComportamientoPersonaje(unsigned int size = 0) : Comportamiento(size){
      paso=0;
    }
    ComportamientoPersonaje(const ComportamientoPersonaje & comport) : Comportamiento(comport){}
    ~ComportamientoPersonaje(){}

    Action think(Sensores sensores);

    int interact(Action accion, int valor);


    ComportamientoPersonaje * clone(){return new ComportamientoPersonaje(*this);}

  private:
    int paso;

};



#endif
