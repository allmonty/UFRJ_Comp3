#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <iterator>

using namespace std;

//===FUNCTOR===//

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

//===AND===//

template <typename Op1, typename Op2>  
struct And : public Functor{
  Op1 op1;
  Op2 op2;
  
  And( Op1 op1, Op2 op2 ) : op1(op1), op2(op2) {}
  
  template <class T> 
  auto operator()( T value ) -> decltype( op1( value ) && op2( value ) ) {
    return op1( value ) && op2( value );
  }
};

template <typename Op1, typename Op2>
inline And< typename enable_if<std::is_base_of<Functor, Op1>::value, Op1>::type,
                typename enable_if<std::is_base_of<Functor, Op2>::value, Op2>::type >
operator && ( Op1 a, Op2 b ) {
  return And<Op1, Op2>( a, b );
}

template <typename Op1, typename Op2>
inline And< Constant<typename enable_if<!std::is_base_of<Functor, Op1>::value, Op1>::type>,
                typename enable_if<std::is_base_of<Functor, Op2>::value, Op2>::type >
operator && ( Op1 a, Op2 b ) {
  Constant<Op1> c(a);

  return And<Constant<Op1>, Op2>( c, b );
}

template <typename Op1, typename Op2>
inline And< typename enable_if<std::is_base_of<Functor, Op1>::value, Op1>::type,
                Constant<typename enable_if<!std::is_base_of<Functor, Op2>::value, Op2>::type> >
operator && ( Op1 a, Op2 b ) {
  Constant<Op2> c(b);

  return And<Op1, Constant<Op2>>( a, c );
}

//===LESS===//

template <typename Op1, typename Op2>  
struct Less : public Functor{
  Op1 op1;
  Op2 op2;
  
  Less( Op1 op1, Op2 op2 ) : op1(op1), op2(op2) {}
  
  template <class T> 
  auto operator()( T value ) -> decltype( op1( value ) < op2( value ) ) {
    return op1( value ) < op2( value );
  }
};

template <typename Op1, typename Op2>
inline Less< typename enable_if<std::is_base_of<Functor, Op1>::value, Op1>::type,
                typename enable_if<std::is_base_of<Functor, Op2>::value, Op2>::type >
operator < ( Op1 a, Op2 b ) {
  return Less<Op1, Op2>( a, b );
}

template <typename Op1, typename Op2>
inline Less< Constant<typename enable_if<!std::is_base_of<Functor, Op1>::value, Op1>::type>,
                typename enable_if<std::is_base_of<Functor, Op2>::value, Op2>::type >
operator < ( Op1 a, Op2 b ) {
  Constant<Op1> c(a);

  return Less<Constant<Op1>, Op2>( c, b );
}

template <typename Op1, typename Op2>
inline Less< typename enable_if<std::is_base_of<Functor, Op1>::value, Op1>::type,
                Constant<typename enable_if<!std::is_base_of<Functor, Op2>::value, Op2>::type> >
operator < ( Op1 a, Op2 b ) {
  Constant<Op2> c(b);

  return Less<Op1, Constant<Op2>>( a, c );
}

//===GREATER===//

template <typename Op1, typename Op2>  
struct Greater : public Functor{
  Op1 op1;
  Op2 op2;
  
  Greater( Op1 op1, Op2 op2 ) : op1(op1), op2(op2) {}
  
  template <class T> 
  auto operator()( T value ) -> decltype( op1( value ) > op2( value ) ) {
    return op1( value ) > op2( value );
  }
};

template <typename Op1, typename Op2>
inline Greater< typename enable_if<std::is_base_of<Functor, Op1>::value, Op1>::type,
                typename enable_if<std::is_base_of<Functor, Op2>::value, Op2>::type >
operator > ( Op1 a, Op2 b ) {
  return Greater<Op1, Op2>( a, b );
}

template <typename Op1, typename Op2>
inline Greater< Constant<typename enable_if<!std::is_base_of<Functor, Op1>::value, Op1>::type>,
                typename enable_if<std::is_base_of<Functor, Op2>::value, Op2>::type >
operator > ( Op1 a, Op2 b ) {
  Constant<Op1> c(a);

  return Greater<Constant<Op1>, Op2>( c, b );
}

template <typename Op1, typename Op2>
inline Greater< typename enable_if<std::is_base_of<Functor, Op1>::value, Op1>::type,
                Constant<typename enable_if<!std::is_base_of<Functor, Op2>::value, Op2>::type> >
operator > ( Op1 a, Op2 b ) {
  Constant<Op2> c(b);

  return Greater<Op1, Constant<Op2>>( a, c );
}

//===LAZY===//

template <typename T, typename F>
class LazyCollection{
  public:
    LazyCollection()
    {}

    // template <typename Fu>
    // class iterator {
    //   public:
    //     iterator( int start , vector<int>& cache, F& func): actual( start ), cache(cache), func(func)
    //     {
    //       firstAccess = true;
    //       isLastCalculated = false;
    //       last = 0;
    //     }
        
    //     bool operator != ( const iterator& b ) {
    //       if(!isLastCalculated){
    //         last = previousFiltered(b.actual);
    //         isLastCalculated = true;
    //       }
    //       return actual <= last;
    //     }
        
