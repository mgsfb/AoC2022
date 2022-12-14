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


struct mnky {
    std::deque<uint64_t> items;
    std::string op;
    int modNum;
    int modDest[2];
    uint64_t insp;
};


int main ()
{

    std::ifstream is("day11.txt");
    std::string n;
    std::vector<std::string> raw;
    int maxMnky = 0;

    while (std::getline(is >> std::ws, n)) {
        raw.push_back(n);
        if (n[0]=='M') maxMnky++;
    }

    uint64_t modredux = 1;
    mnky Mnkys[maxMnky];
    int mnkyDex=0;
    auto it = raw.begin();
    while (it!= raw.end()) {
        Mnkys[mnkyDex].insp = 0;
        it++; // starting items
        std::stringstream ss(*it);
        std::string item;
        ss >> item; ss>>item;
        while (ss>>item) Mnkys[mnkyDex].items.push_back(std::stoi(item));
        it++; // operation
        item =*it;
        item = item.substr(21);
        std::cout << item << std::endl;
        Mnkys[mnkyDex].op = item;
        it++;
        item = *it;
        item = item.substr(19);
        Mnkys[mnkyDex].modNum = std::stoi(item);
        modredux *= Mnkys[mnkyDex].modNum;
        it++;
        item= *it;
        item = item.substr(25);
        Mnkys[mnkyDex].modDest[1] = std::stoi(item);
        it++;
        item= *it;
        item = item.substr(26);
        Mnkys[mnkyDex++].modDest[0] = std::stoi(item);
        it++; // new monkey
    }

    for (int i=1;i!=10001;++i) {
        for (int m=0;m!=maxMnky;++m) {
            Mnkys[m].insp+= Mnkys[m].items.size();
            while (Mnkys[m].items.size()) {
                uint64_t wlvl = Mnkys[m].items.front();
                Mnkys[m].items.pop_front();
                std::string tmp = Mnkys[m].op.substr(2);

                switch (Mnkys[m].op[0]) {
                    default:
                        break;

                    case '+':
                        wlvl += std::stoi(tmp);
                        break;

                    case '*':
                        if (tmp[0]=='o') wlvl*=wlvl;
                        else wlvl *= std::stoi(tmp);
                        break;
                }
                wlvl %= modredux;
                Mnkys[Mnkys[m].modDest[(wlvl % Mnkys[m].modNum == 0)]].items.push_back(wlvl);
            }
        }
    }

    std::vector<uint64_t> insp;
    for (auto M:Mnkys) {
        insp.push_back(M.insp);
    }
    std::sort(insp.begin(),insp.end(),std::greater<int>());

    for (auto it:insp) std::cout << it << "   ";
    std::cout << std::endl;
    std::cout << insp[0] * insp[1] << std::endl;
    return 0;
}
