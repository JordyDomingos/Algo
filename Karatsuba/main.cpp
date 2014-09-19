#include <iostream>
#include <string>

constexpr int kTestArray[][2] = {
  {2343, 422},
  {435, 453234},
  {1, 344},
  {0, 3234},
};

constexpr int kTestArraySize = sizeof(kTestArray) / sizeof(*kTestArray);

// Computes the multiplication between the two number traited as strings
// passed in parameter.
std::string Karatsuba(std::string const &number1, std::string const &number2) {
  return std::string("0");
}

bool Testkaratsuba() {
  return true;
}

bool RunTest() {
  int number_of_failed_tests = 0;

  for (int i = 0; i < kTestArraySize; ++i) {
    std::string result = Karatsuba(std::to_string(kTestArray[i][0]),
				   std::to_string(kTestArray[i][1]));
    int result_in_int = std::stoi(result);
    int expected_result = kTestArray[i][0] * kTestArray[i][1];

    if (result_in_int != expected_result) {
      ++number_of_failed_tests;
      std::cerr << "---- ---- ---- ---" << std::endl;
      std::cerr << "Test number " << i << " FAILED" << std::endl; 
      std::cerr << "The following test failed: "
		<< kTestArray[i][0] << " * " << kTestArray[i][1] << std::endl;
      std::cerr << "The result found by Karatsuba is " << result_in_int << std::endl;
      std::cerr << "The expected result is " << expected_result << std::endl;
      std::cerr << std::endl;
    }
  }
  std::cout << "Karatsuba failed " << number_of_failed_tests << " out of "
	    << kTestArraySize << " tests." << std::endl;
  return !number_of_failed_tests;
}

int main(int argc, char **argv) {
  if (argc != 3)
    return 1;
  RunTest();
}
