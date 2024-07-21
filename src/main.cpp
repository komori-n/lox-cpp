#include <cstdlib>
#include <iostream>
#include "lox.hpp"

int main(int argc, char* argv[]) {
  if (argc > 2) {
    std::cerr << "Usage: cpplox [script]" << std::endl;
    return EXIT_FAILURE;
  }

  komori::Lox lox{};
  if (argc == 2) {
    const bool result = lox.RunFile(argv[1]);
    if (!result) {
      return EXIT_FAILURE;
    }
  } else {
    lox.RunPrompt();
  }

  return EXIT_SUCCESS;
}
