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

    std::ifstream is("day9.txt");
    std::string n;
    int hx=0,hy=0,tx=0,ty=0,numSteps=0;
    std::set<std::pair<int,int>> tlocs;

    while (std::getline(is >> std::ws, n)) {
        numSteps = std::stoi(n.substr(2));
        for (int i=0;i!=numSteps;++i) {
            switch(n[0]) {
                default:
                    break;

                case 'L':
                    hx--;
                    if (tx-hx==2) {
                        tx--;
                        if (ty!=hy) ty=hy;
                    }
                    break;

                case 'R':
                    hx++;
                    if (hx-tx==2) {
                        tx++;
                        if (ty!=hy) ty=hy;
                    }
                    break;

                case 'U':
                    hy++;
                    if (hy-ty == 2) {
                        ty++;
                        if (tx!=hx) tx=hx;
                    }
                    break;

                case 'D':
                    hy--;
                    if (ty-hy == 2) {
                        ty--;
                        if (tx!=hx) tx=hx;
                    }
                    break;
            }
            std::cout << n << "[" << i << "]" << ": head:" << hx <<"," <<hy << ": tail" << tx << "," << ty << std::endl;
            tlocs.insert(std::make_pair(tx,ty));
        }
    }

    std::cout << tlocs.size() << std::endl;
}
