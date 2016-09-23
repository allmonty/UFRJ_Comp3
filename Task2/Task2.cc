#include <string>
#include <iostream>

using namespace std;

class ArrayInt {
    
    public:
        ArrayInt( int n ) : tam( n ), val( new int[n] ) {
        }
    
       void put( int n, int valor ) {
            esta_dentro_dos_limites( n );
            val[n] = valor;
        }   
       
       int at( int n ) const{
            esta_dentro_dos_limites( n );
            return val[n];
       }

       int size() const{
       		return tam;
       }
       
       const ArrayInt& operator = (const ArrayInt& other)
       {
       		if( &other != this)
       		{
       			tam = other.tam;
       			delete [] val;
       			val = new int[tam];
       			for(int i = 0; i < tam; i++)
       			{
       				val[i] = other.val[i];
       			}
       		}
       		return *this;
       }

       int& operator [] (const int& n) {
       		esta_dentro_dos_limites( n );
            return val[n];
       }

       const int& operator [] (const int& n) const {
       		esta_dentro_dos_limites( n );
            return val[n];
       }
       
    protected:
    
        void esta_dentro_dos_limites( int n ) const {
           if( n < 0 && n >= tam )
                erro( "Limite de array ultrapassado" );
        }
        
        void erro( string msg ) const{
            cout << "Erro: " << msg << endl;
            exit(1);
        }
    
    private:
        int tam;
        int *val;
};

void imprime(const ArrayInt& array)
{
	cout << "[ ";
	for(int i = 0; i < array.size(); i++)
	{
		cout << array[i] << " ";
	}
	cout << "]" << endl;
}

int main() {
    ArrayInt m( 10 );
    
    m[5] = 10;
    cout << m[5] << endl;

    ArrayInt o = m;

    cout << o[5] << endl;

    imprime(m);
}