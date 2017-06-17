#include "../Comportamientos_Jugador/jugador.hpp"
#include <stdlib.h>
#include <random>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;


const int ComportamientoJugador::calcularDistancia(const estado &inicio, const estado &dest) const{
	static int xd, yd, dist;
	xd=dest.fila-inicio.fila;
	yd=dest.columna-inicio.columna;
	
	dist=abs(xd)+abs(yd);

	return dist;
}

bool ComportamientoJugador::hayObstaculoEnCasilla(const estado &pos){
	if ( (mapaResultado[pos.fila][pos.columna]=='T' or mapaResultado[pos.fila][pos.columna]=='S' or mapaResultado[pos.fila][pos.columna]=='K')){
//	if(mapaRecorrido[pos.fila][pos.columna]==9999999){
					return false;
	}
	else{
	 return true;
 }
}


bool ComportamientoJugador::TrazarPlan(const estado &inicio, const estado &destino, list <Action> & plan){ 
    bool hellegado= false;
    bool esta;

    Paso inicial, actual, izq, dcha, avanzar;

	plan.clear();


    inicial.pos=inicio;
    inicial.h = calcularDistancia(inicio, destino);
    inicial.g=0;
    inicial.f=inicial.h+inicial.g;

    set<estado> cerrados;
    priority_queue <Paso> pq;
    pq.push(inicial);

    while(!pq.empty() && !hellegado){
        actual=pq.top();
        pq.pop();
        
        if((actual.pos.fila == destino.fila && actual.pos.columna == destino.columna)){//(actual.pos.fila-1 == destino.fila && actual.pos.columna == destino.columna)||(actual.pos.fila+1 == destino.fila && actual.pos.columna == destino.columna)||(actual.pos.fila == destino.fila && actual.pos.columna-1 == destino.columna)||(actual.pos.fila == destino.fila && actual.pos.columna+1 == destino.columna)||
            hellegado=true;
            plan=actual.plan;
			cout << "aaaahhhh";
        }
        else{
            esta=!cerrados.insert(actual.pos).second;
            if(!esta){
                izq=actual;
                izq.g++; 
                izq.f=izq.g+izq.h; 
                izq.plan.push_back(actTURN_L);

	cout << "venga yaaaaaaaaaaaa";

                if(!hayObstaculoEnCasilla(izq.pos)) 
                    pq.push(izq);

				dcha=actual;
                dcha.g++; 
                dcha.f=dcha.g+dcha.h; 
                dcha.plan.push_back(actTURN_R);

                if(!hayObstaculoEnCasilla(dcha.pos)) 
                    pq.push(dcha);
                
                avanzar=actual;
				avanzar.g++;
                avanzar.plan.push_back(actFORWARD);
                avanzar.h=calcularDistancia(avanzar.pos,destino);
                avanzar.f=avanzar.g+avanzar.h;

                
                if(!hayObstaculoEnCasilla(avanzar.pos))
                    pq.push(avanzar);

            }
        }
    }

    return hellegado;

}


