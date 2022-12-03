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
  std::set<uint64_t> max;
  uint64_t temp =0;
  while (std::getline(is, n)) {
    if (n.size()!=0) {
      temp += std::stoi(n);
    } else {
      max.insert(temp);
      temp =0;
    }
  }
  temp=0;
  auto it = max.end();
  it--;
  for (int i=0;i != 3;++i) {
    std::cout << *it << std::endl;
    temp+=*it;
    it--;
  }
  std::cout << temp << std::endl;
}
