#include <iostream>
#include <vector>
using namespace std;

#define N 4
vector<int> putInf;      // 每一行皇后的置放位置情况
vector<int> used(N, 0);  // 每一列只能有一个皇后，记录每一列的状态
vector<vector<int>> ans; // 存储可行方案
int curRow = 0;          // 当前待放皇后的行数
bool judgeLegalPut(int &curRow, int col)
{
    for (int i = curRow - 1; i >= 0; i--)
    {
        if (curRow - i == abs(col - putInf[i]))
        {
            return false;
        }
    }
    return true;
}

void queensAssign(int curRow)
{
    if (curRow >= N)
    {
        ans.push_back(putInf);
        return;
    }
    for (int i = 0; i < N; ++i) // i : 当前行皇后准备放的列数
    {
        if (used[i])
            continue;
        if (judgeLegalPut(curRow, i))
        {
            used[i] = true;
            putInf.push_back(i);
            queensAssign(curRow + 1);
            used[i] = false; // 撤销之前的状态
            putInf.pop_back();
        }
    }
}

void printChessBoard(vector<int> &vec)
{
    cout << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j != vec[i])
                cout << "○";
            else
                cout << "●";
        }
        cout << endl;
    }
    cout << endl;
}
int main()
{
    queensAssign(0);
    int n = 1;
    cout << N << "皇后问题,方案如下:\n"<< endl;
    for (vector<vector<int>>::iterator it = ans.begin(); it != ans.end(); it++)
    {
        cout << "第" << n++ << "种放置方案, 皇后被放于 " << endl;
        for (int i = 0; i < it->size(); i++)
        {
            cout << (*it)[i] + 1 << "  ";
        }
        cout << "列" << endl;
        cout << endl
             << "棋盘布局如下↓" << endl;
        printChessBoard(*it);
    }
    return 0;
}
