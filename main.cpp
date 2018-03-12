#include <iostream>
#include <vector>
#include <vector>
using namespace std;
#define DE 9

bool box[9][10];
bool row[9][10];
//bool col[9][10];
vector<int> emptySpace[9];
vector<int> options[9];

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
    //row
    if(!row[nthRow][cand])
    {
        //col
        //if(!col[nthCol][cand])
        {
            //box
            if(!box[(nthRow/3)*3+(nthCol/3)][cand])
            {
                //cout << "@ " << nthRow << "," << nthCol<< ":" << cand << endl;
                return true;
            }
        }
    }
    return false;
}


bool solve(int mat[9][9], int nthRow, int nthEmpty) {

    for (int l=0; l<9; l++)
        cout << mat[nthRow][l];
    cout << endl;

    if (nthEmpty == emptySpace[nthRow].size())
    {
        cout << "FOUND" << endl;
        return true;
    }
    //TIP iterator: post and pre incrementation
    int curCol = emptySpace[nthRow][nthEmpty];

    vector<int>::iterator it;
    for (it=options[nthRow].begin(); it!=options[nthRow].end(); ++it)
    {
        if(checkSolution(nthRow, emptySpace[nthRow][nthEmpty], *it))
        {
            mat[nthRow][curCol] = *it;
            row[nthRow][*it] = true;
            box[(nthRow/3)*3+(curCol/3)][*it] = true;

            if (solve(mat, nthRow, nthEmpty+1))
                return true;

            mat[nthRow][curCol] = 0;
            row[nthRow][*it] = false;
            box[(nthRow/3)*3+(curCol/3)][*it] = false;
            return false; // TIP
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
                box[i][j] = false;
                row[i][j] = false;
                //col[i][j] = false;
            }
        }

        for (i=0; i<DE; i++)
        {
            for (j=0; j<DE; j++)
            {
                cin >> temp;
                mat[i][j] = temp;
                if(temp==0)
                    emptySpace[i].push_back(j);

                row[i][temp]=true;
                //col[j][temp]=true;
                box[(i/3)*3+(j/3)][temp]=true;
            }
        }
        for (i=0; i<DE; i++)
        {
            for (j=1; j<10; j++)
                if (row[i][j]==false)
                    options[i].push_back(j);
            /*
            list<int>::iterator it;
            cout << "options..." <<endl;
            for (it=emptySpace[i].begin(); it!=emptySpace[i].end(); ++it)
                cout << *it;
            cout<< endl;
             */

        }
        cout << emptySpace[0].back() << endl;

        for (i=0; i<DE; i++)
        {
            solve(mat, i, 0);
            cout << endl;
        }

        showmat(mat);
    }
    return 0;
}