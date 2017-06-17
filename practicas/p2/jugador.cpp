#include "../Comportamientos_Jugador/jugador.hpp"
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<queue>
#include<limits>
#include<set>
#include<list>
#include<unordered_map>

int imin = std::numeric_limits<int>::min(); // minimum value
int imax = std::numeric_limits<int>::max();

using namespace std;

int ComportamientoJugador::Distancia(Estado origen, Estado destino){
    return (abs(origen.fila-destino.fila)+abs(origen.columna-destino.columna));
}

int ComportamientoJugador::NuevosVisibles(char dir){
    int fill = fil, coll = col ;
    int ret = 0 ;
    int bru;

    int contador = 1 ;
    int a,b,c,d,f; // a y b fila o columna e suma o resta filas.
    a = 0 ;        // c y d suma/resta columnas.
    b = 1 ;
    c = 1 ;
    f = 1 ;
    if(brujula%2 == 0){
        a = 1 ;
        b = 0 ;
    }
    if(brujula%3 == 0)
        c = -1 ;
    if(brujula>1)
        f = -1 ;
    switch(dir){
    case'a':
        fill+=a*c;
        coll+=b*c;
        break;
    case'i':
        bru = (brujula+3)%4;
        break;
    case'd':
        bru = (brujula+1)%4;
        break;
    }

    a = 0 ;        // c y d suma/resta columnas.
    b = 1 ;
    c = 1 ;
    f = 1 ;
    if(bru%2 == 0){
        a = 1 ;
        b = 0 ;
    }
    if(bru%3 == 0)
        c = -1 ;
    if(bru>1)
        f = -1 ;

        for(int i = 1 ; i <= 3 ; i++){
            for(int j = 0-(f*i) ; j != 0+(f*i)+f ; j+= f){
                int fi = fill+ c*i*a + j*b ;
                int co = coll+ j*a + c*i*b ;
                if(situado){
                    if(mapaResultado[fi][co] == '?')
                        ret++;
                }
                else{
                    if(mapaAUX[fi][co] == '?')
                        ret++;
                }
                contador++ ;
            }
        }

        return ret ;
}


/////////////////////////////////////////////////////////////////////////////


vector<ComportamientoJugador::Estado> ComportamientoJugador::Vecinos(Estado id){

    vector<ComportamientoJugador::Estado> vecinos ;
    int x,y,d;
    ComportamientoJugador::Estado vecino ;
    x = id.columna ; y = id.fila ; d = id.orientacion ;
    // Girar a la izquierda
    vecino.fila = y ; vecino.columna = x ; vecino.orientacion = (d+3)%4 ;
    vecinos.push_back(vecino) ;
    // Girar a la derecha
    vecino.orientacion = (d+1)%4 ;
    vecinos.push_back(vecino) ;
    // Avanzar ;
    pair<int,int> newpos = Posicion(1,'f',id) ;
    vecino.columna = newpos.second ;
    vecino.fila = newpos.first ;
    vecino.orientacion = d ;
    vecinos.push_back(vecino);

    return vecinos ;
}

// búsqueda en anchura.
bool ComportamientoJugador::breadth_first_search(Estado inicio, Estado objetivo)
{
    //Borro la lista
    plan.clear();

    queue<Estado> frontera ;
    frontera.push(inicio);

    //cout << "\nBúsqueda: " << objetivo ;

    unordered_map<Estado, list<Action>, estadoHash> subplan ;

    list<Action> sp ;

    subplan[inicio] = sp;

    Estado actual ;

    int iteraciones = 0 ;

    while(!frontera.empty() and iteraciones < 1000){
        actual = frontera.front() ;
        frontera.pop() ;

        if(actual == objetivo){ // No se tiene en cuenta la orientación.
            break;
        }


        vector<Estado> v = Vecinos(actual) ;
        // girar a la izquierda
        Estado next = v[0];

        if(!subplan.count(next)){
            frontera.push(next) ;
            subplan[next] = subplan[actual] ;
            subplan[next].push_back(actTURN_L) ;
        }
        // girar a la derecha ;
        next = v[1] ;

        if(!subplan.count(next)){
            frontera.push(next) ;
            subplan[next] = subplan[actual] ;
            subplan[next].push_back(actTURN_R) ;
        }

        // avanzar
        next = v[2] ;

        if(!subplan.count(next)){
            if(PuedoPisar(actual,next) and next.fila > 2 and next.columna > 2){
                frontera.push(next) ;
                subplan[next] = subplan[actual] ;
                subplan[next].push_back(actFORWARD) ;
            }
        }

        iteraciones++;

    }

    if(actual == objetivo){
        plan = subplan[actual] ;
        return true ;
    }else{
        return false ;
    }
}

