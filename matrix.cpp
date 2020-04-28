#include "matrix.h"
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

void mat_def(Matrix& matrix_to_def, int mat_num)
{
    matrix_to_def.created = true;
    cout << "Please choose the size:\n\trow:(1~12) ";
    cin >> matrix_to_def.row;
    cout << "\tclo:(1~12) ";
    cin >> matrix_to_def.col;
    cout << "Please imput the vals:" << endl;
    for (int i = 1; i <= matrix_to_def.row; i++) {
        for (int j = 1; j <= matrix_to_def.col; j++) {
            cin >> matrix_to_def.val[i][j];
        }
    }
    cout << "Mat" << mat_num << " has been created:" << endl;
    for (int i = 1; i <= matrix_to_def.row; i++) {
        for (int j = 1; j <= matrix_to_def.col; j++) {
            cout << matrix_to_def.val[i][j] << " ";
        }
        cout << endl;
    }
}

void mat_add(Matrix& mat_l, Matrix& mat_r, Matrix& mat_ans)
{
    mat_ans.row = mat_l.row;
    mat_ans.col = mat_l.col;
    cout << "MatAns: " << endl;
    for (int i = 1; i <= mat_ans.row; i++) {
        for (int j = 1; j <= mat_ans.col; j++) {
            mat_ans.val[i][j] = mat_l.val[i][j] + mat_r.val[i][j];
            cout << mat_ans.val[i][j] << " ";
        }
        cout << endl;
    }
}

void mat_mmul(Matrix& mat_l, Matrix& mat_r, Matrix& mat_ans)
{
    mat_ans.row = mat_l.row;
    mat_ans.col = mat_r.col;
    cout << "MatAns: " << endl;
    for (int i = 1; i <= mat_ans.row; i++) {
        for (int j = 1; j <= mat_ans.col; j++) {
            int sum = 0;
            for (int k = 1; k <= mat_r.row; k++) {
                sum += mat_l.val[i][k] * mat_r.val[k][j];
            }
            mat_ans.val[i][j] = sum;
            cout << mat_ans.val[i][j] << " ";
        }
        cout << endl;
    }
}

double det(Matrix& a, int n)
{
    double sum = 0;
    if (n == 1)
        return a.val[1][1];
    if (n == 2)
        return a.val[1][1] * a.val[2][2] - a.val[1][2] * a.val[2][1];
    for (int k = 1; k <= n; k++) {
        Matrix b;
        for (int i = 2; i <= n; i++) {
            int col = 1;
            for (int j = 1; j <= n; j++) {
                if (j != k) {
                    b.val[i - 1][col++] = a.val[i][j];
                    //cout<<b[i-1][col-1]<<" ";
                }
            }
            //cout<<endl;
        }
        if (k % 2 == 0) {
            //cout<<a[1][k]*det(b,n-1)<<endl;
            sum -= a.val[1][k] * det(b, n - 1);
        } else {
            //cout<<a[1][k]*det(b,n-1)<<endl;
            sum += a.val[1][k] * det(b, n - 1);
        }
    }
    return sum;
}

void mat_inv(Matrix& mat, Matrix& mat_ans)
{
    Matrix mat_c = mat;
    for (int i = 1; i <= mat.row; i++) {
        for (int j = 1; j <= mat.col; j++) {
            Matrix mat_m;
            for (int k = 1; k <= mat.row - 1; k++) {
                for (int l = 1; l <= mat.col - 1; l++) {
                    if (k < i && l < j) {
                        mat_m.val[k][l] = mat.val[k][l];
                    } else if (k >= i && l < j) {
                        mat_m.val[k][l] = mat.val[k + 1][l];
                    } else if (k < i && l >= j) {
                        mat_m.val[k][l] = mat.val[k][l + 1];
                    } else if (k >= i && l >= j) {
                        mat_m.val[k][l] = mat.val[k + 1][l + 1];
                    }
                }
            }
            if ((i + j) % 2 == 0) {
                mat_c.val[i][j] = det(mat_m, mat.row - 1);
            } else {
                mat_c.val[i][j] = -det(mat_m, mat.row - 1);
            }
        }
    }
    double mat_det = det(mat, mat.row);
    for (int i = 1; i <= mat.row; i++) {
        for (int j = 1; j <= mat.col; j++) {
            mat_ans.val[i][j] = mat_c.val[j][i] / mat_det;
            cout << mat_ans.val[i][j] << " ";
        }
        cout << endl;
    }
}

