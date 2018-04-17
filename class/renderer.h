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
    Entity newEntity(int, int, int, int, int, float, float, float, int);
    void render();
    void run();
    void quickSort(vector<Entity> &, int, int);
    void sortEntities();
    Renderer(int, int, int, char**);
  private:
    void setupRendering();
};

Renderer* g_CurrentInstance;

extern "C"
void rendering() {
  g_CurrentInstance->render();
}

void Renderer::setupRendering() {
  ::g_CurrentInstance = this;
  ::glutDisplayFunc(::rendering);
}

//Constructor
Renderer::Renderer(int window_h, int window_w, int argc, char** argv) {
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
Entity Renderer::newEntity(int x, int y, int w, int h, int angle, float r, float g, float b, int index) {
  Entity entity(x, y, w, h, angle, r, g, b, index);

  entities.push_back(entity);

  return entity;
}

//Renders all Entities
void Renderer::render() {
  //Clear screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  int index = -10000;
  for(int i = 0; i < entities.size(); i++) {
    if(index < entities[i].index) {
      entities[i].render();
      index = entities[i].index;
    }
  }

  //Render
  glutSwapBuffers();
}

/* Basic quick sort */
void Renderer::quickSort(vector <Entity> &array, int low, int high) {
  int i = low;
  int j = high;
  int pivot = array[(i + j) / 2].index;
  Entity temp(0, 0, 0, 0, 0, 0, 0, 0, 0);

  while(i <= j) {
    while(array[i].index < pivot) {
      i++;
    }

    while(array[j].index > pivot) {
      j--;
    }

    if(i <= j) {
      temp = array[i];
      array[i] = array[j];
      array[j] = temp;

      i++;
      j--;
    }
  }

  if(j > low) {
    quickSort(array, low, j);
  }
  if (i < high) {
    quickSort(array, i, high);
  }
}

void Renderer::sortEntities() {
  quickSort(entities, 0, entities.size() - 1);
}

#endif