#include "lib/utils/result.hpp"

namespace result {
  void panic(std::string err_msg, std::string function_name) {
    std::cerr << "Error in Result from " + function_name + ":\n" + err_msg << std::endl;
    Error error_to_throw = {
      function_name,
      err_msg,
    };
    throw (
      error_to_throw
    );
  }
}