void matrix_main()
{
    Matrix matrix[5];
    matrix[4].col = matrix[4].row = 0;
    matrix[4].created = true;
    for (int i = 0; i < 4; i++) {
        matrix[i].created = false;
    }
    string mat_line = "init";
    while (mat_line != "EXIT MAT") {
        getline(cin, mat_line);
        string word[100];
        int l = mat_line.length();
        for (int i = 0; i < 10; i++) {
            word[i].erase(0);
        }
        int j = 0;
        for (int i = 0; i < l; i++) {
            while (mat_line[i] != ' ' && i < l) {
                word[j] += mat_line[i];
                i++;
            }
            j++;
        }
        if (word[0] == "DEF") {
            int mat_num = word[1][3] - '0';
            mat_def(matrix[mat_num], mat_num);
        } else if (word[0] == "ADD") {
            int mat_num_l = word[1][3] - '0';
            int mat_num_r = word[2][3] - '0';
            if (matrix[mat_num_l].created == false) {
                cout << "Mat" << mat_num_l << "hasn't been created!";
            } else if (matrix[mat_num_r].created == false) {
                cout << "Mat" << mat_num_r << "hasn't been created!";
            } else if (matrix[mat_num_l].row != matrix[mat_num_r].row || matrix[mat_num_l].col != matrix[mat_num_r].col) {
                cout << "Size error!" << endl;
            } else {
                mat_add(matrix[mat_num_l], matrix[mat_num_r], matrix[4]);
            }
        } else if (word[0] == "COPY") {
            int mat_num_l = word[1][3] - '0';
            int mat_num_r = word[2][3] - '0';
            if (matrix[mat_num_r].created == false) {
                cout << "Mat" << mat_num_r << " hasn't been created!";
            } else {
                matrix[mat_num_l] = matrix[mat_num_r];
            }
        } else if (word[0] == "CMUL") {
            double c = atof(word[1].c_str());
            int mat_num = word[2][3] - '0';
            if (matrix[mat_num].created == false) {
                cout << "Mat" << mat_num << " hasn't been created!";
            } else {
                matrix[4] = matrix[mat_num];
                cout << "MatAns: " << endl;
                for (int i = 1; i <= matrix[mat_num].row; i++) {
                    for (int j = 1; j <= matrix[mat_num].col; j++) {
                        matrix[4].val[i][j] *= c;
                        cout << matrix[4].val[i][j] << " ";
                    }
                    cout << endl;
                }
            }
        } else if (word[0] == "TRANS") {
            int mat_num = word[1][3] - '0';
            if (matrix[mat_num].created == false) {
                cout << "Mat" << mat_num << " hasn't been created!";
            } else {
                cout << "MatAns: " << endl;
                matrix[4].row = matrix[mat_num].col;
                matrix[4].col = matrix[mat_num].row;
                for (int i = 1; i <= matrix[4].row; i++) {
                    for (int j = 1; j <= matrix[4].col; j++) {
                        matrix[4].val[i][j] = matrix[mat_num].val[j][i];
                        cout << matrix[4].val[i][j] << " ";
                    }
                    cout << endl;
                }
            }
        } else if (word[0] == "MMUL") {
            int mat_num_l = word[1][3] - '0';
            int mat_num_r = word[2][3] - '0';
            if (matrix[mat_num_l].created == false) {
                cout << "Mat" << mat_num_l << "hasn't been created!";
            } else if (matrix[mat_num_r].created == false) {
                cout << "Mat" << mat_num_r << "hasn't been created!";
            } else if (matrix[mat_num_l].col != matrix[mat_num_r].row) {
                cout << "Size error!" << endl;
            } else {
                mat_mmul(matrix[mat_num_l], matrix[mat_num_r], matrix[4]);
            }
        } else if (word[0] == "DET") {
            int mat_num = word[1][3] - '0';
            int n = matrix[mat_num].row;
            if (matrix[mat_num].created == false) {
                cout << "Mat" << mat_num << " hasn't been created!";
            } else if (matrix[mat_num].row != matrix[mat_num].col) {
                cout << "Size error!" << endl;
            } else {
                cout << "Ans: " << det(matrix[mat_num], n) << endl;
            }
        } else if (word[0] == "INV") {
            int mat_num = word[1][3] - '0';
            int n = matrix[mat_num].row;
            if (matrix[mat_num].created == false) {
                cout << "Mat" << mat_num << " hasn't been created!";
            } else if (matrix[mat_num].row != matrix[mat_num].col) {
                cout << "Size error!" << endl;
            } else if (det(matrix[mat_num], n) == 0) {
                cout << "The matrix is singular!" << endl;
            } else {
                matrix[4] = matrix[mat_num];
                cout << "MatAns:" << endl;
                mat_inv(matrix[mat_num], matrix[4]);
            }
        }
    }
}