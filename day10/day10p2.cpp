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

int main ()
{
    std::ifstream is("day10.txt");
    std::string n;
    std::vector<std::string> raw;
    int rsum =0;
    int regX = 1,regXNew = 1;
    int pc = 1, pcUpdate =1;
    int psSig = 40;


    while (std::getline(is >> std::ws, n)) {
        raw.push_back(n);
    }

    auto it = raw.begin();

    // parse
    for (int CRTPos=1;CRTPos!=241;++CRTPos) {
        if (pc == pcUpdate) {
            std::stringstream ss(*it);
            std::string dest = "";
            regX = regXNew;
            ss >> dest;

            switch (dest[0]) {
                default:
                    break;

                case 'a':
                    pcUpdate = pc + 2;
                    ss>>dest;
                    regXNew = regX+ std::stoi (dest);
                    break;

                case 'n':
                    pcUpdate = pc+1;
                    break;
            }
            it++;
        }
        pc++;
        //std::cout << CRTPos << ": " << pc << ", " << regX << std::endl;
        std::cout << ".#"[(int)(((CRTPos-1)%40)-1<=regX && ((CRTPos-1)%40)+1>=regX)];
        if ((CRTPos %40)==0 && CRTPos > 0) std::cout << std::endl;
    }
}
