#ifndef KOMORI_TOKEN_TYPE_HPP_
#define KOMORI_TOKEN_TYPE_HPP_

namespace komori {
enum class TokenType {
  // Single-character tokens
  kLeftParen,
  kRightParen,
  kLeftBrace,
  kRightBrace,
  kComma,
  kDot,
  kMinus,
  kPlus,
  kSemicolon,
  kSlash,
  kStar,

  // Comparison operators
  kBang,
  kBangEqual,
  kEqual,
  kEqualEqual,
  kGreater,
  kGreaterEqual,
  kLess,
  kLessEqual,

  // Literals
  kIdentifier,
  kString,
  kNumber,

  // Keywords
  kAnd,
  kClass,
  kElse,
  kFalse,
  kFun,
  kFor,
  kIf,
  kNil,
  kOr,
  kPrint,
  kReturn,
  kSuper,
  kThis,
  kTrue,
  kVar,
  kWhile,

  kEof,
};
}

#endif  // KOMORI_TOKEN_TYPE_HPP_
