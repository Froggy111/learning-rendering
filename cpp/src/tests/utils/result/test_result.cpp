#include "lib/utils/result.hpp"
#include <iostream>

result::Result<int> tester (bool success);

int main (void) {
  result::Result<int> a = tester(true);
  int b = a.unwrap();
  std::cout << "successful unwrap output: " << b << std::endl;
  result::Result<int> c = tester(false);
  int d = c.unwrap();
  std::cout << "unsuccessful unwrap output: " << d << std::endl;
  return 0;
}

result::Result<int> tester (bool success) {
  result::Result<int> a;
  if (success) {
    a.set_result(1, __PRETTY_FUNCTION__);
  }
  else {
    a.set_err("unsuccessful", __PRETTY_FUNCTION__);
  }
  return a;
}