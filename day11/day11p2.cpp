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
    std::deque<std::string> items;
    std::string op;
    std::string modNum;
    int modDest[2];
    uint64_t insp;
};

//
bool smod (std::string dvsr, std::string mdls) {
    uint64_t currmod = 0;
    uint64_t modnum = std::stoi(mdls);
    std::string inp = dvsr + " % " + mdls + " = ";
    while (dvsr.size() > 9) {
//        std::cout << dvsr << " splits into: ";
        std::string lilmod = dvsr.substr(0,8);
        dvsr = dvsr.substr(8,dvsr.size());
//        std::cout << lilmod << ", " << dvsr << std::endl;
        uint64_t tmp = std::stoull(lilmod)%modnum;
        lilmod = std::to_string(tmp);
        dvsr = lilmod + dvsr;
    }

    currmod = std::stoull(dvsr)%modnum;
//    std::cout << dvsr << " % " << modnum << " = " << currmod << std::endl;
//    std::cout << inp << std::stoull(dvsr)%modnum << std::endl;
    return currmod == 0;
}


// add some big strangs
std::string sadd (std::string big, std::string lbig) {
    int c = 0;

    int bDex = big.size()-1;
    int lbDex = lbig.size()-1;

    std::string snew;

    while (bDex>-1 || c || lbDex>-1) {
        int b = 0;
        if (bDex >-1) {
            b = big[bDex--]-'0';
        }
        int l = c;
        if (lbDex >-1) {
            l+=lbig[lbDex--] - '0';
        }

        c= (b+l)/10;
        snew = std::to_string((b+l)%10) + snew;

    }

//    std::cout << big << " + " << lbig << " = " << snew << std::endl;
    return snew;
}

// slow, easy, elementary-school way. not karatsuba.
std::string smull (std::string s1, std::string s2) {
    int s1Dex = s1.size()-1;

    std::string accum = "";
    uint64_t tens=0,btens=0;
    while (s1Dex>-1) {
        for(int s2Dex = s2.size()-1; s2Dex > -1; s2Dex--) {
//            std::cout << s1[s1Dex] << "::" << s2[s2Dex] << std::endl;
            std::string tmp = std::to_string(((s1[s1Dex])-'0') * ((s2[s2Dex])-'0'));
            tmp += std::string(tens+btens,'0');
            tens++;
            accum = sadd(tmp,accum);
        }
        tens=0;
        btens++;
        s1Dex--;
    }
//    std::cout << s1 << " * " << s2 << " = " << accum << std::endl;
    return accum;
}

int main ()
{

    std::ifstream is("day11test.txt");
    std::string n;
    std::vector<std::string> raw;
    int maxMnky = 0;

    while (std::getline(is >> std::ws, n)) {
        raw.push_back(n);
        if (n[0]=='M') maxMnky++;
    }

    mnky Mnkys[maxMnky];
    int mnkyDex=0;
    auto it = raw.begin();
    while (it!= raw.end()) {
        Mnkys[mnkyDex].insp = 0;
        it++; // starting items
        std::stringstream ss(*it);
        std::string item;
        ss >> item; ss>>item;
        while (ss>>item) {  // lil-endian
            while(item.back()==',') item.pop_back();
            Mnkys[mnkyDex].items.push_back(item);
        }
        it++; // operation
        item =*it;
        item = item.substr(21);
        Mnkys[mnkyDex].op = item;
        it++;
        item = *it;
        item = item.substr(19);
        Mnkys[mnkyDex].modNum = item;
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

    for (int i=1;i!=1001;++i) {
        std::cout << "round " << i << " -------------------" << std::endl;
        for (int m=0;m!=maxMnky;++m) {
//            std::cout << "monkey " << m << std::endl;
            while (Mnkys[m].items.size()) {
                std::string wlvl = Mnkys[m].items.front();
//                std::cout << "item: " << wlvl << std::endl;
                Mnkys[m].items.pop_front();
                std::string tmp = Mnkys[m].op.substr(2);

                switch (Mnkys[m].op[0]) {
                    default:
                        break;

                    case '+':
                        wlvl = sadd(wlvl,tmp);
                        break;

                    case '*':
                        if (tmp[0]=='o') {
                            wlvl = smull(wlvl,wlvl);
                        } else {
                            wlvl = smull(wlvl,tmp);
                        }
                        break;
                }

                bool modd = smod(wlvl,Mnkys[m].modNum);
                Mnkys[Mnkys[m].modDest[modd]].items.push_back(wlvl);
                Mnkys[m].insp++;
            }
            std::cout << std::endl;
        }
    }

    std::vector<uint64_t> insp;
    for (auto M:Mnkys) {
        insp.push_back(M.insp);
        std::cout << M.insp << "   ";
    }
    std::cout << std::endl;
    std::sort(insp.begin(),insp.end(),std::greater<uint64_t>());

    std::cout << insp[0] * insp[1] << std::endl;
    return 0;
}
