Practica 01 Juego de Pong.

Requisitos: Esta practica fue hecha en ubuntu,con compilador g++, opengl y FreeGLUT.

INSTALACIÓN:

Para instalar FreeGLUT en Ubuntu:

sudo apt install freeglut3-dev

COMPILACIÓN:

Desde la carpeta donde se encuentra Base_Pong.cpp ejecutar:

g++ -o Pong Base_Pong.cpp -lGL -lglut -lGLU

EJECUCIÓN:

./Pong

Controles: Los del jugador 1 son W para ir hacia arriba y S para ir hacia abajo, mientras que para el jugador 2 son el 8 y 5 del numpad, por lo que es necesario activarlo.

La pelota se mueve automáticamente,la pelota rebota contra los límites superior e inferior de la pantalla,las paletas pueden moverse verticalmente,la pelota rebota al tocar una paleta,
cuando la pelota sale por el lado izquierdo, el jugador 2 obtiene un punto,cuando la pelota sale por el lado derecho, el jugador 1 obtiene un punto,después de cada punto, 
la pelota vuelve al centro,el marcador se muestra en la terminal.