double ComportamientoJugador::heuristica(Estado a, Estado b){
    int x1,y1,x2,y2 ;
    x1 = a.columna ; x2 = b.columna ;
    y1 = a.fila ; y2 = a.fila ;

    int c1 = abs(x2-x1), c2 = abs(y2-y1) ;
    int ret = c1+c2 ;
    return(ret) ;
}

template<typename T, typename prioridad_t>
struct ColaPrioridad{
    typedef pair<prioridad_t, T> Elemento;
    priority_queue<Elemento, vector<Elemento>, std::greater<Elemento>> elementos ;

    inline bool empty() const { return elementos.empty() ;}

    inline void put(T elemento, prioridad_t prioridad){
        elementos.emplace(prioridad, elemento) ;
    }

    inline T get(){
        T mejor_elemento = elementos.top().second ;
        elementos.pop();
        return mejor_elemento ;
    }
};


bool ComportamientoJugador::A_estrella_search(Estado inicio, Estado objetivo)
{
    //Borro la lista
    plan.clear();

    objetivo.orientacion = 0 ;

    //cout << "\nBuscar: " << objetivo ;

    ColaPrioridad<Estado, double> frontera ;
    frontera.put(inicio,0);

    unordered_map<Estado, list<Action>, estadoHash> subplan ;
    unordered_map<Estado, int, estadoHash> menor_coste ;

    list<Action> sp ;

    subplan[inicio] = sp;
    menor_coste[inicio] = 0;

    Estado actual ;

    int iteraciones = 0 ;

    while(!frontera.empty() ){

        ColaPrioridad<Estado, double> frontera_aux = frontera ;

        /*
        cout << "\nFrontera: \n" ;

        while(!frontera_aux.empty()){
            cout << frontera_aux.get();
        }

        cout << "\n---------------" ;
        */
        iteraciones++;

        actual = frontera.get() ;

        if(actual == objetivo){ // No se tiene en cuenta la orientación.
            break;
        }


        //cout << "\nActual : " << actual ;
         /*        char c ;
        cin >> c ;
         */
        vector<Estado> v = Vecinos(actual) ;

        double nuevo_coste = menor_coste[actual]+1;


        // girar a la izquierda
        Estado next = v[0];

        if(!subplan.count(next) or
           nuevo_coste < menor_coste[next]){
            double prioridad = nuevo_coste + heuristica(next,objetivo);
            frontera.put(next,prioridad) ;
            subplan[next] = subplan[actual] ;
            subplan[next].push_back(actTURN_L) ;
            menor_coste[next] = nuevo_coste ;
        }
        // girar a la derecha ;
        next = v[1] ;

        if(!subplan.count(next) or
           nuevo_coste < menor_coste[next]){
            double prioridad = nuevo_coste + heuristica(next,objetivo);
            frontera.put(next,prioridad) ;
            subplan[next] = subplan[actual] ;
            subplan[next].push_back(actTURN_R) ;
            menor_coste[next] = nuevo_coste ;
        }
        // avanzar
        next = v[2] ;

        char tn = mapaResultado[next.fila][next.columna] ;
        char ta = mapaResultado[actual.fila][actual.columna];

        if(tn == 'A' or tn == 'B' and tn != ta)
            nuevo_coste +=6 ;

        if(!(Distancia(objetivo, actual) == 1 and (ta == 'A' or ta == 'B')))
            if(!subplan.count(next) or
               nuevo_coste < menor_coste[next]){
                if(PuedoPisar(actual,next) and next.fila > 2 and next.columna > 2){
                    double prioridad = nuevo_coste + heuristica(next,objetivo);
                    frontera.put(next,prioridad) ;
                    subplan[next] = subplan[actual] ;
                    subplan[next].push_back(actFORWARD) ;
                    menor_coste[next] = nuevo_coste ;
                }
            }



    }

    if(actual == objetivo){
        //subplan[actual].pop_back();
        plan = subplan[actual] ;
        return true ;
    }else{
        return false ;
    }
}


