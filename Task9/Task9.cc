#include <iostream>
#include <string>

using namespace std;

class Exception
{
    public:
        Exception(string e): message("Exception:" + e){}

        const string message;
};

template <typename Head, typename... Tail>
struct Tuple
{
	Head head;
	Tuple<Tail...> tail;
};

template <typename Head>
struct Tuple<Head>
{
	Head head;
};

template <typename H>
Tuple<H> makeTuple(H head)
{
	Tuple<H> myTuple;
	myTuple.head = head;

	return myTuple;
}

template <typename H, typename... T>
Tuple<H, T...> makeTuple(H head, T... tail)
{
	Tuple<H, T...> myTuple;
	myTuple.head = head;
	myTuple.tail = makeTuple(tail...);

	return myTuple;
}

template <int i, typename H>
H& get(Tuple<H>& tu)
{
	return tu.head;
}

template <int i, typename H, typename...T>
H& get(Tuple<H, T...>& tu)
{
	if(i == 0)
	{
		return tu.head;
	}
	else if(i > 0)
	{
		return get< i-1 >(tu.tail);
	}
	else
	{
		throw new Exception("Get method of Tuples cant receive negative index!");
	}
}

int main()
{
	auto t = makeTuple(10, 20, 30, 40, 50);

	cout << get<0>(t) << endl;
	cout << get<1>(t) << endl;
	cout << get<2>(t) << endl;
	cout << get<3>(t) << endl;
	cout << get<4>(t) << endl;
	cout << get<5>(t) << endl;
	cout << get<-1>(t) << endl;

	return 0;
}