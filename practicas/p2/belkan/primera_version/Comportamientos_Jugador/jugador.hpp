#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H
#include <list>
#include "comportamientos/comportamiento.hpp"
using namespace std;

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
	fil=99;
	col=99;
	brujula=0; // 0: Norte, 1: Este, 2: Sur, 3: Oeste.
	ultimaAccion = actIDLE;
//	girar_derecha=false;
	bien_situado=false;
	hay_puerta=0;
	hay_objeto=0;
	for(int i=0; i<200; i++){
		for(int j=0; j<200; j++){
			mapaAux[i][j]='?';
			mapaRecorrido[i][j]=0;
			mapaAuxRec[i][j]=0;
		}
	}
	tiempo=0;
	posx=99;
	posy=99;
	cantidad=0;
	hueso=biquini=zapatillas=llave=regalo=false;
	PK=pos=0;
	PK_visto=false;
      tengo_regalo = false;

      estoy_ejecutando_plan =false;
      error_plan =false;
	rey_visto=false;
	rey.fila=0;rey.columna=0;
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    void Reinicio();

    Action think(Sensores sensores);

    int interact(Action accion, int valor);


    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}


  private:

    struct estado{
    	int fila;
    	int columna;
    	int orientacion;
		friend bool operator<(const estado & a, const estado & b){
			return (a.fila+a.columna) > (b.fila+b.columna);
		}
    };

	struct Paso{
		estado pos;
		float g, h, f;
		list <Action> plan;
		friend bool operator<(const Paso & a, const Paso & b){
			return a.f > b.f;
		}
	};

	int fil,col;
	int brujula;
	Action ultimaAccion;
//	bool girar_derecha;
	bool bien_situado;
    bool tengo_regalo;
	int hay_puerta;
	int hay_objeto;
	int PK, pos; bool PK_visto;
	int mapaRecorrido[200][200], mapaAuxRec[200][200];
	char mapaAux[200][200];
	int tiempo;
	int posx, posy;
	int cantidad;
	bool hueso, biquini, zapatillas, llave, regalo;
	bool rey_visto;
    bool estoy_ejecutando_plan;
    bool error_plan;
    list <Action> plan;
	estado rey;

	const int calcularDistancia(const estado &inicio, const estado &dest) const;
	bool hayObstaculoEnCasilla(const estado &pos);
    bool pathFinding(const estado &origen, const estado &destino, list<Action> &plan);
    bool TrazarPlan(const estado &origen, const estado &destino, list<Action> &plan);
};


#endif
