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

struct dir {
  uint64_t size;
  vector <struct dir*> subd;
  struct dir* parent;
} dir_t;

int main ()
{
  std::ifstream is("day7.txt");
  std::string n = "$ cd /";
  std::vector<std::string> raw;
  std::string num_stacks;

//  while (std::getline(is >> std::ws, n)) {
    raw.push_back(n);
//  }

  dir_t /;
  /.parent = &dir;  // I am my own dad.


  // parse
  auto it = raw.begin();
  dir_t *curr = &/;
  while (true) {
    switch (*it[2]) {
      case 'c': // cd
        stringstream ss(*it);
        std::string dest;
        for (std::string w; ss>>dest; );
        std::cout << dest << std::endl;
        break;

      case 'l': //ls
        break;
    }

    break;
  }

}
