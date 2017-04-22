#include "../include/common.h"
#include "../include/dataHandler.h"
#include "../include/shaderHandler.h"
#include "../include/lightHandler.h"
#include "../include/perspectiveHandler.h"
#include "../include/teapot.h"
#include "../include/wall.h"

class Generics{
  std::vector<GenericObject *> gens;
  Generics() {
    gens.push_back(new Teapot());
    for (int i = 0; i < 6; i++) gens.push_back(new Wall());
  }
public:
  static Generics& getInstance() { static Generics inst; return inst; }
  std::vector<GenericObject *> & getObjects() { return gens; }
  ~Generics() { for (auto thing : gens) delete thing; }
};


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
  static ShaderHandler &sh = ShaderHandler::getInstance();
  static std::vector<GenericObject*> &drawable = Generics::getInstance().getObjects();
  static GLuint baseProgram = sh.getProgramId("teapotShader");
  static LightHandler &lh = LightHandler::getInstance();
  static PerspectiveHandler &ph = PerspectiveHandler::getInstance();






  //Actual drawing of the scene
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(baseProgram);

  lh.loadAttributes(baseProgram);
  lh.next();
  ph.loadAttributes(baseProgram);

  for (auto generic : drawable) {
    generic->loadAttributes(baseProgram);
    generic->drawVerts();
  }
  std::cout << glGetError() << std::endl;
  glutSwapBuffers();
}
void idleHandler() { displayHander(); }


int main(int argc, char *argv[]) {
  DataHandler &d = DataHandler::getInstance();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE|
		      GLUT_MULTISAMPLE|GLUT_ACCUM);
  glutInitWindowPosition(d.getXmlFloat("window/x"),
			 d.getXmlFloat("window/y"));
  glutInitWindowSize(d.getXmlFloat("window/width"),
		     d.getXmlFloat("window/height"));
  glutCreateWindow(d.getXmlStr("window/title").c_str());
  glewInit();
  //instantiates shaders
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);


  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  glutDisplayFunc(displayHander);
  glutIdleFunc(idleHandler);
  glutKeyboardFunc(keyboardHandler);
  glutMainLoop();

  return 0;
}
