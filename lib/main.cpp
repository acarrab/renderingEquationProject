#include "../include/common.h"
#include "../include/dataHandler.h"
#include "../include/lightHandler.h"
#include "../include/perspectiveHandler.h"

#include "../include/genericsHandler.h"
#include "../include/shader.h"


void keyboardHandler(unsigned char key, int x, int y) {
  switch(key) {
  case 'q':
    exit(0);
    break;
  case 'm':
    std::cout << x << ", " << y << std::endl;
    break;
  }
}
void displayHander() {
  static Shader baseProg("teapotShader");//, shadowMapGenProg("shadowShader");
  static GenericsHandler &gh = GenericsHandler::getInstance();
  static PerspectiveHandler &ph = PerspectiveHandler::getInstance();
  static LightHandler lh;
  static Light l;

  static int i = 1;
  static const int iterations = 1000000;
  static const float brightFactor = 1.0;
  glClear(GL_DEPTH_BUFFER_BIT);

  if (i < iterations) {
    if (i == 1)  { lh.next(l, gh); i++; }
    glUseProgram(baseProg.id);
    l.loadAttributes(baseProg.id);
    ph.loadAttributes(baseProg.id);
    //draw objects
    for (auto generic : gh) {
      generic->loadAttributes(baseProg.id);
      generic->drawVerts();
    }
    lh.next(l, gh);

    glAccum(GL_ACCUM, 1.0/iterations );
    glAccum(GL_RETURN, iterations/i++);
    //glFlush();
  }



  glutSwapBuffers();

  glutSwapBuffers();

}
void idleHandler() { displayHander(); }


int main(int argc, char *argv[]) {
  DataHandler &d = DataHandler::getInstance();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE|GLUT_MULTISAMPLE|GLUT_ACCUM);
  glutInitWindowPosition(d.getXmlInt("window/x"), d.getXmlInt("window/y"));
  glutInitWindowSize(d.getXmlInt("window/width"), d.getXmlInt("window/height"));
  glutCreateWindow(d.getXmlStr("window/title").c_str());
  glewInit();


  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearAccum(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_ACCUM_BUFFER_BIT);

  /*  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);//GL_SRC_ALPHA, GL_DST_ALPHA);
  glBlendEquation(GL_MAX);*/

  glutDisplayFunc(displayHander);
  glutIdleFunc(idleHandler);
  glutKeyboardFunc(keyboardHandler);
  glutMainLoop();

  return 0;
}
