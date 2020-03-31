#pragma once

class Scene {
private:
public:
  Scene();
  Scene(const char* filename);
  ~Scene();

  char* render();
};