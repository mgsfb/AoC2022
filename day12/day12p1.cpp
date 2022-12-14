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



int FF (int curr, int R, int C, int Z, const std::vector<std::vector<int>> &map, std::vector<std::vector<int>> &cost)
{
    if (R<0 || C<0 || R>map.size()-1 || C>map[0].size()-1 || curr >= 10000) return 10000;

    int Zcurr = map[R][C];
    if (Zcurr==-14) Zcurr = 0;
    if (Zcurr==-28) Zcurr = 'z'-'a';

    if (cost[R][C] <= curr || (Z < (Zcurr-1))) return 10000;

//    std::cout << R << ", " << C << " :: " << cost[R][C] << " vs. " << curr << std::endl;
    cost[R][C]=curr;
    if (map[R][C] == -28) std::cout << "END!!!!" << std::endl; // got to the end.


    return curr;
}


int main ()
{
    std::ifstream is("day12.txt");
    std::string n;
    std::vector<std::vector<int>> map;
    std::vector<std::vector<int>> cost;

    int start =0, startCtr =0;

    while (std::getline(is >> std::ws, n)) {
        if (n.contains('E')) start=startCtr;
        startCtr++;
        std::vector<int> tmp (n.size(),10000);
        cost.push_back(tmp);
        int tmpDex =0;
        for (auto C:n) {
            tmp[tmpDex++]=C-'a';
        }
        map.push_back(tmp);

    }

    struct spot {int cost, R, C, Zs;} N = {0,start,0,0};
    std::multimap<int, spot> dest;

    dest.insert({0,N});

    int bC=0, bcost=10000;
    int dist = 10000;
    while (dest.size()) {
        auto dit = dest.begin();
        N = (*dit).second;
        dit = dest.erase(dit);
        if (N.cost == FF(N.cost,N.R,N.C,N.Zs,map,cost)) {

            if (N.C > bC || N.cost < bcost ) {
                std::cout << N.R << ", " << N.C << " cost " << N.cost << " moving from " << N.Zs << " to " << map[N.R][N.C] << std::endl;
                bC = N.C;
                bcost = N.cost;
            }

            if (map[N.R][N.C] == -28) dist = std::min(dist,N.cost);
            else {
                N.Zs = map[N.R][N.C];
                if (N.Zs ==-14) N.Zs =0;
                N.cost++;
                N.R++;
                dest.insert({N.cost,N});
                N.R-=2;
                dest.insert({N.cost,N});
                N.R++;
                N.C++;
                dest.insert({N.cost,N});
                N.C-=2;
                dest.insert({N.cost,N});
            }
        }
    }

    std::cout << dist << std::endl;

}
