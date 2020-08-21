#ifndef NUMERIC_ALIASES_H
#define NUMERIC_ALIASES_H

namespace morphac {
namespace common {
namespace aliases {

template<typename T>
auto Infinity = std::numeric_limits<T>::infinity();

template<typename T>
auto Epsilon = std::numeric_limits<T>::epsilon();


}  // namespace aliases
}  // namespace common
}  // namespace morphac

#endif
