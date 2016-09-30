#include <string>
#include <iostream>

using namespace std;

class Exception
{
    public:
        Exception(string e): message("Exception:" + e){}

        const string message;
};

template <class Type>
class Array {
    
    public:
        Array() : tam( 0 ), val( new Type[0] ) {}

        Array( int n ) : tam( n ), val( new Type[n] ) {}
        
        // Construtor de cópia
        Array( const Array& p ) : tam( p.tam ), val( new Type[p.tam] ) {
          for( int i = 0; i < tam; i++ )
            val[i] = p.val[i];
        }

        ~Array() {
            delete[] val;
        }
        
        const Array& operator = ( const Array* n ) {
            //cout << "teste 1: " << n->tam << endl;
            return this->operator=(*n);
        }

        const Array& operator = ( const Array& n ) {
            // cout << "teste 2: " << n.tam << endl;
            if( &n != this ) {
                delete [] val;
                val = new Type[n.tam];
                tam = n.tam;
            
                for( int i = 0; i < tam; i++ )
                    val[i] = n.val[i];
            }
            
            return *this;
        }
    
        // const int& aceita constantes: a[2]
        Type& operator [] ( const int& n ) {
            verifica_se_esta_dentro_dos_limites( n );
            return val[n];
        }       
        
        const Type& operator [] ( const int& n ) const  {
            verifica_se_esta_dentro_dos_limites( n );
            return val[n];
        }
    
        void put( int n, Type valor ) {
            verifica_se_esta_dentro_dos_limites( n );
            val[n] = valor;
        }   
       
       Type at( int n ) const{
            verifica_se_esta_dentro_dos_limites( n );
            return val[n];
       }   
       
       int tamanho() const {
            return tam;
       }

    protected:
    
        void verifica_se_esta_dentro_dos_limites( int n ) const {
           if( n < 0 || n >= tam ) 
                throw Exception( "Limite de array ultrapassado" );
        }
    
    private:
        int tam;
        Type *val;
};

template<class Type>
class Matrix {
    public:
        Matrix() : rows(0), cols(0), mat() {}

        Matrix( int r, int c ) : rows( r ), cols( c ), mat( r )
        {
            for(int i = 0; i < r; i++)
            {
                mat[i] = new Array<Type>(c);
            }
        }
        
        // Construtor de cópia
        Matrix( const Matrix& p ) : rows( p.rows ), cols( p.cols ), mat( p.rows )
        {
            for(int i = 0; i < rows; i++)
            {
                mat[i] = new Array<Type>(cols);
            }

            for(int i = 0; i < rows; i++)
                for( int j = 0; j < cols; j++ )
                    mat[i][j] = p.mat[i][j];
        }

        const Matrix& operator = ( const Matrix& m ) {
            mat = m.mat;
            rows = m.rows;
            cols = m.cols;
            
            return *this;
        }

        // const int& aceita constantes: a[2]
        Array<Type>& operator [] ( const int& n ) {
            return mat[n];
        }       
        
        const Array<Type>& operator [] ( const int& n ) const {
            return mat[n];
        }

        const Matrix operator * ( const Matrix& b) const {
            Matrix mulMat(rows, b.cols);

            for(int i = 0; i < rows; ++i)
            {
                for(int j = 0; j < b.cols; ++j)
                {
                    for(int k = 0; k < cols; ++k)
                    {
                        mulMat.mat[i][j] += mat[i][k] * b[k][j];
                    }
                }
            }

            return mulMat;
        }

        const Matrix operator + ( const Matrix& b) const {
            if(rows != b.rows || cols != b.cols)
                throw Exception("Matrix must have the same size in sum");

            Matrix sumMat(rows, b.cols);

            for(int i = 0; i < rows; ++i)
            {
                for(int j = 0; j < cols; ++j)
                {
                    sumMat.mat[i][j] = mat[i][j] + b[i][j];
                }
            }

            return sumMat;
        }

        void realloc(int r, int c)
        {
            Array<Array<Type>> newMat(r);
            for(int i = 0; i < r; i++)
            {
                newMat[i] = new Array<Type>(c);
            }

            for(int i = 0; i < r; i++)
            {
                if(i >= rows)
                    break;

                for(int j = 0; j < c; j++)
                {
                    if(j >= cols)
                        break;

                    newMat[i][j] = mat[i][j];
                }
            }

            mat = newMat;
            rows = r;
            cols = c;
        }

        void clear()
        {
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    (*this)[i][j] = 0;
                }
            }
        }

        int Rows() const {return rows;}

        int Cols() const {return cols;}

    private:
        int rows;
        int cols;
        Array<Array<Type>> mat;
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

    Array<int> a(5);
    a[2] = 1987;

    Array<Array<int>> b(5);
    b[2] = new Array<int>(5);
    b[2][2] = 1986;

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

    h.realloc(3, 3);

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