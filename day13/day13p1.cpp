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
#include <functional>
#include <queue>


int main ()
{
    std::ifstream is("day13test.txt");
    std::string n;
    std::vector<std::string> raw;

    while (std::getline(is >> std::ws, n)) {
        raw.push_back(n);
    }

    auto it = raw.begin();

    int index = 1;
    int goodsum = 0;
    while (it != raw.end()) {
        std::string L = *it;
        it++;
        std::string R = *it;
        it++;

        auto Lit = L.begin();
        auto Rit = R.begin();
        bool gud = true;

        // parse into sections


            // do conversions, or...
            Lit++; Rit++;
            if (Lnum > Rnum) {
                std::cout << index << " bad where Lnum = " << Lnum << " and Rnum = " << Rnum << std::endl;
                gud=false;
            }
        }
        if (Rit==R.end() && Lit!=L.end()) {
            std::cout << index << " bad because R ended first" << std::endl;
            gud=false;
        }

        if (gud) {
            std::cout << index << " is good?" << std::endl;
            goodsum+=index;
        }
        index++;
    }

    std::cout << goodsum << std::endl;

    return 0;
}
