#ifndef KOMORI_OBJECT_HPP_
#define KOMORI_OBJECT_HPP_

#include <string>
#include <variant>

namespace komori {
using Object = std::variant<std::nullptr_t, std::string, double>;
}

#endif  // KOMORI_OBJECT_HPP_