bool ComportamientoJugador::SuperarObstaculo(){
    // devuelve true si ha habido error o false si no.
    // susceptible de mejorar!
    //cout << "\nSuperar Obstaculo." ;
    bool tengo = lotengo[supd-'0'];
    switch(supd){
    case '0':
            if(estoy_ejecutando_plan)
                plan.push_front(actTURN_L);
            else
                accion = actTURN_R;
            return true;
    case '1':
    case '2':
    case '3':
    case '4':
        if(encimade == 'A' or encimade == 'B'){
            if(!estoy_ejecutando_plan)
                Giro();
            return true;
        }else{
            if(tengo){
                if(estoy_ejecutando_plan)
                    plan.push_front(actTURN_L);
                else
                    accion = actTURN_R;
                return true;
        }else if(miobj == '_'){
            if(estoy_ejecutando_plan)
                plan.push_front(actPICKUP);
            else
                accion = actPICKUP ;
            return false;
        }else{
            if(estoy_ejecutando_plan)
                plan.push_front(actPUSH);
            else
                accion = actPUSH ;
            return false ;
        }
        }
        break;

    case 'a':
        if(estoy_ejecutando_plan)
            plan.push_front(actTURN_R);
        else
            accion = actTURN_R ;
        return true;
        break;
    case 'r':
        //cout << "\nAMOH A VEL" ;
        if(lotengo[4]){
            if(encimade == 'A' or encimade == 'B'){
                //cout << "\nEncimade bosque o agua" ;
                if(estoy_ejecutando_plan){
                    plan.push_front(actTURN_R);
                    return true ;
                }
                else{
                    Giro();
                }
            }
            else if(miobj == '4'){
                if(estoy_ejecutando_plan){
                    plan.push_front(actGIVE) ;
                }
                else
                    accion = actGIVE ;
                return false;
            }else if(miobj == '_'){
                if(estoy_ejecutando_plan)
                    plan.push_front(actPOP);
                else
                    accion = actPOP;
                return false;
            }else{
                if(estoy_ejecutando_plan){
                    plan.push_front(actPUSH);
                }else{
                    accion = actPUSH ;
                }
                return false;
            }
        }else{
            if(estoy_ejecutando_plan)
                plan.push_front(actTURN_R);
            else
                Giro();
            return true ;
        }
        break;
    case 'l':
        if(miobj=='0'){
            if(estoy_ejecutando_plan){
                plan.push_front(actGIVE);
            }
            else{
                accion = actGIVE ;
            }
            return false;
        }else{
            if(estoy_ejecutando_plan){
                plan.push_front(actTURN_R);
                return true;
            }
            else
                Giro();
            return false;
        }
        break;
    }
    switch(delante){
    case 'A':
        if(encimade != 'B'){
            if(lotengo[1]){
                if(miobj != '1'){
                    if(miobj != '_'){
                        if(estoy_ejecutando_plan)
                            plan.push_front(actPUSH);
                        else
                            accion = actPUSH;
                        return false;
                    }else{
                        if(estoy_ejecutando_plan)
                            plan.push_front(actPOP) ;
                        else
                            accion = actPOP;
                        return false;
                    }
                }
            }else{
                return true;
            }
        }else{return true ;}
        break ;
    case 'B':
        if(encimade != 'A'){
            if(lotengo[2]){
                if(miobj != '2'){
                    if(miobj != '_'){
                        if(estoy_ejecutando_plan)
                            plan.push_front(actPUSH);
                        else
                            accion = actPUSH;
                        return false;
                    }else{
                        if(estoy_ejecutando_plan)
                            plan.push_front(actPOP) ;
                        else
                            accion = actPOP;
                        return false;
                    }
                }
            }else{return true ;}
        }else{return true;}
        break ;
    case 'D':
        if(puerta_abierta == 0){
            if(encimade != 'A' and encimade != 'B'){
                if(lotengo[3]){
                    if(miobj != '3'){
                        if(miobj != '_'){
                            if(estoy_ejecutando_plan)
                                plan.push_front(actPUSH);
                            else
                                accion = actPUSH;
                            return false;
                        }else{
                            if(estoy_ejecutando_plan)
                                plan.push_front(actPOP) ;
                            else
                                accion = actPOP;
                            return false;
                        }
                    }else{
                        if(estoy_ejecutando_plan)
                            plan.push_front(actGIVE);
                        else
                            accion = actGIVE ;
                        puerta_abierta = 3 ;
                        return false;
                    }
                }return true;
            }else{
                return true;
            }
        }
        break ;
    case 'P':
        return true ;
        break ;
    case 'M':
        return true ;
        break;
    }
    return false ;
}

