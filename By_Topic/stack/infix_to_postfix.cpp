//{ Driver Code Starts
// C++ implementation to convert infix expression to postfix
#include <iostream>
#include <stack>
#include <unordered_map>

using namespace std;


// } Driver Code Ends
class Solution {
  public:

    int precedence(char c)
    {
        if (c == '^') return 5;
        if (c == '*' or c == '/') return 4;
        if (c == '+' or c == '-') return 3;
        else return -1;
    }


    bool is_operand(char c)
    {
        return ((c >= 'A' and c <= 'Z') or
            (c >= 'a' and c <= 'z'));

    }

    // Function to convert an infix expression to a postfix expression.
    string infixToPostfix(string s) {
        string ans = "";
        stack<int> stk;
        for (char c: s)
        {
            if (is_operand(c))
            {
                ans += c;
            }
            else if (c == '(')
            {
                stk.push(c);
            }
            else if (c == ')')
            {
                while (!stk.empty() and stk.top() != '(')
                {
                    ans += stk.top();
                    stk.pop();
                }
                stk.pop();
            }
            else
            {
                while (!stk.empty() and precedence(c) <= precedence(stk.top()))
                {
                    ans += stk.top();
                    stk.pop();
                }
                stk.push(c);
            }
        }

        while (!stk.empty()) {
            ans += stk.top();
            stk.pop();
        }

        return ans;
    }
};


//{ Driver Code Starts.
// Driver program to test above functions
int main() {
    int t;
    cin >> t;
    cin.ignore(INT_MAX, '\n');
    while (t--) {
        string exp;
        cin >> exp;
        Solution ob;
        cout << ob.infixToPostfix(exp) << endl;
    }
    return 0;
}

// } Driver Code Ends