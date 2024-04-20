#include <iostream>
#ifndef HOMEWORK_MATRIXES_MATRIX_H
#define HOMEWORK_MATRIXES_MATRIX_H

template<typename T>
class Matrix
{
private:
    size_t height;
    size_t width;
    T** rows;
public:
    //Constructors, destructor
    Matrix(); //default constructor

    Matrix(const Matrix&); //copy constructor

    static Matrix null(size_t height); //one-argument constructor

    Matrix(size_t height, size_t width); //two-arguments constructor

    Matrix(size_t height, size_t width, T** rows); //normal constructor

    static Matrix identity(size_t dimension);

    ~Matrix(); //destructor

    //Getters, setters
    inline size_t Height() const;

    inline size_t Width() const;

    const T& get_value(size_t row, size_t column) const;

    void set_value(size_t height, size_t width, T value);

    void set_size(size_t height, size_t width);


    //Comparisons
    bool operator==(const Matrix& other) const;

    bool operator!=(const Matrix& other) const;

    bool operator==(const T& k) const;

    bool operator!=(const T& k) const;

    //Matrix operations
    Matrix& operator=(const Matrix& other); //assignment

    Matrix operator*(const T& k) const; //multiplication by number

    Matrix operator+(const Matrix& other) const; //plus

    Matrix operator-(const Matrix& other) const; //minus

    Matrix operator*(const Matrix& other) const; //multiplication


    //Elementary operations

    void swap_rows(size_t row1, size_t row2); //1st type operation

    void multiply_row(size_t row, T k); //2nd type operation

    void add_multiplied_row(size_t row1, size_t row2, T k); //3rd type operation


    //Hard operations (transpose, determinant, inverse matrix)

    Matrix Transpose() const;

    double determinant() const;

    Matrix operator!() const; //inverse matrix
};


//Input, Output
template<typename T>
std::ostream& operator<<(std::ostream& o, const Matrix<T>& m);
template<typename T>
std::istream& operator>>(std::istream& i, Matrix<T>& m);

#endif //HOMEWORK_MATRIXES_MATRIX_H