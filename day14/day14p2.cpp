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

struct rockPt {int R, C;};

// 1 landed, -1 done, -2 blocked
int DropSand (std::vector<std::vector<int>> &board, int R, int C)
{

    if (R >= board.size() || C>=board[0].size() || C < 0) return -1; //
    if (board[R][C] != 0) return -2;

    int landed = DropSand(board,R+1,C);

    if (landed == -2) landed = DropSand(board,R+1,C-1);
    else if (landed==-1) return -1;

    if (landed == -2) landed = DropSand(board,R+1,C+1);
    else if (landed==-1) return -1;

    if (landed == 1 || landed ==-1) return landed;

    board[R][C]=1;
    return 1;
}

int main ()
{
    std::ifstream is("day14.txt");
    std::string n;
    std::vector<std::vector<rockPt>> rockPts;

    const int Rmargin = 100;
    int minR = 1000, minC=1000, maxR = 0, maxC = 0;
    int sR = 0, sC=500;


    while (std::getline(is >> std::ws, n)) {
        std::stringstream ss(n);
        rockPt tPt;
        std::string tmpStr = "";
        std::vector<rockPt> tvPts;
        while (std::getline(ss >> std::ws, tmpStr, '>')) {
            if (tmpStr.back() == '-') tmpStr=tmpStr.substr(0,tmpStr.size()-1);
            tPt.C = std::stoi(tmpStr.substr(0,3));
            tPt.R = std::stoi(tmpStr.substr(4,tmpStr.size()));
            minR = std::min(tPt.R,minR);
            minC = std::min(tPt.C,minC);
            maxR = std::max(maxR,tPt.R);
            maxC = std::max(maxC,tPt.C);
            tvPts.push_back(tPt);

        }
        rockPts.push_back(tvPts);
    }

    //normalize

    std::cout << "C range: " << minC <<", " << maxC << "  R range: " << minR << ", " << maxR << std::endl;

    // build the board... 0 is open, otherwise blocked.
    std::vector<std::vector<int>> board (maxR+2, std::vector<int>(maxC*2,0));

    rockPt in,out;
    for (auto const &rptR:rockPts) {
        out = rptR[0];
        for (int ptDex=1;ptDex!=rptR.size();++ptDex) {
            std::swap(in,out);
            out = rptR[ptDex];

            std::cout << in.R << ", " << in.C << " to " << out.R << ", " << out.C << std::endl;

            int dC = in.C - out.C;

            switch(dC) {
                default: // changing C
                    for (int C=std::min(in.C,out.C); C<=std::max(in.C,out.C); ++C) {
                        int R = in.R;
                        board[R][C] = 1;
                    }
                    break;

                case 0: // changing R
                    for (int R=std::min(in.R,out.R);R<=std::max(in.R,out.R); ++R) {
                        int C = in.C;
                        board[R][C] = 1;
                    }
                    break;
            }
        }
        std::cout << std::endl;
    }

    std::vector<int> floor (board[0].size(),1);
    board.push_back(floor);

    std::cout << sC << std::endl;

    for (auto br:board) {
        for (auto bc:br) {
            std::cout << bc;
        }
        std::cout << std::endl;
    }

    int sands = 0;
    bool full = false;
    int rslt =0;
    while (!full) {
        rslt = DropSand (board,sR,sC);
        switch (rslt) {
            default:
                full = true;
                break;

            case 1:
                sands++;
                break;
        }
    }

    std::cout << sands << "   " << rslt << std::endl;

    return 0;
}
