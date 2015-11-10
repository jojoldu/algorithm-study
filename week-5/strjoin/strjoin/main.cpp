//
//  main.cpp
//  strjoin
//
//  Created by 강대원 on 2015. 11. 11..
//  Copyright © 2015년 강대원. All rights reserved.
//

#include <iostream>
#include <queue>
#include <vector>

using namespace std;
struct comparator {
    bool operator()(int x, int y) {
        return x > y;
    }
};
int pop(priority_queue<int, vector<int>, comparator> *strs) {
    if (strs->empty())
        return 0;
    int val = strs->top();
    strs->pop();
    return val;
}

int main(int argc, const char * argv[]) {
    int cases, n, i, val;
    int str1, str2;
    int result;
    priority_queue<int, vector<int>, comparator> strs;
    cin >> cases;
    while (cases--) {
        cin >> n;
        result = 0;
        for (i = 0; i < n; i++) {
            cin >> val;
            strs.push(val);
        }
        for (i = 0; i < n - 1; i++) {
            str1 = pop(&strs);
            str2 = pop(&strs);
            result += str1 + str2;
            strs.push(str1+str2);
        }
        cout << result << endl;
        while (!strs.empty()) strs.pop();
    }
    return 0;
}
