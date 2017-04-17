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

#include "../include/shaderHandler.h"

void keyboardHandler(unsigned char key, int x, int y) {
  switch(key) {
  case 'q':
    exit(0);
    break;
  }
}
std::vector< std::pair<GLuint, GLuint> > & initObjects() {
  static std::vector< std::pair<GLuint, GLuint> > objects(1);
  static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
  };
  glGenBuffers(1, &objects[0].first);
  glBindBuffer(GL_ARRAY_BUFFER, objects[0].first);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
	       g_vertex_buffer_data, GL_STATIC_DRAW);
  objects[0].second = 3;
  return objects;
}
void displayHander() {
  static std::vector< std::pair<GLuint, GLuint> > &objs = initObjects();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for (auto obj : objs) {
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, obj.first);
    glDrawArrays(GL_TRIANGLES, 0, obj.second);
    glDisableVertexAttribArray(0);
  }
  glutSwapBuffers();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE|
		      GLUT_MULTISAMPLE|GLUT_ACCUM);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(800,800);
  glutCreateWindow("testing GL");
  glewInit();
  //instantiates shaders
  ShaderHandler &shaderProgramHandler = ShaderHandler::getInstance();
  shaderProgramHandler.useProgram("shader");

  glutDisplayFunc(displayHander);
  glutKeyboardFunc(keyboardHandler);
  glutMainLoop();

  return 0;
}
