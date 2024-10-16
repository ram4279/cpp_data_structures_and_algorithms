//{ Driver Code Starts
// C++ implementation to convert infix expression to postfix
#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <type_traits>
#include <unordered_map>

using namespace std;
class sn {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> map;
        stack<int> stk;
        for (int i = nums2.size(); i >= 0; i--)
        {
            if (stk.empty())
            {
                stk.push(nums2[i]);
                map[nums2[i]] = -1;
            }
            else
            {
                while (!stk.empty() and stk.top() < nums2[i])
                {
                    stk.pop();
                }
                if (!stk.empty())
                {
                    map[nums2[i]] = stk.top();
                    stk.push(nums2[i]);
                }
                else
                {
                    map[nums2[i]] = -1;
                }
            }
        }

        vector<int> result;
        for (int i = 0; i < nums1.size(); i++)
        {
            result.push_back(map[nums1[i]]);
        }

        return result;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

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
            (c >= 'a' and c <= 'z') or 
            (c >= '0' and c <= '9'));
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

    string infixToPrefix(string s) {
        reverse(s.begin(), s.end());
        string ans = "";
        stack<int> stk;
        for (char c: s)
        {
            if (is_operand(c))
            {
                ans += c;
            }
            else if (c == ')')
            {
                stk.push(c);
            }
            else if (c == '(')
            {
                while (!stk.empty() and stk.top() != ')')
                {
                    ans += stk.top();
                    stk.pop();
                }
                stk.pop();
            }
            else
            {
                if (c == '^')
                {
                    while (!stk.empty() and precedence(c) <= precedence(stk.top()))
                    {
                        ans += stk.top();
                        stk.pop();
                    }
                    stk.push(c);
                }
                else
                {
                    while (!stk.empty() and precedence(c) < precedence(stk.top()))
                    {
                        ans += stk.top();
                        stk.pop();
                    }
                    stk.push(c);
                }
            }
        }

        while (!stk.empty()) {
            ans += stk.top();
            stk.pop();
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }

    string postToInfix(string exp) {
        stack<string> stk;
        for (char c: exp)
        {
            if (is_operand(c))
            {
                stk.push(string(1,c));
            }
            else
            {
                string second = stk.top(); stk.pop();
                string first = stk.top(); stk.pop();
                string ans = "(" + first + string(1,c) + second + ")";
                stk.push(ans);
            }
        }
        return stk.top();
    }

    string preToInfix(string pre_exp) 
    {
        stack<string> stk;
        int size = pre_exp.size();
        for (int i = size - 1; i >= 0; i--)
        {
            char c = pre_exp[i];
            if (is_operand(c))
            {
                stk.push(string(1,c));
            }
            else
            {
                string first = stk.top(); stk.pop();
                string second = stk.top(); stk.pop();
                stk.push("(" + first + string(1,c) + second + ")");
            }
        }
        return stk.top();
    }

    string postToPre(string post_exp)
    {
        stack<string> stk;
        for (char c: post_exp)
        {
            if (is_operand(c))
            {
                stk.push(string(1,c));
            }
            else
            {
                string second = stk.top(); stk.pop();
                string first = stk.top(); stk.pop();
                stk.push(string(1,c) + first + second);
            }
        }
        return stk.top();
    }

    string preToPost(string pre_exp)
    {
        stack<string> stk;
        int size = pre_exp.size();
        for (int i = size - 1; i >= 0; i--)
        {
            char c = pre_exp[i];
            if (is_operand(c))
            {
                stk.push(string(1,c));
            }
            else
            {
                string first = stk.top(); stk.pop();
                string second = stk.top(); stk.pop();
                stk.push(first + second + string(1,c));
            }
        }
        return stk.top();
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
        // cout << ob.infixToPrefix(exp) << endl;
        // cout << ob.infixToPostfix(exp) << endl;
        cout << ob.postToPre(exp) << endl;
    }
    return 0;
}

// } Driver Code Ends