//Nama Program: Stadium Molineux
//Dikerjakan oleh : Jorge Joseph Rorong (672017234)
//                  Kores Bonsapia (672017224)
//Project ini sebagai TR Grafika Komputer

#ifdef __APPLE__
#include <unistd.h>
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define DEGREES_PER_PIXEL	0.6f
#define UNITS_PER_PIXEL		0.1f
#define ZOOM_FACTOR		    0.04f

#define BULB_RADIUS		    0.3f
#define SPOTLIGHT_RADIUS	0.5f
#define ROOM_SIZE			4.0f
#define WALL_THICKNESS		0.05f

void EnableLighting();


typedef struct
{
	bool leftButton;
	bool rightButton;
	int x;
	int y;
} MouseState;

MouseState mouseState = { false, false, 0, 0 };

/* setting angles rotasi */
float xRotate = 0, yRotate = 0;

/* setting pointer untuk quadrics soalnya nanti panggil spheres dan cylinders */
GLUquadricObj* bulbObj;

/* setting posisi kamera dan orientasi -- masih ingat gluLookAt kan? */
GLfloat eye[] = { 0, 0, 10 };
GLfloat at[] = { 0, 0, 0 };

/* posisi light1 -- sejajar sumbu z (akan kita gunakan nanti) */
GLfloat light1_position[] = { 0.0, 0.0, 1.0, 1.0 };

/* Nah ini bentuk ruangannya, kita beri nama "ruangkotak".
 * Ruang kotak ini nanti terdiri dari 3 tembok kemudian di tengah ada bola kecil sebagai pusat. 
 */
