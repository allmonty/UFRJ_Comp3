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

int main()
{
  int tab[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  vector<int> v;

  cout << "====TAB====" << endl;
  tab | []( auto x ) { cout << x*x << endl; };
  
  cout << "===TAB->V===" << endl;
  tab | [&v]( auto x ) { v.push_back( x ); };
  
  cout << "===VECTOR===" << endl;
  v   | []( auto x ) { cout << x*x << endl; };

  cout << "===TESTE COM STRING===" << endl;

  string tab2[3] = {"To", "Testando", "\\o/"};

  vector<string> v2;

  cout << "====TAB====" << endl;
  tab2 | []( auto x ) { cout << x << endl; };
  
  cout << "===TAB->V===" << endl;
  tab2 | [&v2]( auto x ) { v2.push_back( x ); };
  
  cout << "===VECTOR===" << endl;
  v2   | []( auto x ) { cout << x << endl; };

	return 0;
}