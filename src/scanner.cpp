#include "scanner.hpp"

#include <unordered_map>

namespace komori {
namespace detail {
namespace {
const std::unordered_map<std::string, TokenType> kKeywords{
    {"and", TokenType::kAnd},     {"class", TokenType::kClass},   {"else", TokenType::kElse},
    {"false", TokenType::kFalse}, {"for", TokenType::kFor},       {"fun", TokenType::kFun},
    {"if", TokenType::kIf},       {"nil", TokenType::kNil},       {"or", TokenType::kOr},
    {"print", TokenType::kPrint}, {"return", TokenType::kReturn}, {"super", TokenType::kSuper},
    {"this", TokenType::kThis},   {"true", TokenType::kTrue},     {"var", TokenType::kVar},
    {"while", TokenType::kWhile},
};
}  // namespace

Scanner::Scanner(std::string source) : source_{std::move(source)} {}

WithErrorVec<std::vector<Token>> Scanner::ScanTokens() {
  std::vector<Token> tokens;
  errors_.clear();

  while (!IsAtEnd()) {
    start_ = current_;
    if (std::optional<Token> maybe_token = ScanToken()) {
      tokens.emplace_back(std::move(maybe_token.value()));
    }
  }

  tokens.emplace_back(TokenType::kEof, "", nullptr, line_);
  return {tokens, errors_};
}

std::optional<Token> Scanner::ScanToken() {
  const char c = Advance();
  switch (c) {
    case '(':
      return CutToken(TokenType::kLeftParen);
    case ')':
      return CutToken(TokenType::kRightParen);
    case '{':
      return CutToken(TokenType::kLeftBrace);
    case '}':
      return CutToken(TokenType::kRightBrace);
    case ',':
      return CutToken(TokenType::kComma);
    case '.':
      return CutToken(TokenType::kDot);
    case '-':
      return CutToken(TokenType::kMinus);
    case '+':
      return CutToken(TokenType::kPlus);
    case ';':
      return CutToken(TokenType::kSemicolon);
    case '*':
      return CutToken(TokenType::kStar);

    case '!':
      return CutToken(Match('=') ? TokenType::kBangEqual : TokenType::kBang);
    case '=':
      return CutToken(Match('=') ? TokenType::kEqualEqual : TokenType::kEqual);
    case '<':
      return CutToken(Match('=') ? TokenType::kLessEqual : TokenType::kLess);
    case '>':
      return CutToken(Match('=') ? TokenType::kGreaterEqual : TokenType::kGreater);

    case '/':
      if (Match('/')) {
        while (!IsAtEnd() && Peek() != '\n') {
          Advance();
        }
        return std::nullopt;
      } else {
        return CutToken(TokenType::kSlash);
      }

    case ' ':
    case '\r':
    case '\t':
      return std::nullopt;
    case '\n':
      ++line_;
      return std::nullopt;

    case '"':
      return CutString();

    default:
      if (std::isdigit(c)) {
        return CutNumber();
      } else if (std::isalpha(c) || c == '_') {
        return CutIdentifier();
      }

      errors_.emplace_back(line_, "Unexpected character.");
      return std::nullopt;
  }
}

Token Scanner::CutToken(TokenType type, Object literal) {
  return Token{type, source_.substr(start_, current_ - start_), std::move(literal), line_};
}

std::optional<Token> Scanner::CutString() {
  while (!IsAtEnd() && Peek() != '"') {
    if (Peek() == '\n') {
      ++line_;
    }
    Advance();
  }

  if (IsAtEnd()) {
    errors_.emplace_back(line_, "Unterminated string.");
    return std::nullopt;
  }

  Advance();
  std::string literal = source_.substr(start_ + 1, current_ - start_ - 2);
  return CutToken(TokenType::kString, std::move(literal));
}

std::optional<Token> Scanner::CutNumber() {
  while (std::isdigit(Peek())) {
    Advance();
  }

  if (Peek() == '.' && std::isdigit(PeekNext())) {
    Advance();
    while (std::isdigit(Peek())) {
      Advance();
    }
  }

  const std::string str = source_.substr(start_, current_ - start_);
  const double literal = std::stod(str);
  return CutToken(TokenType::kNumber, literal);
}

std::optional<Token> Scanner::CutIdentifier() {
  while (std::isalnum(Peek()) || Peek() == '_') {
    Advance();
  }
  const std::string text = source_.substr(start_, current_ - start_);
  if (const auto it = kKeywords.find(text); it != kKeywords.end()) {
    return CutToken(it->second, text);
  } else {
    return CutToken(TokenType::kIdentifier, text);
  }
}

char Scanner::Advance() {
  return source_[current_++];
}

bool Scanner::IsAtEnd() const {
  return current_ >= source_.size();
}

bool Scanner::Match(char expected) {
  if (IsAtEnd()) {
    return false;
  }
  if (source_[current_] != expected) {
    return false;
  }

  ++current_;
  return true;
}

char Scanner::Peek() const {
  if (IsAtEnd()) {
    return '\0';
  }
  return source_[current_];
}

char Scanner::PeekNext() const {
  if (current_ + 1 >= source_.size()) {
    return '\0';
  }
  return source_[current_ + 1];
}
}  // namespace detail

WithErrorVec<std::vector<Token>> ScanTokens(const std::string& source) {
  detail::Scanner scanner{source};
  return scanner.ScanTokens();
}
}  // namespace komori
