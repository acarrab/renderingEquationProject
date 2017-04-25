#include "../include/common.h"
#include "../include/dataHandler.h"
#include "../include/shaderHandler.h"
#include "../include/lightHandler.h"
#include "../include/perspectiveHandler.h"

#include "../include/genericsHandler.h"


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
  static GLuint baseProgram = ShaderHandler::getInstance().getProgramId("teapotShader");
  static LightHandler &lh = LightHandler::getInstance();
  static PerspectiveHandler &ph = PerspectiveHandler::getInstance();
  static GenericsHandler &gh = GenericsHandler::getInstance();

  //Actual drawing of the scene
  static int i = 0, total = 100000;

  if (i < total) {
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(baseProgram);

    lh.loadAttributes(baseProgram);
    ph.loadAttributes(baseProgram);

    for (auto generic : gh) {
      generic->loadAttributes(baseProgram);
      generic->drawVerts();
    }

    lh.next();
  }
  glutSwapBuffers();
}
void idleHandler() { displayHander(); }


int main(int argc, char *argv[]) {
  DataHandler &d = DataHandler::getInstance();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE|
		      GLUT_MULTISAMPLE);
  glutInitWindowPosition(d.getXmlFloat("window/x"),
			 d.getXmlFloat("window/y"));
  glutInitWindowSize(d.getXmlFloat("window/width"),
		     d.getXmlFloat("window/height"));
  glutCreateWindow(d.getXmlStr("window/title").c_str());
  glewInit();


  //glEnable(GL_DEPTH_TEST);
  //glDepthFunc(GL_LESS);

  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);//GL_ONE, GL_ONE);

  glutDisplayFunc(displayHander);
  glutIdleFunc(idleHandler);
  glutKeyboardFunc(keyboardHandler);
  glutMainLoop();

  return 0;
}
