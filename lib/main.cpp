#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glx.h>
#include <GL/glext.h>

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../include/data.h"
#include "../include/teapot.h"

void keyboardHandler(unsigned char key, int x, int y) {
  switch(key) {
  case 'q':
    std::cout << x << ", " << y << std::endl;
    exit(0);
    break;
  }
}


void displayHander() {
  static Teapot tp(Data::g().getXmlStr("teapot/shader"));
  tp.draw();
  glutSwapBuffers();
}

int main(int argc, char *argv[]) {
  Data &d = Data::getInstance();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE|
		      GLUT_MULTISAMPLE|GLUT_ACCUM);
  glutInitWindowPosition(d.getXmlFloat("window/x"),
			 d.getXmlFloat("window/y"));
  glutInitWindowSize(d.getXmlFloat("window/width"),
		     d.getXmlFloat("window/height"));
  glutCreateWindow(d.getXmlFloat("window/title").
c_str());
  glewInit();
  //instantiates shaders
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);


  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
  createPerspective();


  glutDisplayFunc(displayHander);
  glutKeyboardFunc(keyboardHandler);
  glutMainLoop();

  return 0;
}
