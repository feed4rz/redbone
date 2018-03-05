#ifndef ENTITY_H
#define ENTITY_H

//Object that is being display on the screen
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

//Renders the Entity
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

#endif