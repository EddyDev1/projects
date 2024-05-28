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


int main(int argc, char* argv[])
{
    std::map<int, std::array<int, 3>, std::greater<int>> mp;

    auto solve_case = [&]() -> void
    {
      auto it = mp.begin();
      int line, kg;

      std::array<int, 3> prev = { it->second[0], it->second[1], it->second[2] };
      cout << prev[2] << " " << prev[0] << '\n';
      ++it;

      for (; it!= mp.end(); ++it)
      {
        line = it->second[1];
        kg = it->second[0];

        if (line > prev[1] && kg > prev[0])
        {
          prev = { kg, line, it->second[2] };
          cout << prev[2] << " " << kg << '\n';
        }
      }

      auto last_try = mp.find(prev[2]);
      ++last_try;
      kg = last_try->second[0];

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
      
      if (mp.count(iq))
      {
        mp[iq][0] = std::min(mp[iq][0], kg);
        mp[iq][1] = mp[iq][0] == kg ? n++ : mp[iq][1];
      }
      else
        mp[iq] = { kg, n++, iq };
    }

    ifs.close();
    solve_case();
        
    return 0;
}