#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glx.h>
#include <GL/glext.h>

#include <iostream>
#include <vector>
#include <string>
#include "../include/winData.h"





void displayHander() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
  glVertex3f(-0.5,-0.5,0.0);
  glVertex3f(0.5,0.0,0.0);
  glVertex3f(0.0,0.5,0.0);
  glEnd();

  glutSwapBuffers();
}
void keyboardHandler(unsigned char key, int x, int y) {
  switch(key) {
  case 'q':
    exit(0);
    break;
  default:
    break;
  }
}

int main(int argc, char *argv[]) {
  WinData w;
  ObjHandler("teapot");
  glutInit(&argc, argv);
  glutInitWindowPosition(w[0], w[1]);
  glutInitWindowSize(w[2], w[3]);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE|
		      GLUT_MULTISAMPLE|GLUT_ACCUM);
  glutCreateWindow(w.getTitle().c_str());
  glutDisplayFunc(displayHander);
  glutKeyboardFunc(keyboardHandler);
  glutMainLoop();

  return 0;
}
