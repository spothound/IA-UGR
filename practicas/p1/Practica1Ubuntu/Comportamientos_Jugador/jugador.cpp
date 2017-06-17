#include "../Comportamientos_Jugador/jugador.hpp"
#include<iostream>
#include<utility>
#include<time.h>


void ComportamientoJugador::NoPisar(){
    if(situado){
        memoria[fil+f2][col+c2] = tiempo+10;
    }else{
        memoriaAUX[fil+f2][col+c2] = tiempo+10;
    }
}

void ComportamientoJugador::Giro(){
    if(rand()%2==0)
        accion = actTURN_R;
    else
        accion = actTURN_L;
    char ti ;
    char td ;
    if(situado){
        ti = mapaResultado[fil-c2][col+f2] ;
        td = mapaResultado[fil+c2][col-f2] ;
    }

    if(!situado){
        ti = mapaAUX[fil-c2][col+f2] ;
        td = mapaAUX[fil+c2][col-f2] ;
    }

    if(ti != '?' and PuedoPisar(ti) and izquierda < derecha){
        accion = actTURN_L;
        cout << "\nGiro izquierda porque no puedo pisar"<<flush;
    }
    if(td != '?' and PuedoPisar(td) and derecha < izquierda){
        accion = actTURN_R;
        cout << "\nGiro derecha porque no puedo pisar" << flush ;
    }
}
bool ComportamientoJugador::PuedoPisar(char c){
    bool ret = true ;
    switch(c){
    case 'B':
        if(!lotengo[2])
            ret = false ;
        if(encimade == 'A')
            ret = false;
        break;
    case 'A':
        if(!lotengo[1])
            ret = false ;
        if(encimade == 'B')
            ret = false ;
        break;
    case 'D':
        if(!lotengo[3])
            ret = false ;
        break;
    case 'P':
    case 'M':
    case '?':
        ret = false ;
        break ;
    }
    return ret ;

}
void ComportamientoJugador::Reinicio(){
    situado = false ;
    nobjetos = 0;
    abierta = 0;
    fil = col = 99;
    for(int i = 0 ; i < 200 ; i++)
        for(int j = 0 ; j < 200 ; j++){
            memoriaAUX[i][j] = 0;
            mapaAUX[i][j] = '?' ;
        }
    for(int i = 0 ; i < 4 ; i++){
        lotengo[i] = false ;
    }

    brujula = 0 ;
    ultimaAccion = actIDLE;
}



