\# Práctica 2D - Unity



\## Descripción



En esta practica se realizo todo lo solicitado en las indicaciones del pdf trabajando con un proyecto 2D del tipo Universal.

Se configuro el spritesheet mediante el Sprite editor, se creo el personaje principal como prefab y se agregaron los componente de Sprite Renderer, Box Collider 2D y Rigidbody 2D, confugrando Gravity Scale = 0, esto debido a que nosotros configuraremos la gravedad en practicas posteriores. Se creo el script de Jugador.cs para detectar las coliciones, mostrando en la consola el nombre del objeto con el que produce la colision. Se creo también el script para detectar el movimiento horizontal y vertical mediante Update(), mostrando los inputs detectados en consola. La detección de las colisiones está implementada en el script y utiliza Debug.Log() para imprimir en la consola el objeto con el que se realiza la colisión, aunque durante la prueba no se llegó a verificar visualmente dicho mensaje en la consola.



\## Ejecución



Para ejecutar la practica se debe presionar el botón Play en la parte superior de Unity.

Mientras esta ejecutando la practica se deben presionar las teclas A, D o la barra espaciadora, para moverse a la izquierda, derecha o saltar.

Estos inputs se muestran en la consola mediante mensajes del script ControlJugador.cs

La detección de colisiones también está implementada en Jugador.cs y utiliza la consola para mostrar el nombre del objeto con el que se produce la colisión.



\### Fin :)

