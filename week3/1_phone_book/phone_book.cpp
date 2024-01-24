#include <iostream>
#include <string>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::cin;
using std::string;
using std::vector;

struct Query {
  string type, name;
  int number;
};

vector<Query> read_queries() {
  int n;
  cin >> n;
  vector<Query> queries(n);
  for (int i = 0; i < n; ++i) {
    cin >> queries[i].type;
    if (queries[i].type == "add")
      cin >> queries[i].number >> queries[i].name;
    else
      cin >> queries[i].number;
  }
  return queries;
}

void write_responses(const vector<string>& result) {
  for (size_t i = 0; i < result.size(); ++i) std::cout << result[i] << "\n";
}
vector<string> contacts(100000000, "");

vector<string> process_queries_new(const vector<Query>& queries) {
  vector<string> result;
  vector<string> contacts(100000000, "");

  // Keep list of all existing (i.e. not deleted yet) contacts.

  for (size_t i = 0; i < queries.size(); ++i)
    if (queries[i].type == "add") {
      contacts[queries[i].number] = (queries[i].name);
    } else if (queries[i].type == "del") {
      contacts[queries[i].number] = "";
    } else {
      string response = contacts[queries[i].number];
      if (response == "") {
        response = "not found";
      }
      result.push_back(response);
    }
  return result;
}

vector<string> process_queries(const vector<Query>& queries) {
  vector<string> result;
  // Keep list of all existing (i.e. not deleted yet) contacts.
  vector<Query> contacts;
  for (size_t i = 0; i < queries.size(); ++i)
    if (queries[i].type == "add") {
      bool was_founded = false;
      // if we already have contact with such number,
      // we should rewrite contact's name
      for (size_t j = 0; j < contacts.size(); ++j)
        if (contacts[j].number == queries[i].number) {
          contacts[j].name = queries[i].name;
          was_founded = true;
          break;
        }
      // otherwise, just add it
      if (!was_founded) contacts.push_back(queries[i]);
    } else if (queries[i].type == "del") {
      for (size_t j = 0; j < contacts.size(); ++j)
        if (contacts[j].number == queries[i].number) {
          contacts.erase(contacts.begin() + j);
          break;
        }
    } else {
      string response = "not found";
      for (size_t j = 0; j < contacts.size(); ++j)
        if (contacts[j].number == queries[i].number) {
          response = contacts[j].name;
          break;
        }
      result.push_back(response);
    }
  return result;
}

int main() {
#if defined(__unix__) || defined(__APPLE__)
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0) {
    if (rl.rlim_cur < rl.rlim_max) {
      rl.rlim_cur = rl.rlim_max;
      result = setrlimit(RLIMIT_STACK, &rl);
      if (result != 0) {
        std::cerr << "setrlimit returned result = " << result << std::endl;
      }
    }
  }

#endif

  write_responses(process_queries_new(read_queries()));
  return 0;
}