void ruangkotak()
{
	
	//bangun atas
	glClear(GL_COLOR_BUFFER_BIT);
  
   glBegin(GL_POLYGON);
  glColor3f(1.0, 0.7, 0.0);    /* tribun utara */
  
  glVertex3f(-3.3, 3.5, 1.3);
  glVertex3f(3.3, 3.5, 1.3);
  glVertex3f(2.5, 2.0, 0.0);
  glVertex3f(1.0, 2.2, 0.0);
  glVertex3f(-1.0, 2.2, 0.0);
  glVertex3f(-2.5, 2.0, 0.0);

    glEnd();
    
   glBegin(GL_POLYGON);
  glColor3f(0.7, 0.7, 0.7);    /* atap */
  
  glVertex3f(-3.3, 3.5, 1.5);
  glVertex3f(3.3, 3.5, 1.5);
  glVertex3f(2.5, 2.0, 1.3);
  glVertex3f(1.0, 2.2, 1.3);
  glVertex3f(-1.0, 2.2, 1.3);
  glVertex3f(-2.5, 2.0, 1.3);

    glEnd();
  
     glBegin(GL_POLYGON); //samping kiri
        glColor3f(1.0, 0.7, 0.4);
       glVertex3f(-3.3, 3.5, 1.5);
         glVertex3f(-2.5, 2.0, 0.0);
  glVertex3f(-3.2, 2.5, 0.0);
  glVertex3f(-3.4, 3.5, 0.0);

  glEnd();
  
  
     glBegin(GL_POLYGON);
  glColor3f(1.0, 0.7, 0.5);    /* wall */
  
  glVertex3f(-3.3, 3.5, 1.5);
  glVertex3f(3.3, 3.5, 1.5);
  glVertex3f(3.4, 3.5, 0.0);
  glVertex3f(1.0, 4.2, 0.0);
  glVertex3f(-1.0, 4.2, 0.0);
  glVertex3f(-3.4, 3.5, 0.0);

    glEnd();
  
       glBegin(GL_POLYGON); //samping kanan
        glColor3f(1.0, 0.7, 0.4);
       glVertex3f(3.3, 3.5, 1.5);
         glVertex3f(2.5, 2.0, 0.0);

  glVertex3f(3.4, 3.5, 0.0);

  glEnd();
  
  
    glBegin(GL_POLYGON); //samping kanan
    glColor3f(1.0, 0.7, 0.4);
    glVertex3f(3.3, 3.5, 1.5);
    glVertex3f(2.5, 2.0, 0.0);

  glVertex3f(3.4, 3.5, 0.0);

  glEnd();
  
  
  //bangunan bawah

  
   glBegin(GL_POLYGON);
  glColor3f(1.0, 0.7, 0.0);    /* tribun selatan */
  glVertex3f(-3.3, -3.5, 1.3);
  glVertex3f(3.3, -3.5, 1.3);
  glVertex3f(2.5, -2.0, 0.0);
  glVertex3f(1.0, -2.2, 0.0);
  glVertex3f(-1.0, -2.2, 0.0);
  glVertex3f(-2.5, -2.0, 0.0);
    glEnd();

   glBegin(GL_POLYGON);
  glColor3f(0.7, 0.7, 0.7);    /* atap */
  glVertex3f(-3.3, -3.5, 1.5);
  glVertex3f(3.3, -3.5, 1.5);
  glVertex3f(2.5, -2.0, 1.3);
  glVertex3f(1.0, -2.2, 1.3);
  glVertex3f(-1.0, -2.2, 1.3);
  glVertex3f(-2.5, -2.0, 1.3);
    glEnd();
  
     glBegin(GL_POLYGON); //samping kiri
        glColor3f(1.0, 0.7, 0.4);
       glVertex3f(-3.3, -3.5, 1.5);
         glVertex3f(-2.5, -2.0, 0.0);
  glVertex3f(-3.2, -2.5, 0.0);
  glVertex3f(-3.4, -3.5, 0.0);
  glEnd();
  
  
     glBegin(GL_POLYGON);
  glColor3f(1.0, 0.7, 0.5);    /* wall */
  glVertex3f(-3.3, -3.5, 1.5);
  glVertex3f(3.3, -3.5, 1.5);
  glVertex3f(3.4, -3.5, 0.0);
  glVertex3f(1.0, -4.2, 0.0);
  glVertex3f(-1.0, -4.2, 0.0);
  glVertex3f(-3.4, -3.5, 0.0);

    glEnd();
  
       glBegin(GL_POLYGON); //samping kanan
        glColor3f(1.0, 0.7, 0.4);
       glVertex3f(3.3, -3.5, 1.5);
         glVertex3f(2.5, -2.0, 0.0);
  glVertex3f(3.4, -3.5, 0.0);
  glEnd();
  
    glBegin(GL_POLYGON); //samping kanan
    glColor3f(1.0, 0.7, 0.4);
    glVertex3f(3.3, -3.5, 1.5);
    glVertex3f(2.5, -2.0, 0.0);
    glVertex3f(3.4, -3.5, 0.0);
  glEnd();
  
  //bangun kanan
  
 glBegin(GL_POLYGON);
  glColor3f(1.0, 0.7, 0.0);    /* tribun */
  
  glVertex3f(4.2, 2.0, 1.3);
  glVertex3f(4.2, -2.0, 1.3);
  glVertex3f(3.0, -2.0, 0.0);
  glVertex3f(3.2, -1.0, 0.0);
  glVertex3f(3.2, 1.0, 0.0);
  glVertex3f(3.0, 2.0, 0.0);
  glEnd(); 
  
  
   glBegin(GL_POLYGON);
  glColor3f(0.7, 0.7, 0.7);    /* atap */
  glVertex3f(4.2, 2.0, 1.5);
  glVertex3f(4.2, -2.0, 1.5);
  glVertex3f(3.0, -2.0, 1.3);
  glVertex3f(3.2, -1.0, 1.3);
  glVertex3f(3.2, 1.0, 1.3);
  glVertex3f(3.0, 2.0, 1.3);
  glEnd(); 
  
  glBegin(GL_POLYGON); //samping kiri
  glColor3f(1.0, 0.7, 0.4);
  glVertex3f(4.2, 2.0, 1.5);
  glVertex3f(3.0, 2.0, 0.0);
  glVertex3f(4.2, 2.0, 0.0);
  glEnd();
  
  glBegin(GL_POLYGON); //samping kanan
  glColor3f(1.0, 0.7, 0.4);
  glVertex3f(4.2, -2.0, 1.5);
  glVertex3f(3.0, -2.0, 0.0);
  glVertex3f(4.2, -2.0, 0.0);
  glEnd();
  
   glBegin(GL_POLYGON);
  glColor3f(1.0, 0.7, 0.5);    /* wall */
  glVertex3f(4.2, 2.0, 1.5);
  glVertex3f(4.2, -2.0, 1.5);
  glVertex3f(4.2, -2.0, 0.0);
  glVertex3f(4.4, -1.0, 0.0);
  glVertex3f(4.4, 1.0, 0.0);
  glVertex3f(4.2, 2.0, 0.0);
  glEnd(); 
  
    //bangun kiri
 glBegin(GL_POLYGON);
  glColor3f(1.0, 0.7, 0.0);    /* tribun */
  glVertex3f(-4.2, 2.0, 1.7);
  glVertex3f(-4.2, -2.0, 1.7);
  glVertex3f(-3.0, -2.0, 0.0);
  glVertex3f(-3.2, -1.0, 0.0);
  glVertex3f(-3.2, 1.0, 0.0);
  glVertex3f(-3.0, 2.0, 0.0);
  glEnd(); 
  
     glBegin(GL_POLYGON);
  glColor3f(0.7, 0.7, 0.7);    /* atap */
  glVertex3f(-4.2, 2.0, 2);
  glVertex3f(-4.2, -2.0, 2);
  glVertex3f(-3.0, -2.0, 1.7);
  glVertex3f(-3.2, -1.0, 1.7);
  glVertex3f(-3.2, 1.0, 1.7);
  glVertex3f(-3.0, 2.0, 1.7);
  glEnd(); 
  
  glBegin(GL_POLYGON); //samping kiri
  glColor3f(1.0, 0.7, 0.4);
  glVertex3f(-4.2, 2.0, 2);
  glVertex3f(-3.0, 2.0, 0.0);
  glVertex3f(-4.2, 2.0, 0.0);
  glEnd();
  
  glBegin(GL_POLYGON); //samping kanan
  glColor3f(1.0, 0.7, 0.4);
  glVertex3f(-4.2, -2.0, 2);
  glVertex3f(-3.0, -2.0, 0.0);
  glVertex3f(-4.2, -2.0, 0.0);
  glEnd();
  
   glBegin(GL_POLYGON);
  glColor3f(1.0, 0.7, 0.5);    /* wall */
  glVertex3f(-4.2, 2.0, 2);
  glVertex3f(-4.2, -2.0, 2);
  glVertex3f(-4.2, -2.0, 0.0);
  glVertex3f(-4.4, -1.0, 0.0);
  glVertex3f(-4.4, 1.0, 0.0);
  glVertex3f(-4.2, 2.0, 0.0);
  glEnd(); 
  
  //Lines
  glBegin(GL_LINES);
  glColor3f(1.0, 1.0, 1.0);
      glLineWidth(100);
  glVertex3f(-3.3, 3.5, 1.5);
  glVertex3f(3.3, 3.5, 1.5);
   glVertex3f(3.3, 3.5, 1.5);
   glVertex3f(2.5, 2.0, 1.3);
  glVertex3f(2.5, 2.0, 1.3);
  glVertex3f(1.0, 2.2, 1.3);
    glVertex3f(1.0, 2.2, 1.3);
   glVertex3f(-1.0, 2.2, 1.3);
  glVertex3f(-1.0, 2.2, 1.3);
  glVertex3f(-2.5, 2.0, 1.3);
    glVertex3f(-3.3, 3.5, 1.5);
    glVertex3f(-2.5, 2.0, 1.3);
    
    
     glVertex3f(-1.2, 3.5, 1.5);
     glVertex3f(-1.0, 2.2, 0.0);
       glVertex3f(1.2, 3.5, 1.5);
     glVertex3f(1.0, 2.2, 0.0);
  
  
  glVertex3f(-3.3, -3.5, 1.5);
  glVertex3f(3.3, -3.5, 1.5);
   glVertex3f(3.3, -3.5, 1.5);
   glVertex3f(2.5, -2.0, 1.3);
  glVertex3f(2.5, -2.0, 1.3);
  glVertex3f(1.0, -2.2, 1.3);
    glVertex3f(1.0, -2.2, 1.3);
   glVertex3f(-1.0, -2.2, 1.3);
  glVertex3f(-1.0, -2.2, 1.3);
  glVertex3f(-2.5, -2.0, 1.3);
    glVertex3f(-3.3, -3.5, 1.5);
    glVertex3f(-2.5, -2.0, 1.3);
  
       glVertex3f(-1.2, -3.5, 1.5);
     glVertex3f(-1.0, -2.2, 0.0);
       glVertex3f(1.2, -3.5, 1.5);
     glVertex3f(1.0, -2.2, 0.0);
  
  
  
    glVertex3f(4.2, 2.0, 1.5);
  glVertex3f(4.2, -2.0, 1.5);
    glVertex3f(4.2, -2.0, 1.5);
  glVertex3f(3.0, -2.0, 1.3);
  glVertex3f(3.0, -2.0, 1.3);
  glVertex3f(3.2, -1.0, 1.3);
    glVertex3f(3.2, -1.0, 1.3);
  glVertex3f(3.2, 1.0, 1.3);
  glVertex3f(3.2, 1.0, 1.3);
  glVertex3f(3.0, 2.0, 1.3);
    glVertex3f(3.0, 2.0, 1.3);
    glVertex3f(4.2, 2.0, 1.5);
  
  
      glVertex3f(3.2, -1.0, 0.0);
            glVertex3f(4.2, -1.0, 1.5);
            
  glVertex3f(3.2, 1.0, 0.0);
    glVertex3f(4.2, 1.0, 1.5);
  
  
  glVertex3f(-4.2, 2.0, 2);
  glVertex3f(-4.2, -2.0, 2);
    glVertex3f(-4.2, -2.0, 2);
  glVertex3f(-3.0, -2.0, 1.7);
  glVertex3f(-3.0, -2.0, 1.7);
  glVertex3f(-3.2, -1.0, 1.7);
    glVertex3f(-3.2, -1.0, 1.7);
  glVertex3f(-3.2, 1.0, 1.7);
  glVertex3f(-3.2, 1.0, 1.7);
  glVertex3f(-3.0, 2.0, 1.7);
    glVertex3f(-3.0, 2.0, 1.7);
    glVertex3f(-4.2, 2.0, 2);
  
  glVertex3f(-3.2, -1.0, 0.0);
  glVertex3f(-4.2, -1.1, 2);
  glVertex3f(-3.2, 1.0, 0.0);
    glVertex3f(-4.2, 1.1, 2);  
    glEnd(); 

  glBegin(GL_QUADS);
  glColor3f(0.2, 0.6, 0.2); //lapangan utama
  glVertex3f(-2.5, -1.5, 0.0);
  glVertex3f(2.5, -1.5, 0.0);
  glVertex3f(2.5, 1.5, 0.0);
  glVertex3f(-2.5, 1.5, 0.0);
 glEnd(); 
 
     glBegin(GL_LINES);
  glColor3f(1.2, 1.6, 1.2);
  glVertex3f(-2.5, -1.5, 0.001); //garis tepi
  glVertex3f(2.5, -1.5, 0.001);
  glVertex3f(2.5, 1.5, 0.001);
  glVertex3f(-2.5, 1.5, 0.001);
  glVertex3f(-2.5, -1.5, 0.001);
  glVertex3f(-2.5, 1.5, 0.001);
  glVertex3f(2.5, -1.5, 0.001);
  glVertex3f(2.5, 1.5, 0.001);
  glVertex3f(0.0, 1.5, 0.001); //garis tengah
  glVertex3f(0.0, -1.5, 0.001);
   glEnd(); 
   
   glBegin(GL_LINE_STRIP);
     glColor3f(1.2, 1.6, 1.2);
  glVertex3f(-2.5, 0.85, 0.001); //garis luar gawang kiri
  glVertex3f(-1.8, 0.85, 0.001);
  glVertex3f(-1.8, -0.85, 0.001);
  glVertex3f(-2.5, -0.85, 0.001);
 glEnd();  
 
    glBegin(GL_LINE_STRIP);
     glColor3f(1.2, 1.6, 1.2);
  glVertex3f(-2.5, 0.4, 0.001); //garis dalam gawang kiri
  glVertex3f(-2.2, 0.4, 0.001);
  glVertex3f(-2.2, -0.4, 0.001);
  glVertex3f(-2.5, -0.4, 0.001);
 glEnd();  
 
    glBegin(GL_LINE_STRIP);
     glColor3f(1.2, 1.6, 1.2);
  glVertex3f(2.5, 0.85, 0.001); //garis gawang kanan
  glVertex3f(1.8, 0.85, 0.001);
  glVertex3f(1.8, -0.85, 0.001);
  glVertex3f(2.5, -0.85, 0.001);
 glEnd();  
     glBegin(GL_LINE_STRIP);
     glColor3f(1.2, 1.6, 1.2);
  glVertex3f(2.5, 0.4, 0.001); //garis dalam gawang kanan
  glVertex3f(2.2, 0.4, 0.001);
  glVertex3f(2.2, -0.4, 0.001);
  glVertex3f(2.5, -0.4, 0.001);
 glEnd();  
 
     glBegin(GL_LINE_STRIP);
     glColor3f(1.2, 1.6, 1.2);
  glVertex3f(2.5, 0.1, 0.0); //tiang gawang kanan
  glVertex3f(2.5, 0.1, 0.1);
  glVertex3f(2.5, -0.1, 0.1);
  glVertex3f(2.5, -0.1, 0.0);
 glEnd();  
 
      glBegin(GL_LINE_STRIP);
     glColor3f(1.2, 1.6, 1.2);
  glVertex3f(-2.5, 0.1, 0.0); //tiang gawang kiri
  glVertex3f(-2.5, 0.1, 0.1);
  glVertex3f(-2.5, -0.1, 0.1);
  glVertex3f(-2.5, -0.1, 0.0);
 glEnd();  
 
   glBegin(GL_POLYGON); // outer sprint lane
  glColor3f(0.7, 0.2, 0.2);
  glVertex3f(-4.0, -2.5, -0.01);
    glVertex3f(-3.5, -3.0, -0.01);
  glVertex3f(3.5, -3.0, -0.001);
    glVertex3f(4.0, -2.5, -0.001);
  glVertex3f(4.0, 2.5, -0.001);
    glVertex3f(3.5, 3.0, -0.001);
  glVertex3f(-3.5, 3.0, -0.001);
    glVertex3f(-4.0, 2.5, -0.001);
 glEnd(); 

   glBegin(GL_POLYGON); //sprint lane
  glColor3f(0.8, 0.2, 0.2);
  glVertex3f(-3.0, -1.5, -0.0001);
    glVertex3f(-2.5, -2.0, -0.0001);
  glVertex3f(2.5, -2.0, -0.0001);
    glVertex3f(3.0, -1.5, -0.0001);
  glVertex3f(3.0, 1.5, -0.0001);
    glVertex3f(2.5, 2.0, -0.0001);
  glVertex3f(-2.5, 2.0, -0.0001);
    glVertex3f(-3.0, 1.5, -0.0001);
 glEnd(); 
 
   glBegin(GL_POLYGON); // all around
  glColor3f(0.5, 0.5, 0.5);
  glVertex3f(-6.0, -4.5, -0.01);
    glVertex3f(-5.5, -5.0, -0.01);
  glVertex3f(5.5, -5.0, -0.01);
    glVertex3f(6.0, -4.5, -0.01);
  glVertex3f(6.0, 4.5, -0.01);
    glVertex3f(5.5, 5.0, -0.01);
  glVertex3f(-5.5, 5.0, -0.01);
    glVertex3f(-6.0, 4.5, -0.01);
  glEnd(); 
  
  
    glBegin(GL_QUADS);
  glColor3f(1.0, 0.7, 0.5); //bench kiri
  glVertex3f(-0.4, 1.7, 0.1);
  glVertex3f(-0.2, 1.7, 0.1);
  glVertex3f(-0.2, 1.7, 0.0);
  glVertex3f(-0.4, 1.7, 0.0);
  
    glVertex3f(-0.4, 1.7, 0.1);
  glVertex3f(-0.4, 1.6, 0.1);
  glVertex3f(-0.4, 1.6, 0.0);
  glVertex3f(-0.4, 1.7, 0.0);
  
      glVertex3f(-0.2, 1.7, 0.1);
  glVertex3f(-0.2, 1.6, 0.1);
  glVertex3f(-0.2, 1.6, 0.0);
  glVertex3f(-0.2, 1.7, 0.0);
  
    glColor3f(0.9, 0.7, 0.5);
   glVertex3f(-0.4, 1.7, 0.1);
  glVertex3f(-0.2, 1.7, 0.1);
  glVertex3f(-0.2, 1.58, 0.1);
  glVertex3f(-0.4, 1.58, 0.1);
  
      glColor3f(1, 1, 1);
   glVertex3f(-0.4, 1.7, 0.02);
  glVertex3f(-0.2, 1.7, 0.02);
  glVertex3f(-0.2, 1.65, 0.02);
  glVertex3f(-0.4, 1.65, 0.02);
  
    glColor3f(1.0, 0.7, 0.5); //bench kanan
  glVertex3f(0.4, 1.7, 0.1);
  glVertex3f(0.2, 1.7, 0.1);
  glVertex3f(0.2, 1.7, 0.0);
  glVertex3f(0.4, 1.7, 0.0);
  
    glVertex3f(0.4, 1.7, 0.1);
  glVertex3f(0.4, 1.6, 0.1);
  glVertex3f(0.4, 1.6, 0.0);
  glVertex3f(0.4, 1.7, 0.0);
  
      glVertex3f(0.2, 1.7, 0.1);
  glVertex3f(0.2, 1.6, 0.1);
  glVertex3f(0.2, 1.6, 0.0);
  glVertex3f(0.2, 1.7, 0.0);
  
    glColor3f(0.9, 0.7, 0.5);
   glVertex3f(0.4, 1.7, 0.1);
  glVertex3f(0.2, 1.7, 0.1);
  glVertex3f(0.2, 1.58, 0.1);
  glVertex3f(0.4, 1.58, 0.1);
  
      glColor3f(1, 1, 1);
   glVertex3f(0.4, 1.7, 0.02);
  glVertex3f(0.2, 1.7, 0.02);
  glVertex3f(0.2, 1.65, 0.02);
  glVertex3f(0.4, 1.65, 0.02);
 glEnd(); 
  
      glBegin(GL_POLYGON);
  glColor3f(0.7, 0.7, 0.7); //scoreboard
  glVertex3f(2.6, 1.7, 0.0);
  glVertex3f(2.7, 1.6, 0.0);
    glVertex3f(2.7, 1.6, 1.2);
  glVertex3f(2.6, 1.7, 1.2);
 glEnd(); 
  
        glBegin(GL_POLYGON);
  glColor3f(1, 1, 1);
  glVertex3f(2.4, 1.9, 0.9);
  glVertex3f(2.9, 1.4, 0.9);
    glVertex3f(2.89, 1.39, 1.2);
  glVertex3f(2.39, 1.89, 1.2);
 glEnd(); 
  
          glBegin(GL_LINE_STRIP);
  glColor3f(0.0, 0.0, 0.0);
  glVertex3f(2.4, 1.9, 0.9);
  glVertex3f(2.9, 1.4, 0.9);
  glVertex3f(2.89, 1.39, 1.2);
  glVertex3f(2.39, 1.89, 1.2);
  glEnd(); 
  
    glBegin(GL_LINE_STRIP); //Logo
    glColor3f(1, 1, 1);
    glVertex3f(0.05, -0.2, 0.001);
    glVertex3f(0.1, 0.0, 0.001);
    glVertex3f(0.30, 0.1, 0.001);
    glVertex3f(0.1, 0.4, 0.001);
    glVertex3f(0.05, 0.3, 0.001);  
    glVertex3f(-0.05, 0.3, 0.001);
    glVertex3f(-0.1, 0.4, 0.001);    
    glVertex3f(-0.30, 0.1, 0.001);
    glVertex3f(-0.1, 0.0, 0.001);
    glVertex3f(-0.05, -0.2, 0.001);
    glVertex3f(0.05, -0.2, 0.001);
 glEnd(); 
  
      glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex3f(0.05, 0.05, 0.001);
    glVertex3f(0.13, 0.05, 0.001);
    glVertex3f(0.13, 0.15, 0.001);
    glVertex3f(0.05, 0.05, 0.001);
 glEnd(); 
  
        glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex3f(-0.05, 0.05, 0.001);
    glVertex3f(-0.13, 0.05, 0.001);
    glVertex3f(-0.13, 0.15, 0.001);
    glVertex3f(-0.05, 0.05, 0.001);
 glEnd(); 
  
  
 
}

