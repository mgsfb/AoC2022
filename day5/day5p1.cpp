#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>
#include <set>
#include <cstdint>
#include <bitset>
#include <algorithm>
#include <map>
#include <stack>

int main ()
{
  std::ifstream is("day5p1.txt");
  std::string n;
  std::vector<std::string> stacks_in;
  std::vector<std::string> commands;
  std::string num_stacks;

  uint32_t score =0;

  while (std::getline(is >> std::ws, n)) {
    std::cout << n << std::endl;
    if (n[0]=='[') stacks_in.push_back(n);
    else {
      num_stacks = n;
      break;
    }
  }

  while (std::getline(is >> std::ws, n)) {
    commands.push_back(n);
  }

  std::cout << commands.size() << std::endl;

  int last_stack =(*(num_stacks.end()-1))-'0';
  last_stack++;

  std::vector<std::stack<char>> stacks(last_stack+1);

  auto it = stacks_in.rbegin();
  while (it!=stacks_in.rend()) {
    std::string S = *it;
    for (int i=1;i<S.size();i+=4) {
      if (std::isalpha(S[i])) {
        stacks[(i/4)+1].push(S[i]);
      }
    }
    it++;
  }

  for (auto lngcmd: commands) {
    std::cout << lngcmd << std::endl;
    std::string tn = "";
    int cmd[3] ={0};
    int nDex=0;
    for (auto guy:lngcmd) {
      if (std::isdigit(guy)) {
        tn+=guy;
      } else if (tn.size()>0) {
        cmd[nDex++] = std::stoi(tn);
        tn = "";
      }
    }
    cmd[nDex] = std::stoi(tn);

    std::stack<char> temp;
    for (int i=0;i<cmd[0];++i) {
      std::cout << i << " ";
      temp.push(stacks[cmd[1]].top());
      stacks[cmd[1]].pop();
    }
    while (temp.size()) {
      stacks[cmd[2]].push(temp.top());
      temp.pop();
    }
  }

  for (int i=1;i!=stacks.size();++i) {
    std::cout << stacks[i].top() << " ";
  }
  std::cout << std::endl;
  return 0;
}
