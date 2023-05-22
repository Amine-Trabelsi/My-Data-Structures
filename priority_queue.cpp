#include <iostream>
#include <vector>
#include <math.h>
using namespace std;


// binary heap
// type T is expected to be comparable
template<typename T>
class binary_heap {
public:
	// function to insert an element to the heap
	virtual void insert(T value) = 0;
	// function to get the minimum element from the heap
	virtual T top() = 0;
	// function to pop the minimum element
	virtual void pop() = 0;
};

// minimum priority queue implementation
template<typename T>
class my_priority_queue : public binary_heap<T> {
private:
	int sz = 0;
	vector<T> container;
	void clean_up(int node) {
		if(node == 0)return;
		int parent = floor(((double)node - 1)/2);
		if(container[parent] > container[node]) {
			swap(container[parent], container[node]);
			clean_up(parent);
		}
	}
	void clean_down(int node) {
		int left = 2 * node + 1;
		int right = 2 * node + 2;
		if(left >= sz)return; // if there is no left node then there is no children
		if(container[left] <= container[right]) {
			if(container[left] < container[node]){
				swap(container[left], container[node]);
				clean_down(left);
			}
		} else {
			if(container[right] < container[node]) {
				swap(container[right], container[node]);
				clean_down(right);
			}
		}
	}
public:	
	void insert(T value) override {
		// insert at last position in vector
		// fix heap property (go up)
		container.push_back(value);
		sz++;
		clean_up(sz-1);
	}
	T top() override {
		// root at index 1
		if(sz == 0) throw runtime_error("PQ is empty");
		return container[0];
	}
	void pop () override {
		// swap root with last node
		// delete last node
		// fix heap property (go down)
		swap(container[0], container[sz-1]);
		container.pop_back();
		sz--;
		clean_down(0);
	}
};

int main() {
	my_priority_queue<int> q;
	int n; cin>>n;
	while(n--) {
		int x;
		cin>>x;
		q.insert(x);
		cout << q.top() << endl;
	}
	return 0;
}