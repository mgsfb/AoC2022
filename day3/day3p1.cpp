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
  std::string n;
  uint32_t score =0;
  while (std::getline(is >> std::ws, n)) {
    // sort bags
    auto m_it = n.begin()+n.size()/2;
    std::sort(n.begin(),m_it);
    std::sort(m_it,n.end());

    // find element
    auto bag1_it = n.begin();
    auto bag2_it = m_it;
    while (bag1_it < m_it && bag2_it < n.end()) {
      char temp1 = *bag1_it;
      if (*bag1_it==*bag2_it) {
        // score
        if (temp1-'A' > 26) score+=temp1-'a'+1;
        else score+=temp1-'A'+27;
        break;
      }
      if (*bag1_it < *bag2_it) bag1_it++;
      else bag2_it++;
    }

  }
  std::cout << score << std::endl;
  return 0;
}
