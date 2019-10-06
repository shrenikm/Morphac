#ifndef ERROR_MACROS_H
#define ERROR_MACROS_H

#include <iostream>

#ifndef NDEBUG
#define MORPH_ASSERT(conditon, error_message, exception)                    \
  {                                                                         \
    if (!(condition)) {                                                     \
      std::cerr << "------- Assertion failed -------" << std::endl;         \
      std::cerr << "Failed in file: " << __FILE__ << std::endl;             \
      std::cerr << "Failed inside function: " << __FUNCTION__ << std::endl; \
      std::cerr << "Failed at line: " << __LINE__ << std::endl;             \
      throw exception(error_message);                                       \
    }                                                                       \
  }
#endif

#define MORPH_REQUIRE(condition, error_message, exception)                  \
  {                                                                         \
    if (!(condition)) {                                                     \
      std::cerr << "------- Requirement failed -------" << std::endl;       \
      std::cerr << "Failed in file: " << __FILE__ << std::endl;             \
      std::cerr << "Failed inside function: " << __FUNCTION__ << std::endl; \
      std::cerr << "Failed at line: " << __LINE__ << std::endl;             \
      throw exception(error_message);                                       \
    }                                                                       \
  }

#define MORPH_WARNING(condition, warning_message)                            \
  {                                                                          \
    if (condition) {                                                         \
      std::cerr << "------- Warning -------" << std::endl;                   \
      std::cerr << "Warning in file: " << __FILE__ std::endl;                \
      std::cerr << "Warning inside function: " << __FUNCTION__ << std::endl; \
      std::cerr << "Warning at line: " << __LINE__ << std::endl;             \
      std::cerr << "Warning message: " << #warning_message << std::endl;     \
    }                                                                        \
  }

#endif
