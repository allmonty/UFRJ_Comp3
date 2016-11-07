#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Exception
{
    public:
        Exception(string e): message("Exception:" + e){}

        const string message;
};

template <int N, typename A, typename F>
void operator | ( A (&elements)[N], F functor)
{
  for(int i = 0; i < N; i++)
  {
    functor( *(elements+i) );
  }
}

template <typename A, typename F>
void operator | ( vector<A> elements, F functor)
{
  for(A element : elements)
  {
    functor(element);
  }
}

struct Multiplicador_X_X
{
  template <typename T>
  auto operator () (T a) -> decltype( a * a )
  {
    return a*a;
  }
};

template <typename A>
struct Multiplicador_Const_X
{
  A n;

  template <typename T>
  auto operator () (T a) -> decltype( n * a )
  {
    return n*a;
  }
};

struct Var
{
  Multiplicador_X_X operator * (Var x)
  {
    Multiplicador_X_X multi;
    return multi;
  }

  template <typename C>
  Multiplicador_Const_X<C> operator * (C x)
  {
    Multiplicador_Const_X<C> multi;
    multi.n = x;
    return multi;
  }
};

template <typename C>
Multiplicador_Const_X<C> operator * (C n, Var x)
{
  Multiplicador_Const_X<C> multi;
  multi.n = n;
  return multi;
}

int main()
{
  int tab[10] =  { 1, 2, 3, 2, 3, 4, 6, 0, 1, 8 };
  vector<int> v;
  Var x;

  tab | [ &v ]( int x ) { v.push_back( x ); };
    
  cout << "===1===" << endl;
  auto op = x * x;
  v | [ &op ]( int x ) { cout << op( x ) << endl; };

  cout << "===2===" << endl;
  auto op2 = x * 2;
  v | [ &op2 ]( int x ) { cout << op2( x ) << endl; };

  cout << "===3===" << endl;
  auto op3 = 2 * x;
  v | [ &op3 ]( int x ) { cout << op3( x ) << endl; };

	return 0;
}