#ifndef KOMORI_TOKEN_HPP_
#define KOMORI_TOKEN_HPP_

#include <string>
#include "object.hpp"
#include "token_type.hpp"

namespace komori {
struct Token {
  TokenType type;
  std::string lexeme;
  Object literal;
  uint64_t line;

  Token(TokenType type, std::string lexeme, Object literal, uint64_t line)
      : type{type}, lexeme{std::move(lexeme)}, literal{std::move(literal)}, line{line} {}

  std::string ToString() const {
    return std::string{"type: "} + std::to_string(static_cast<int>(type)) + ", lexeme: '" + lexeme +
           "', line: " + std::to_string(line);
  }
};
}  // namespace komori

#endif  // KOMORI_TOKEN_HPP_
