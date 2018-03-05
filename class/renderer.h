#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

using namespace std;

//Tick function
void glutTimer(int value){
  glutPostRedisplay();
  glutTimerFunc(1, glutTimer, 1);
}

//Stores all entities and renders them
class Renderer {
  public:
    vector <Entity> entities;
    Entity newEntity(int, int, int, int, int, float, float, float);
    void render();
    void run();
    Renderer(int, int, int, char**);
  private:
    int entitiesAmount;
    void setupRendering();
};

Renderer* g_CurrentInstance;

extern "C"
void rendering() {
  g_CurrentInstance->render();
}

void Renderer::setupRendering() {
  ::g_CurrentInstance  = this;
  ::glutDisplayFunc(::rendering);
}

//Constructor
Renderer::Renderer(int window_h, int window_w, int argc, char** argv) {
  entitiesAmount = 0;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(window_h, window_w);
  glutCreateWindow("Test");

  glutTimerFunc(1, glutTimer, 1);

  glOrtho(0.f, window_h, window_w, 0.f, 0.f, 1.f);

  setupRendering();
}

//Runs main loop
void Renderer::run() {
  glutMainLoop();
}

//Creates new Entity
Entity Renderer::newEntity(int x, int y, int w, int h, int angle, float r, float g, float b) {
  Entity entity(x, y, w, h, angle, r, g, b);

  entities.push_back(entity);

  entitiesAmount = entitiesAmount + 1;

  return entity;
}

//Renders all Entities
void Renderer::render() {
  //Clear screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for(int i = 0; i < entitiesAmount; i++) {
    entities[i].render();
  }

  //Render
  glutSwapBuffers();
}

#endif