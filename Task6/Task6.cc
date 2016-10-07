#include <iostream>
#include <vector>

using namespace std;

template <typename T, typename F>
void forEach(vector<T> v, F functor)
{
	for(int i = 0; i < v.size(); i++)
	{
		functor(v[i]);
	}
}

template <typename T>
vector<T>& operator<<(vector<T>& v, const T& x)
{
	v.push_back(x);
	return v;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
	os << "[ ";
    forEach(v, [](int x){cout << x << " ";} );
    os << "]";
    return os;
}

int main()
{
	vector<int> v;

	// for(int i = 0; i < 10; i++)
	// {
	// 	v << i;
	// 	cout << "Size: " << v.size() << "   Capacity: " << v.capacity() << endl;
	// 	cout << v << endl << endl;
	// }

	v << 5 << 8 << 9;
	
	cout << v << endl;

	forEach(v, [](auto x){cout << x*x << " ";});
	cout << endl;
}