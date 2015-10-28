#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstring>
#define M 100
#define SIZE 27
using namespace std;

int n;

bool flag;

char words[M][11];

int graph[SIZE][SIZE][M];
int graphCount[SIZE][SIZE];

int check[SIZE][2];
int result[M];

int first(char *word) {
    return word[0] - 'a';
}

int last(char *word) {
    return word[strlen(word) - 1] - 'a';
}

void WORDCHAIN(int x, int cnt) {
    if (cnt == n) {
        flag = true;
        return;
    }
    int i, wordIndex;
    for (i = 0; i < SIZE; i++){
        if (graphCount[x][i] != 0) {
            wordIndex = graph[x][i][--graphCount[x][i]];
            result[cnt] = wordIndex;
            WORDCHAIN(i, cnt + 1);
        }
        if (flag) return;
    }
}

int main()
{
    int cases, i, f, l, j;
    ifstream in("input.txt");
    int start, end;
    bool fail = false;
    char word[11];
    cin >> cases;
    while (cases--) {
        for (i = 0; i<SIZE; i++){
            check[i][0] = 0;
            check[i][1] = 0;
            for (j = 0; j<SIZE; j++){
                graphCount[i][j] = 0;
            }
        }
        fail = false;
        cin >> n;
        for (i = 0; i < n; i++){
            cin >> word;
            f = first(word);
            l = last(word);
            check[f][0]++;
            check[l][1]++;
            strcpy(words[i], word);
            graph[f][l][graphCount[f][l]++] = i;
        }
        start = end = -1;
        
        for (i = 0; i < SIZE; i++){
            if (check[i][0] == check[i][1] + 1) {
                if (start != -1) {
                    fail = true;
                }
                start = i;
            }
            else if (check[i][0] + 1 == check[i][1]) {
                if (end != -1) {
                    fail = true;
                }
                end = i;
            }
            else if (check[i][0] == check[i][1]) {
                continue;
            }
            else{
                fail = true;
                break;
            }
        }
        
        if (!fail) {
            flag = false;
            if (start != -1 && end != -1) {
                flag = false;
                WORDCHAIN(start, 0);
            }
            else if (start == -1 && end == -1){
                start = words[0][0] - 'a';
                WORDCHAIN(start, 0);
            }
            if (flag) {
                for (i = 0; i < n; i++){
                    cout << words[result[i]] << " ";
                }
            }
            else{
                cout << "IMPOSSIBLE";
            }
        } else if (fail) {
            cout << "IMPOSSIBLE";
        }
        cout << endl;
    }
    return 0;
}