#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <regex>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <array>
#include <bitset>
#define rep(i,n) for (i = 0; i < n; ++i) 
#define REP(i,k,n) for (i = k; i <= n; ++i) 
#define REPR(i,k,n) for (i = k; i >= n; --i)
#define pb push_back
#define all(a) a.begin(), a.end()
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define ll long long 
#define uint unsigned long long
#define inf 0x3f3f3f3f3f3f3f3f
#define mxl INT64_MAX
#define mnl INT64_MIN
#define mx INT32_MAX
#define mn INT32_MIN
#define endl '\n'
using namespace std;

ll mod (ll a, ll b) {
    return (a % b + b) %b;
}

// // This checks that the matrices are equivalent to each other. 
// bool isNotChanged(vector<vector<char>>& M1, vector<vector<char>>& M2) {
//     int R = M1.size(), C = M2.size();
//     int count = 0;
//     int totalCells = 0;
//     for (int r = 0;r<R;r++) {
//         for (int c = 0;c<C;c++) {
//             totalCells++;
//             if (M1[r][c] == M2[r][c]) {
//                 count++;
//             }
//         }
//     }
//     return count==totalCells;
// }

// void searchSeats(vector<vector<char>>& M) {
//     int R = M.size(), C= M[0].size();
//     for (int r = 0;r<R;r++) {
//         for (int c = 0;c<C;c++) {
//             if (M[r][c]=='.') {
//                 continue;
//             }
//             int cntOccupied = 0;
//             for (pair<int,int> pa : dirs) {
                
//             }
//         }
//     }
// }


// int main() { 
//     vector<pair<ll,ll>> dirs = {{1,0},{0,1},{-1,0},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}};
//     freopen("inputDay11.txt","r",stdin);
//     string x;
//     vector<vector<char>> M;
//     ll r = 0;
//     while (getline(cin,x)) {        
//         M.push_back(vector<char>{});
//         for (int i = 0;i<x.size();i++) {
//             M[r].push_back(x[i]);
//         }
//         r++;
//     }
//     ll R = M.size(), C = M[0].size();
//     vector<vector<char>> MM = M;
//     for (int i = 0;i<100;i++) {
//         for (int r = 0;r<R;r++) {
//             for (int c = 0;c<C;c++) {
//                 if (M[r][c]=='.') {
//                     continue;
//                 }
//                 ll cntOccupied = 0;
//                 ll cntFloor = 0;
//                 for (pair<ll,ll> pa : dirs) {
//                     ll dx= pa.first;
//                     ll dy = pa.second;
//                     ll x = r;
//                     ll y = c;
//                     bool occupied = false;
//                     while (x>=0 && x<R && y>=0 && y<C && M[x][y]=='.') {
//                         if (M[x][y]=='#') {
//                             occupied = true;
//                         }
//                         x+=dx;
//                         y+=dy;
//                     }
//                     if (occupied) {
//                         cntOccupied++;
//                     }
//                 }   
//                 if (M[r][c]=='L' && cntOccupied==0) {
//                     MM[r][c] = '#';
//                 } else if (M[r][c]=='#' && cntOccupied>=5) {
//                     MM[r][c] = 'L';
//                 }
//             }
//         }
//         if (isNotChanged(M, MM)) {
//             break;
//         }
//         M = MM;
//     }
    
//     ll res = 0;
//     for (int r = 0;r<R;r++) {
//         for (int c = 0;c<C;c++) {
//             if (M[r][c]=='#') {
//                 res++;
//             }
//         }
//     }
//     cout<<res<<endl;
//     return 0;
// }

int main() {

    freopen("inputDay13.txt","r",stdin);
    string buses;
    cin >>buses;
    istringstream s(buses);
    string bus;
    vector<vector<ll>> times;
    int offset = -1;

    while (getline(s,bus,',')) {
        offset++;
        if (bus=="x") {
            continue;
        } 
        ll val = stoi(bus);
        times.push_back({val,offset});
    }
    cout<<solve(times)<<endl;
    return 0;
}