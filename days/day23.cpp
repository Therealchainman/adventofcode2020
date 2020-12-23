#include "../libraries/aoc.h"

struct Cups {
    vector<ll> cups;
};

struct Game {
    Cups c;
    ll destination;
    ll indexD;
    set<ll> pickedUp;
    ll move;
    vector<ll> picked;
    ll curIndex;
};

Game g;

string playGame() {
    ll n = g.c.cups.size();
    while (g.move<100) {
        ll curCup = g.c.cups[g.curIndex];
        for (ll j = 1;j<=3;j++) {
            g.pickedUp.insert(g.c.cups[mod(g.curIndex+j,n)]);
            g.picked.push_back(g.c.cups[mod(g.curIndex+j,n)]);
        }
        for (int i = 0;i<3;i++) {
            vector<ll>::iterator it = find(g.c.cups.begin(),g.c.cups.end(),g.picked[i]);
            g.c.cups.erase(it,it+1);
        }
        assert(g.pickedUp.size()==3);
        g.destination = curCup-1==0 ? 9 : curCup-1;
        while (g.pickedUp.count(g.destination)>0) {
            g.destination--;
            if (g.destination==0) {
                g.destination=9;
            }
        }
        for (int i = 0;i<g.c.cups.size();i++) {
            if (g.destination==g.c.cups[i]) {
                g.indexD=i+1;
                break;
            }
        }
        g.indexD = mod(g.indexD,n);
        assert(g.pickedUp.count(g.destination)==0);
        assert(g.c.cups.size()==6);
        for (int i = 0;i<3;i++) {
            g.c.cups.insert(g.c.cups.begin()+g.indexD,g.picked[i]);
            g.indexD++;
            g.indexD=mod(g.indexD,n);

        }
        for (int i = 0;i<g.c.cups.size();i++) {
            if (g.c.cups[i]==curCup) {
                g.curIndex = i + 1;
                break;
            }
        }
        assert(g.c.cups.size()==9);
        g.move++;
        g.pickedUp.clear();
        g.picked.clear();
        g.curIndex=mod(g.curIndex,n);
    }
    set<ll> visited;
    ll start;
    for (start=0;start<n;start++) {
        if (g.c.cups[start]==1) {
            break;
        }
    }
    string res="";
    visited.insert(1);
    start = mod(++start,n);
    while (visited.count(g.c.cups[start])==0) {
        res+=to_string(g.c.cups[start]);
        visited.insert(g.c.cups[start]);
        start= mod(++start,n);
    }
    return res;
}

int main() {

    freopen("inputs/big.txt","r",stdin);
    string input;
    Cups c;
    getline(cin,input);
    for (char ch : input) {
        c.cups.push_back(ch-'0');
    }
    g.c=c;
    g.move=0;
    g.curIndex = 0;
    cout<<playGame()<<endl;
    return 0;
}