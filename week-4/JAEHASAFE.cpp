#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

vector<int> getPiTable(string str) {
    int length = str.size();
    vector<int> pi(length, 0);
    int begin = 1;
    int matched = 0;
    while (begin + matched < length){
        if (str[begin + matched] == str[matched]){
            matched++;
            pi[begin + matched - 1] = matched;
        }
        else{
            if (matched == 0){
                begin++;
            }
            else{
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    return pi;
}

int kmp(string H, string N){
    int n = H.size(), m = N.size();
    vector<int> pi = getPiTable(N);
    int begin = 0, matched = 0;
    while (begin <= n - m){
        if (matched < m && H[begin + matched] == N[matched]){
            matched++;
            if (matched == m)return begin;
        }
        else{
            if (matched == 0)
                begin++;
            else{
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    return -1;
}

int JAEHASAFE(vector<string> &deals) {
    bool turn = false;
    int result = 0;
    for (int i = 1; i < deals.size(); i ++){
        if (turn) {
            result += kmp(deals[i-1]+deals[i-1], deals[i]);
            turn = false;
        }else{
            result += kmp(deals[i]+deals[i], deals[i-1]);
            turn = true;
        }
    }
    return result;
}

int main()
{
    int cases;
    int i;
    int n;
    string deal;
    vector<string> deals;
    cin >> cases;
    while (cases--){
        cin >> n;
        for (i = 0; i < n + 1; i++){
            cin >> deal;
            deals.push_back(deal);
        }
        cout << JAEHASAFE(deals) << endl;
        deals.clear();
    }
    return 0;
}