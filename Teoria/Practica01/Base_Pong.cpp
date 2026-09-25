//Base_Pong.cpp : A bouncing ball 

//#include <windows.h> //the windows include file, required by all windows applications
#include <GL/glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls
#include <math.h>
#include <iostream>

#define PI 3.1415926535898  

double xpos, ypos, ydir, xdir;         // x and y position for house to be drawn
double sx, sy, squash;                 // xy scale factors
double rot, rdir;                      // rotation
double ball_speed;

double posicion_paleta1, posicion_paleta2;
double velocidad_paletas;

int puntos_p1 = 0;
int puntos_p2 = 0;

GLfloat T1[16] = {1.,0.,0.,0.,\
                  0.,1.,0.,0.,\
                  0.,0.,1.,0.,\
                  0.,0.,0.,1.};

GLfloat S[16] = {1.,0.,0.,0.,\
                 0.,1.,0.,0.,\
                 0.,0.,1.,0.,\
                 0.,0.,0.,1.};

GLfloat T[16] = {1.,0.,0.,0.,\
                 0., 1., 0.,0.,\
                 0.,0.,1.,0.,\
                 0.,0.,0.,1.};

GLint circle_points = 100; 

void MyCircle2f(GLfloat centerx, GLfloat centery, GLfloat radius)
{
  GLint i;
  GLdouble angle;

  glBegin(GL_POLYGON); 

  for (i = 0; i < circle_points; i++) {    
    angle = 2 * PI * i / circle_points; 
    glVertex2f(centerx + radius * cos(angle),
               centery + radius * sin(angle)); 
  } 

  glEnd();
}

GLfloat RadiusOfBall = 15.;

void draw_ball()
{
  glColor3f(0.6, 0.3, 0.);
  MyCircle2f(0., 0., RadiusOfBall);
}


// Dibujar las dos paletas
void dibujar_paletas()
{
  glBegin(GL_QUADS);

  // Paleta p1
  glColor3f(1.0, 0.6, 0.0);

  glVertex2f(10., posicion_paleta1 - 20.);
  glVertex2f(15., posicion_paleta1 - 20.);
  glVertex2f(15., posicion_paleta1 + 20.);
  glVertex2f(10., posicion_paleta1 + 20.);

  // Paleta p2
  glColor3f(1.0, 0.0, 0.0);

  glVertex2f(145., posicion_paleta2 - 20.);
  glVertex2f(150., posicion_paleta2 - 20.);
  glVertex2f(150., posicion_paleta2 + 20.);
  glVertex2f(145., posicion_paleta2 + 20.);

  glEnd();
}


// Reiniciar la pelota después de un punto
void reiniciar_pelota()
{
  xpos = 80.;
  ypos = 60.;

  xdir = -xdir;
  ydir = 1;
}


void Display(void)
{
  glutSwapBuffers(); 
  glClear(GL_COLOR_BUFFER_BIT);


  // Movimiento horizontal de la pelota
  xpos += xdir * ball_speed;


  // Movimiento vertical de la pelota
  if (ypos >= 120 - RadiusOfBall) {
    ydir = -1;
  }
  else if (ypos <= RadiusOfBall) {
    ydir = 1;
  }

  ypos += ydir * ball_speed;


  // Punto p2
  if (xpos < 0) {

    puntos_p2++;

    std::cout << "P1: " << puntos_p1
              << " - " << puntos_p2
              << " :P2" << std::endl;

    reiniciar_pelota();
  }


  // Punto p1
  if (xpos > 160) {

    puntos_p1++;

    std::cout << "P1: " << puntos_p1
              << " - " << puntos_p2
              << " :P2" << std::endl;

    reiniciar_pelota();
  }


  // Colisión con la paleta izquierda
  if (xdir < 0 &&
      xpos - RadiusOfBall <= 15. &&
      xpos + RadiusOfBall >= 10. &&
      ypos + RadiusOfBall >= posicion_paleta1 - 20. &&
      ypos - RadiusOfBall <= posicion_paleta1 + 20.) {

    xdir = 1;
    xpos = 15. + RadiusOfBall;
  }


  // Colisión con la paleta derecha
  if (xdir > 0 &&
      xpos + RadiusOfBall >= 145. &&
      xpos - RadiusOfBall <= 150. &&
      ypos + RadiusOfBall >= posicion_paleta2 - 20. &&
      ypos - RadiusOfBall <= posicion_paleta2 + 20.) {

    xdir = -1;
    xpos = 145. - RadiusOfBall;
  }


  // Transformación de la pelota
  T[12] = xpos;
  T[13] = ypos;

  glLoadMatrixf(T);

  T1[13] = -RadiusOfBall;
  glMultMatrixf(T1);

  S[0] = sx;
  S[5] = sy;

  glMultMatrixf(S);

  T1[13] = RadiusOfBall;
  glMultMatrixf(T1);

  draw_ball();


  // Reiniciar la transformación para dibujar las paletas
  glLoadIdentity();

  // Dibujar las paletas
  dibujar_paletas();


  glutPostRedisplay(); 
}

void teclado(unsigned char key, int x, int y)
{
  // Paleta izquierda
  if (key == 'w' || key == 'W')
    posicion_paleta1 += velocidad_paletas;

  if (key == 's' || key == 'S')
    posicion_paleta1 -= velocidad_paletas;


  // Paleta derecha
  if (key == '8')
    posicion_paleta2 += velocidad_paletas;

  if (key == '5')
    posicion_paleta2 -= velocidad_paletas;


  // Limitar la paleta izquierda a la pantalla
  if (posicion_paleta1 > 100.)
    posicion_paleta1 = 100.;

  if (posicion_paleta1 < 20.)
    posicion_paleta1 = 20.;


  // Limitar la paleta derecha a la pantalla
  if (posicion_paleta2 > 100.)
    posicion_paleta2 = 100.;

  if (posicion_paleta2 < 20.)
    posicion_paleta2 = 20.;
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(0.0, 160.0, 0.0, 120.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


void init(void)
{
  // Fondo azul oscuro
  glClearColor(0.02, 0.03, 0.10, 1.0);


  // Posición inicial de la pelota
  xpos = 80;
  ypos = RadiusOfBall;

  xdir = 1;
  ydir = 1;


  // Configuración original de la pelota
  sx = 1.;
  sy = 1.;
  squash = 0.9;

  rot = 0;

  ball_speed = 1.5;


  // Posición inicial de las paletas
  posicion_paleta1 = 60.;
  posicion_paleta2 = 60.;

  velocidad_paletas = 2.;
}


int main(int argc, char* argv[])
{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  glutInitWindowSize(320, 240);

  glutCreateWindow("Bouncing Ball");

  init();

  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(teclado);

  glutMainLoop();

  return 1;
}
