#ifndef KOMORI_RESULT_HPP_
#define KOMORI_RESULT_HPP_

#include <string>
#include <vector>

namespace komori {
struct Error {
  uint64_t line;
  std::string message;
};

template <typename T>
struct WithErrorVec {
  T value;
  std::vector<Error> errors;
};
}  // namespace komori

#endif  // KOMORI_RESULT_HPP_
