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

    std::ifstream is("day8.txt");
    std::string n;
    std::vector<std::string> raw;
    std::string num_stacks;
    std::vector<std::vector<int>> trees;
    std::vector<std::vector<int>> vizprod;
    int maxprod =0;

    while (std::getline(is >> std::ws, n)) {
        std::vector<int> temp;
        std::vector<int> temp2;
        for (auto C:n) {
            int ttree = C - '0';
            temp.push_back(ttree);
            temp2.push_back(1);
        }
        trees.push_back(temp);
        vizprod.push_back(temp2);
    }

    // while the number increases, everyone can see. check how far away.
    // if it's the same or less
    // it resets. I should make this a function...

    for (auto R=1;R!=trees.size()-1;++R) {
        // vizL
        int C=1;
        std::vector<int> viznum(trees[0].size(),0);
        while (C < trees[0].size()-1) {
            if (trees[R][C] <= trees[R][C-1]) {
                viznum[C]=1;
            } else {
                viznum[C]+=1+viznum[C-1];
                while (C > viznum[C] && trees[R][C] > trees[R][C-viznum[C]]) viznum[C] += viznum[C-viznum[C]];
            }

            vizprod[R][C] *= viznum[C];
            std::cout << vizprod[R][C];
            C++;
        }
        std::cout << std::endl;

        // vizR
        std::fill(viznum.begin(), viznum.end(), 0);
        C=trees[0].size()-2;

        while (C > 0) { // don't need the 0 tree
            if (trees[R][C] <= trees[R][C+1]) {
                viznum[C] = 1;
            } else {
                viznum[C]+=1+viznum[C+1];
                while (trees[0].size()-1-C > viznum[C] && trees[R][C] > trees[R][C+viznum[C]]) viznum[C] += viznum[C+viznum[C]];
            }

            vizprod[R][C] *= viznum[C];
            std::cout << vizprod[R][C] << " ";
            C--;
        }
        std::cout << std::endl;
    }

    for (auto C=1;C!=trees[0].size()-1;++C) {

        // vizL
        int R=1;
        std::vector<int> viznum(trees.size(),0);
        while (R < trees.size()) {
            if (trees[R][C] <= trees[R-1][C]) {
                viznum[R]=1;
            } else {
                viznum[R]+=1+viznum[R-1];
                while (R > viznum[R] && trees[R][C] > trees[R-viznum[R]][C]) viznum[R] += viznum[R-viznum[R]];
            }

            vizprod[R][C] *= viznum[R];
            R++;
        }

        // vizR
        std::fill(viznum.begin(), viznum.end(), 0);
        R=trees.size()-2;

        while (R > 0) {
            if (trees[R][C] <= trees[R+1][C]) {
                viznum[R] = 1;
            } else {
                viznum[R]+=1+viznum[R+1];
                while (trees.size()-1-R > viznum[R] && trees[R][C] > trees[R+viznum[R]][C]) viznum[R] += viznum[R+viznum[R]];
            }

            vizprod[R][C] *= viznum[R];
            maxprod = std::max(maxprod,vizprod[R][C]);
            R--;
        }
    }

    std::cout << maxprod << std::endl;
}
