//Base_Pong.cpp : A bouncing ball 

//#include <windows.h> //the windows include file, required by all windows applications
#include <GL/glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls
#include <math.h>

#define PI 3.1415926535898 

double xpos, ypos, ydir, xdir;
double sx, sy, squash;
double rot, rdir;
double ball_speed;

double posicion_paleta1, posicion_paleta2;
double velocidad_paletas;

GLfloat T1[16] = {1.,0.,0.,0.,\
                  0.,1.,0.,0.,\
                  0.,0.,1.,0.,\
                  0.,0.,0.,1.};

GLfloat S[16] = {1.,0.,0.,0.,\
                 0.,1.,0.,0.,\
                 0.,0.,1.,0.,\
                 0.,0.,0.,1.};

GLfloat T[16] = {1.,0.,0.,0.,\
                 0., 1., 0., 0.,\
                 0.,0.,1.,0.,\
                 0.,0.,0.,1.};

GLint circle_points = 100; 

void MyCircle2f(GLfloat centerx, GLfloat centery, GLfloat radius){
  GLint i;
  GLdouble angle;

  glBegin(GL_POLYGON); 

  for (i = 0; i < circle_points; i++) {    
    angle = 2*PI*i/circle_points; 
    glVertex2f(centerx+radius*cos(angle), centery+radius*sin(angle)); 
  } 

  glEnd();
}

GLfloat RadiusOfBall = 15.;

// Draw the ball, centered at the origin
void draw_ball() {
  glColor3f(0.6,0.3,0.);
  MyCircle2f(0.,0.,RadiusOfBall);
}

// Dibujar las dos paletas
void dibujar_paletas() {

  glBegin(GL_QUADS);

  // Paleta izquierda - amarillo/naranja
  glColor3f(1.0, 0.6, 0.0);

  glVertex2f(10., posicion_paleta1 - 20.);
  glVertex2f(15., posicion_paleta1 - 20.);
  glVertex2f(15., posicion_paleta1 + 20.);
  glVertex2f(10., posicion_paleta1 + 20.);

  // Paleta derecha - rojo
  glColor3f(1.0, 0.0, 0.0);

  glVertex2f(145., posicion_paleta2 - 20.);
  glVertex2f(150., posicion_paleta2 - 20.);
  glVertex2f(150., posicion_paleta2 + 20.);
  glVertex2f(145., posicion_paleta2 + 20.);

  glEnd();
}

// Movimiento de las paletas
void teclado(unsigned char key, int x, int y)
{
  // Jugador 1
  if (key == 'w' || key == 'W')
    posicion_paleta1 += velocidad_paletas;

  if (key == 's' || key == 'S')
    posicion_paleta1 -= velocidad_paletas;

  // Jugador 2
  if (key == 'i' || key == 'I')
    posicion_paleta2 += velocidad_paletas;

  if (key == 'k' || key == 'K')
    posicion_paleta2 -= velocidad_paletas;
}

void Display(void)
{
  // swap the buffers
  glutSwapBuffers(); 

  //clear all pixels with the specified clear color
  glClear(GL_COLOR_BUFFER_BIT);

  // Shape has hit the ground! Stop moving and start squashing down and then back up 
  if (ypos == RadiusOfBall && ydir == -1  ) { 
    sy = sy*squash ; 

    if (sy < 0.8)
      // reached maximum suqash, now unsquash back up 
      squash = 1.1;

    else if (sy > 1.) {
      // reset squash parameters and bounce ball back upwards
      sy = 1.;
      squash = 0.9;
      ydir = 1;
    }

    sx = 1./sy;

  } else {

    // Movimiento vertical
    ypos += ydir*ball_speed;

    // Movimiento horizontal
    xpos += xdir*ball_speed;

    // Si toca la parte superior, cambia dirección hacia abajo
    if (ypos >= 120-RadiusOfBall){
      ydir = -1;
    }

    // Si toca la parte inferior, cambia dirección hacia arriba
    else if (ypos <= RadiusOfBall){
      ydir = 1;
    }

    // Colisión con la paleta izquierda
    if (xdir < 0 &&
        xpos - RadiusOfBall <= 15. &&
        xpos + RadiusOfBall >= 10. &&
        ypos >= posicion_paleta1 - 20. &&
        ypos <= posicion_paleta1 + 20.) {

      xdir = 1;
      xpos = 15. + RadiusOfBall;
    }

    // Colisión con la paleta derecha
    if (xdir > 0 &&
        xpos + RadiusOfBall >= 145. &&
        xpos - RadiusOfBall <= 150. &&
        ypos >= posicion_paleta2 - 20. &&
        ypos <= posicion_paleta2 + 20.) {

      xdir = -1;
      xpos = 145. - RadiusOfBall;
    }
  }

  // Translate the bouncing ball to its new position
  T[12]= xpos;
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

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluOrtho2D(0.0, 160.0, 0.0, 120.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
}

void init(void){

  // Fondo azul oscuro
  glClearColor(0.02,0.03,0.10,1.0);

  xpos = 80;
  ypos = RadiusOfBall;

  xdir = 1;
  ydir = 1;

  sx = 1.;
  sy = 1.;
  squash = 0.9;

  rot = 0;
  ball_speed = 1.5;

  // Posición y velocidad de las paletas
  posicion_paleta1 = 60.;
  posicion_paleta2 = 60.;
  velocidad_paletas = 2.;
}

int main(int argc, char* argv[])
{
  glutInit( & argc, argv );
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (320, 240);   
  glutCreateWindow("Bouncing Ball");

  init();

  glutDisplayFunc(Display);
  glutKeyboardFunc(teclado);
  glutReshapeFunc(reshape);

  glutMainLoop();

  return 1;
}
