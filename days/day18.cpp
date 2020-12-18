#include "../libraries/aoc.h"

// part 1
// ll evaluate(ll x, ll y, char oper) {
//     return oper == '+' ? x + y : x*y;
// }

// struct number {
//     vector<string> lines;
// };

// ll computeRow(string expr, int &pos) {
//     ll x,y;
//     if (expr[pos]=='(') {
//         x = computeRow(expr,++pos);
//     } else {
//         x = expr[pos] - '0';   
//     }
//     pos++;
//     while (pos<expr.size() && expr[pos]!=')') {
//         char oper = expr[pos++];
//         if (expr[pos]=='(') {
//             y = computeRow(expr,++pos);
//         } else {
//             y = expr[pos]-'0';
//         }
//         x = evaluate(x,y,oper);
//         pos++;
//     }
//     return x;
// }


// ll solve(number n) {
//     ll ans = 0;
//     int start;
//     for (string line : n.lines) {
//         start = 0;
//         ans+=computeRow(line,start);
//     }
//     return ans;
// }

// int main() {
//     freopen("inputs/big.txt","r",stdin);
//     number n;
//     string input,tmp,operands;
//     while (getline(cin,input)) {
//         istringstream s(input);
//         operands = "(";
//         while (getline(s,tmp,' ')) {
//             operands+=tmp;
//         }
//         operands+=")";
//         n.lines.push_back(operands);
//     }
//     int start = 0;
//     cout<<solve(n)<<endl;
//     return 0;
// }

// part 2
ll evaluate(ll x, ll y, char oper) {
    return oper == '+' ? x + y : x*y;
}

struct number {
    vector<string> lines;
};

ll computeRow(string expr, bool prec) {
    stack<char> operatorStack;
    stack<ll> operandStack;
    ll a, b;
    for (char oper : expr) {
        if (isdigit(oper)) {
            operandStack.push(oper-'0');
        } else if (oper=='(') {
            operatorStack.push('(');
        } else if (oper==')') {
            while (!operatorStack.empty() && operatorStack.top()!='(') {
                a = operandStack.top();
                operandStack.pop();
                b = operandStack.top();
                operandStack.pop();
                operandStack.push(evaluate(a,b,operatorStack.top()));
                operatorStack.pop();
            }
            operatorStack.pop();
        } else if (oper == '+' || oper=='*') {
            while (!operatorStack.empty() && operatorStack.top() != '(' && (!prec || prec && oper=='*' && operatorStack.top()=='+')) {
                a = operandStack.top();
                operandStack.pop();
                b = operandStack.top();
                operandStack.pop();
                operandStack.push(evaluate(a,b,operatorStack.top()));
                operatorStack.pop();
            }
            operatorStack.push(oper);
        }
    }
    return operandStack.top();
}


ll solve(number n,bool prec) {
    ll ans = 0;
    for (string line : n.lines) {
        ans+=computeRow(line,prec);
    }
    return ans;
}

int main() {
    freopen("inputs/big.txt","r",stdin);
    number n;
    string input,tmp,operands;
    while (getline(cin,input)) {
        istringstream s(input);
        operands = "(";
        while (getline(s,tmp,' ')) {
            operands+=tmp;
        }
        operands+=")";
        n.lines.push_back(operands);
    }
    int start = 0;
    // part 1
    cout<<solve(n,false)<<endl;
    // part 2
    cout<<solve(n,true)<<endl;
    return 0;
}