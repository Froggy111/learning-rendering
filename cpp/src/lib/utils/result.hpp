#ifndef RESULT_HPP
#define RESULT_HPP

#include <string>
#include <iostream>

namespace result {
  struct Error {
    std::string function_name = "";
    std::string error = "";
  };

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
      std::cerr << "Error in Result from " + this->function_name + ":\n" + err_msg << std::endl;
      Error error_to_throw = {
        this->function_name,
        this->err_msg,
      };
      throw (
        error_to_throw
      );
    }
  };

  template <typename T>
  Result<T> error(std::string err_msg, std::string function_name) {
    Result<T> res;
    res.set_err(err_msg, function_name);
    return res;
  }
  
  template<typename T>
  Result<T> success(T result, std::string function_name) {
    Result<T> res;
    res.set_result(result, function_name);
    return res;
  }

  void panic(std::string err_msg, std::string function_name);
}

#endif