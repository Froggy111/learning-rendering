#include <string>
#include <iostream>

namespace result {
  struct Error;
  template <typename T>
  class Result {
  private:
    T result;
    bool err;
    std::string err_msg;
    std::string function_name;
  public:
    void set_err(std::string err_msg, std::string function_name) {
    this->err_msg = err_msg;
    this->err = true;
    this->function_name = function_name;
  }

    void set_result(T result, std::string function_name) {
    this->result = result;
    this->err = false;
    this->err_msg = "";
    this->function_name = function_name;
  }
  
    T unwrap(void) {
    if (!this->err) {
      return this->result;
    }
    std::cerr << "Error in Result from " + this->function_name + ": " + err_msg << std::endl;
    Error error_to_throw = {
      this->function_name,
      this->err_msg,
    };
    throw (
      error_to_throw
    );
  }
  };
  struct Error {
    std::string function_name = "";
    std::string error = "";
  };
}