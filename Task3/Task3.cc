#include <string>
#include <iostream>

using namespace std;

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
       
       Type at( int n ) const {
            verifica_se_esta_dentro_dos_limites( n );
            return val[n];
       }   
       
       int tamanho() const {
           return tam;
       }       

    protected:
    
        void verifica_se_esta_dentro_dos_limites( int n ) const {
           if( n < 0 || n >= tam ) 
                erro( "Limite de array ultrapassado" );
        }
        
        void erro( string msg ) const {
            cout << "Erro: " << msg << endl; 
            exit( 1 );
        }
    
    private:
        int tam;
        Type *val;
};

template <class Type>
void imprime(const Array<Type>& b)
{
    cout << "[ ";
    for(int i = 0; i < b.tamanho(); i++)
        cout << b[i] << " ";
    cout << "]\n";
}

template <class Type>
void imprime(const Array<Array<Type>>& b)
{
    for(int i = 0; i < b.tamanho(); i++)
        imprime(b[i]);
}

template <class Type>
ostream& operator << (ostream& o, const Array<Type>& a)
{
    o << "[ ";
    for(int i = 0; i < a.tamanho(); i++)
        o << a[i] << " ";
    o << "]\n";
    return o;
}

template <class Type>
ostream& operator << (ostream& o, const Array<Array<Type>>& a)
{
    for(int i = 0; i < a.tamanho(); i++)
        o << a[i];
    return o;
}

int main() {
    cout << "Test A:" << endl;
    Array<int> a(5);
    a[2] = 1987;
    imprime(a);

    cout << "\nTest A2:" << endl;
    Array<Array<int>> a2;
    a2 = new Array<Array<int>>(4);
    a2[2] = a;
    imprime(a2);

    cout << "\nTest B:" << endl;
    Array<int> b;
    b = new Array<int>(6);
    b[2] = 1999;
    imprime(b);

    cout << "\nTest C:" << endl;
    Array<Array<int>> c;
    c = new Array<Array<int>>(7);
    c[2] = new Array<int>(8);
    c[2][2] = 1992;
    imprime(c);

    cout << "\nTest D:" << endl;
    Array<Array<int>> d(9);
    d[2] = new Array<int>(10);
    d[2][3] = 2016;
    cout << d << endl;
}