bool ComportamientoJugador::PuedoPisar(Estado actual, Estado objetivo){
    char ac, oc;
    if(situado){
        ac = mapaResultado[actual.fila][actual.columna];
        oc = mapaResultado[objetivo.fila][objetivo.columna];
    }else{
        ac = mapaAUX[actual.fila][actual.columna];
        oc = mapaAUX[objetivo.fila][objetivo.columna];
    }

    return PuedoPisar(ac,oc) ;
}

bool ComportamientoJugador::PuedoPisar(Estado id){
    char c ;
    if(situado){
        c = mapaResultado[id.fila][id.columna] ;
    }else{
        c = mapaAUX[id.fila][id.columna] ;
    }

    return PuedoPisar(c) ;
}

bool ComportamientoJugador::PuedoPisar(char c){
    return PuedoPisar(encimade, c) ;
}

bool ComportamientoJugador::PuedoPisar(char actual, char c){
    bool ret = true ;
    switch(c){
    case 'B':
        if(!lotengo[2] or actual == 'A')
            ret = false ;
        if(encimade == 'A')
            ret = false ;
        break;
    case 'A':
        if(!lotengo[1] or actual == 'B')
            ret = false ;
        if(encimade == 'B')
            ret = false ;
        break ;
    case 'D':
        if(!lotengo[3])
            ret = false ;
        else return true;
        break ;
    case 'P':
    case 'M':
    case '?':
        ret = false ;
        break ;
    }
    return ret ;
}

bool ComportamientoJugador::MejorGiroIzquierda(){
    bool ret = false;
    char tiz, tde ;
    pair <int,int> pizq, pder;
    pizq = Posicion(1,'l');
    pder = Posicion(1,'r');
    char obji ;
    char objd ;
    if(situado){
        tiz = mapaResultado[pizq.first][pizq.second];
        tde = mapaResultado[pder.first][pder.second];
        obji = superficie[pizq.first][pizq.second];
        objd = superficie[pder.first][pder.second];
    }else{
        tiz = mapaAUX[pizq.first][pizq.second];
        tde = mapaAUX[pder.first][pder.second];
        obji = superficieAUX[pizq.first][pizq.second];
        objd = superficieAUX[pder.first][pder.second];
    }

    if(!PuedoPisar(tiz))
        izquierda = imax;
    if(!PuedoPisar(tde))
        derecha = imax;
    if(obji != '_')
        izquierda = imax ;
    if(objd != '_')
        derecha = imax ;
    izquierda -= NuevosVisibles('i');
    derecha -= NuevosVisibles('d');
    if(izquierda <= derecha)
        ret = true;

    return ret ;
}


