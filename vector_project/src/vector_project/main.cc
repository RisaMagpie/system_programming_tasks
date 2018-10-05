#include <new>
#include <algorithm>
#include <fstream>
#include <random>
using namespace std;

template <typename T>
class Vector
{
protected:
	T * allocator;
public:
	size_t size;
	//constructors:

	//empty constructor
	Vector()
	{
		allocator = new T[0];
		size = 0;
	}

	//copy constructor
	Vector(Vector<T> &existingVector)
	{
		this->size = existingVector.sizeOfVector();
		for (size_t counter = 0; counter < this->size; counter++)
		{
			allocator[counter] = ::forward(existingVector.allocator[counter]);
		}
	}

	//move constructor
	Vector(Vector &&existingVector)
	{
		allocator = nullptr;
		size = existingVector.size;
		allocator = existingVector.allocator;
		existingVector.allocator = nullptr;
	}

	//simple methods
	//begin() - return iterator on the first element
	T *begin() const
	{
		return allocator;
	}

	//end() - iterator on the after last element
	T *end() const
	{
		return (allocator + size);
	}

	//size() - num of elements in the Vector
	size_t sizeOfVector() const
	{
		return size;
	}

	//difficult methods:
	//push_back(T) - add element at the tail
	void push_back(T&& value)
	{
		T *newAlloc = new T[size + 1];
		size_t counter = 0;
		while (counter < size) {
			newAlloc[counter] = ::move(this->allocator[counter]);
			counter++;
		}
		newAlloc[size] = ::move(value);
		delete[] allocator;
        allocator = newAlloc;
		size += 1; 
	}

	//pop_back() - drop element at the tail
	void pop_back()
	{
		size -= 1;
		T *newAlloc = new T[size];
		size_t counter = 0;
		while (counter < size) {
			newAlloc[counter] = ::move(this->allocator[counter]);
			counter++;
		}
		delete[] allocator;
        allocator = newAlloc;		 
	}

	//erase() - delete elements //look cpp
	//erase one element at position = num_of_pos
	void erase(size_t num_of_pos)
	{
		//move the tail on one position and pop_back
		if (this.sizeOfVector() >= num_of_pos) {
			for (size_t counter = num_of_pos; counter<this.sizeOfVector(); counter++) {
				allocator[counter] = ::forward(allocator[counter + 1]);
			}
			this.pop_back();
		}
	}

	void erase(size_t first_num, size_t last_num)
	{
		if (first_num>last_num) {
			first_num += last_num;
			last_num = first_num - last_num;
			first_num = first_num - last_num;
		}
		//move the tail on (last_num-first_num) position and pop_back
		if (this.sizeOfVector() >= last_num) {
			for (size_t counter = first_num; counter<this.sizeOfVector(); counter++) {
				allocator[counter] = ::forward(allocator[counter + (last_num - first_num)]);
			}
			for (size_t counter = first_num; counter<size; counter++) {
				this.pop_back();
			}
		}
	}
	//swap() vectors
	void swap(Vector<T> &rightVector)
	{
		Vector<T> tmp(*this);
		this = ::move(rightVector);
		rightVector = ::move(tmp);
	}

	//friend void Swap(Vector<T>&, Vector<T>&);

	//operators:
	//operator=
	Vector<T> &operator=(const Vector<T> &&rightVector)
	{
		Vector<T> tmp(rightVector);
		this.swap(tmp);
		return *this;
	}

	Vector<T> &operator=(Vector<T> &&rightVector)
	{
		this->swap(rightVector);
		return *this;
	}

	T &operator[](const size_t pos) {
		return allocator[pos];
	}

	//destructor
	~Vector()
	{
		delete[] allocator;
	}
};

//swap() vectors
template <typename T>
void Swap(Vector<T> &leftVector, Vector<T> &rightVector)
{
	leftVector.swap(rightVector);
};

int main()
{
	::ofstream myLog("myLog.txt", ::ofstream::out);
	myLog << "Hello";

	//create vector with ofstream elements
	::ofstream ofs1("ofs1.txt", ::ofstream::out);
	::ofstream ofs2("ofs2.txt", ::ofstream::out);
	::ofstream ofs3("ofs3.txt", ::ofstream::out);
	::ofstream ofs4("ofs4.txt", ::ofstream::out);

	Vector<::ofstream> myVec;
	
	myVec.push_back(::move(ofs1));
	myVec.push_back(::move(ofs2));
	myVec.push_back(::move(ofs3));
	myVec.push_back(::move(ofs4));

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(myVec.begin(), myVec.end(), g);

	myVec[0] << 1;
	myVec[1] << 2;
	myVec[2] << 3;
	myVec[3] << 4;

	return 0;
}