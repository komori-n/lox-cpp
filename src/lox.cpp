#include "lox.hpp"
#include "scanner.hpp"

#include <fstream>
#include <iostream>

namespace komori {
bool Lox::RunFile(const std::string& file_path) {
  had_error_ = false;

  std::ifstream file{file_path};
  std::string bytes{std::istreambuf_iterator<char>{file}, {}};

  RunFile(bytes);
  return !had_error_;
}

void Lox::RunPrompt() {
  std::string line;
  for (;;) {
    had_error_ = false;
    std::cout << "> ";
    if (!std::getline(std::cin, line)) {
      break;
    }

    Run(line);
  }
}

void Lox::Run(const std::string& bytes) {
  WithErrorVec<std::vector<Token>> tokens = ScanTokens(bytes);

  for (const auto& error : tokens.errors) {
    Error(error.line, error.message);
  }
  for (const auto& token : tokens.value) {
    std::cout << token.ToString() << std::endl;
  }
}

void Lox::Error(uint64_t line, std::string_view message) {
  Report(line, "", message);
}
void Lox::Report(uint64_t line, std::string_view where, std::string_view message) {
  std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
  had_error_ = true;
}
}  // namespace komori
