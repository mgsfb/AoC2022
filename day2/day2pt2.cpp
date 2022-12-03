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

// X = one less
// Y = same
// Z = one more

int main ()
{
  std::ifstream is("day2pt1.txt");
  std::string n;
  std::vector<std::string> raw;
  uint32_t score =0;
  while (std::getline(is >> std::ws, n)) {
    std::cout << n << ", ";
    switch (n[2]) {
      case 'X': // you lose
      score+=((n[0]+2)-'A')%3+1;
      break;
      case 'Y': //you tie
      score+=n[0]-'A'+4;  // score for the move +3
      break;
      case 'Z': //you win
      score+=((n[0]-'A'+1)%3)+7;  // score for the move +6
      break;
    }
  }

  std::cout << std::endl << score << std:: endl;
  return 0;
}
