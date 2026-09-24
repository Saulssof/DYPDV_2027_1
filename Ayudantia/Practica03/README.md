Practica03.
En esta práctica se implementó un sistema de movimiento manual para el personaje utilizando aceleración, velocidad y cálculo manual de
deltatime, se agrego la desaceleracion automatica cuando no hay input, cambio de dirección mediante aceleración, límite de velocidad, gravedad diferenciada para mejorar la caída, coyote time y jump buffering para mejorar el salto

La comunicación entre Jugador.cs y ControlJugador.cs se mantiene mediante GetComponent<Jugador>(). El script Jugador.cs se encarga de detectar las colisiones con el suelo y mantener actualizado el estado enSuelo, evitando que el personaje continúe cayendo mientras permanece sobre el piso.

El personaje se mueve con A,D y salta con ESPACIO.
