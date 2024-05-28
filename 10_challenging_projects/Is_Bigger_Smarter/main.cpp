#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using std::cout;
using std::cin;

struct comp
{
    bool operator() (const int& lhs, const int& rhs) const
    { return lhs > rhs; }
};


int main(int argc, char* argv[])
{
    std::map<int, std::priority_queue<int, std::vector<int>, std::greater<int>>, comp> mp;
    std::unordered_map<int, int> nline;
    
    auto run_case = [&]() -> void
    {
      auto it = mp.begin();
      int line, kg;

      std::array<int, 3> prev = { it->second.top(), nline[it->first], it->first };
      cout << prev[2] << " " << prev[0] << '\n';
      ++it;

      for (; it!= mp.end(); ++it)
      {
        line = nline[it->first];
        kg = it->second.top();

        if (line > prev[1] && kg > prev[0])
        {
          prev = { it->second.top(), line, it->first };
          cout << prev[2] << " " << kg << '\n';
        }
        else if(line > prev[1] && it->second.size() > 1)
        {
          while(!it->second.empty() && it->second.top() < prev[0])
            it->second.pop();

          if (!it->second.empty())
          {
            prev = { it->second.top(), line, it->first };
            cout << prev[2] << " " << kg << '\n';
          }
        }
      }

      auto last_try = mp.find(prev[2]);
      ++last_try;
      kg = last_try->second.top();

      if (kg > prev[0])
        cout << last_try->first << " " << kg << '\n';
    };

    std::ifstream ifs(argv[1]);
    int iq, kg, n = 1;
    std::string data;

    while(getline(ifs, data))
    {
      std::stringstream ss(data);
      ss >> kg >> iq;
      
      mp[iq].push(kg);

      if (nline.count(iq))
        n++;
      else
        nline[iq] = n++;
    }

    ifs.close();
    run_case();
        
    return 0;
}