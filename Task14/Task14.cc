#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <iterator>

using namespace std;

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

//===PERCENT===//

template <typename Op1, typename Op2>  
struct Percent : public Functor{
  Op1 op1;
  Op2 op2;
  
  Percent( Op1 op1, Op2 op2 ) : op1(op1), op2(op2) {}
  
  template <class T> 
  auto operator()( T value ) -> decltype( op1( value ) % op2( value ) ) {
    return op1( value ) % op2( value );
  }
};

template <typename Op1, typename Op2>
inline Percent< typename enable_if<std::is_base_of<Functor, Op1>::value, Op1>::type,
                typename enable_if<std::is_base_of<Functor, Op2>::value, Op2>::type >
operator % ( Op1 a, Op2 b ) {
  return Percent<Op1, Op2>( a, b );
}

template <typename Op1, typename Op2>
inline Percent< Constant<typename enable_if<!std::is_base_of<Functor, Op1>::value, Op1>::type>,
                typename enable_if<std::is_base_of<Functor, Op2>::value, Op2>::type >
operator % ( Op1 a, Op2 b ) {
  Constant<Op1> c(a);

  return Percent<Constant<Op1>, Op2>( c, b );
}

template <typename Op1, typename Op2>
inline Percent< typename enable_if<std::is_base_of<Functor, Op1>::value, Op1>::type,
                Constant<typename enable_if<!std::is_base_of<Functor, Op2>::value, Op2>::type> >
operator % ( Op1 a, Op2 b ) {
  Constant<Op2> c(b);

  return Percent<Op1, Constant<Op2>>( a, c );
}

//===EQUALS===//

template <typename Op1, typename Op2>  
struct Equals : public Functor{
  Op1 op1;
  Op2 op2;
  
  Equals( Op1 op1, Op2 op2 ) : op1(op1), op2(op2) {}
  
  template <class T> 
  auto operator()( T value ) -> decltype( op1( value ) == op2( value ) ) {
    return op1( value ) == op2( value );
  }
};

template <typename Op1, typename Op2>
inline Equals< typename enable_if<std::is_base_of<Functor, Op1>::value, Op1>::type,
                typename enable_if<std::is_base_of<Functor, Op2>::value, Op2>::type >
operator == ( Op1 a, Op2 b ) {
  return Equals<Op1, Op2>( a, b );
}

template <typename Op1, typename Op2>
inline Equals< Constant<typename enable_if<!std::is_base_of<Functor, Op1>::value, Op1>::type>,
                typename enable_if<std::is_base_of<Functor, Op2>::value, Op2>::type >
operator == ( Op1 a, Op2 b ) {
  Constant<Op1> c(a);

  return Equals<Constant<Op1>, Op2>( c, b );
}

template <typename Op1, typename Op2>
inline Equals< typename enable_if<std::is_base_of<Functor, Op1>::value, Op1>::type,
                Constant<typename enable_if<!std::is_base_of<Functor, Op2>::value, Op2>::type> >
operator == ( Op1 a, Op2 b ) {
  Constant<Op2> c(b);

  return Equals<Op1, Constant<Op2>>( a, c );
}


//==========================================//
template <typename T, typename F>
inline typename std::enable_if<
	std::is_base_of<Functor, F>::value &&
	std::is_member_object_pointer<int(T::iterator::*)
>::value, T>::type
operator | ( T tab, F f ){
  std::vector<int> v;

  for( auto x : tab )
  {
    if(f( x ))
    {
    	v.push_back(x);
    }
  }
  
  return v;
}

//===Declaring a variable X===//
Var x;

int main() {
  vector<int> v = { 1, 2, 3, 4 };
  
  cout << "=== RESULT ===" << endl;
  auto f = ( v | x % 2 == 0);
  for( auto s : f )
  	cout << s << endl;

  return 0;  
}