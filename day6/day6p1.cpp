
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>
#include <unordered_set>
#include <cstdint>
#include <bitset>
#include <algorithm>
#include <map>
#include <stack>



int main ()
{
  std::ifstream is("day6p1.txt");
  std::string n;
  while (std::getline(is >> std::ws, n)) {}


  std::cout << n.size() << std::endl;
  std::map <char,int> lastFour;
  std::unordered_set <char> rpts;
  auto itOut = n.begin();

  for (int i=0;i!=4;++i) {
    lastFour[*itOut]++;
    if (lastFour[*itOut] > 1) rpts.insert(*itOut);
    itOut++;
  }


  int count = 4;
  auto itIn = n.begin();
  while(itOut != n.end()) {
    if (rpts.size()==0) break;
    if (--lastFour[*itIn] <= 1) rpts.erase(*itIn);
    if (++lastFour[*itOut] > 1) rpts.insert(*itOut);
    std::cout << n.substr(count-3,4) << "::";
    count++;
    for (auto C: rpts) std::cout << C << ", ";
    std::cout << std::endl;
    itIn++;
    itOut++;
  }

  std::cout << count << std::endl;
  return 0;
}
