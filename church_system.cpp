#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using std::cout;
using std::cin;

// make more secure? all of it is public..
struct Person
{
  int age, years_a_member;
  int num_children;
  double tithes;

  std::string name, status;
  std::string martial_status;
  std::string affiliation;

  std::vector<std::pair<std::string, int> > children;
};

struct last_name_sort
{
  bool operator()(const std::string& lhs, const std::string& rhs) const
  { 
    std::string lhs_end = lhs.substr(lhs.find(' ') + 1), rhs_end = rhs.substr(rhs.find(' ') + 1);
    return (lhs_end == rhs_end) ? lhs < rhs : lhs_end < rhs_end; 
  }
};

//data formation:
const std::string format = "name,age,years_a_member,num_children,status,martial_status,affiliation,children,tithes";

int init(std::string filename, std::unordered_map<std::string, Person>& roster)
{
  cout << "Retrieving data...\n" << '\n';

  std::ifstream infile(filename);

  if (!infile.is_open())
  {
    cout << "Error: " << filename << " could not open. Quit and try again.\n";
    cout << "Please run this program with a valid .csv file.\n";
    return -1;
  }

  std::string temp;
  Person person;
  int k = 0;

  while(getline(infile, temp))
  {
    if (k == 0)
    {
      ++k;
      continue;
    }
    
    std::vector<std::string> data;
    std::stringstream ss(temp);
    std::string word;

    while (getline(ss, word, ','))
      data.push_back(word);

    for (int i = 0; i < data.size(); i++)
    {
      switch (i)
      {
        case 0:
          person.name = data[i];
          break;
        case 1:
          person.age = std::stoi(data[i]);
          break;
        case 2:
          person.years_a_member = std::stoi(data[i]);
          break;
        case 3:
          person.num_children = std::stoi(data[i]);
          break;
        case 4:
          person.status = data[i];
          break;
        case 5:
          person.martial_status = data[i];
          break;
        case 6:
          person.affiliation = data[i];
          break;
        case 7:
        {
          int prev = -1, age, pos;
          std::string child;

          if (person.num_children > 1)
          {

            for (int j = 0; j < data[i].length(); j++)
            {
              if (data[i][j] == '_')
                pos = j;

              if (data[i][j] == '|' || j == data[i].length() - 1)
              {
                if (prev == -1)
                {
                  child = data[i].substr(0, pos);
                  age = std::stoi(data[i].substr(pos + 1, j));
                  person.children.push_back(std::make_pair(child, age));
                  prev = j;
                }
                else
                {
                  child = data[i].substr(prev + 1, pos - prev - 1);
                  age = std::stoi(data[i].substr(pos + 1, j));
                  person.children.push_back(std::make_pair(child, age));
                  prev = j;
                }
              }
            }
          }
          else if (person.num_children == 1)
          {
            pos = data[i].find('_');
            child = data[i].substr(0, pos);
            age = std::stoi(data[i].substr(pos + 1));
            person.children.push_back(std::make_pair(child, age));
          }
          break;
        }
        case 8:
          person.tithes = std::stod(data[i]);
          break;
        default: break;
      }
    }

    roster[person.name] = person;
  }
  
  infile.close();
  return 1;
}

void save(std::string filename, std::unordered_map<std::string, Person>& roster)
{
  cout << "Saving roster...\n";

  if (filename != "error.csv")
  {
    std::ofstream outfile(filename);

    if (!outfile.is_open())
    {
      cout << "Error: " << filename << " could not open.\n";
      return;
    }

    outfile << format << '\n';

    for (auto const& [name, person] : roster)
    {
      outfile << name << ',' << person.age << ',';
      outfile << person.years_a_member << ',' << person.num_children << ',';
      outfile << person.status << ',' << person.martial_status << ',';
      outfile << person.affiliation << ',';

      if (person.num_children >= 1)
      {
        for (int i = 0; i < person.num_children; i++)
          if (i + 1 != person.num_children)
            outfile << person.children[i].first << '_' << person.children[i].second << '|';
          else
            outfile << person.children[i].first << '_' << person.children[i].second;
      }
      else
        outfile << "none_0";

      outfile << ',' << person.tithes << '\n';
    }

    outfile.close();
  }
  else
  {
    cout << "Program initlized with an error. No changes made or saved.\n";
    cout << "Closing...\n";
    return;
  }


  cout << "Saved roster. Closing..." << '\n';
}

std::string add_string(std::string prompt, int pick = 0)
{
  std:: string t;
  bool verify = false;

  if (pick == 1) // string data
  {
    do
    {
      cout << prompt;
      getline(cin >> std::ws, t);

      int n = t.length(), i = 0;

      while (i < n)
      {
        while (i < n && t[i] == ' ' || t[i] == '-')
          ++i;

        if (isdigit(t[i]) || !isalpha(t[i]))
        {
          verify = true;
          break;
        }

        i++;
      }

      if (verify)
        cout << '\n';

    } while (verify);
  }
  else // number data
  {
    do
    {
      cout << prompt;
      getline(cin >> std::ws, t);
      int n = t.length(), i = 0;

      while (i < n)
      {
        while (i < n && t[i] == '.')
          ++i;
        
        if (!isdigit(t[i]) || isalpha(t[i]))
        {
          verify = true;
          break;
        }

        i++;
      }

      if (verify)
        cout << '\n';

    } while (verify);
  }

  return t;
}

