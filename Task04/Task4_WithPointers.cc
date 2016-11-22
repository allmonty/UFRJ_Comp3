#include <string>
#include <iostream>

using namespace std;

class Exception
{
    public:
        Exception(string e): message("Exception:" + e){}

        const string message;
};

template<class Type>
class Matrix {
    public:
        class Line {
            public: 
                Line( Type* lineStart, int lineSize ):
                        lineStart( lineStart ), lineSize(lineSize) {}
                          
                Type& operator[]( const int& c ) {
                    if( c >= lineSize )
                        throw Exception("ELimiteUltrapassado");
                    return lineStart[c];
                }

                const Type& operator[]( const int& c ) const{
                    if( c >= lineSize )
                        throw Exception("ELimiteUltrapassado");
                    return lineStart[c];
                }

            private:
                Type* lineStart;
                int lineSize;
        };
        
        Matrix() : mat( new Type[0] ), rows( 0 ), cols( 0 ) {
            clear();
        }

        Matrix( int l, int c ) : mat( new Type[l*c] ), rows( l ), cols( c ) {
            clear();
        }

        ~Matrix() {delete [] mat;}

        const Matrix& operator = ( const Matrix* m ) {
            return this->operator=(*m);
        }

        const Matrix& operator = ( const Matrix& m ) {
            if( &m != this ) {
                delete [] mat;
                mat = new Type[m.rows*m.cols];
                cols = m.cols;
                rows = m.rows;
            
                for( int i = 0; i < m.rows*m.cols; i++ )
                    mat[i] = m.mat[i];
            }
            
            return *this;
        }
    
        Type at( int l, int c ) {
            return mat[l*cols + c];
        }
        
        Line operator[]( const int& l ) {
            if( l >= rows )
                throw Exception("ELimiteUltrapassado");
            return Line( mat + l*cols, cols );
        }

        const Line operator[]( const int& l ) const{
            if( l >= rows )
                throw Exception("ELimiteUltrapassado");
            return Line( mat + l*cols, cols );
        }
        
        Matrix operator * ( const Matrix& b) const {
            if(cols != b.rows)
                throw Exception("Matrixes could not be multiplied, sizes dont match");

            Matrix mulMat(rows, b.cols);

            for(int i = 0; i < rows; ++i)
            {
                for(int j = 0; j < b.cols; ++j)
                {
                    for(int k = 0; k < cols; ++k)
                    {
                        mulMat[i][j] += (*this)[i][k] * b[k][j];
                    }
                }
            }

            return mulMat;
        }

        Matrix operator + ( const Matrix& b) const {
            if(rows != b.rows || cols != b.cols)
                throw Exception("Matrix must have the same size in sum");

            Matrix sumMat(rows, b.cols);

            for(int i = 0; i < rows; ++i)
            {
                for(int j = 0; j < cols; ++j)
                {
                    sumMat[i][j] = (*this)[i][j] + b[i][j];
                }
            }

            return sumMat;
        }

        void resize(int r, int c)
        {
            Matrix<Type> newMat(r,c);

            for(int i = 0; i < r; i++)
            {
                if(i >= rows)
                    break;

                for(int j = 0; j < c; j++)
                {
                    if(j >= cols)
                        break;

                    newMat[i][j] = (*this)[i][j];
                }
            }

            (*this) = newMat;
        }

        void clear()
        {
            for(int i = 0; i < rows*cols; ++i)
                mat[i] = 0;
        }

        int Rows() const {return rows;}

        int Cols() const {return cols;}

    private:
        Type *mat;
        int rows;
        int cols;
};

void printMatrix(const Matrix<double>& m)
{
    for(int i = 0; i < m.Rows(); i++)
    {
        cout << "[ ";
        for(int j = 0; j < m.Cols(); j++)
        {
            cout << m[i][j] << " ";
        }
        cout << "]" << endl;
    }
}

int main() {

    cout << "Multiplication:" << endl;

    Matrix<double> c(3, 2), d(2, 3), e;

    c[0][0] = 1;
    c[0][1] = 2;
    c[1][0] = 3;
    c[1][1] = 4;
    c[2][0] = 5;
    c[2][1] = 6;

    d[0][0] = 1;
    d[0][1] = 2;
    d[0][2] = 3;
    d[1][0] = 4;
    d[1][1] = 5;
    d[1][2] = 6;

    e = c * d;

    printMatrix(e);

    cout << "Addition:" << endl;

    Matrix<double> f(2, 2), g(2, 2), h;

    f[0][0] = 1;
    f[0][1] = 2;
    f[1][0] = 3;
    f[1][1] = 4;

    g[0][0] = 1;
    g[0][1] = 2;
    g[1][0] = 3;
    g[1][1] = 4;

    h = f + g;

    printMatrix(h);

    cout << "Realloc:" << endl;

    h.resize(3, 3);

    printMatrix(h);

    cout << "Clear:" << endl;

    h.clear();

    printMatrix(h);

    cout << "Insertion:" << endl;

    Matrix<double> m(5, 5);

    try
    {
        m[2][2] = 45;
        cout << m[2][2] << endl;

        cout << "Throwing Exception:" << endl;

        m[99][99] = 50;
    }
    catch (Exception e)
    {
        cout << e.message << endl;
    }

}