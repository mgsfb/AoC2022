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
  std::ifstream is("p1.txt");
  std::string n1;
  uint32_t score =0;
  while (std::getline(is >> std::ws, n1)) {

    // get two more
    std::string n2, n3;
    std::getline(is >> std::ws, n2);
    std::getline(is >> std::ws, n3);

    // sort
    std::sort(n1.begin(),n1.end());
    std::sort(n2.begin(),n2.end());
    std::sort(n3.begin(),n3.end());

    // find element
    auto n1_it = n1.begin();
    auto n2_it = n2.begin();
    auto n3_it = n3.begin();

    while (n1_it < n1.end() && n2_it < n2.end() && n3_it < n3.end()) {
      auto it = n1_it;
      char temp = *n1_it;
      if (*n1_it == *n2_it && *n1_it==*n3_it) {
        // score
        if (temp-'A' > 26) score+=temp-'a'+1;
        else score+=temp-'A'+27;
        break;
      }

      // because I don't know how to make a pointer to an iterator
      temp = std::min({*n1_it,*n2_it,*n3_it});
      if (temp == *n1_it) n1_it++;
      if (temp == *n2_it) n2_it++;
      if (temp == *n3_it) n3_it++;
    }
  }

  std::cout << score << std::endl;
  return 0;
}
