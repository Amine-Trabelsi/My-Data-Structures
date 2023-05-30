// Amine trabelsi
// hashmap impelementation using linear probing
#include <iostream>
#include <functional>
#include <vector>
#include <utility>


template <class K, class V> 
class ILinkedHashMap {
	public:
		virtual int size() = 0;
		virtual bool isEmpty() = 0;
		virtual void put(K key) = 0;
		virtual void remove(K key) = 0;
		virtual V get(K key) = 0;
};
template <class K, class V> 
class Hashmap : ILinkedHashMap<K, V> {
	private :
		int number_of_elements = 0;
		const int MAX_SIZE = 1000000;
		std::hash<K> Hash_function;
		std::vector<std::size_t> container;
		std::vector<std::string> orig;
		std::vector<V> values;
		int compress(std::size_t hash_code) {
			return ((939565 * hash_code + 4040123209) % 1041530473) % MAX_SIZE;
		}
	public :
		Hashmap() {
			container.assign(MAX_SIZE+60,-1);
			orig.assign(MAX_SIZE+60,"");
			values.assign(MAX_SIZE+60,0);
		}
		int size() { return this->number_of_elements; }
		bool isEmpty(){return this->number_of_elements == 0; };
		void put(K key){
			std::size_t hsh = Hash_function(key);
			int index = compress(hsh);
			while(values[index] != 0 && container[index] != hsh) {
				index = (index+1) % MAX_SIZE;
			}
			container[index] = hsh;
			orig[index] = key;
			values[index]++;
			number_of_elements++;
		};
		void remove(K key){
			std::size_t hsh = Hash_function(key);
			int index = compress(hsh);
			while(values[index] != 0 && container[index] != hsh) {
				index = (index+1) % MAX_SIZE;
			}
			values[index] = 0;
		};
		V get(K key){
			std::size_t hsh = Hash_function(key);
			int index = compress(hsh);
			while(values[index] != 0 && container[index] != hsh) {
				index = (index+1) % MAX_SIZE;
			}
			return values[index];

		}
		int index(std::string s) {
			return compress(Hash_function(s));
		}
		void extract(std::vector<std::pair<std::string,int>> &v) {
			for(int i=0;i<MAX_SIZE;i++) {
				if((int)values[i] > 0) {
					v.push_back({orig[i],values[i]});
				}
			}
		}
};
bool biggerorequal(std::pair<std::string,int> &a,std::pair<std::string,int> &b) {
	if(a.second == b.second) {
		return a.first <= b.first;
	}
	return a.second > b.second;
}
void merge(std::vector<std::pair<std::string,int>> &v, int left,int mid, int right) {
	int first_pointer = left;
	int second_pointer = mid+1;
	int length = right-left+1;
	// std::cout << left << " " << mid << " " << right << std::endl;
	std::vector<int> temparr(length);
	std::vector<std::string> temparrN(length);
	for(int i=0;i<length;i++) {
		if((first_pointer <= mid && second_pointer <= right && biggerorequal(v[first_pointer], v[second_pointer])) 
			|| second_pointer > right) {
			// std::cout << "here" << std::endl;
			temparr[i] = v[first_pointer].second;
			temparrN[i] = v[first_pointer].first;
			first_pointer++;
		} else if(second_pointer <= right) {
			// std::cout << i << " : " << second_pointer << std::endl;
			temparr[i] = v[second_pointer].second;
			temparrN[i] = v[second_pointer].first;
			second_pointer++;
		}
	}
	for(int i=0;i<length;i++) {
		v[i+left].second = temparr[i];
		v[i+left].first = temparrN[i];
	}
}
void merge_sort(std::vector<std::pair<std::string,int>> &v, int left, int right) {
	// std::cout << left << " " << right << std::endl;
	if(left == right) {
		return;
	}
	// else
	int mid = (left+right)/2;
	merge_sort(v, left,mid);
	merge_sort(v, mid+1,right);
	merge(v, left,mid,right);
	// std::cout << "done" << std::endl;
}
int main() {
	int N;
	std::cin>>N;
	Hashmap<std::string,int> mp;
	for(int i=0;i<N;i++) {
		std::string s;
		std::cin>>s;
		mp.put(s);
	}
	std::vector<std::pair<std::string,int>> answer;// = {{"not",1},{"to",2},{"be",2},{"or",1}};
	mp.extract(answer);
	merge_sort(answer, 0, (int)answer.size() - 1);
	for(auto i:answer) {
		std::cout << i.first << " " << i.second << std::endl;
	}
	return 0;
}