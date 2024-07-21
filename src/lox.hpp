#ifndef KOMORI_LOX_HPP_
#define KOMORI_LOX_HPP_

#include <cstdint>
#include <string>

namespace komori {
class Lox {
 public:
  bool RunFile(const std::string& file_path);
  void RunPrompt();

 private:
  void Run(const std::string& bytes);

  void Error(uint64_t line, std::string_view message);
  void Report(uint64_t line, std::string_view where, std::string_view message);

  bool had_error_{false};
};
}  // namespace komori

#endif  // KOMORI_LOX_HPP_
