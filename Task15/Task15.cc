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

//===INTERVAL=//

class Interval {
  public:
    Interval( int start, int end ): _start(start), _end(end) {}
    
    class iterator {
      public:
        iterator( int start ): actual( start ) {}
        
        bool operator != ( const iterator& b ) {
          return actual != b.actual;
        }
        
        iterator& operator++ () {
          ++actual;
          return *this;
        }
        
        int operator * () {
          return actual;
        }
        
      private:
        int actual;  
    };
    
    iterator begin() {
      return iterator( _start );
    }
    
    iterator end() {
      return iterator( _end);
    }
    
  private:
    int _start;
    int _end;
};

//===LAZY===//

template <typename F>
class LazyCollection{
  public:
    LazyCollection(Interval interval, F functor) : interv(interval), func(functor)
    {}

    template <typename Fu>
    class iterator {
      public:
        iterator( int start , vector<int>& cache, F& func): actual( start ), cache(cache), func(func)
        {
          firstAccess = true;
          isLastCalculated = false;
          last = 0;
        }
        
        bool operator != ( const iterator& b ) {
          if(!isLastCalculated){
            last = previousFiltered(b.actual);
            isLastCalculated = true;
          }
          return actual <= last;
        }
        
        iterator& operator++ () {
          actual = nextFiltered(actual);
          cache.push_back(actual);
          return *this;
        }
        
        int operator * () {
          if(firstAccess)
          {
            if(func(actual) == true)
            {
              cache.push_back(actual);
            }
            else
            {
              operator++();
            }
            firstAccess = false;
          }
          return actual;
        }

        int nextFiltered(int n)
        {
          ++n;
          while(func(n) == false)
            ++n;
          return n;
        }

        int previousFiltered(int n)
        {
          while(func(n) == false)
            --n;
          return n;
        }
        
      private:
        bool firstAccess;
        bool isLastCalculated;
        int last;
        int actual;
        vector<int>& cache;
        typename std::enable_if<std::is_base_of<Functor, Fu>::value, Fu>::type func;
    };
    
    iterator<F> begin() {
      return iterator<F>( *interv.begin(), cache, func );
    }
    
    iterator<F> end() {
      return iterator<F>( *interv.end(), cache, func );
    }

    typename std::enable_if<std::is_base_of<Functor, F>::value, F>::type
    getFunctor()
    {
      return func;
    }

    Interval getInterval()
    {
      return interv;
    }

    void print()
    {
      cout << "Vec: ";
      for(auto elem : cache)
        cout << elem << " | ";
      cout << endl;
    }
    
  private:
    vector<int> cache;
    Interval interv;
    typename std::enable_if<std::is_base_of<Functor, F>::value, F>::type func;
};

//==========================================//

template <typename F>
inline typename std::enable_if<
  std::is_base_of<Functor, F>::value ,
  LazyCollection<F>>::type
operator | (Interval interv, F f )
{
  LazyCollection<F> lazy (interv, f);
  return lazy;
}

template <typename F1, typename F2>
inline auto
operator | (LazyCollection<F1> lazy, F2 f ) ->
                  typename std::enable_if<
                  std::is_base_of<Functor, F1>::value &&
                  std::is_base_of<Functor, F2>::value ,
                  LazyCollection<decltype(lazy.getFunctor() && f)>>::type
{
  auto func =  (lazy.getFunctor() && f);
  
  LazyCollection<decltype(func)> auxLazy (lazy.getInterval(), func);
  return auxLazy;
}

//===Declaring a variable X===//
Var x;

class teste{};

int main() {
  Interval v(1, 1 << 31 );

  auto lazy = (v | x % 2 == 0) | x % 3 == 0;

  int i = 0;
  for(auto elem : lazy)
  {
    if(++i > 100) break;
    cout << elem << endl;
  }

  return 0;  
}