/*
 
 ID: 63011283
 Name: Rachapoom Phanchotong
 Lab No: 8
 Question No: 1
 Date: February 23, 2021
 
 */

#include <iostream>
#include <vector>
using namespace std;
class Matrix {
private:
    int *data;
    int rows, cols;
    
public:
    Matrix() : rows{0}, cols{0}, data{nullptr} {}
    Matrix(int aRows, int aCols) {
        setMatrix(aRows, aCols);
    }
    
    // Copy Constructor
    Matrix(const Matrix& other) {
        this->setMatrix(other.rows, other.cols);
        for (int i = 0; i < other.rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                this->setDataIndex(i, j, other.getDataIndex(i, j));
            }
        }
    }
    
    // Overload assignment operator
    Matrix& operator=(const Matrix matrix) {
        setMatrix(matrix.rows, matrix.cols);
        for (int i = 0; i < matrix.rows; i++) {
            for (int j = 0; j < matrix.cols; j++) {
                this->setDataIndex(i, j, matrix.getDataIndex(i, j));
            }
        }
        return *this;
    }
    
    ~Matrix() {
        if (data) {
            delete[] data;
        }
    }
    
    void setMatrix(int aRows, int aCols) {
        if (aRows > 0 && aCols > 0) {
            data = new int[aRows * aCols];
            rows = aRows;
            cols = aCols;
        }
        else {
            rows = 0;
            cols = 0;
            data = nullptr;
        }
    }
    int getRows() const {
        return rows;
    }
    int getCols() const {
        return cols;
    }
    void setDataIndex(int i, int j, int val) {
        *(data + (((i) * cols) + j)) = val;
        
    }
    int getDataIndex(int i, int j) const {
        return *(data + (((i) * cols) + j));
    }
    Matrix mulMatrix(const Matrix &multiplier) {
        Matrix result;
        int rows{getRows()}, cols{getCols()}, value;
        if (cols == multiplier.getRows()) {
            result.setMatrix(rows, multiplier.getCols());
            for(int i{0}; i < rows; ++i) {
                for(int j{0}; j < multiplier.getCols(); ++j) {
                    value = 0;
                    for (int k = 0; k < cols;k++) {
                        value += getDataIndex(i, k) *
                        multiplier.getDataIndex(k, j);
                    }
                    result.setDataIndex(i,j,value);
                }
            }
        }
        return result;
    }
    Matrix addMatrix(const Matrix &adder) {
        Matrix result;
        int rows{getRows()}, cols{getCols()};
        if (adder.getRows() == rows && adder.getCols() == cols) {
            result.setMatrix(rows, cols);
            for(int i{0}; i < rows; i++) {
                for (int j{0}; j < cols; j++) {
                    result.setDataIndex(i,j,getDataIndex(i,j) + adder.getDataIndex(i,j));
                }
            }
        }
        return result;
    }
    
};
void enterMatrixRowsAndCols(const string prompt, int &numRows, int &numCols);
void enterMatrixData(const string matrixName, Matrix &matrix);
void printMatrix(const string matrixName, const Matrix &matrix);
void displayResult(const Matrix &matrixA, const Matrix &matrixB, const Matrix &matrixC);
void processMatrixAddition();
void processMatrixMultiplication();

int main() {
    int choice{};
    do {
        cout << "The program to do the matrix addition or multiplication" << endl;
        cout << "This program will ask you the information of Matrix A and B and show the result in Matrix C" << endl;
        cout << "1.Matrix Addition\n2.Matrix Multiplication\n0.Exit\n";
        cout << "Your choice: ";
        cin >> choice;
        switch(choice) {
            case 1:
                processMatrixAddition();
                break;
            case 2:
                processMatrixMultiplication();
                break;
            case 0:
                break;
            default:
                cout << "Enter 0-3 only\n\n";
        }
        
    } while(choice != 0);
    cout << "Good bye\n";
    return 0;
}
void processMatrixAddition() {
    int numRowsA, numColsA;
    int numRowsB, numColsB;
    string errMsg {"Error! Matrix A and B must have the same dimension to perform the addition"};
    enterMatrixRowsAndCols("Enter rows and cols for Matrix A separated By space ", numRowsA, numColsA);
    enterMatrixRowsAndCols("Enter rows and cols for Matrix B separated By space ", numRowsB, numColsB);
    if ((numRowsA == numRowsB) && (numColsA == numColsB)) {
        Matrix matrixA(numRowsA, numColsA), matrixB(numRowsB, numColsB);
        enterMatrixData("A", matrixA);
        enterMatrixData("B", matrixB);
        Matrix matrixC = matrixA.addMatrix(matrixB);
        if (matrixC.getRows() != 0) {
            displayResult(matrixA, matrixB, matrixC);
        }
        else {
            cout << errMsg << endl;
        }
        
    }
    else {
        cout << errMsg << endl;
    }
}

void processMatrixMultiplication() {
    int numRowsA, numColsA;
    int numRowsB, numColsB;
    string errMsg {"Error! Matrix A and B dimensions do not match to perform the multiplication"};
    enterMatrixRowsAndCols("Enter rows and cols for Matrix A separated By space ", numRowsA, numColsA);
    enterMatrixRowsAndCols("Enter rows and cols for Matrix B separated By space ", numRowsB, numColsB);
    if (numColsA == numRowsB ) {
        Matrix matrixA(numRowsA, numColsA), matrixB(numRowsB, numColsB);
        enterMatrixData("A", matrixA);
        enterMatrixData("B", matrixB);
        Matrix matrixC = matrixA.mulMatrix(matrixB);
        if (matrixC.getRows() != 0) {
            displayResult(matrixA, matrixB, matrixC);
        }
        else {
            cout << errMsg << endl;
        }
        
    }
    else {
        cout << errMsg << endl;
    }
}
void enterMatrixRowsAndCols(const string prompt, int &numRows, int &numCols) {
    cout << prompt;
    cin >> numRows >> numCols;
}
void enterMatrixData(const string matrixName, Matrix &matrix) {
    int value;
    for(int i{0}; i < matrix.getRows(); ++i) {
        for(int j{0}; j < matrix.getCols(); ++j) {
            cout << matrixName <<"[" << i+1 << "]" << "[" << j+1 << "] ";
            cin >> value;
            matrix.setDataIndex(i,j,value);
        }
    }
}
void printMatrix(const string matrixName, const Matrix &matrix) {
    int value;
    for(int i{0}; i < matrix.getRows(); ++i) {
        for(int j{0}; j < matrix.getCols(); ++j) {
            value = matrix.getDataIndex(i, j);
            cout << matrixName <<"[" << i+1 << "]" << "[" << j+1 << "] " << value << " ";
        }
        cout << endl;
    }
}
void displayResult(const Matrix &matrixA, const Matrix &matrixB, const Matrix &matrixC) {
    cout << "-----------------------" << endl;
    printMatrix("A", matrixA);
    cout << "-----------------------" << endl;
    printMatrix("B", matrixB);
    cout << "-----------------------" << endl;
    printMatrix("C", matrixC);
    cout << "-----------------------" << endl;
}