void ComportamientoJugador::Pulgarcito(){
    //cout << "\nPulgarcito" ;
    if(MejorGiroIzquierda()){
        if(izquierda < avanza)
            accion = actTURN_L;
        if(izquierda == avanza)
            if(NuevosVisibles('i' <= NuevosVisibles('a')))
                accion = actTURN_L;
    }else{
            if(derecha < avanza)
                accion = actTURN_R;
            if(derecha == avanza)
                if(NuevosVisibles('d') <= NuevosVisibles('a'))
                    accion = actTURN_R;
    }

    // cout << "\nA:" <<  avanza << "\tI:" << izquierda <<"\tD:" << derecha<< flush;

}


void ComportamientoJugador::Giro(){
    if(MejorGiroIzquierda()){
        accion = actTURN_L;
    }else{
        accion = actTURN_R;

    }
}



 pair<int,int> ComportamientoJugador::Posicion(int pasos, char direccion){
     Estado origen;
     origen.fila = fil;
     origen.columna = col;
     origen.orientacion = brujula;
     Posicion(pasos, direccion, origen );
 }

 pair<int,int> ComportamientoJugador::Posicion(int pasos, char direccion,
                                               Estado pos){
     int fil = pos.fila ;
     int col = pos.columna ;
     int brujula = pos.orientacion ;
    pair<int,int> ret ;
    int f2,c2;
    f2 = c2 = 0 ;
    switch(brujula){
    case(0):
        f2 = -1 ;
        break ;
    case(1):
        c2 = 1 ;
        break ;
    case(2):
        f2 = 1 ;
        break ;
    case(3):
        c2 = -1 ;
        break ;
    }

    switch(direccion){
    case('f'): //front
        ret = make_pair(fil+f2*pasos,col+c2*pasos) ;
        break;
    case('b'): //back
        ret = make_pair(fil-f2*pasos,col-c2*pasos) ;
        break;
    case('r'): //right
        ret = make_pair(fil+c2*pasos,col-f2*pasos) ;
        break;
    case('l'): //left
        ret = make_pair(fil-c2*pasos,col+f2*pasos) ;
        break;

    }
    return ret ;
}

void ComportamientoJugador::situar(Sensores sensores){
    int filaux = fil ;
    int colaux = col ;
    fil = sensores.mensajeF;
    col = sensores.mensajeC;

    int despf = filaux - fil;
    int despc = colaux - col;


    situado = true ;

    for(int i = 0 ; i < 100 ; i++)
        for(int j = 0 ; j < 100 ; j++){
            if(mapaAUX[i+despf][j+despc] != '?')
                mapaResultado[i][j] = mapaAUX[i+despf][j+despc];
            if(memoriaAUX[i+despf][j+despc] != 0){
                memoria[i][j] = memoriaAUX[i+despf][j+despc];
                superficie[i][j] = superficieAUX[i+despf][j+despc];
            }
        }
    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 100 ; j++){
            mapaResultado[i][j] = 'P' ;
            mapaResultado[j][i] = 'P' ;
            mapaResultado[99-i][j] = 'P' ;
            mapaResultado[j][99-i] = 'P' ;
        }
    }
}
void ComportamientoJugador::Cartografiar(Sensores sensores){
    if(situado) mapaResultado[fil][col] = encimade ;
    else mapaAUX[fil][col] = encimade ;

    // ESCRIBO LO QUE VEO EN EL MAPA RESULTADO.
    int contador = 1 ;
    int a,b,c,d,f; // a y b fila o columna e suma o resta filas.
    a = 0 ;        // c y d suma/resta columnas.
    b = 1 ;
    c = 1 ;
    f = 1 ;
    if(brujula%2 == 0){
        a = 1 ;
        b = 0 ;
    }
    if(brujula%3 == 0)
        c = -1 ;
    if(brujula>1)
        f = -1 ;
    for(int i = 1 ; i <= 3 ; i++){
        for(int j = 0-(f*i) ; j != 0+(f*i)+f ; j+= f){
            int fi = fil+ c*i*a + j*b ;
            int co = col+ j*a + c*i*b ;
            if(situado){
                mapaResultado[fi][co] = sensores.terreno[contador] ;
                if(sensores.superficie[contador] == 'r'){
                    Estado newobjetivo ;
                    newobjetivo.orientacion = 0 ;
                    newobjetivo.fila = fi ;
                    newobjetivo.columna = co;
                    objetivos.insert(newobjetivo);
                }
                superficie[fi][co] = sensores.superficie[contador] ;
            }
            else{
                mapaAUX[fi][co] = sensores.terreno[contador] ;
                superficieAUX[fi][co] = sensores.superficie[contador] ;
            }
            contador++ ;
        }
    }

}



