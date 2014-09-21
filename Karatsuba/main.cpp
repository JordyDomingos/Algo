#include <iostream>
#include <string>
#include <vector>

constexpr char kBase[] = "0123456789";

// We dont wan't to count the '\0'.
constexpr int kBaseSize = sizeof(kBase) - 1;

constexpr int kTestArray[][2] = {
  {2343, 119},
  {453234, 435},
  {1, 344},
  {0, 3234},
};

constexpr int kTestArraySize = sizeof(kTestArray) / sizeof(*kTestArray);

int PositionInBase(char digit) {
  return std::find(kBase, kBase + kBaseSize, digit) - kBase;
}

// Computes the addition  between the two number traited as strings
// passed in parameter.
std::string Add(std::string const &number1, std::string const &number2) {
  std::string result;

  const std::string &longest_number = number1.size() > number2.size() ?
    number1 : number2;
  const std::string &shortest_number = longest_number == number1 ?
    number2 : number1;

  result.reserve(longest_number.size() + 1);

  // We use the reverse iterators to start from the less significant digit
  // to the the most significant.
  auto digit_in_shortest_number = shortest_number.rbegin();
  int restraint = 0;

  for (auto digit_in_longest_number = longest_number.rbegin();
       digit_in_longest_number != longest_number.rend();
       ++digit_in_longest_number) {
    int digit1_position_in_base = PositionInBase(*digit_in_longest_number);

    // Initialize to 0 so that if all the digits of the number are consumed
    // then this digit won't have any influence (adding 0 to a number does not
    // change the number).
    int digit2_position_in_base = 0;

    if (digit_in_shortest_number != shortest_number.rend()) {
      digit2_position_in_base =  PositionInBase(*digit_in_longest_number);
      ++digit_in_shortest_number;
    }
    const char digit_addition_result =
      kBase[(digit1_position_in_base + digit2_position_in_base +
	     restraint) % kBaseSize];
    restraint = (digit1_position_in_base + digit2_position_in_base)
      / kBaseSize;
    result.insert(result.begin(), digit_addition_result);
  }
  return result;
}

// Basic multiplication algorithm taught in school.
std::string Multiplication(std::string const &number1,
			   std::string const &number2) {
  std::vector<std::string> intermediate_results;

  for (auto digit_in_number2 = number2.rbegin();
       digit_in_number2 != number2.rend(); ++digit_in_number2) {
    int offset = 0;
    int digit_in_number2_pos = PositionInBase(*digit_in_number2);

    for (auto digit_in_number1 = number1.rbegin();
	 digit_in_number1 != number1.rend(); ++digit_in_number1, ++offset) {
      int digit_in_number1_pos = PositionInBase(*digit_in_number1);
      int result = digit_in_number1_pos * digit_in_number2_pos;
      std::string result_in_string('0', offset);

      result_in_string.insert(result_in_string.begin(),
			      kBase[digit_in_number1_pos % kBaseSize]);
      if (result > kBaseSize)
	result_in_string.insert(result_in_string.begin(),
				kBase[digit_in_number2_pos / kBaseSize]);
      intermediate_results.push_back(result_in_string);
    }
  }
  std::string result = "0";
  for (int i = 0; i < intermediate_results.size(); ++i)
    result = Add(result, intermediate_results[i]);
  return result;
}

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
    std::string result = Add(std::to_string(kTestArray[i][0]),
			     std::to_string(kTestArray[i][1]));
    int result_in_int = std::stoi(result);
    int expected_result = kTestArray[i][0] + kTestArray[i][1];

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
