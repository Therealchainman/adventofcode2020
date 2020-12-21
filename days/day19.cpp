#include "../libraries/aoc.h"

string trim(string s) {
    string ans = "";
    for (char ch : s) {
        if (ch=='"' || ch=='"') {
            continue;
        }
        ans+=ch;
    }
    return ans;
}

template<typename T>
bool isMatch(T pattern, string text) {
    if (text.size()!=pattern.size()) {
        return false;
    }
    int n = text.size();
    int i = 0;
    for (i = 0;i<n;i++) {
        if (pattern[i]!=string(1,text[i])) {
            return false;
        }
    }
    return i==n;
}

bool isNumber(const string &s) {
  return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

struct rule {
    string nameS, subR1, subR2;
    int numSubs = 1;
    int name;
    size_t sizeMax = numeric_limits<size_t>::max();
    bool isChar = false;
    string character;
    vector<string> R1, R2;

    explicit rule(string &line) {
        nameS = line.substr(0,line.find(':'));
        name = stoi(nameS);
        // start part 2
        if (name==8) {
            line = "8: 42 | 42 8";
        } else if (name==11) {
            line = "11: 42 31 | 42 11 31";
        }
        // end part 2
        size_t foundChar = line.find('"');
        if (foundChar<sizeMax) {
            isChar = true;
            character = trim(line.substr(foundChar));
            return;
        }
        size_t found = line.find(" |");
        if (found<sizeMax) {
            subR1 = line.substr(nameS.size()+2,found-nameS.size()-2);
            subR2 = line.substr(found + 3);
            numSubs++;
        } else {
            subR1 = line.substr(nameS.size()+2);
        }
        istringstream s(subR1);
        string tmp;
        while (getline(s,tmp,' ')) {
            R1.push_back(tmp);
        }
        istringstream t(subR2);
        while (getline(t,tmp,' ')) {
            R2.push_back(tmp);
        }
    }
};

struct message {
    vector<string> texts;
    map<int, rule*> rules;
};

// not using this one. 
template<typename T>
vector<T> create_copy(vector<T> const &vec) {
    vector<T> v(vec.size());
    copy(vec.begin(),vec.end(),v.begin());
    return v;
}

bool noNumbers(vector<string> vec) {
    for (string v : vec) {
        if (isNumber(v)) {
            return false;
        }
    }
    return true;
}

void printString(vector<string> t) {
    string str = "";
    for (string x : t) {
        str+=x;
    }
    
}

int solve(message m) {
    int ans = 0;
    for (string text : m.texts) {
        set<vector<string>> vis;
        cout<<text<<endl;
        vector<vector<string>> patterns;
        bool onlyChars = false;
        vector<string> start = {"0"};
        patterns.push_back(start);
        while (!onlyChars && !patterns.empty()) {
            onlyChars = true;
            vector<vector<string>> vec;
            int k = 0;
            int counter = 0;
            while (k<patterns.size()) {
                vector<string> pat = patterns[k];
                if (vis.count(pat)) {
                    patterns.erase(patterns.begin()+k);
                    continue;
                }
                vis.insert(pat);
                if (pat.size()>text.size()) {
                    patterns.erase(patterns.begin()+k);
                    continue;
                }
                if (pat.size()==text.size() && noNumbers(pat)) {
                    ans+=isMatch(pat,text);
                    patterns.erase(patterns.begin()+k);
                    continue;
                }
                k++;
                vector<vector<string>> patterns2;
                vector<string> pat2;
                patterns2.push_back(pat2);
                for (string s : pat) {
                    if (patterns2.empty()) {
                        break;
                    }
                    if (isNumber(s)) {
                        onlyChars = false;
                        int num = stoi(s);
                        rule* r = m.rules[num];
    
                        if (r->isChar) {
                            int j = 0;
                            for (int j = 0;j<patterns2.size();j++) {
                                patterns2[j].push_back(r->character);
                            }
                            continue;
                        }
                        if (r->numSubs==1) {
                            for (string s1 : r->R1) {
                                for (int i = 0;i<patterns2.size();i++) {
                                    patterns2[i].push_back(s1);
                                }
                            }
                        } else if (r->numSubs==2) {
                            vector<vector<string>> cpatterns = patterns2;
                            for (string s1 : r->R1) {
                                for (int i = 0;i<patterns2.size();i++) {
                                    patterns2[i].push_back(s1);
                                }
                            }
                            for (string s2 : r->R2) {
                                counter++;
                                for (int i =0;i<cpatterns.size();i++) {
                                    cpatterns[i].push_back(s2);
                                }
                            }
                            patterns2.insert(patterns2.end(),cpatterns.begin(),cpatterns.end());
                        }
                    } else {
                        for (int i = 0;i<patterns2.size();i++) {
                            patterns2[i].push_back(s);
                        }
                    }
                }
                vec.insert(vec.end(),patterns2.begin(),patterns2.end());
            }
            cout<<counter<<endl;
            patterns = vec;
        }
    }
    return ans;
}

int main() {
    freopen("inputs/big.txt","r",stdin);
    string input;
    message m;
    while (getline(cin,input)) {
        if (input.empty()) {
            break;
        }
        rule* r = new rule(input);
        m.rules[r->name] = r;
    }
    cout<<m.rules[0]<<endl;
    while (getline(cin,input)) {
        m.texts.push_back(input);
    }
    // part 1

    // part 2
    auto start = high_resolution_clock::now();
    cout<<solve(m)<<endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop-start);
    cout<<duration.count()<<endl;


    return 0;
}