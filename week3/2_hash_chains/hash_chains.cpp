#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

struct StringNode {
    string s;
    StringNode* next;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<string> elems;
    vector<StringNode*> hashTable; 


    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
        hashTable.resize(bucket_count, nullptr);
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQueryNew(const Query& query) {
        if (query.type == "check") {
            StringNode * p = hashTable[query.ind];
            while (p != nullptr) {
                std::cout << p -> s << " ";
                p = p -> next;
            }
            std::cout << "\n";
        } else {
            size_t hash = hash_func(query.s);
            StringNode * p = hashTable[hash];
            while (p != nullptr && p->s != query.s) {
                p = p -> next;
            }
            if (query.type == "find")
                writeSearchResult(p != nullptr);
            else if (query.type == "add") {
                if (p == nullptr) {
                    StringNode * newNode = new StringNode;
                    newNode -> s = query.s;
                    newNode -> next = hashTable[hash];
                    hashTable[hash] = newNode;
                }
            } else if (query.type == "del") {
                if (p != nullptr) {
                    if (hashTable[hash] -> s == query.s) {
                        StringNode * tmp =  hashTable[hash];
                        hashTable[hash] = hashTable[hash] -> next;
                        delete tmp;
                    } else {
                        StringNode * pp = hashTable[hash];
                        while (pp -> next != nullptr && pp->next->s != query.s) {
                            pp = pp->next;
                        }
                        StringNode * tmp = pp-> next;
                        pp->next = pp->next->next;
                        delete tmp;
                    }
                }
            }
        }
    }


    void processQuery(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
                if (hash_func(elems[i]) == query.ind)
                    std::cout << elems[i] << " ";
            std::cout << "\n";
        } else {
            vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != elems.end());
            else if (query.type == "add") {
                if (it == elems.end())
                    elems.push_back(query.s);
            } else if (query.type == "del") {
                if (it != elems.end())
                    elems.erase(it);
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQueryNew(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
