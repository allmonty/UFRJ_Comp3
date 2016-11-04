#include <iostream>
#include <string>

using namespace std;

class Exception
{
    public:
        Exception(string e): message("Exception:" + e){}

        const string message;
};

template <int N>
struct Fibonacci
{
  static const long long result = Fibonacci<N-1>::result + Fibonacci<N-2>::result;
};

template <>
struct Fibonacci<1>
{
  static const long long result = 1;
};

template <>
struct Fibonacci<0>
{
  static const long long result = 0;
};

template <int A, int B>
struct MDC
{
  static const int result = MDC<A%B, B%A>::result;
};

template <int A>
struct MDC<A, 0>
{
  static const int result = A;
};

template <int B>
struct MDC<0, B>
{
  static const int result = B;
};

int main()
{
  cout << Fibonacci<50>::result << endl;

  cout << MDC<18, 12>::result << endl;
  cout << MDC<18, 24>::result << endl;
  cout << MDC<18, 36>::result << endl;

	return 0;
}