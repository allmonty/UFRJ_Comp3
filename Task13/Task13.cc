#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>

using namespace std;

template <int N, typename T, typename F>
void operator | ( T (&tab)[N], F f ) {
  for( auto x : tab )
    f( x );
}

template <typename T, typename F>
void operator | ( T tab, F f ) {
  for( auto x : tab )
    f( x );
}

//==========================================//

struct Functor {};

struct Var : public Functor {
  template <typename T>
  T operator()( T value ) {
    return value;
  }
};

template <typename C>
struct Constant : public Functor {
  C v;

  Constant(C v) : v(v) {}

  template <typename T>
  C operator()( T value ) {
    return v;
  }
};

//===MULTIPLICADOR===//

template <typename Op1, typename Op2>  
struct Multiplicador : public Functor{
  Op1 op1;
  Op2 op2;
  
  Multiplicador( Op1 op1, Op2 op2 ) : op1(op1), op2(op2) {}
  
  template <class T> 
  auto operator()( T value ) -> decltype( op1( value ) * op2( value ) ) {
    return op1( value ) * op2( value );
  }
};

template <typename Op1, typename Op2>
inline Multiplicador< typename enable_if<std::is_base_of<Functor, Op1>::value, Op1>::type,
                      typename enable_if<std::is_base_of<Functor, Op2>::value, Op2>::type >
operator * ( Op1 a, Op2 b ) {
  return Multiplicador<Op1, Op2>( a, b );
}

template <typename Op1, typename Op2>
inline Multiplicador< Constant<typename enable_if<!std::is_base_of<Functor, Op1>::value, Op1>::type>,
                      typename enable_if<std::is_base_of<Functor, Op2>::value, Op2>::type >
operator * ( Op1 a, Op2 b ) {
  Constant<Op1> c(a);

  return Multiplicador<Constant<Op1>, Op2>( c, b );
}

template <typename Op1, typename Op2>
inline Multiplicador< typename enable_if<std::is_base_of<Functor, Op1>::value, Op1>::type,
                      Constant<typename enable_if<!std::is_base_of<Functor, Op2>::value, Op2>::type> >
operator * ( Op1 a, Op2 b ) {
  Constant<Op2> c(b);

  return Multiplicador<Op1, Constant<Op2>>( a, c );
}

//===SOMADOR===//

template <typename Op1, typename Op2>  
struct Somador : public Functor{
  Op1 op1;
  Op2 op2;
  
  Somador( Op1 op1, Op2 op2 ) : op1(op1), op2(op2) {}
  
  template <class T> 
  auto operator()( T value ) -> decltype( op1( value ) + op2( value ) ) {
    return op1( value ) + op2( value );
  }
};

template <typename Op1, typename Op2>
inline Somador< typename enable_if<std::is_base_of<Functor, Op1>::value, Op1>::type,
                typename enable_if<std::is_base_of<Functor, Op2>::value, Op2>::type >
operator + ( Op1 a, Op2 b ) {
  return Somador<Op1, Op2>( a, b );
}

template <typename Op1, typename Op2>
inline Somador< Constant<typename enable_if<!std::is_base_of<Functor, Op1>::value, Op1>::type>,
                typename enable_if<std::is_base_of<Functor, Op2>::value, Op2>::type >
operator + ( Op1 a, Op2 b ) {
  Constant<Op1> c(a);

  return Somador<Constant<Op1>, Op2>( c, b );
}

template <typename Op1, typename Op2>
inline Somador< typename enable_if<std::is_base_of<Functor, Op1>::value, Op1>::type,
                Constant<typename enable_if<!std::is_base_of<Functor, Op2>::value, Op2>::type> >
operator + ( Op1 a, Op2 b ) {
  Constant<Op2> c(b);

  return Somador<Op1, Constant<Op2>>( a, c );
}

//===Declaring a variable X===//
Var x;

int main() {
  int tab[] =  { 1, 2, 3, 4 };
  vector<int> v;
    
  tab | [ &v ]( int x ) { v.push_back( x ); };
    
  auto op1 = x * x;

  auto op2 = x * x * x;

  auto op3 = 2*x + 1; 

  auto op4 = 3.14 * x;

  auto op5 = x + "!";

  cout << "=== OP1 ===" << endl;
  v | [ &op1 ]( int n ) { cout << op1( n ) << endl; };

  cout << "=== OP2 ===" << endl;
  v | [ &op2 ]( int n ) { cout << op2( n ) << endl; };

  cout << "=== OP3 ===" << endl;
  v | [ &op3 ]( int n ) { cout << op3( n ) << endl; };

  cout << "=== OP4 ===" << endl;
  v | [ &op4 ]( int n ) { cout << op4( n ) << endl; };

  cout << "=== OP5 ===" << endl;
  v | [ &op5 ]( int n ) { cout << op5( std::to_string(n) ) << endl; };

  return 0;  
}