Action ComportamientoJugador::think(Sensores sensores){

    if(sensores.reset) Reinicio();

    switch(ultimaAccion){
    case actFORWARD:
        if(!sensores.colision){
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
        }
        break ;
    case actTURN_L:
        brujula = (brujula+3)%4 ;
        break ;
    case actTURN_R:
        brujula = (brujula+1)%4 ;
        break ;
    }

    if(sensores.terreno[0] == 'K' and !situado){
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
                if(memoriaAUX[i+despf][j+despc] != 0)
                    memoria[i][j] = memoriaAUX[i+despf][j+despc];
            }
    }

    encimade = sensores.terreno[0] ;



    if(situado) mapaResultado[fil][col] = encimade;
    else mapaAUX[fil][col] = encimade;

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
            if(situado)
                mapaResultado[fi][co] = sensores.terreno[contador] ;
            else
                mapaAUX[fi][co] = sensores.terreno[contador] ;
            contador++ ;
        }
    }

    ////////////////////////////////////////////

    // ¿memoria a los lados y delante?


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

    if(situado){
        delante = memoria[fil+f2][col+c2];
        izquierda = memoria[fil-c2][col+f2];
        derecha = memoria[fil+c2][col-f2];
    }else{
        delante = memoriaAUX[fil+f2][col+c2];
        izquierda = memoriaAUX[fil-c2][col+f2];
        derecha = memoriaAUX[fil+c2][col-f2];
    }

    ////////////////////////////////////////////////

    accion = actFORWARD ;
    tiempo++;

    // 23
    if(tiempo % 23 == 0)
        Giro();

    if(situado) memoria[fil][col] = tiempo;
    else memoriaAUX[fil][col] = tiempo;


    char frente = sensores.terreno[2];
    char sup = sensores.superficie[2];
    char miobj = sensores.objetoActivo;
    bool tengo ;

    for(int i = 1 ; i <= 15 ; i++){
        if(sensores.superficie[2] == 'l'){
            if(lotengo[0] && miobj != '0' && encimade != 'A' && encimade != 'B')
                if(miobj != '_')
                    accion = actPUSH;
                else
                    accion = actPOP;
            else
                Giro();
        }
    }

    switch(sup){
    case '0':
    case '1':
    case '2':
    case '3':
        tengo = lotengo[sup-'0'];
        if(tengo){
            NoPisar();
            //si no lo tengo:
        }else if(miobj == '_'){ // y no tengo nada en las manos
            accion = actPICKUP; // cojo el objeto
            nobjetos++;
            cout << "\nCojo un objeto" << flush;
            lotengo[sup-'0'] = true;
        } else{
            if(encimade == 'A' or encimade == 'B'){
                cout << "\nNo cojo porque necesito mi objeto" << flush;
                NoPisar();
                accion = actTURN_R;
            }else{
                accion = actPUSH;
                cout << "\nGuardo objeto en la mochila" << flush ;
            }
            break;
            case 'a':
                Giro();
                break ;
                case 'l':
                    if(miobj == '0'){
                        accion = actGIVE;
                        lotengo[0] = false ;
                        nobjetos--;
                    }else{
                        NoPisar();
                    }
                    break;
        }
    }

    if(accion == actFORWARD){
        bool especial = false ;
        char objeto;

        if(PuedoPisar(frente)){
            switch(frente){
            case 'B':
                objeto = '2';
                especial = true;
                break;
            case 'A':
                objeto = '1';
                especial = true;
                break;
            case 'D':
                objeto = '3';
                especial = true;
                break ;
            }

            if(especial){
                if(miobj != objeto){
                    if(miobj != '_'){
                        if(!(encimade == 'A')
                           and !(encimade == 'B')){
                            accion = actPUSH;
                            cout << "\nGuardo objeto en mochila" << flush ;
                        }else{Giro() ; }
                    }else{
                        accion = actPOP;
                        cout << "\nCojo objeto de la mochila" << flush;
                    }
                }
            }
        }else{ // No puedo pisar, giro
            cout << "\nNo puedo pisar" << flush;
            Giro() ;

        }

        if(abierta == 0 and lotengo[3]
           and((situado and mapaResultado[fil+c2][col-f2]=='D')or
               !situado and mapaAUX[fil+c2][col-f2]=='D')){
            accion = actTURN_R;
            cout << "\nGiro a la derecha para abrir una puerta" << flush;
        }
        if(abierta == 0 and lotengo[3]
           and ((situado and mapaResultado[fil-c2][col+f2]=='D')or
                !situado and mapaAUX[fil-c2][col+f2]=='D')){
            accion = actTURN_L;
            cout << "\nGiro a la izquierda para abrir una puerta" << flush;
        }

        char tiz, tde;

        if(situado){
            tiz = mapaResultado[fil-c2][col+f2];
            tde = mapaResultado[fil+c2][col-f2];
        }else{
            tiz = mapaAUX[fil-c2][col+f2];
            tde = mapaAUX[fil+c2][col-f2];
        }

        bool izqok = false ;
        if(accion == actFORWARD){
            if(izquierda < delante and tiz != '?' and PuedoPisar(tiz)){
                izqok = true;
                accion = actTURN_L;
                cout << "\ngiro a la izquierda porque he pisado por ahi\n"
                     << flush;
            }else{
                if(izquierda >= derecha)
                    cout << "\nNo giro a la izquierda porque la derecha es mejor." << flush;
                if(tiz == '?')
                    cout << "\nNo giro a la izquierda porque ???? " << flush ;
                if(!PuedoPisar(tiz))
                    cout << "\nNo giro a la izquierda porque no puedo pisar" << flush ;
            }
            if(derecha < delante and tde != '?' and PuedoPisar(tde)){
                if(!izqok || derecha < izquierda){
                accion = actTURN_R;
                cout << "\ngiro a la derecha porque he pisado por ahi "
                     << flush;
                }
            }else{
                if(derecha >= izquierda)
                    cout << "\nNo giro a la derecha porque la izquierda es mejor." << flush;
                if(tde == '?')
                    cout << "\nNo giro a la derecha porque ???? " << flush ;
                if(!PuedoPisar(tde))
                    cout << "\nNo giro a la derecha porque no puedo pisar" << flush ;
            }
        }
    }
    if(frente == 'D' and miobj == '3' and abierta == 0){
        accion = actGIVE;
        cout << "\nAbro la puerta" << flush;
        abierta = 5 ;
    }
    if(abierta > 0 )
        abierta--;

    /*
      if(situado){
      cout << "\n\n\t\n" << flush ;
      for(int i = 0 ; i < 30 ; i++){
      for(int j = 0 ; j < 30 ; j++)
      printf("[%04d]",memoria[i][j]);
      cout << flush ;
      cout << endl << flush;
      }
      }*/

    if(!situado){
        if(sensores.terreno[2] == 'K')
            accion = actFORWARD;
        else if(PuedoPisar(sensores.terreno[2])){
            if(sensores.terreno[6] == 'K')
                accion = actFORWARD;
            else{
                if(PuedoPisar(sensores.terreno[6])){
                    if(sensores.terreno[12] == 'K')
                        accion = actFORWARD;
                }
            }
        }
        char casilla ;
        int l = 1 ;
        bool seguir = true ;
        while(l < 5 and seguir){
            casilla = mapaAUX[fil-c2*l][col+f2*l];
            if(casilla == '?' or !PuedoPisar(casilla))
                seguir = false ;
            if(casilla == 'K')
                accion = actTURN_L;
            l++;
        }
        while(l < 5 and seguir){
            casilla = mapaAUX[fil+c2*l][col-f2*l];
            if(casilla == '?' or !PuedoPisar(casilla))
                seguir = false ;
            if(casilla == 'K')
                accion = actTURN_R;
            l++;
        }
    }
    ultimaAccion = accion;

    return accion ;
}
int ComportamientoJugador::interact(Action accion, int valor){
    return false;
}
