#ifndef KOMORI_SCANNER_HPP_
#define KOMORI_SCANNER_HPP_

#include <optional>
#include <string>
#include <vector>
#include "error.hpp"
#include "token.hpp"

namespace komori {
namespace detail {
class Scanner {
 public:
  explicit Scanner(std::string source);

  WithErrorVec<std::vector<Token>> ScanTokens();

 private:
  std::optional<Token> ScanToken();

  Token CutToken(TokenType type, Object literal = nullptr);
  std::optional<Token> CutString();
  std::optional<Token> CutNumber();
  std::optional<Token> CutIdentifier();
  char Advance();

  bool IsAtEnd() const;
  bool Match(char expected);
  char Peek() const;
  char PeekNext() const;

  std::string source_;
  std::size_t start_{};
  std::size_t current_{};
  std::size_t line_{1};

  std::vector<Error> errors_;
};
}  // namespace detail

WithErrorVec<std::vector<Token>> ScanTokens(const std::string& source);
}  // namespace komori

#endif  // KOMORI_SCANNER_HPP_