    //     iterator& operator++ () {
    //       actual = nextFiltered(actual);
    //       cache.push_back(actual);
    //       return *this;
    //     }
        
    //     int operator * () {
    //       if(firstAccess)
    //       {
    //         if(func(actual) == true)
    //         {
    //           cache.push_back(actual);
    //         }
    //         else
    //         {
    //           operator++();
    //         }
    //         firstAccess = false;
    //       }
    //       return actual;
    //     }

    //     int nextFiltered(int n)
    //     {
    //       ++n;
    //       while(func(n) == false)
    //         ++n;
    //       return n;
    //     }

    //     int previousFiltered(int n)
    //     {
    //       while(func(n) == false)
    //         --n;
    //       return n;
    //     }
        
    //   private:
    //     bool firstAccess;
    //     bool isLastCalculated;
    //     int last;
    //     int actual;
    //     vector<int>& cache;
    //     typename std::enable_if<std::is_base_of<Functor, Fu>::value, Fu>::type func;
    // };
    
    // iterator<F> begin() {
    //   return iterator<F>( *interv.begin(), cache, func );
    // }
    
    // iterator<F> end() {
    //   return iterator<F>( *interv.end(), cache, func );
    // }

    // typename std::enable_if<std::is_base_of<Functor, F>::value, F>::type
    // getFunctor()
    // {
    //   return func;
    // }

    // Interval getInterval()
    // {
    //   return interv;
    // }

    // void print()
    // {
    //   cout << "Vec: ";
    //   for(auto elem : cache)
    //     cout << elem << " | ";
    //   cout << endl;
    // }

    void create(int head) {
      head = head;
    }

    template<typename F1, typename F2>
    void create(const vector<int>& refList, F func, int head, LazyCollection<T, F1> leftLazy, LazyCollection<T, F2> rightLazy)
    {
      refList = refList;
      funcGenerator = func;
      head = head;
      leftLazy = leftLazy;
      rightLazy = rightLazy;
    }

    template<typename F1, typename F2>
    void create(const vector<int>& refList, int head, LazyCollection<T, F1> leftLazy, LazyCollection<T, F2> rightLazy)
    {
      refList = refList;
      head = head;
      leftLazy = leftLazy;
      rightLazy = rightLazy;
    }
    
  private:
    const vector<int>& refList;
    typename std::enable_if<std::is_base_of<Functor, F>::value, F>::type funcGenerator;
    vector<int> ownList;
    LazyCollection<T, F> leftLazy;
    LazyCollection<T, F> rightLazy;
};

// //==========================================//

// template <typename F>
// inline typename std::enable_if<
//   std::is_base_of<Functor, F>::value ,
//   LazyCollection<F>>::type
// operator | (Interval interv, F f )
// {
//   LazyCollection<F> lazy (interv, f);
//   return lazy;
// }

// template <typename F1, typename F2>
// inline auto
// operator | (LazyCollection<F1> lazy, F2 f ) ->
//                   typename std::enable_if<
//                   std::is_base_of<Functor, F1>::value &&
//                   std::is_base_of<Functor, F2>::value ,
//                   LazyCollection<decltype(lazy.getFunctor() && f)>>::type
// {
//   auto func =  (lazy.getFunctor() && f);
  
//   LazyCollection<decltype(func)> auxLazy (lazy.getInterval(), func);
//   return auxLazy;
// }

// template <typename T, typename F>
// inline typename std::enable_if<
//   std::is_member_object_pointer<int(T::iterator::*)>::value &&
//   std::is_base_of<Functor, F>::value,
//   vector<typename T::value_type>>::type
// operator | ( T tab, F f ){
//   vector<typename T::value_type> v;

//   for( auto x : tab )
//   {
//     if(f( x ))
//     {
//      v.push_back(x);
//     }
//   }
  
//   return v;
// }

//===Declaring a variable X===//
Var x;

//============================//

template <typename T>
T head(vector<T> list)
{
  return list[0];
}

template <typename T>
vector<T> tail(vector<T> list)
{
  list.erase(list.begin());
  return list;
}

//===QS===//
template <typename T, typename F>
inline typename std::enable_if<
  std::is_base_of<Functor, F>::value,
  LazyCollection<typename T::value_type, F>>::type
qs( vector<T> lista, F func ) {
  if(lista.size() == 1)
  {
    return new LazyCollection<T, F>(head(lista));
  }
  else
  {
    return new LazyCollection<T, F>(lista, func,
                          head(lista),
                          qs( tail( lista ), x < head(lista)),
                          qs( tail( lista ), x > head(lista)) );
  }
}

template <typename T>
inline LazyCollection<T, F> qs( vector<T> lista ) {
  if(lista.size() == 1)
  {
    return new LazyCollection<T, F>(head(lista));
  }
  else
  {
    return new LazyCollection<T, F>(lista, head(lista),
                          qs( tail( lista ), x < head(lista)),
                          qs( tail( lista ), x > head(lista)) );
  }
}

int main() {
  vector<int> tab = { 3, 8, 1, 2, 5, 4, 7, 6, 10, 9 };

  auto f = qs( tab );

  // for( auto s : f )
  //   cout << s << endl;

  return 0;  
}