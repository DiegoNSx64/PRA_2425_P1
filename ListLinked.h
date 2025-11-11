#include <ostream>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {

    private:
 	Node<T>* first; 
	int n; 
       

    public:

        ListLinked() : first(nullptr), n(0) {}
	~ListLinked()  {
		while (first != nullptr) {
			Node<T>* aux = first->next;
			delete first;
			first = aux;
		}
	}


	void insert(int pos,  T e) override {
		if (pos < 0 || pos > n)
			throw std::out_of_range("Posición inválida en insert()");


		if (pos == 0)
			first = new Node<T>(e, first);
		else {
			Node<T>* prev = first;
			for (int i = 0; i < pos - 1; ++i)
				prev = prev->next;


			prev->next = new Node<T>(e, prev->next);
		}
		++n;
	}



	void append( T e) override {
		insert(n, e);
	}


	void prepend( T e) override {
		insert(0, e);
	}



	T remove(int pos) override {
		if (pos < 0 || pos >= n)
			throw std::out_of_range("Posición inválida en remove()");


		Node<T>* eliminar;
		T valor;


		if (pos == 0) {
			eliminar = first;
			valor = first->data;
			first = first->next;
		} else {
			Node<T>* prev = first;
			for (int i = 0; i < pos - 1; ++i)
				prev = prev->next;


			eliminar = prev->next;
			valor = eliminar->data;
			prev->next = eliminar->next;
		}


		delete eliminar;
		--n;
		return valor;
	}
	
	T get(int pos) const override {
		if (pos < 0 || pos >= n)
			throw std::out_of_range("Posición inválida en get()");


		Node<T>* actual = first;
		for (int i = 0; i < pos; ++i)
			actual = actual->next;


		return actual->data;
	}



	int search( T e) const override {
		Node<T>* actual = first;
		int i = 0;
		while (actual != nullptr) {
		if (actual->data == e)
			return i;
		actual = actual->next;
		++i;
		}
		return -1;
	}



	bool empty() const override {
		return n == 0;
	}



	int size() const override {
		return n;
	}



	T operator[](int pos) {
		if (pos < 0 || pos >= n)
			throw std::out_of_range("Posición inválida en operator[]");


		Node<T>* actual = first;
		for (int i = 0; i < pos; ++i)
			actual = actual->next;


		return actual->data;
	}



	friend std::ostream& operator<<(std::ostream& out, const ListLinked<T>& list) {
		Node<T>* actual = list.first;
		out << "[";
		while (actual != nullptr) {
		out << actual->data;
		if (actual->next != nullptr)
			out << ", ";
		actual = actual->next;
		}
		out << "]";
		return out;
	}
};
