#include<iostream>
#include<vector>

template<typename T>
struct Node
{
	T n;
	struct Node* prev;
};

template<typename T>
class stack 
{
public:
	stack(size_t cap = 2) : s(0)
	{
		Head = nullptr;
	}

	stack(stack& st) 
	{
		Node<T>* next = st.get_head();
		
		while (next != nullptr)
		{
			push_back(next->n);
			next = next->prev;
		}

		reverse();
	}

	Node<T>* get_head() const { return Head; }

	size_t size()const { return s; }

	void push_back(T push) { Head = new Node<T>{ push, Head }; s++; }

	T pop_back() 
	{
		T ret = Head->n;
		auto Cop = Head;
		Head = Head->prev;

		delete Cop;

		s--;

		return ret;
	}

	void clear()
	{
		Node<T>* next = Head;
		while (next != nullptr)
		{
			Head = next;
			next = next->prev;
			delete Head;
		}
		s = 0;
	}

	void reverse()
	{
		Node<T>* current = Head;
		Node<T>* prev = nullptr, * next = nullptr;

		while (current != nullptr) 
		{
			next = current->prev;
			current->prev = prev;

			prev = current;
			current = next;
		}
		Head = prev;
	}

	void print(std::ostream& out) const
	{
		Node<T>* next = Head;

		while (next != nullptr)
		{
			out << next->n << ", ";
			next = next->prev;
		}
		out << std::endl;
	}

	stack& operator +(const T& plus)
	{
		push_back(plus);
		return *this;
	}

	T operator --() { return pop_back(); }

	~stack() 
	{
		clear();
	}

private:

	Node<T>* Head;
	size_t s;

};

template<typename T>
std::ostream& operator<< (std::ostream& out, const stack<T>& st)
{
	st.print(out);
	return out;
}

void test_push_Stack() 
{
	stack<int> S;

	for (int i = 0; i < 100; ++i) { S.push_back(i); }

	std::cout << "test_push_Stack - Done!" << std::endl;
}

void test_pop_Stack()
{
	stack<int> S;

	for (int i = 0; i < 100; ++i) { S.push_back(i); }

	while (S.size() != 0) 
	{
		std::cout << S.pop_back() << ", ";
	}

	std::cout << "test_pop_Stack - Done!" << std::endl;
}

void test_copy_Stack() 
{
	stack<int> S;

	for (int i = 0; i < 100; ++i) { S.push_back(i); }

	stack<int> copy(S);

	while (copy.size() != 0)
	{
		std::cout << copy.pop_back() << ", ";
	}

	std::cout << "test_copy_Stack - Done!" << std::endl;
}

void test_print_Stack()
{
	stack<int> S;

	for (int i = 0; i < 100; ++i) { S.push_back(i); }


	std::cout << S;
	std::cout << "test_print_Stack - Done!" << std::endl;
}

void test_PM_Stack()
{
	stack<int> S;

	for (int i = 0; i < 100; ++i) { S+i; }

	while (S.size() != 0) { std::cout << --S << ", "; }

	std::cout << "test_PM_Stack - Done!" << std::endl;
}

int main() 
{
	test_push_Stack();
	std::cout << std::endl;

	test_pop_Stack();
	std::cout << std::endl;

	test_copy_Stack();
	std::cout << std::endl;

	test_print_Stack();
	std::cout << std::endl;

	test_PM_Stack();

	return 0;
}