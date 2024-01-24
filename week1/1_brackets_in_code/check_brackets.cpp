#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    int result = -1;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            opening_brackets_stack.push(Bracket(next, position));
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if (opening_brackets_stack.empty()) {
                result = position;
                break;
            }
            Bracket &top = opening_brackets_stack.top();
            opening_brackets_stack.pop();
            if (!top.Matchc(next)) {
                result = position;
                break;
            }
        }
    }

    if (result == -1) {
        while (!opening_brackets_stack.empty()) {
            result = opening_brackets_stack.top().position;
            opening_brackets_stack.pop();
        }
    }

    if (result == -1) {
        std::cout << "Success";
    } else {
        std::cout << result + 1;
    }
    

    // Printing answer, write your code here

    return 0;
}
