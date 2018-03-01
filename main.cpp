#include <windows.h>
#include <GL/glut.h>
#include <vector>

using namespace std;

void glutTimer(int value){
  glutPostRedisplay();
  glutTimerFunc(1, glutTimer, 1);
}

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
    void newEntity(int, int, int, int, int, float, float, float);
    void newEntity2(int, int, int, int, int, float, float, float);
    void render();
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

  glutMainLoop();
}

void Renderer::newEntity(int x, int y, int w, int h, int angle, float r, float g, float b) {
  Entity entity(x, y, w, h, angle, r, g, b);

  entities.push_back(entity);

  entitiesAmount = entitiesAmount + 1;
}

void Renderer::newEntity2(int x, int y, int w, int h, int angle, float r, float g, float b) {
  Entity entity(x, y, w, h, angle, r, g, b);
}

void Renderer::render() {
  //Clear screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //Sets color
  glColor3f(0, 1, 0);

  //Drawes rectangle
  glRectf(50, 50, 50 + 100, 50 + 100);

  newEntity(10, 10, 100, 100, 0, 1, 0, 0);
  newEntity(20, 20, 100, 100, 0, 1, 0, 0);
  newEntity(30, 30, 100, 100, 0, 1, 0, 0);

  for(int i = 0; i < entitiesAmount; i++) {
    entities[i].render();
  }

  newEntity(40, 40, 100, 100, 0, 1, 0, 0);

  //Render
  glutSwapBuffers();
}
 
int main(int argc, char** argv) {
  Renderer renderer(640, 480, argc, argv);

  renderer.newEntity(50, 50, 100, 100, 0, 1, 0, 0);

  renderer.newEntity(70, 70, 100, 100, 0, 1, 0, 0);
}