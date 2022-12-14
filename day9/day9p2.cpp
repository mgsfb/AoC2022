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
    int hx[10]={0},hy[10]={0},numSteps=0;
    std::set<std::pair<int,int>> tlocs;

    while (std::getline(is >> std::ws, n)) {
        numSteps = std::stoi(n.substr(2));
        int ddx=0,ddy=0;
        for (int i=0;i!=numSteps;++i) {
            switch(n[0]) {
                default:
                    break;

                case 'L':
                    hx[0]--;
                    ddx=1;
                    break;

                case 'R':
                    hx[0]++;
                    ddx=1;
                    break;

                case 'U':
                    hy[0]++;
                    ddy=1;
                    break;

                case 'D':
                    hy[0]--;
                    ddy=1;
                    break;
            }
            std::cout << n << ": " << hx[0] << ", " << hy[0] << "   ";
            for (int j=1;j!=10;++j) {
                int dx = std::abs(hx[j-1]-hx[j]);
                int dy = std::abs(hy[j-1]-hy[j]);

                if (dx==2) {
                    if (hx[j-1]>hx[j]) hx[j]++;
                    else hx[j]--;

                    if (dy==1 && hy[j-1]!=hy[j]) hy[j]=hy[j-1];
                }

                if (dy ==2) {
                    if (hy[j-1]>hy[j]) hy[j]++;
                    else hy[j]--;

                    if (dx==1 && hx[j-1]!=hx[j]) hx[j]=hx[j-1];
                }
                std::cout << hx[j] << ", " << hy[j] << "   ";
            }
            tlocs.insert(std::make_pair(hx[9],hy[9]));
            std::cout << ":: " << tlocs.size() << std::endl;
        }
    }

    std::cout << tlocs.size() << std::endl;
}
