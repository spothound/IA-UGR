#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;


void ComportamientoJugador::Reinicio(){
    situado = false ;
    for(int i = 0 ; i < 4 ; i++){
        lotengo[i] = false ;
    }
    brujula = 0 ;
    ultimaAccion = actIDLE ;
}

Action ComportamientoJugador::think(Sensores sensores){

    Action accion = actIDLE;

    if(sensores.reset)
        Reinicio() ;

    cout << "Terreno: ";
    for (int i=0; i<sensores.terreno.size(); i++)
        cout << sensores.terreno[i];
    cout << endl;

    cout << "Superficie: ";
    for (int i=0; i<sensores.superficie.size(); i++)
        cout << sensores.superficie[i];
    cout << endl;

    cout << "Colision: " << sensores.colision << endl;
    cout << "Mochila: " << sensores.mochila << endl;
    cout << "Reset: " << sensores.reset << endl;
    cout << "Vida: " << sensores.vida << endl;
    cout << "Fila: " << sensores.mensajeF << endl;
    cout << "Columna: " << sensores.mensajeC << endl;
    cout << "objetoActivo: " << sensores.objetoActivo << endl;
    cout << endl;

    switch(ultimaAccion){
    case actFORWARD:
        switch(brujula){
        case 0: // NORTE
            fil-- ;
            break ;
        case 1: //ESTE
            col++ ;
            break ;
        case 2: //SUR
            fil++ ;
            break ;
        case 3: //OESTE
            col-- ;
            break ;
        }
        break ;
    case actTURN_L:
        brujula = (brujula+3)%4 ;
        break ;
    case actTURN_R:
        brujula = (brujula+1)%4 ;
        break ;
    }

    if(sensores.terreno[0]=='K' and !situado){
        fil = sensores.mensajeF ;
        col = sensores.mensajeC ;
        situado = true ;
    }


    if(situado)
        mapaResultado[fil][col] = sensores.terreno[0] ;

    if( plan.empty()){
        plan.push(actFORWARD) ;
        plan.push(actFORWARD) ;
        plan.push(actTURN_L)  ;
        plan.push(actFORWARD) ;
        plan.push(actFORWARD) ;
        plan.push(actTURN_R)  ;
    }

    accion = plan.front() ;
    plan.pop() ;

    if(accion == actFORWARD){
        int r ;
        char frente = sensores.terreno[2] ;
        switch(frente){
        case 'B':
        case 'A':
        case 'P':
        case 'M':
        case 'D':
            r = rand()%2 ;
            if(r == 0)
                accion = actTURN_R ;
            else
                accion = actTURN_L ;
        }
    }


    ultimaAccion = accion ;
    return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
