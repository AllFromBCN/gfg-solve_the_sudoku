#include <iostream>
#include <vector>
#include <vector>
using namespace std;
#define DE 9

bool abox[9][10];
bool arow[9][10];
bool acol[9][10];
vector<int> options[9];

void setMat(int mat[][9], int i, int j, int num, bool set)
{
    if (set)
        mat[i][j] = num;
    else mat[i][j] = 0;

    arow[i][num]=set;
    acol[j][num]=set;
    abox[(i/3)*3+(j/3)][num]=set;
}

void showmat(int mat[][9])
{
    for (int i=0; i<DE; i++)
    {
        for (int j=0; j<DE; j++)
            cout << mat[i][j] ;
        cout << endl;
    }
}
bool checkSolution(int nthRow, int nthCol, int cand)
{
    if(!arow[nthRow][cand])
        if(!acol[nthCol][cand])
            if(!abox[(nthRow/3)*3+(nthCol/3)][cand])
                return true;
    return false;
}

bool checkEmptycell(int mat[][9], int &row, int &col)
{
    for (row=0; row<DE; row++)
    {
        for (col=0; col<DE; col++)
        {
            if(mat[row][col] == 0)
                return false;
        }
    }
    return true;
}

bool solve(int mat[9][9]) {
    int row, col;

    if (checkEmptycell(mat, row, col))
        return true;

    //TIP iterator: post and pre incrementation
    vector<int>::iterator it;
    for (it=options[row].begin(); it!=options[row].end(); ++it)
    {
        if (checkSolution(row, col, *it))
        {
            setMat(mat, row, col, *it, true);
            if (solve(mat))
                return true;
            setMat(mat, row, col, *it, false);
        }
    }
}


int main() {
    int T, i, j, temp;
    cin >> T;
    while (T--)
    {
        int mat[DE][DE];
        for (i=0; i<DE; i++)
        {
            for (j=0; j<DE; j++)
            {
                abox[i][j] = false;
                arow[i][j] = false;
                acol[i][j] = false;
            }
        }

        for (i=0; i<DE; i++)
        {
            for (j=0; j<DE; j++)
            {
                cin >> temp;
                setMat(mat,i,j,temp, true);
            }
        }
        for (i=0; i<DE; i++)
        {
            for (j=1; j<10; j++)
                if (arow[i][j]==false)
                    options[i].push_back(j);
        }

        solve(mat);
        showmat(mat);

        for (i=0; i<DE; i++)
            options[i].clear();
    }
    return 0;
}