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
#include "../include/objectHandler.h"
#include "../include/shaderHandler.h"

void createViewVolume() {
  glEnable(GL_DEPTH_TEST);
  //set projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30, 1.0, 0.1, 20.0);
  //set view volume
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 3.5, 6.0,  // eye
	    0.0, 0.5, 0,  // view
	    0.0, 1.0, 0.0); // up
}

void createLights() {
  // Fill light
  float light0_ambient[] = { 0.4, 0.0, 0.4, 0.1 };
  float light0_diffuse[] = { 0.5, 0.3, 0.8, 1.0 };
  float light0_specular[] = { 1.0, 0.4, 1.3, 1.0 };
  float light0_position[] = { 0.25, 0.3, 0.1, 1.0 };
  float light0_direction[] = { -0.2, -0.3, 0.0, 1.0};

  // Turn off scene default ambient.
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light0_ambient);

  // Make specular correct for spots.
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,1);

  glLightfv(GL_LIGHT0,GL_AMBIENT,light0_ambient);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);
  glLightfv(GL_LIGHT0,GL_SPECULAR,light0_specular);
  glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,1.0);
  glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,180.0);
  glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,0.5);
  glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,0.1);
  glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,0.01);
  glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
  glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,light0_direction);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}
int createMaterials() {
  float mat_ambient[] = {1.0,1.0,1.0,1.0};
  float mat_diffuse[] = {0.9,0.9,0.9,1.0};
  float mat_specular[] = {0.7,0.7,0.7,1.0};
  float mat_shininess[] = {15.0};

  glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
  glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
  return 0;
}
void displayHander() {
  static obj_data *od = ObjHandler::getInstance().getObjDataOf("teapot");
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBindVertexArray(od->pointer);
  glDrawArrays(GL_TRIANGLES, 0, od->vertices);
  //glutSolidTeapot(.07);
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
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE|
		      GLUT_MULTISAMPLE|GLUT_ACCUM);
  glutInitWindowPosition(w[0], w[1]);
  glutInitWindowSize(w[2], w[3]);
  glutCreateWindow(w.getTitle().c_str());

  glClearColor(0.9, 0.0, 0.0, 1.0);

  createViewVolume();
  createLights();

  obj_data *od = ObjHandler::getInstance().getObjDataOf("teapot");

  std::cerr << od->data.size() << std::endl;
  //for (auto i : od->data) std::cout << i << std::endl;
  glGenBuffers(1,&od->pointer);
  glBindBuffer(GL_ARRAY_BUFFER, od->pointer);
  glBufferData(GL_ARRAY_BUFFER, od->data.size() * sizeof(float), &od->data[0], GL_STATIC_DRAW);
  glVertexPointer(3, GL_FLOAT, 3 * sizeof(GLfloat), NULL);
  //glNormalPointer(GL_FLOAT, 3 * sizeof(GLfloat), (GLfloat *)(od->normalIndex * sizeof(GLfloat)));
  //glTexCoordPointer(4, GL_FLOAT, 2 * sizeof(GLfloat), (GLfloat *)(od->textureIndex * sizeof(GLfloat)));

  glEnableClientState(GL_VERTEX_ARRAY);
  //  glEnableClientState(GL_NORMAL_ARRAY);
  //glEnableClientState(GL_TEXTURE_COORD_ARRAY);


  ShaderHandler &shaderProgramHandler = ShaderHandler::getInstance();

  glutDisplayFunc(displayHander);
  glutKeyboardFunc(keyboardHandler);
  glutMainLoop();

  return 0;
}
