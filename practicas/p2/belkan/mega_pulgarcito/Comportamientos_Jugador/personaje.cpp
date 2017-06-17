#include "../Comportamientos_Jugador/personaje.hpp"


Action ComportamientoPersonaje::think(Sensores sensores){
  Action accion;
  paso++;

  switch (paso%7){
      case 0: accion = actTURN_R;
              break;
      case 4: accion = actTURN_L;
  }
  return accion;
}

int ComportamientoPersonaje::interact(Action accion, int valor){
  if(accion == actGIVE or accion == actTHROW){
    if(valor == '4'){
      return 4;
    }
    else{
      return 0;
    }

  }
  else{
    return 0;
  }
}