void add(std::unordered_map<std::string, Person>& roster)
{
  // in the future add the option for adding a child?
  // use regex to verify instead?
  Person temp;

  temp.name = add_string("Name: ", 1);
  temp.status = add_string("Status: ", 1);
  temp.martial_status = add_string("Marital status: ", 1);
  temp.affiliation = add_string("Affiliation: ", 1);

  temp.age = std::stoi(add_string("Age: "));
  temp.years_a_member = std::stoi(add_string("Years a member: "));
  temp.num_children = std::stoi(add_string("Number of children: "));

  if (temp.num_children >= 1)
  {
    std::pair<std::string, int> child;
    for (int i = 0; i < temp.num_children; i++)
    {
      child.first = add_string("Child name: ", 1);
      child.second = std::stoi(add_string("Child age: "));
      temp.children.push_back(child);
    }
  }

  temp.tithes = std::stod(add_string("Tithes $: "));
  cout << "Successfully added!\n\n";
  roster[temp.name] = temp;
}

void remove(std::unordered_map<std::string, Person>& roster, char option = 's', std::string nname = "")
{
  if (option == 'e' && roster.count(nname))
  {
    roster.erase(nname);
    return;
  }

  std::string name = add_string("Enter name: ", 1);

  if (option == 's' && roster.count(name))
    roster.erase(name);
  else
    cout << "ERROR: " << name << " not found. Cannot remove.\n";
}

void display(Person person)
{
  cout << '\n' << person.name << ' ' << person.age << " years old\n";
  cout << "Currently a " << person.status << " of the church and is " << person.martial_status << " tithes: $" << person.tithes << '\n';
  cout << "A member of: " << person.affiliation << " for " << person.years_a_member << " years\n";
  cout << "Number of children: " << person.num_children << '\n';

  if (person.num_children != 0)
  {
    for(auto& child : person.children)
      cout << child.first << " is " << child.second << " years old\n";
  }

  cout << '\n';
}

void searchAndEdit(std::unordered_map<std::string, Person>& roster)
{
  std::string str = add_string("Enter name: ", 1), str2;

  if (roster.count(str))
  {
    display(roster[str]);
    cout << "What do you want to edit?\n";
    cout << "1. Name\n2. Age\n3. None\n";

    cin >> str2;

    switch (str2[0])
    {
      case '1':
      {
        std::string new_name = add_string("New name: ", 1);
        roster[new_name] = roster[str];
        roster[new_name].name = new_name;
        remove(roster, 'e', str);
        break;
      }
      case '2':
        roster[str].age = std::stoi(add_string("New age: "));
        break;
      default:
        break;
    }
  }
  else
  {
    cout << "ERROR: " << str << " not in the roster\n";
  }

  cout << '\n';
}

void view(std::unordered_map<std::string, Person>& roster)
{
  // In the future ask for display method like 'last name alphabetical'
  std::string str;
  cout << "Sort by:\n1. No Sorting\n2. First Name\n3. Last Name\n";
  getline(cin >> std::ws, str);

  switch(str[0])
  {
    case '1':
    {
      for (auto const& [name, person] : roster)
        cout << name << ' ' << person.age << '\n';
      break;
    }
    case '2':
    {
      std::map<std::string, Person> temp2(roster.begin(), roster.end());

      for (auto const& [name, person] : temp2)
        cout << name <<' ' << person.age << '\n';
      break;
    }
    case '3':
    {
      std::map<std::string, Person, last_name_sort> temp(roster.begin(), roster.end(), last_name_sort());

      for (auto const& [name, person] : temp)
        cout << name <<' ' << person.age << '\n';
      break;
    }
    default:
    break;
  }

  cout << '\n';
}

/**
 * @brief Main function for the Church Roster System.
 *
 * This function is the entry point for the Church Roster System.
 * It initializes the church roster from a CSV file, prompts the user to choose an action, and then performs the chosen action on the roster.
 * Finally, the function saves the updated roster to a CSV file.
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments themselves. 
 * @return An integer exit code.
 */
int main(int argc, char* argv[])
{
  std::unordered_map<std::string, Person> roster;
  std::string choice;

  int status = init(argc > 1 ? argv[1] : "error.csv", roster);
  if (status == -1) return -1;

  do
  {
    cout << "Church Roster System\n";
    cout << "1. Add a person to the roster\n2. Remove a person from the roster\n3. Search and Edit a person in the roster\n4. View entire roster\n5. Quit\nPick an option to get started:\n";

    cin.clear();
    getline(cin >> std::ws, choice);

    if (choice.length() > 1)
    {
      do
      {
        cout << "Enter a number between 1 and 5.\n";
        getline(cin, choice);
      } while (choice.length() != 1);
    }

    switch (choice[0])
    {
      case '1':
        add(roster);
        break;
      case '2':
        remove(roster);
        break;
      case '3':
        searchAndEdit(roster);
        break;
      case '4':
        view(roster);
        break;
      case '5':
        break;
    }
  } while (1 && choice[0] != '5');

  save(argc > 1 ? argv[1] : "error.csv", roster);

  return 0;
}