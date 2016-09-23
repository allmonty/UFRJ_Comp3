#include <iostream>
#include <string>

using namespace std;

class ArrayInt
{
public:
	//Esse método de atribuição direta é melhor,
	//pois ele chama os construtores das variáveis
	ArrayInt(int size) : length(size), array(new int[size])
	{}

	void put(int index, int value)
	{
		if(is_inside_bounds(index))
		{
			array[index] = value;
		}
	}

	int at(int index)
	{
		if(is_inside_bounds(index))
		{
			return array[index];
		}
		return 0;
	}

protected:
	bool is_inside_bounds(int index)
	{
		if(index >= length || index < 0)
		{
			erro("Access is out of bounderies!!");
			return false;
		}
		else
		{
			return true;
		}
	}

	void erro(string erro)
	{
		cout << "Erro: " << erro << endl; 
	}

private:
	int length = 0;
	int* array;
};

int main()
{
	ArrayInt myArray = 10;

	std::cout << "Putting 42 in index 9...\n";
	myArray.put(9, 42);
	std::cout << "Putting 42 in index 11...\n";
	myArray.put(11, 42);
	std::cout << "Putting 42 in index -1...\n";
	myArray.put(-1, 42);

	std::cout << "\n\nAccessing index 9...\n";
	std::cout << myArray.at(9) << "\n";
	std::cout << "Accessing index 11...\n";
	std::cout << myArray.at(11) << "\n";
	std::cout << "Accessing index -1...\n";
	std::cout << myArray.at(-1) << "\n";
}