void DrawScene()
{
	/* Setting rotasi di sumbu X dan Y */
	glRotatef(xRotate, 0, 1, 0);
	glRotatef(yRotate, 1, 0, 0);

	ruangkotak();
}


void Display(void)
{
	/* Menggambar buffer sebelumnya */
	glDrawBuffer(GL_BACK);

	/* Membersihkan tampilan/layar */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* (Re)posisi atau memposisikan ulang posisi kamera */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], 0, 1, 0);

	DrawScene();

	glFlush();
	glutSwapBuffers();
}

/*
 * Setting supaya tombol kiri kanan atas bawah berfungsi untuk translasi.
 */
void SpecialKey(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		/* Kamera akan geser ke kanan dan gambar geser ke kiri */
		eye[0] = eye[0] + UNITS_PER_PIXEL;
		at[0] = at[0] + UNITS_PER_PIXEL;
		break;
	case GLUT_KEY_RIGHT:
		eye[0] = eye[0] - UNITS_PER_PIXEL;
		at[0] = at[0] - UNITS_PER_PIXEL;
		break;
	case GLUT_KEY_UP:
		eye[1] = eye[1] - UNITS_PER_PIXEL;
		at[1] = at[1] - UNITS_PER_PIXEL;
		break;
	case GLUT_KEY_DOWN:
		eye[1] = eye[1] + UNITS_PER_PIXEL;
		at[1] = at[1] + UNITS_PER_PIXEL;
		break;
	case GLUT_KEY_END:	/* zoom out */
		eye[0] = (1 + ZOOM_FACTOR) * eye[0] - at[0] * ZOOM_FACTOR;
		eye[1] = (1 + ZOOM_FACTOR) * eye[1] - at[1] * ZOOM_FACTOR;
		eye[2] = (1 + ZOOM_FACTOR) * eye[2] - at[2] * ZOOM_FACTOR;
		break;
	case GLUT_KEY_HOME: /* zoom in */
		eye[0] = (1 - ZOOM_FACTOR) * eye[0] + at[0] * ZOOM_FACTOR;
		eye[1] = (1 - ZOOM_FACTOR) * eye[1] + at[1] * ZOOM_FACTOR;
		eye[2] = (1 - ZOOM_FACTOR) * eye[2] + at[2] * ZOOM_FACTOR;
		break;
	}
	glutPostRedisplay();
}

