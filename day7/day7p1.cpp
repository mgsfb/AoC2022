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

struct dir {
  uint64_t size;
  std::string name;
  std::map <std::string, dir*> subs;
  std::map <std::string, uint64_t> files;
  dir* parent;
} root;


uint64_t tree_sum (dir *target) {
  uint64_t temp =0, tot =0;
  auto it = target->subs.begin();
  while (it!=target->subs.end()) {
    temp = tree_sum((*it).second);
    if (tot + temp < 100000) tot+=temp;
    it++;
  }
  if (target != target->parent) target->parent->size += target->size;
  temp = target->size < 100000 ? target->size : 0;
  return std::max(tot,temp);
}

int main ()
{
  root.parent = &root;
  root.name = "/";
  root.size = 0;

  std::ifstream is("day7.txt");
  std::string n;
  std::vector<std::string> raw;
  std::string num_stacks;

  while (std::getline(is >> std::ws, n)) {
    raw.push_back(n);
  }

  // parse
  auto it = raw.begin();
  dir *curr = &root;
  while (it!=raw.end()) {
    std::stringstream ss(*it);
    std::string dest = "";

    switch ((*it)[2]) {
      case 'c': // cd

        for (;ss>>dest; );

        if (!dest.compare("/")) curr = &root;
        else if (!dest.compare("..")) curr = curr->parent;
        else curr = curr->subs[dest];

        break;

      case 'l': //ls
        break;

      case 'r': // dir
      {
        dest = *it;
        dest = dest.substr(4,dest.size()-4);
        dir* temp = new dir;
        temp->parent = curr;
        curr->subs[dest] = temp;
        temp->name = dest;
        temp->size = 0;
      }
        break;

      default:  // add a file

        ss>>dest;
        uint64_t fsize = std::stoull(dest);
        ss>>dest;
        curr->files[dest] = fsize;
        curr->size += fsize;
        break;
    }
    it++;
  }

  std::cout << "built" << std::endl;
  uint64_t ans = tree_sum(&root);
  std::cout << "totaled:" << ans << std::endl;

  // print the tree
  uint64_t tot = 0;
  int indent =0;
  std::stack<std::pair<dir*,int>> sbdirs;
  sbdirs.push({&root,0});
  while (sbdirs.size()) {
    dir *dpt = sbdirs.top().first;
    indent = sbdirs.top().second;
    tot+= dpt-> size < 100000 ? dpt-> size : 0;
    sbdirs.pop();
    auto iit = dpt->subs.rbegin(), oit = dpt->subs.rend();
    while (iit != oit) {
      sbdirs.push({(*iit++).second,indent+1});
    }
    std::cout << std::string(indent,'\t') << " --------"[indent] << dpt->name << " --" << dpt->size << std::endl;
  }

  std::cout << tot << std::endl;
}
