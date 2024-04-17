#include "Matrix.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>


//Constructors
template<typename T1>
Matrix<T1>::Matrix() //default constructor
{
    this->height = 0;
    this->width = 0;
    this->rows = NULL;
}

template<typename T1>
Matrix<T1>::Matrix(const Matrix& other) //copy constructor
{
    this->height = other.height;
    this->width = other.width;
    this->rows = new T1* [height];
    for (int i = 0; i < height; i++)
    {
        this->rows[i] = new T1[width];
        for (int j = 0; j < width; j++)
            this->rows[i][j] = other.rows[i][j];
    }
}

template<typename T1>
Matrix<T1>::Matrix(size_t dimension) //one-argument constructor
{
    this->height = dimension;
    this->width = dimension;
    this->rows = new T11* [dimension];
    for (int i = 0; i < dimension; i++)
    {
        this->rows[i] = new T11[width];
        for (int j = 0; j < width; j++)
            this->rows[i][j] = 0;
    }
}
template<typename T1>
Matrix<T1>::Matrix(size_t height, size_t width) //two-arguments constructor
{
    this->height = height;
    this->width = width;
    this->rows = new T1* [height];
    for (int i = 0; i < height; i++)
    {
        this->rows[i] = new T1[width];
        for (int j = 0; j < width; j++)
            this->rows[i][j] = 0;
    }
}

template<typename T1>
Matrix<T1>::Matrix(size_t height, size_t width, T1** rows) //normal constuctor
{
    this->height = height;
    this->width = width;
    this->rows = new T1* [height];
    for (int i = 0; i < height; i++)
    {
        this->rows[i] = new T1[width];
        for (int j = 0; j < width; j++)
            this->rows[i][j] = 0;
    }
}

template<typename T1>
Matrix<T1> Matrix<T1>::identity(size_t dimension)
{
    Matrix result(dimension);
    for (size_t i = 0; i < dimension; i++)
        result.set_value(i, i, 1);
    return result;
}

template<typename T1>
Matrix<T1>::~Matrix()
{
    for (int i = 0; i < this->height; i++)
        delete[] this->rows[i];
    delete[] this->rows;
}


//Getters, setters
template<typename T1>
inline size_t Matrix<T1>::Height() const
{
    return this->height;
}

template<typename T1>
inline size_t Matrix<T1>::Width() const
{
    return this->width;
}

template<typename T1>
const T1& Matrix<T1>::get_value(size_t row, size_t column) const
{
    return this->rows[row][column];
}

template<typename T1>
void Matrix<T1>::set_value(size_t row, size_t column, T1 value)
{
    this->rows[row][column] = value;
}

template<typename T1>
void Matrix<T1>::set_size(size_t height, size_t width)
{
    for (int i = 0; i < this->height; i++)
        delete[] this->rows[i];
    delete[] this->rows;
    this->height = height;
    this->width = width;
    this->rows = new T1* [height];
    for (int i = 0; i < height; i++)
    {
        this->rows[i] = new T1[width];
        for (int j = 0; j < width; j++)
            this->set_value(i, j, 0);
    }
}


