#include "Application.h"
#include <iostream>
#include <stdexcept>

int main(int argc, char *argv[]) {
  try {
    Application app;
    app.run();
  } catch (std::exception &e) {
    std::cout << "\nEXCEPTION: " << e.what() << std::endl;
  }

  return 0;
}
