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

// A A == 1
// A B == 7
// A C ==

int main ()
{
  std::ifstream is("day2pt1.txt");
  std::string n;
  std::vector<std::string> raw;
  uint32_t score =0;
  while (std::getline(is >> std::ws, n)) {
    n[2]-=23;
    std::cout << n << ", ";
    score+= (n[2]-'A')+1;
    if (n[0]==n[2]) score+=3;
    else if (n[0]==n[2]-1 || (n[0]=='C' && n[2]=='A')) score+=6;
  }

  std::cout << score << std:: endl;
  return 0;
}
