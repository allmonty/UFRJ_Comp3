#include <iostream>

class ArrayInt
{
public:
	ArrayInt(int size)
	{
		length = size;
		array = new int[size];
	}

	void put(int index, int value)
	{
		if(index >= length || index < 0)
		{
			std::cout << "Access [" << index << "] is out of bounderies!!\n";
			return;
		}

		std::cout << "Success!!!\n";
		array[index] = value;
	}

	int at(int index)
	{
		if(index >= length || index < 0)
		{
			std::cout << "Access [" << index << "] is out of bounderies!!\n";
			return 0;
		}

		std::cout << "Success!!!\n";
		return array[index];
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