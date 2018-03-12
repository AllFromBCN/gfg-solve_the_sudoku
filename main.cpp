//solve the sudoku
//backtracking
#include <iostream>
#include <vector>
using namespace std;
#define DE 9

void setMat(int mat[][9], int i, int j, int num, bool set, bool arow[][10], bool acol[][10], bool abox[][10])
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
            cout << mat[i][j] << " " ;
        //cout << endl;
    }
    cout << endl;
}
bool checkSolution(int nthRow, int nthCol, int cand, bool arow[][10], bool acol[][10], bool abox[][10]) {
    return !arow[nthRow][cand] && !acol[nthCol][cand] && !abox[(nthRow / 3) * 3 + (nthCol / 3)][cand];
}

bool checkEmptycell(int mat[][9], int &row, int &col)
{
    for (row=0; row<DE; row++)
        for (col=0; col<DE; col++)
            if(mat[row][col] == 0)
                return true;
    return false;
}

bool solve(int mat[9][9], vector<int> options[], bool arow[9][10], bool acol[9][10], bool abox[9][10]) {
    int row, col;

    if (!checkEmptycell(mat, row, col)) //row and col are assigned the empty space
        return true;

    vector<int>::iterator num;

    //TIP iterator: post and pre incrementation
    for (num=options[row].begin(); num!=options[row].end(); ++num) //1,2,7,9
    {
        if (checkSolution(row, col, *num, arow, acol, abox))
        {
            setMat(mat, row, col, *num, true, arow, acol, abox);

            if (solve(mat, options, arow, acol, abox))
                return true;

            setMat(mat, row, col, *num, false, arow, acol, abox);
        }
    }
    return false;
}

int main() {
    int T;
    cin >> T;
    while (T--)
    {
        int i, j, temp;
        int mat[9][9];
        bool abox[DE][DE+1] = {{false}}; // TIP : initializing the bool array
        bool arow[DE][DE+1] = {{false}}; // TIP
        bool acol[DE][DE+1] = {{false}};
        vector<int> options[DE];

        for (i=0; i<DE; i++)
            for (j=0; j<DE; j++)
            {
                cin >> temp;  // temp == 1, ... 9
                setMat(mat, i, j, temp, true, arow, acol, abox);
            }

        for (i=0; i<DE; i++)
            for (j=1; j<10; j++)
                if (arow[i][j] == false)
                    options[i].push_back(j);

        if(solve(mat, options, arow, acol, abox))
        {
            showmat(mat);
        } else
            cout << "No possible answer" << endl;

    }
    return 0;
}

/*

 Basic Backtracking
  1. printing part
  2. checkTheSolution (returns bool)
  3. backtracking part (undo if it cannot reach the destination)
    1. starts with checking the destination
    2. if not, check the current situation
        1. if current situation fits, activate the recursive function by putting the next element
  4. For the invalid inputs, always start the btr functkion in a condition and set it to return bool value, so that if it returns false, we print an error message.

  Problem-specific
  0. Dividing a matrix into row and col may not be so important! -- unlike the NQueen prob
  1. No need to set the next element
  2. iterator of vector
    1. preincrement and postincrement : in case of postincrement, the value is copied somewhere and return the previous value as well. Therefore, for iterator, use preincrement.
    2. List and vector both have iterator.
    3. You know that you should call the value by *.
  3. Why I not LIST?
    1. was not efficient for access as an array (oneList[a][b])
    2. List may be effective for inserting and deleting (front and back); yet, retrieving vector was better

  Others
  1. "May reach the end of blah" : check the return value
 */