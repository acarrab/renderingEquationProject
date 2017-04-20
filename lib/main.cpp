#include "../include/common.h"
#include "../include/data.h"
#include "../include/teapot.h"
#include "../include/box.h"

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
  static Box box(Data::g().getXmlStr("box/shader"));
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  tp.display();
  box.display();
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
  glutCreateWindow(d.getXmlStr("window/title").c_str());
  glewInit();
  //instantiates shaders
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);


  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  glutDisplayFunc(displayHander);
  glutKeyboardFunc(keyboardHandler);
  glutMainLoop();

  return 0;
}
