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
 std::ifstream is("day4.txt");
  std::string n;
  uint32_t score =0;
  while (std::getline(is >> std::ws, n)) {
    std::cout << n << ": ";
    int t[4],tDex=0;
    std::string temp[4];

    for (auto C:n) {
      if (std::isdigit(C)) temp[tDex]+=C;
      else tDex++;
    }

    for (int i=0;i!=4;++i) {
      t[i]=std::stoi(temp[i]);
    }

    // check for overlap
    int high = std::max({t[1],t[3]});
    int low = std::min({t[0],t[2]});
    std::vector<int> tasks (high+1,0);
    for (int i=0;i!=2;++i) {
      do {
        tasks[t[i*2]++]+=i+1;
      } while (t[i*2] <= t[(i*2)+1]);
    }

    bool d1 = false;

    do {
      switch (tasks[low]) {
        case 3:
          d1 = true;
          break;
        default:
          break;
      }
      low++;
    } while (low <= high);

    if (d1) {
      score++;
      std::cout << "Y";
    } else {
      std::cout << "N";
    }
    std::cout << std::endl;
  }
  std::cout << score << std::endl;
  return 0;
}