void ComportamientoJugador::Reiniciar(){
    //char stop ;
    //cout << "\nATENCIÓN! PARADA POR MUERTE. REANUDAR INTRODUCIENDO UN CARACTER" ;
    //cin >> stop ;

    fil = col = 99;
    ultimaAccion = actIDLE;
    situado = false;
    brujula = 0;
    estoy_ejecutando_plan =false;
    error_plan =false;
    nobjetos = 0;
    for(int i = 0 ; i < 200 ; i++){
        for(int j = 0 ; j < 200 ; j++){
            memoriaAUX[i][j] = 0 ;
            mapaAUX[i][j] = '?' ;
        }
    }
    for(int i = 0 ; i < 5 ; i++)
        lotengo[i] = false ;

}

bool ComportamientoJugador::hayObstaculoDelante
(const vector<unsigned char> & terreno,
 const vector<unsigned char> & superficie){
    if ( (terreno[2]=='T' or terreno[2]=='S' or terreno[2]=='K')){
        if(superficie[2] == '_')
            return false;
        switch(superficie[2]){
        case '0': case '1': case '2': case'3':case'4':
        case'r':
        case'l':
        case'a':
            return true ;
        }
    }
    else{
        return true;
    }
    return true ;
}

void PintaPlan(list<Action> plan){
    //cout << "\n" ;
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

    accion = actFORWARD;
    tiempo++ ;
    //cout << "\n -- " << tiempo << "--- \n" ;

    miobj = sensores.objetoActivo ;
    encimade = sensores.terreno[0] ;
    supd = sensores.superficie[2] ;
    delante = sensores.terreno[2] ;

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
        break;
    case actTURN_R:
        brujula = (brujula+1)%4;
        break;
    case actPICKUP:
        if (miobj != '_'){
            lotengo[miobj-'0'] = true ;
            nobjetos = 0 ;
            for(int i = 0 ; i < 5 ; i++)
                if(lotengo[i]) nobjetos++;
        }
        break;
    case actGIVE:
        if (sensores.objetoActivo != '_'){
            lotengo[miobj-'0']=true;
            nobjetos = 0 ;
            for(int i = 0 ; i < 5 ; i++)
                if(lotengo[i]) nobjetos++;
        }
        break;
    case actTHROW:
        if(sensores.objetoActivo != '_'){
            lotengo[miobj -'0'] = true ;
            nobjetos = 0 ;
            for(int i = 0 ; i < 5 ; i++)
                if(lotengo[i]) nobjetos++;
        }
        break ;
    case actPUTDOWN:
        if(sensores.objetoActivo != '_'){
            lotengo[miobj - '0'] = true ;
            nobjetos = 0 ;
            for(int i = 0 ; i < 5; i++)
                if(lotengo[i]) nobjetos++;
        }
        break;
    }

    if(error_plan){
        error_plan = false ;
        estoy_ejecutando_plan = false ;
    }

    // ESCRIBO EN EL MAPA LO QUE VEO.
    Cartografiar(sensores);


    if (sensores.terreno[0]=='K' and !situado){
        situar(sensores);
        situado = true;
    }


    // planificación.
    if (paseo == 0 and situado and !estoy_ejecutando_plan){
        Estado origen;
        origen.fila = fil;
        origen.columna = col;
        origen.orientacion = brujula;
        Estado destino;
        ColaPrioridad<Estado, int> destinos ;

        if(!lotengo[4] and sensores.regalos.size()>0){
            //cout << "\n~~~ Buscando regalo ~~~" ;
            int i = 0;
            while(i < sensores.regalos.size()){
                destino.fila = sensores.regalos[i].first;
                destino.columna = sensores.regalos[i].second;
                destinos.put(destino, Distancia(origen,destino));
                i++;
            }

            while(!destinos.empty() and !estoy_ejecutando_plan){
                destino = destinos.get();
                estoy_ejecutando_plan = A_estrella_search(origen, destino) ;
            }
        }

        if(lotengo[4] and objetivos.size() > 0){
            //cout << "\n~~~ Buscando rey ~~~" ;
            set<Estado>::iterator it = objetivos.begin() ;
            while(it != objetivos.end()){
                Estado destino = *it ;
                destinos.put(destino,Distancia(origen,destino));
                ++it;
            }

            while(!destinos.empty() and !estoy_ejecutando_plan){
                destino = destinos.get();
                estoy_ejecutando_plan = A_estrella_search(origen, destino) ;
            }
        }
        if(!estoy_ejecutando_plan)
            paseo += 15 ;
        else
            accion = actIDLE ;

    }


    // MONITORIZAR PLAN
    if(estoy_ejecutando_plan){
        //cout << "\nMONITORIZO" ;

        //cout << "\nMonitorizando plan." ;
        //arreglar plan:
        if(!error_plan and plan.front() == actFORWARD)
           error_plan = SuperarObstaculo();

        if(!error_plan and sensores.superficie[2] == 'a' or sensores.superficie[2] == 'l'
           or sensores.superficie[6] == 'a'
           or sensores.superficie[6] == 'l'){
            //cout << "\nHAY ARGÚN BICHO DELANTE" ;
            plan.push_front(actTURN_R) ;
            error_plan = true;
        }

        // Decidir la nueva acción de movimiento
        if (!error_plan){
            accion = plan.front();
            plan.erase(plan.begin());
            //PintaPlan(plan);
        }else{
            //cout << "\nError!!" ;
            paseo += 20 ;
        }

    }else{ // movimiento si no hay plan y la accion es avanzar
    if(!estoy_ejecutando_plan and accion == actFORWARD){
        //cout << "\nOIGA" ;
        pair<int,int> front, right, left;
        front = Posicion(1,'f');
        right = Posicion(1,'r');
        left = Posicion(1,'l') ;
        accion = actFORWARD;

        //cout << "\n NO.PLAN" ;

        if(situado){
            avanza = memoria[front.first][front.second];
            izquierda = memoria[left.first][left.second];
            derecha = memoria[right.first][right.second];
        }else{
            avanza = memoriaAUX[front.first][front.second];
            izquierda = memoriaAUX[left.first][left.second];
            derecha = memoriaAUX[right.first][right.second];
        }

        bool error ;

        switch(supd){
        case'0':
        case'1':
        case'2':
        case'3':
        case'4':
            SuperarObstaculo();
            break;
        default:
            Pulgarcito();
            if(accion == actFORWARD)
                if(SuperarObstaculo())
                    Giro() ;
            break;
        }
    }

    }


    if(situado) memoria[fil][col] = tiempo;
    else memoriaAUX[fil][col] = tiempo;

    // Recordar la ultima accion y ultimo objeto
    ultimaAccion = accion;
    if(puerta_abierta > 0)
        puerta_abierta-- ;

    if(plan.size() == 1){
        paseo = 10 ;
    }

    if(paseo > 0){
        paseo-- ;
        //cout << "\nPASEO";
    }

    if(accion == actPUTDOWN or accion == actTHROW or accion == actGIVE){
        lotengo[miobj-'0'] = false ;
        nobjetos--;
    }
    //cout << "\nmiobj: " << miobj << flush ;



    switch(accion){
    case actGIVE:
        //cout << "\nDAR";
        break ;
    case actTHROW:
        //cout << "\nLANZAR";
        break;
    case actPUTDOWN:
        //cout << "\nSoltar" ;
        break ;
    }

    //cout << flush ;

    if (plan.size()==0){
        estoy_ejecutando_plan = false;
    }

    return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
    return false;
}
