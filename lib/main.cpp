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

class DisplayHandler {
  DataHandler &dh;
  GenericsHandler &gh;
  PerspectiveHandler &ph;
  LightHandler lh;
  Light l;
  int bounces, iterations;
  float additional, retScalar;
  Shader baseProg;
  GLuint lid;
  int i;
public:
  DisplayHandler() :
    dh(DataHandler::getInstance()),
    gh(GenericsHandler::getInstance()),
    ph(PerspectiveHandler::getInstance()),
    lh(),l(),
    bounces(dh.getXmlInt("light/bounces")),
    iterations(dh.getXmlInt("light/iterations")),
    additional(100.0 / bounces / iterations),
    retScalar(bounces * iterations / 100.0),
    baseProg("teapotShader"),
    lid(glGetUniformLocation(baseProg.id, "lightId")),
    i(1) {}
  void displayFrame() {
    if (i <= iterations) {
      glUniform1i(lid, 0);
      for (int j = 0; j < bounces; j++) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glUseProgram(baseProg.id);
	l.loadAttributes(baseProg.id);
	ph.loadAttributes(baseProg.id);
	//draw objects
	for (auto generic : gh) {
	  generic->loadAttributes(baseProg.id);
	  generic->drawVerts();
	}
	lh.next(l, gh);
	glAccum(GL_ACCUM, additional);
	glUniform1i(lid, 1);
      }
      lh.next(l, gh);
      i++;
      glAccum(GL_RETURN, retScalar/static_cast<float>(i));
      glutSwapBuffers();
    }
  }

};
void display() { static DisplayHandler displayer; displayer.displayFrame(); }


void idleHandler() { display(); }


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


  glutDisplayFunc(display);
  glutIdleFunc(idleHandler);
  glutKeyboardFunc(keyboardHandler);
  glutMainLoop();

  return 0;
}
