#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>
#include <set>
#include <cstdint>
#include <bitset>
#include <algorithm>
#include <map>
#include <stack>

int main ()
{
  std::ifstream is("day1.1.txt");
  std::string n;
  std::vector<std::string> raw;
  uint64_t temp =0, max =0;
  while (std::getline(is, n)) {
    if (n.size()!=0) {
      temp += std::stoi(n);
    } else {
      max = temp > max ? temp : max;
      temp =0;
    }
  }
  std::cout << max << std::endl;
}