/* 
 * Setting supaya tombol + dan - untuk zoom in dan zoom out serta q untuk keluar
 */
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':	SpecialKey(GLUT_KEY_HOME, 0, 0);
		break;
	case 's':	SpecialKey(GLUT_KEY_END, 0, 0);
		break;
	case 'q':	exit(0);
	}
}

void Mouse(int button, int state, int x, int y)
{
	// update state tombol, jadi kalo di klik kiri mouse baru diaktifkan rotasi
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
			mouseState.leftButton = true;
		else
			mouseState.leftButton = false;
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
			mouseState.rightButton = true;
		else
			mouseState.rightButton = false;
	}

	// update posisi mouse, supaya gampang tracking/atau membaca pergerakan mouse untuk rotasi
	mouseState.x = x;
	mouseState.y = y;
}

void MouseMove(int x, int y)
{
	/* Hitung perpindahan posisi dalam pergerakan */
	int xDelta = mouseState.x - x;
	int yDelta = mouseState.y - y;

	/* Posisi mouse */
	mouseState.x = x;
	mouseState.y = y;

	/* Kalo tombol kiri mouse diklik, lakukan rotasi jika mouse digerakan */
	if (mouseState.leftButton) {
		xRotate -= xDelta * DEGREES_PER_PIXEL;
		yRotate -= yDelta * DEGREES_PER_PIXEL;
	}
	
	/* Kalo tombol kanan mouse diklik, lakukan translasi jika mouse digerakan */
	else if (mouseState.rightButton) {
		eye[0] += xDelta * UNITS_PER_PIXEL;
		eye[1] -= yDelta * UNITS_PER_PIXEL;
		at[0] += xDelta * UNITS_PER_PIXEL;
		at[1] -= yDelta * UNITS_PER_PIXEL;
	}
	glutPostRedisplay();
}

void myInit()
{
	/* setting warna menjadi hitam saat membersihkan window */
	glClearColor(0.0, 0.0, 0.0, 1.0);

	/* Setting warna menjadi merah (apabila tidak ada efek pencahayaan yang digunakan) */
	glColor3f(1.0, 0.0, 0.0);

	/* Panggil dan aktifkan quadrics */
	bulbObj = gluNewQuadric();
	gluQuadricDrawStyle(bulbObj, GLU_FILL);

	/* Setting proyeksi perspective */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0f, 1.0f, 0.1f, 40.0f);

	/* Setting posisi kamera */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], 0, 1, 0);

	/* Aktifkan hidden--surface--removal */
	glEnable(GL_DEPTH_TEST);

}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("TR -672017234, 672017224");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	myInit();
	glutMainLoop();
}
