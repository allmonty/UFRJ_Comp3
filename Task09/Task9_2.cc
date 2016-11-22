#include <iostream>
#include <string>

using namespace std;

//Solution from https://github.com/eliben/code-for-blog/blob/master/2014/variadic-tuple.cpp

class Exception
{
    public:
        Exception(string e): message("Exception:" + e){}

        const string message;
};

template <typename... Ts> struct Tuple {};

template <typename T, typename... Ts>
struct Tuple<T, Ts...> : Tuple<Ts...>
{
  Tuple(T t, Ts... ts) : Tuple<Ts...>(ts...), tail(t){}

  T tail;
};

template <size_t, typename> struct elem_type_holder;

template <typename T, typename... Ts>
struct elem_type_holder<0, Tuple<T, Ts...>>
{
   typedef T type;
};

template <size_t k, typename T, typename... Ts>
struct elem_type_holder<k, Tuple<T, Ts...>>
{
  typedef typename elem_type_holder<k - 1, Tuple<Ts...>>::type type;
};

template <size_t k, typename... Ts>
typename std::enable_if< k == 0, typename elem_type_holder<0, Tuple<Ts...>>::type&>::type
get(Tuple<Ts...>& t)
{
  return t.tail;
}

template <size_t k, typename T, typename... Ts>
typename std::enable_if< k != 0, typename elem_type_holder<k, Tuple<T, Ts...>>::type&>::type
get(Tuple<T, Ts...>& t) {
  Tuple<Ts...>& base = t;
  return get<k - 1>(base);
}

int main()
{
	auto t = Tuple<int, double, string>(10, 20.5, "Test");

	cout << get<0>(t) << endl;
	cout << get<1>(t) << endl;
	cout << get<2>(t) << endl;

	return 0;
}