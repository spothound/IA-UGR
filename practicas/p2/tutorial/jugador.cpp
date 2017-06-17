#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
#include <vector>
#include <queue>
using namespace std;


bool ComportamientoJugador::pathFinding(const estado &origen, const estado &destino, list<Action> &plan){

	//Borro la lista
	plan.clear();

	estado st = origen;

	int difF = origen.fila - destino.fila;
	int difC = origen.columna - destino.columna;

	// Reduzco la distancia en columnas
	if (difC < 0){
		if (st.orientacion == 0){
			plan.push_back(actTURN_R);
			st.orientacion = 1;
		}
		else if (st.orientacion == 3){
					plan.push_back(actTURN_R);
					plan.push_back(actTURN_R);
					st.orientacion = 1;
		}
		else if (st.orientacion == 2){
					plan.push_back(actTURN_L);
					st.orientacion = 1;
		}
	}
	else if (difC > 0){
		if (st.orientacion == 0){
			plan.push_back(actTURN_L);
			st.orientacion = 3;
		}
		else if (st.orientacion == 1){
					plan.push_back(actTURN_R);
					plan.push_back(actTURN_R);
					st.orientacion = 3;
		}
		else if (st.orientacion == 2){
					plan.push_back(actTURN_R);
					st.orientacion = 3;
		}
	}

	// Avanzo la diferencia entre columnas
	if (difC<0)
	  difC = -difC;

  for (int i=0; i < difC; i++){
		plan.push_back(actFORWARD);
	}

	// Reduzco la distancia en filas
	if (difF < 0){
		if (st.orientacion == 1){
			plan.push_back(actTURN_R);
			st.orientacion = 2;
		}
		else if (st.orientacion == 3){
					plan.push_back(actTURN_L);
					st.orientacion = 2;
		}
	}
	else if (difF > 0){
		if (st.orientacion == 1){
			plan.push_back(actTURN_L);
			st.orientacion = 0;
		}
		else if (st.orientacion == 3){
					plan.push_back(actTURN_R);
					st.orientacion = 0;
		}
	}


	// Avanzo la diferencia entre columnas
	if (difF<0)
	  difF = -difF;

  for (int i=0; i < difF; i++){
		plan.push_back(actFORWARD);
	}

	return true;
}

void ComportamientoJugador::Reiniciar(){
	fil = col = 99;
	ultimaAccion = actIDLE;
	bien_situado = false;
	brujula = 0;
	estoy_ejecutando_plan =false;
	error_plan =false;

}

bool hayObstaculoDelante(const vector<unsigned char> & terreno, const vector<unsigned char> & superficie){
	if ( (terreno[2]=='T' or terreno[2]=='S' or terreno[2]=='K') and
				superficie[2]=='_'){
					return false;
	}
	else{
	 return true;
 }
}

void PintaPlan(list<Action> plan){
	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			cout << "A ";
		}
		else if (*it == actTURN_R){
			cout << "D ";
		}
		else if (*it == actTURN_L){
			cout << "I ";
		}
		else {
			cout << "- ";
		}
		it++;
	}
	cout << endl;
}


Action ComportamientoJugador::think(Sensores sensores){

	Action accion = actIDLE;

	if (sensores.reset){
		Reiniciar();
	}

	// Actualización de la información del mundo
	switch (ultimaAccion) {
		case actFORWARD:
		  if (!sensores.colision){
				switch (brujula) {
					case 0: // Norte
					  fil--;
						break;
					case 1: // Este
					  col++;
						break;
					case 2: // Sur
						fil++;
						break;
					case 3: // Oeste
						col--;
						break;
				}
			}
			break;
		case actTURN_L:
			brujula = (brujula+3)%4;
			if (rand()%2==0) girar_derecha=true;
			else  girar_derecha=false;
		  break;
		case actTURN_R:
			brujula = (brujula+1)%4;
			if (rand()%2==0) girar_derecha=true;
			else  girar_derecha=false;
		  break;
		case actPICKUP:
			if (sensores.objetoActivo == '4'){
				tengo_regalo = true;
				estoy_ejecutando_plan = false;
			}
			break;
			case actGIVE:
				if (sensores.objetoActivo == '_'){
					tengo_regalo = false;
				}
				break;
	}

	if (error_plan){
		estoy_ejecutando_plan = false;
	}

	if (estoy_ejecutando_plan and plan.front() == actFORWARD and hayObstaculoDelante(sensores.terreno, sensores.superficie)){
		if (sensores.superficie[2] == 'a' or sensores.superficie[2] == 'l'){
			plan.push_front(actIDLE);
			error_plan = false;
		}
		else {
			error_plan=true;
		}
	}
	else {
		error_plan = false;
	}

	if (bien_situado){
		mapaResultado[fil][col] = sensores.terreno[0];
	}

	if (sensores.terreno[0]=='K' and !bien_situado){
		fil = sensores.mensajeF;
		col = sensores.mensajeC;
		bien_situado = true;
	}

	if (bien_situado and !tengo_regalo and !estoy_ejecutando_plan and sensores.regalos.size()>0){
		estado origen;
		origen.fila = fil;
		origen.columna = col;
		origen.orientacion = brujula;

		estado destino;
		destino.fila = sensores.regalos[0].first;
		destino.columna = sensores.regalos[0].second;

		estoy_ejecutando_plan = pathFinding(origen, destino, plan);
	}



	// Decidir acciones de no movimiento
	if (sensores.superficie[2] == '4' and sensores.objetoActivo == '_'){
		accion = actPICKUP;
	}
	else if (sensores.superficie[2] == 'r' and sensores.objetoActivo == '4'){
		accion = actGIVE;
	}
	// Decidir la nueva acción de movimiento
	else if (estoy_ejecutando_plan and !error_plan){
		accion = plan.front();
		plan.erase(plan.begin());
		PintaPlan(plan);
		if (plan.size()==0){
			estoy_ejecutando_plan = false;
		}
	}
	else if ( !hayObstaculoDelante(sensores.terreno, sensores.superficie)){
		accion = actFORWARD;
	}
	else if (!girar_derecha) {
		accion = actTURN_L;
	}
	else {
		accion = actTURN_R;
	}

	// Recordar la ultima accion
	ultimaAccion = accion;
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
