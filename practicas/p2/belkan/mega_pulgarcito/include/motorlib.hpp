#ifndef MOTORLIB
#define MOTORLIB


#include "motorlib/monitor.hpp"

extern MonitorJuego monitor;

void lanzar_motor_juego();
void lanzar_motor_juego(int acc);
void lanzar_motor_juego2(MonitorJuego &monitor);
void nucleo_motor_juego(MonitorJuego & monitor, int acc);
void lanzar_motor_grafico(int argc, char ** argv);


#endif