//Comparisons
bool Matrix<T1>::operator==(const Matrix& other) const
{
    if (this->Height() != other.Height() || this->Width() != other.Width())
        return false;
    for (size_t i = 0; i < this->Height(); i++)
        for (size_t j = 0; j < this->Width(); j++)
        {
            T1 value1 = this->get_value(i, j);
            T2 value2 = other.get_value(i, j);
            if (value1 != value2)
                return false;
        }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const
{
    return !(*this == other);
}

bool Matrix::operator==(const T1& k) const
{
    return *this == Matrix::identity(this->Height()) * k;
}

bool Matrix::operator!=(const T1& k) const
{
    return !(*this == k);
}


//Matrix operations
Matrix& Matrix::operator=(const Matrix& other) //assignment
{
    if (this != &other)
    {
        this->set_size(other.Height(), other.Width());
        for (int i = 0; i < this->Height(); i++)
        {
            this->rows[i] = new T1[width];
            for (int j = 0; j < this->Width(); j++)
                this->set_value(i, j, other.get_value(i, j));
        }
    }
    return *this;
}

Matrix Matrix::operator*(const T2& k) const //multiplication by number
{
    Matrix result(this->Height(), this->Width());
    for (size_t i = 0; i < this->Height(); i++)
    {
        for (size_t j = 0; j < this->Width(); j++)
        {
            T1 value = this->get_value(i, j);
            result.set_value(i, j, value * k);
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix& other) const
{
    if (this->Height() != other.Height() || this->Width() != other.Width())
        throw std::invalid_argument("Matrixes must have same dimension to do this operation");
    Matrix result(this->Height(), this->Width());
    for (size_t i = 0; i < this->Height(); i++)
    {
        for (size_t j = 0; j < this->Width(); j++)
        {
            T1 value1 = this->get_value(i, j);
            T2 value2 = other.get_value(i, j);
            result.set_value(i, j, value1 + value2);
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const
{
    if (this->Height() != other.Height() || this->Width() != other.Width())
        throw std::invalid_argument("Matrixes must have same dimension to do this operation");

    Matrix result(this->Height(), this->Width());
    result = *this + (other * (-1));
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const
{
    if (this->Width() != other.Height())
        throw std::invalid_argument("Width of first matrix must be equal to height of second matrix"
            " to do this operation");
    Matrix result(this->Height(), other.Width());
    for (size_t i = 0; i < this->Height(); i++)
        for (size_t j = 0; j < other.Width(); j++)
        {
            T1 value_sum = 0;
            for (size_t k = 0; k < this->Width(); k++)
            {
                T1 value1;
                T2 value2;
                value1 = this->get_value(i, k);
                value2 = other.get_value(k, j);
                value_sum += value1 * value2;
            }
            result.set_value(i, j, value_sum);
        }
    return result;
}

Matrix operator*(const T1& k, const Matrix& m) {
    return m * k;
}


//Elementary operations
template<typename T1>
void Matrix<T1>::swap_rows(size_t row1, size_t row2)
{
    if (row1 >= this->Height() || row2 >= this->Height())
        throw std::invalid_argument("Row index is incorrect");
    std::swap(this->rows[row1], this->rows[row2]);
}

void Matrix::multiply_row(size_t row, T2 k)
{
    if (row > this->Height())
        throw std::invalid_argument("Row index is incorrect");
    if (k == 0)
        throw std::invalid_argument("k mustn't be 0");
    for (size_t j = 0; j < this->Width(); j++)
    {
        T1 value = this->get_value(row, j);
        this->set_value(row, j, value * k);
    }
}

void Matrix::add_multiplied_row(size_t row1, size_t row2, T2 k)
{
    if (row1 > this->height || row2 > this->width)
        throw std::invalid_argument("Row index is incorrect");
    if (row1 == row2)
        throw std::invalid_argument("You must pick different rows");
    for (size_t j = 0; j < this->width; j++)
    {
        T1 value1 = this->get_value(row1, j);
        T1 value2 = this->get_value(row2, j);
        this->set_value(row1, j, value1 + value2 * k);
    }
}


//Hard operations
template<typename T1>
Matrix<T1> Matrix<T1>::Transpose() const
{
    Matrix result(this->Width(), this->Height());
    for (size_t i = 0; i < this->Width(); i++)
        for (size_t j = 0; j < this->Height(); j++)
        {
            T1 value = this->get_value(i, j);
            result.set_value(j, i, value);
        }
    return result;
}

template<typename T1>
double Matrix<T1>::determinant() const
{
    size_t size = this->Height();
    if (size != this->Width())
        throw std::invalid_argument("Matrix must be square");
    else if (size == 2)
    {
        T1 a = this->get_value(0, 0);
        T1 b = this->get_value(0, 1);
        T1 c = this->get_value(1, 0);
        T1 d = this->get_value(1, 1);
        return (a * d - b * c);
    }
    else
    {
        Matrix m(*this);
        T1 result = 1;
        for (size_t i = 0; i < size; i++)
        {
            size_t k = i;
            T1 max_abs = m.get_value(k, i);
            for (size_t j = i + 1; j < size; j++)
                if (std::abs(m.get_value(j, i)) > std::abs(max_abs))
                {
                    k = j;
                    max_abs = m.get_value(k, i);
                }
            if (max_abs == 0)
                return 0;
            if (i != k)
                result *= -1;
            m.swap_rows(i, k);
            result *= max_abs;
            m.multiply_row(i, 1 / max_abs);
            for (size_t j = i + 1; j < size; j++)
            {
                if (std::abs(m.get_value(j, i)) == 0)
                    continue;
                T1 coef = -m.get_value(j, i);
                m.add_multiplied_row(j, i, coef);
            }
        }
        return result;
    }
}

template<typename T1>
Matrix<T1> Matrix<T1>::operator!() const
{
    size_t size = this->Height();
    const T1 det = this->determinant();
    if (size != this->Width())
        throw std::invalid_argument("Matrix must be square");
    else if (this->determinant() == 0)
    {
        Matrix m(size);
        return m;
    }
    else if (size == 2)
    {
        T1 a = this->get_value(0, 0);
        T1 b = this->get_value(0, 1);
        T1 c = this->get_value(1, 0);
        T1 d = this->get_value(1, 1);

        Matrix m(size);
        m.set_value(0, 0, d);
        m.set_value(0, 1, -b);
        m.set_value(1, 0, -c);
        m.set_value(1, 1, a);

        return (1 / det) * m;
    }
    else
    {
        Matrix m = Matrix(*this);
        Matrix result = Matrix::identity(size);

        for (size_t i = 0; i < size; i++)
        {
            size_t k = i;
            T1 max_abs = m.get_value(k, i);
            for (size_t j = i + 1; j < size; j++)
                if (std::abs(m.get_value(j, i)) > std::abs(max_abs))
                {
                    k = j;
                    max_abs = m.get_value(k, i);
                }
            m.swap_rows(i, k);
            result.swap_rows(i, k);

            m.multiply_row(i, 1 / max_abs);
            result.multiply_row(i, 1 / max_abs);
            for (size_t j = 0; j < size; j++)
            {
                if (j == i || std::abs(m.get_value(j, i)) == 0)
                    continue;
                T1 coef = -m.get_value(j, i);
                m.add_multiplied_row(j, i, coef);
                result.add_multiplied_row(j, i, coef);
            }
        }
        return result;
    }
}


//Input, Output
template<typename T1>
std::istream& operator>>(std::istream& in, Matrix<T1>& m)
{
    size_t height, width;
    in >> height >> width;
    m.set_size(height, width);
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            T1 value;
            in >> value;
            m.set_value(i, j, value);
        }
    }
    return in;
}

template<typename T1>
std::ostream& operator<<(std::ostream& out, const Matrix<T1>& m)
{
    const size_t height = m.Height();
    const size_t width = m.Width();
    if (height == 0) out << "empty";
    else
    {
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
                out << m.get_value(i, j) << ' ';
            out << std::endl;
        }
    }
    return out;
}