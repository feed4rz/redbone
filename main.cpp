#include "core.h"
 
int main(int argc, char** argv) {
  Renderer renderer(640, 480, argc, argv);

  renderer.newEntity(50, 50, 100, 100, 0, 0, 1, 0);

  renderer.newEntity(70, 70, 100, 100, 0, 1, 0, 0);

  renderer.run();
}