#include <iostream>
#include <vector>

using namespace std;

template <typename T, typename F>
void forEach(T begin, T end, F functor)
{
	for(auto itr = begin; itr != end; ++itr)
	{
		functor(*itr);
	}
}

int main()
{
	vector<int> v1 = {1, 2, 3, 4};
	int v2[] = {1, 2, 3, 4};

	cout << "Vector:" << endl;
	forEach(v1.begin(), v1.end(), [](int x){cout << x << endl;});

	cout << "Array:" << endl;
	forEach(&v2[1], &v2[3], [](int x){cout << x << endl;});
}