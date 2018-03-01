#include <windows.h>
#include <GL/glut.h>
#include <vector>

using namespace std;

//Entity class
class Entity {
  public:
    int x;
    int y;
    int w;
    int h;
    int angle;
    float r;
    float g;
    float b;
    void render();
    Entity(int X, int Y, int W, int H, int ANGLE, float R, float G, float B);
};

//Constructor
Entity::Entity(int X, int Y, int W, int H, int ANGLE, float R, float G, float B) {
  x = X;
  y = Y;
  w = W;
  h = H;
  angle = ANGLE;
  r = R;
  g = G;
  b = B;
}

void Entity::render() {
  //Rotates the canvas
  glTranslatef(x + (w / 2), y + (h / 2), 0);
  glRotatef(angle, 0, 0, 1);
  glTranslatef(-(x + (w / 2)), -(y + (h / 2)), 0);

  //Sets color
  glColor3f(r, g, b);

  //Drawes rectangle
  glRectf(x, y, x + w, y + h);

  //Rotates the canvas back to original
  glTranslatef(x + (w / 2), y + (h / 2), 0);
  glRotatef(-angle, 0, 0, 1);
  glTranslatef(-(x + (w / 2)), -(y + (h / 2)), 0);
}

class Renderer {
  public:
    vector <Entity> entities;
    Entity newEntity(int x, int y, int w, int h, int angle, float r, float g, float b);
    Entity newEntity2(int x, int y, int w, int h, int angle, float r, float g, float b);
    void render();
    Renderer(int window_h, int window_w, int argc, char** argv);
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

Renderer::Renderer(int window_h, int window_w, int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(window_h, window_w);
  glutCreateWindow("Test");

  glOrtho(0.f, window_h, window_w, 0.f, 0.f, 1.f);

  setupRendering();

  glutMainLoop();

  entitiesAmount = 0;
}

Entity Renderer::newEntity(int x, int y, int w, int h, int angle, float r, float g, float b) {
  Entity entity(x, y, w, h, angle, r, g, b);

  entities.push_back(entity);

  entitiesAmount = entitiesAmount + 1;

  return entity;
}

Entity Renderer::newEntity2(int x, int y, int w, int h, int angle, float r, float g, float b) {
  Entity entity(x, y, w, h, angle, r, g, b);

  return entity;
}

void Renderer::render() {
  //Clear screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //Sets color
  glColor3f(0, 1, 0);

  //Drawes rectangle
  glRectf(50, 50, 50 + 100, 50 + 100);

  for(int i = 0; i < entitiesAmount; i++) {
    newEntity2(10*i, 10*i, 100, 100, 0, 1, 0, 0).render();
  }

  //Render
  glutSwapBuffers();
}
 
int main(int argc, char** argv) {
  Renderer renderer(640, 480, argc, argv);

  renderer.newEntity(10, 10, 100, 100, 0, 1, 0, 0);
}