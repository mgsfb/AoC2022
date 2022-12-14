#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>
#include <set>
#include <cstdint>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>

struct dir {
  uint64_t size;
  std::string name;
  std::map <std::string, dir*> subs;
  std::map <std::string, uint64_t> files;
  dir* parent;
} root;



int main ()
{

    std::ifstream is("day8.txt");
    std::string n;
    std::vector<std::string> raw;
    std::string num_stacks;
    std::vector<std::vector<int>> trees;
    std::vector<std::vector<int>> seen;

    while (std::getline(is >> std::ws, n)) {
        std::vector<int> temp;
        std::vector<int> temp2;
        for (auto C:n) {
            int ttree = C - '0';
            temp.push_back(ttree);
            temp2.push_back(0);
        }
        trees.push_back(temp);

        seen.push_back(temp2);

    }

    for (auto R=0;R!=trees.size();++R) {
        int rowMax = 0;
        int C = trees[0].size()-1;
        seen[R][C]=1;
        while (rowMax < 9 && C > -1) {
            if (trees[R][C] > rowMax) {
                seen[R][C] = 1;
                rowMax = trees[R][C];
//                std::cout << "going down" << R << "," << C << " :: rowmax-" << rowMax << std::endl;
            }
            C--;
        }
        rowMax=0;
        C=0;
        seen[R][C]=1;
        while (rowMax < 9 && C < trees[0].size()) {
            if (trees[R][C] > rowMax) {
                seen[R][C] = 1;
                rowMax = trees[R][C];

//                std::cout << "going up" << R << "," << C << std::endl;
            }
            C++;
        }
    }

    for (auto C=0;C!=trees[0].size();++C) {
        int rowMax = 0;
        int R = 0;
        seen[R][C]=1;
        while (rowMax < 9 && R < trees.size()) {
            if (trees[R][C] > rowMax) {
                seen[R][C] = 1;
                rowMax = trees[R][C];
            }
            R++;
        }
        rowMax = 0;
        R = trees.size()-1;
        seen[R][C]=1;
        while (rowMax < 9 && R > -1) {
            if (trees[R][C] > rowMax) {
                seen[R][C] = 1;
                rowMax = trees[R][C];
            }
            R--;
        }
    }

    int total = 0;

    for (auto R:seen) {
        for (auto I:R) {
            std::cout << I;
            total +=I;
        }
        std::cout << std::endl;
    }

    std::cout << total << std::endl;
}