void ComportamientoJugador::Reinicio(){
	fil=99;
	col=99;
	brujula=0; // 0: Norte, 1: Este, 2: Sur, 3: Oeste.
	ultimaAccion = actIDLE;
	for(int i=0; i<200; i++)
		for(int j=0; j<200; j++)
			mapaAux[i][j]='?';
//	girar_derecha=false;

	for(int i=0; i<200; i++)
		for(int j=0; j<200; j++)
			mapaRecorrido[i][j]=mapaAuxRec[i][j];
//			mapaRecorrido[i][j]=0;
	tiempo=0;
	posx=99;
	posy=99;

	bien_situado=false;
	cantidad=0;
	hay_puerta=0;
	hay_objeto=0;
	hueso=biquini=zapatillas=llave=regalo=false;
	PK=pos=0;
	PK_visto=false;
	estoy_ejecutando_plan =false;
	error_plan =false;
	rey_visto=false;
	rey.fila=0;rey.columna=0;
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

	if(sensores.reset)
		Reinicio();

	switch (ultimaAccion){
		case actFORWARD:
			if(!sensores.colision){
				switch (brujula){
					case 0: // Norte
						fil--;
						posx--;
					break;
					case 1: // Este
						col++;
						posy++;
					break;
					case 2: // Sur
						fil++;
						posx++;
					break;
					case 3: // Oeste
						col--;
						posy--;
					break;
				}
			}
		break;

		case actTURN_L:
			brujula = (brujula+3)%4;
		break;

		case actTURN_R:
			brujula = (brujula+1)%4;
		break;


	}	

	tiempo++;
	mapaRecorrido[posx][posy]=tiempo;


	// En esta matriz de tamano 100x100 hay que escribir el mapa solucion
	// mapaResultado[fila][columna] = lo que hay en fila columna

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

	if(sensores.objetoActivo == '0')
		hueso=true;
	else if(sensores.objetoActivo == '1')
		biquini=true;
	else if(sensores.objetoActivo == '2')
		zapatillas=true;
	else if(sensores.objetoActivo == '3')
		llave=true;
	else if(sensores.objetoActivo == '4'){
		regalo=true;
		estoy_ejecutando_plan = false;
	}


	if (bien_situado){
		int x=1,y=-1;
		int n=-1, m=3, z=-1;
		mapaAuxRec[fil][col]=tiempo;
		  for(int i=0; i<16; i++){ 

				if(i==0){
					n=3;
					mapaResultado[fil][col]=sensores.terreno[0];
				}
				else{ 

					switch (brujula) {
						case 0:
							mapaResultado[fil-x][col+y]=sensores.terreno[i];
							if(sensores.superficie[i]=='r'){
								rey.fila=fil-x;
								rey.columna=col+y;
								rey_visto=true;
							}
						break;

						case 1:
							mapaResultado[fil+y][col+x]=sensores.terreno[i];
							if(sensores.superficie[i]=='r'){
								rey.fila=fil+y;
								rey.columna=col+x;
								rey_visto=true;
							}
						break;

						case 2:
							mapaResultado[fil+x][col-y]=sensores.terreno[i];
							if(sensores.superficie[i]=='r'){
								rey.fila=fil+x;
								rey.columna=col-y;
								rey_visto=true;
							}
						break;

						case 3:
							mapaResultado[fil-y][col-x]=sensores.terreno[i];
							if(sensores.superficie[i]=='r'){
								rey.fila=fil-y;
								rey.columna=col-x;
								rey_visto=true;
							}
						break;

			 		 }

					y++;

					if(i==n){
						m+=2;
						n=n+m;
						x++;
						y=--z;
					}
				}					

		}


	}

	if(!bien_situado){
	int x=1,y=-1;
	int n=-1, m=3, z=-1;
		
		  for(int i=0; i<16; i++){ 

				if(i==0){
					n=3;
					mapaAux[fil][col]=sensores.terreno[0];
				}
				else{ 

					switch (brujula) {
						case 0:
							mapaAux[fil-x][col+y]=sensores.terreno[i];
						break;

						case 1:
							mapaAux[fil+y][col+x]=sensores.terreno[i];
						break;

						case 2:
							mapaAux[fil+x][col-y]=sensores.terreno[i];
						break;

						case 3:
							mapaAux[fil-y][col-x]=sensores.terreno[i];
						break;

			 		 }

					y++;

					if(i==n){
						m+=2;
						n=n+m;
						x++;
						y=--z;
					}
				}					

		}
	}
	

	if (sensores.terreno[0]=='K' && !bien_situado){
		for(int i=0; i<200; i++){
			for(int j=0; j<200; j++){
				if(mapaAux[i][j]!='?')
					mapaResultado[i-(fil-sensores.mensajeF)][j-(col-sensores.mensajeC)]=mapaAux[i][j];
				if(mapaRecorrido[i][j]!=0 || mapaRecorrido[i][j]!=9999999){
					mapaAuxRec[i-(posx-sensores.mensajeF)][j-(posy-sensores.mensajeC)]=mapaRecorrido[i][j];
//					mapaRecorrido[i][j]+=mapaAuxRec[i][j];
				}
			}
		}
		fil = sensores.mensajeF;
		col = sensores.mensajeC;
//		posx = sensores.mensajeF;
//		posy = sensores.mensajeC;
		bien_situado = true;
		PK_visto=false;
		PK=pos=0;
	}

	if (bien_situado and !regalo and !estoy_ejecutando_plan and sensores.regalos.size()>0){
		estado origen;
		origen.fila = fil;
		origen.columna = col;
		origen.orientacion = brujula;

		estado destino;
		destino.fila = sensores.regalos[0].first;
		destino.columna = sensores.regalos[0].second;

		estoy_ejecutando_plan = TrazarPlan(origen, destino, plan);
	}

	if (rey_visto and regalo and !estoy_ejecutando_plan){
		estado origen;
		origen.fila = fil;
		origen.columna = col;
		origen.orientacion = brujula;

		estado destino;
		destino.fila = rey.fila;
		destino.columna = rey.columna;

		estoy_ejecutando_plan = TrazarPlan(origen, destino, plan);
	}

	if((sensores.superficie[1]=='0' && hueso==false) || (sensores.superficie[1]=='1' && biquini==false) || (sensores.superficie[1]=='2' && zapatillas==false) || (sensores.superficie[1]=='3' && llave==false) || (sensores.superficie[1]=='4' && regalo==false)){
		hay_objeto=1;
	}

	else if((sensores.superficie[3]=='0' && hueso==false) || (sensores.superficie[3]=='1' && biquini==false) || (sensores.superficie[3]=='2' && zapatillas==false) || (sensores.superficie[3]=='3' && llave==false) || (sensores.superficie[3]=='4' && regalo==false)){
		hay_objeto=3;
	}

	if(sensores.terreno[1]=='D' && llave==true && sensores.superficie[1]=='d'){
		hay_puerta=1;
	}

	else if(sensores.terreno[3]=='D' && llave==true && sensores.superficie[3]=='d'){
		hay_puerta=3;
	}

	if(!bien_situado)
		if(!PK_visto)
			for(int i=1; i<=15; i++){
				if(sensores.terreno[i]=='K'){
					PK_visto=true;
					PK=i;
				}
			}


//	mapaRecorrido[posx][posy]=tiempo;



	cout << "Terreno: ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];
	cout << endl;

	cout << "Superficie: ";
	for (int i=0; i<sensores.superficie.size(); i++)
		cout << sensores.superficie[i];
	cout << endl;

	cout << "Colisión: " << sensores.colision << endl;
	cout << "Mochila: " << sensores.mochila << endl;
	cout << "Reset: " << sensores.reset << endl;
	cout << "Vida: " << sensores.vida << endl;
	cout << "objetoActivo: " << sensores.objetoActivo << endl;
	cout << endl;

	random_device random;
	mt19937 generator(random());
	uniform_int_distribution <int> distribution(0,1);


	if(cantidad==4 && ultimaAccion==actPUSH){
		accion=actTHROW;
		cantidad--;
		if(sensores.objetoActivo == '0')
			hueso=false;
		else if(sensores.objetoActivo == '1')
			biquini=false;
		else if(sensores.objetoActivo == '2')
			zapatillas=false;
		else if(sensores.objetoActivo == '3')
			llave=false;
		else if(sensores.objetoActivo == '4')
			regalo=false;
	}

	else if(sensores.terreno[2]=='D' && sensores.objetoActivo == '3' && sensores.superficie[2]=='d'){
	 	accion=actGIVE;
	}

	else if(sensores.superficie[2]=='r' && sensores.objetoActivo=='4'){
		accion=actGIVE;
		regalo=false;
	}
	
	else if(sensores.superficie[2]=='l' && sensores.objetoActivo=='0'){
		accion=actGIVE;
		hueso=false;
	}

	else if((sensores.superficie[2]=='0' || sensores.superficie[2]=='1' || sensores.superficie[2]=='2' || sensores.superficie[2]=='3' || sensores.superficie[2]=='4') && sensores.objetoActivo == '_'){
		accion=actPICKUP;
		cantidad++;
	}	
	
	else if(sensores.mochila != '_' && sensores.objetoActivo == '_')
		accion=actPOP;

	else if(((sensores.superficie[2]=='0' && hueso==false) || (sensores.superficie[2]=='1' && biquini==false) || (sensores.superficie[2]=='2' && zapatillas==false) || (sensores.superficie[2]=='3' && llave==false) || (sensores.superficie[2]=='4' && regalo==false)) && sensores.objetoActivo != '_' && sensores.terreno[0]!='B' && sensores.terreno[0]!='A'){
		accion=actPUSH;
	}

	else if(sensores.superficie[2]=='l' && hueso==true && sensores.objetoActivo!='0' && sensores.terreno[0]!='B' && sensores.terreno[0]!='A'){
		accion=actPUSH;
	}
	else if(sensores.terreno[2]=='A' && biquini==true && sensores.objetoActivo!='1' && sensores.terreno[0]!='B' && sensores.terreno[0]!='A')
		accion=actPUSH;

	else if(sensores.terreno[2]=='B' && zapatillas==true && sensores.objetoActivo!='2' && sensores.terreno[0]!='B' && sensores.terreno[0]!='A')
		accion=actPUSH;

	else if(sensores.terreno[2]=='D' && sensores.superficie[2]=='d' && llave==true && sensores.objetoActivo!='3')
		accion=actPUSH;

	else if(sensores.superficie[2]=='r' && regalo==true && sensores.objetoActivo!='4' && sensores.terreno[0]!='B' && sensores.terreno[0]!='A')
		accion=actPUSH;

	else if (estoy_ejecutando_plan and !error_plan){
		accion = plan.front();
		cout << "MIERDA";
		plan.erase(plan.begin());
		PintaPlan(plan);
		if (plan.size()==0){
			estoy_ejecutando_plan = false;
		}
	}

	else if(ultimaAccion==actFORWARD && (hay_puerta==1 || hay_puerta==3)){
		if(hay_puerta==1){
			accion=actTURN_L;
			hay_puerta=0;
		}
		else if(hay_puerta==3){
			accion=actTURN_R;
			hay_puerta=0;
		}
	}

	else if(ultimaAccion==actFORWARD && PK>0 && PK<16 && pos==0){
		if(PK==1||PK==4||PK==5||PK==9||PK==10||PK==11){
			accion=actTURN_L;
			pos=1;
		}
		else if(PK==3||PK==7||PK==8||PK==13||PK==14||PK==15){
			accion=actTURN_R;
			pos=3;
		}
		PK=0;
	}

	else if(PK_visto && pos!=0 && ultimaAccion==actFORWARD){
		if(pos==1)
			accion=actTURN_R;
		else
			accion=actTURN_L;
		pos=0;
		PK_visto=false;
	}

	else if(PK_visto && sensores.terreno[2]!='M' && sensores.terreno[2]!='A' && sensores.terreno[2]!='B' && sensores.superficie[2]=='_'){
		accion=actFORWARD;
	}

	else if(ultimaAccion==actFORWARD && (hay_objeto==1 || hay_objeto==3)){
		if(hay_objeto==1){
			accion=actTURN_L;
			hay_objeto=0;
		}
		else if(hay_objeto==3){
			accion=actTURN_R;
			hay_objeto=0;
		}
	}


	else if(sensores.superficie[2]=='l' || sensores.superficie[2]=='a'){

	  switch (distribution(random)) {
	    case 0:
	      accion=actTURN_L;
	    break;

	    case 1:
	      accion=actTURN_R;
	    break;
	  }
	}
	
	else{
		if(sensores.terreno[2]=='A' && sensores.objetoActivo == '1' || sensores.terreno[2]=='B' && sensores.objetoActivo == '2') //Si comento este if con su respectivo else y lo siguiente (*), haría pulgarcito dentro del bosque y el agua, pero me salen peores resultados.
			accion=actFORWARD;
		
		else{
			
			switch (brujula){
			case 0: // Norte
								for(int i=1,k=-1; i<=3; i++,k++){
					if(sensores.terreno[i]=='P' || sensores.terreno[i]=='M' ||  (sensores.terreno[i]=='A' && sensores.objetoActivo != '1') || (sensores.terreno[i]=='B' && sensores.objetoActivo != '2'))
					mapaRecorrido[posx-1][posy+k]=9999999;
						
					else if((sensores.superficie[2]=='d' && llave==false)  || (sensores.superficie[2]=='r' && regalo==false)  || (sensores.superficie[2]=='0' || sensores.superficie[2]=='1' || sensores.superficie[2]=='2' || sensores.superficie[2]=='3' || sensores.superficie[2]=='4'))
					mapaRecorrido[posx-1][posy]=9999999;
				}

				if(mapaRecorrido[posx-1][posy]==0)
						accion=actFORWARD;
				else if(mapaRecorrido[posx][posy-1]==0)
						accion=actTURN_L;
				else if(mapaRecorrido[posx][posy+1]==0)
						accion=actTURN_R;
				else {
					if(mapaRecorrido[posx-1][posy]<mapaRecorrido[posx][posy-1] && sensores.terreno[2]!='A' && sensores.terreno[2]!='B')//(*) Junto con los sensores de terreno.
							accion=actFORWARD; 
					else if(mapaRecorrido[posx][posy-1]<mapaRecorrido[posx][posy+1])
							accion=actTURN_L;
					else
							accion=actTURN_R;
				}

				
			break;
			case 1: // Este
								for(int i=1,k=-1; i<=3; i++,k++){
					if(sensores.terreno[i]=='P' || sensores.terreno[i]=='M' ||  (sensores.terreno[i]=='A' && sensores.objetoActivo != '1') || (sensores.terreno[i]=='B' && sensores.objetoActivo != '2'))
					mapaRecorrido[posx+k][posy+1]=9999999;
						
					else if((sensores.superficie[2]=='d' && llave==false)  || (sensores.superficie[2]=='r' && regalo==false)  || (sensores.superficie[2]=='0' || sensores.superficie[2]=='1' || sensores.superficie[2]=='2' || sensores.superficie[2]=='3' || sensores.superficie[2]=='4'))
					mapaRecorrido[posx][posy+1]=9999999;
				}

				if(mapaRecorrido[posx][posy+1]==0)
						accion=actFORWARD;
				else if(mapaRecorrido[posx-1][posy]==0)
						accion=actTURN_L;
				else if(mapaRecorrido[posx+1][posy]==0)
						accion=actTURN_R;
				else{
					if(mapaRecorrido[posx][posy+1]<mapaRecorrido[posx-1][posy] && sensores.terreno[2]!='A' && sensores.terreno[2]!='B')
						accion=actFORWARD; 
					else if(mapaRecorrido[posx-1][posy]<mapaRecorrido[posx+1][posy])
						accion=actTURN_L;
					else
						accion=actTURN_R;
				}

			break;
			case 2: // Sur
				for(int i=1,k=-1; i<=3; i++,k++){
					if(sensores.terreno[i]=='P' || sensores.terreno[i]=='M' ||  (sensores.terreno[i]=='A' && sensores.objetoActivo != '1') || (sensores.terreno[i]=='B' && sensores.objetoActivo != '2'))
					mapaRecorrido[posx+1][posy-k]=9999999;
						
					else if((sensores.superficie[2]=='d' && llave==false)  || (sensores.superficie[2]=='r' && regalo==false)  || (sensores.superficie[2]=='0' || sensores.superficie[2]=='1' || sensores.superficie[2]=='2' || sensores.superficie[2]=='3' || sensores.superficie[2]=='4'))
					mapaRecorrido[posx+1][posy]=9999999;
				}
			
				if(mapaRecorrido[posx+1][posy]==0)
						accion=actFORWARD;
				else if(mapaRecorrido[posx][posy+1]==0)
						accion=actTURN_L;
				else if(mapaRecorrido[posx][posy-1]==0)
						accion=actTURN_R;
				else{
					if(mapaRecorrido[posx+1][posy]<mapaRecorrido[posx][posy+1] && sensores.terreno[2]!='A' && sensores.terreno[2]!='B')
						accion=actFORWARD; 
					else if(mapaRecorrido[posx][posy+1]<mapaRecorrido[posx][posy-1])
						accion=actTURN_L;
					else
						accion=actTURN_R;
				}

			break;
			case 3: // Oeste
				for(int i=1,k=-1; i<=3; i++,k++){
					if(sensores.terreno[i]=='P' || sensores.terreno[i]=='M' ||  (sensores.terreno[i]=='A' && sensores.objetoActivo != '1') || (sensores.terreno[i]=='B' && sensores.objetoActivo != '2'))
					mapaRecorrido[posx-k][posy-1]=9999999;
						
					else if((sensores.superficie[2]=='d' && llave==false)  || (sensores.superficie[2]=='r' && regalo==false)  || (sensores.superficie[2]=='0' || sensores.superficie[2]=='1' || sensores.superficie[2]=='2' || sensores.superficie[2]=='3' || sensores.superficie[2]=='4'))
					mapaRecorrido[posx][posy-1]=9999999;
				}

				if(mapaRecorrido[posx][posy-1]==0)
						accion=actFORWARD;
				else if(mapaRecorrido[posx+1][posy]==0)
						accion=actTURN_L;
				else if(mapaRecorrido[posx-1][posy]==0)
						accion=actTURN_R;
				else{
					if(mapaRecorrido[posx][posy-1]<mapaRecorrido[posx+1][posy] && sensores.terreno[2]!='A' && sensores.terreno[2]!='B')
						accion=actFORWARD; 
					else if(mapaRecorrido[posx+1][posy]<mapaRecorrido[posx-1][posy])
						accion=actTURN_L;
					else
						accion=actTURN_R;
				}

			break;
			}
		}
	}

	

	ultimaAccion = accion;

	return accion;

}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
