#include <fstream>
#include <iostream> // cout, stoi
#include <map>
#include <random> // time, srand
#include <unordered_map>
#include <vector> // vector

using std::cout;
using std::endl;
using std::cerr;

void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
  cerr << ' ' << H;
  dbg_out(T...);
}
#ifdef NEAL_DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

int main(int argc, char **argv) {
  std::ios::sync_with_stdio(false);
#ifndef NEAL_DEBUG
  std::cin.tie(nullptr);
#endif

  if(argc == 3){
    std::fstream getdict(argv[2], std::ios::in), getfile(argv[1], std::ios::in);
    std::string input, temp, inform = "", temp1;

    std::unordered_map<std::string, std::string > dict;

    while(getline(getdict, input))
      dict[input] = input;

    getdict.close();

    while(getline(getfile, input)){
      if(!dict.count(input)){
        cout<<"'"<<input<<"' is not in your dictionary";
        for(int i = 65; i < 123; i++){
          char c = i; temp = temp1 = input;
          auto it = temp.find(c);
          temp1+=c;

          if(dict.count(temp1))
            inform+="'", inform+=dict[temp1], inform+="', ";
          
          if(it != std::string::npos){
            temp.erase(temp.begin() + it);

            if(dict.count(temp))
              inform+="'", inform+=dict[temp], inform+="', ";
          }
        } 
          
        temp = temp1 = input;
        for(int i = 0; i < temp.length()-1; i++){
          char t = temp[i], tt = temp1[i];
          temp[i] = temp[i+1];
          temp[i+1] = t;
          temp1[i] = temp1[i+1];
          temp1[i+1] = tt;

          if(dict.count(temp))
            inform+="'", inform+=dict[temp], inform+="', ";
          else if(dict.count(temp1))
            inform+="'", inform+=dict[temp1], inform+="', ";
          
          temp = input;
        }

        if(inform.length() > 0)
          inform.pop_back(), inform.pop_back(), inform.append("?"), cout<<", did you mean "<<inform<<endl, inform="";
        else 
          cout<<", there are no similar words in your dictionary.\n";
      }
    }

    getfile.close();

  } else {
    cout<<"usage: ./a.out urdoc.ext dict.ext\n";
    return -1;
  }

  return 0;
}