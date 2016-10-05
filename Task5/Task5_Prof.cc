#include <iostream>
#include <cmath>

using namespace std;

template <class T, class F>
void forEach( T m, int tam, F& functor ) {
  for( int i = 0; i < tam; i++ )
    functor( m[i] );
}

template <class T>
class Serie {
  public:
    Serie() : soma_x( 0 ), soma_x2( 0 ), n( 0 ) {}
    
    void operator() ( const T& x ) {
      this->soma_x += x;
      this->soma_x2 += x * x ;
      n++;
    }
    
    const T& somaX() const {
        return soma_x;
    }
    
    const T& somaX2() const {
        return soma_x2;
    }
    
    int total() const {
        return n;
    }
    
  private:
    T soma_x;
    T soma_x2;
    int n;
};

template <class T>
double desvPad( const Serie<T>& s ) {
    return sqrt( (s.somaX2() - s.somaX() * s.somaX() / s.total()) / s.total() );
}

int main( int argc, char* argv[] ) {
  int tab[] = { 1, 2, 3, 4, 5 };
  
  Serie<double> serie;
  forEach( tab, 5, serie );

  cout << desvPad( serie ) << endl;
  
  return 0;
}