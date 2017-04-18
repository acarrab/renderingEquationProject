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
#include "../include/winData.h"
#include "../include/shaderHandler.h"
#include "../include/objectHandler.h"
#include "../include/teapot.h"

glm::mat4 createPerspective() {
  static bool first = true;
  static glm::mat4 mvp;
  if (first) {
    first = false;
    WinData &w = WinData::getInstance();
    glm::mat4 Projection = glm::perspective(45.0f,
					    (float)w.width()/(float)w.height(),
					    .1f,
					    100.0f);

    glm::mat4 View = glm::lookAt(glm::vec3(4, 4, -3), //camera loc
				 glm::vec3(0, 0, 0), //looking at
				 glm::vec3(0, 1, 0));  //up

    glm::mat4 Model = glm::mat4(1.0f);//identity matrix

    mvp = Projection * View * Model;
  }
  return mvp;
}
void keyboardHandler(unsigned char key, int x, int y) {
  switch(key) {
  case 'q':
    std::cout << x << ", " << y << std::endl;
    exit(0);
    break;
  }
}


void displayHander() {
  static Teapot tp(Data::g().getXmlStr("teapot/shader"), createPerspective());
  tp.draw();
  glutSwapBuffers();
}

int main(int argc, char *argv[]) {
  WinData &w = WinData::getInstance();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE|
		      GLUT_MULTISAMPLE|GLUT_ACCUM);
  glutInitWindowPosition(w[0], w[1]);
  glutInitWindowSize(w[2], w[3]);
  glutCreateWindow(w.getTitle().c_str());
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
