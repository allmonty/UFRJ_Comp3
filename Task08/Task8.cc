#include <iostream>
#include <string>

using namespace std;

class Exception
{
    public:
        Exception(string e): message("Exception:" + e){}

        const string message;
};

struct Data {
  int dia;
  int mes;
  int ano;
};

template <typename T>
class RefCounter {
public:
    RefCounter() : ptr( nullptr ), count(0) { cout << "Criou RefCounter |01| " << ptr << endl; }
    RefCounter( T* d ) : ptr( d ), count(1) { cout << "Criou RefCounter |02| " << ptr << endl; }
    
    void addOneRef()
    {
    	cout << "Ganhou uma referência | " << ptr << " | Antes: "<< count;
    	count++;
    	cout << " | Agora: " << count << endl;
    }

    void delOneRef()
    {
    	cout << "Perdeu uma referência | " << ptr << " | Antes: "<< count;
    	count--;
    	if(count <= 0)
    	{
    		cout << " | Agora: Destruido" << endl;
    		delete ptr;
    		delete this;
    	}
    	else
    	{
    		cout << " | Agora: " << count << endl;
    	}
    }

private:
	int count;
	T* ptr;
};

template <typename T>
class AutoRef {
public:
    AutoRef()
    {
    	ptrCounter = new RefCounter<T>();
    	cout << "Criou AutoRef |01| " << ptrCounter << endl;
    }

    AutoRef( T* d )
    {
    	ptrCounter = new RefCounter<T>(d);
    	cout << "Criou AutoRef |02| " << ptrCounter << endl;
    }

    ~AutoRef() {
		ptrCounter->delOneRef();
    }

    AutoRef<T>& operator = ( const AutoRef<T>& valor ) {
    	ptrCounter->delOneRef();
    	ptrCounter = valor.ptrCounter;
    	ptrCounter->addOneRef();
    	return *(this);
    }

    AutoRef<T>& operator = ( T* valor ) {
    	ptrCounter->delOneRef();
    	ptrCounter = new RefCounter<T>(valor);
    	return *(this);
    }

    T* operator -> () {
      	if( ptrCounter->ptr == nullptr )
			throw Exception("null pointer");
      
      	return ptrCounter->ptr;
    }
    
    T& operator * () {
      	if( ptrCounter->ptr == nullptr )
			throw Exception("null pointer");
      
      	return *(ptrCounter->ptr);
    }

private:
	RefCounter<T>* ptrCounter;
};

int main() {
	AutoRef<Data> a, b;

	cout << endl;
	  
	a = new Data();
	  
	cout << endl;

	b = new Data();
  
	cout << endl;

	cout << "===Atribuição===" << endl;
  	a = b;

  	cout << endl << "Final da main" << endl << endl;

  	return 0;
}
