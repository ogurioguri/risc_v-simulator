#pragma once
namespace Komeiji {
template<class T, int N>
class circularqueue {
 public:
  circularqueue() = default;
  circularqueue(const circularqueue &other){
	head = other.head;
	tail = other.tail;
	for (int i = head; i != tail; i = (i + 1) % N) {
	  data[i] = other.data[i];
	}
  };
  circularqueue& operator=(const circularqueue &other){
	if(this == &other){
	  return *this;
	}
	head = other.head;
	tail = other.tail;
	for (int i = head; i != tail; i = (i + 1) % N) {
	  data[i] = other.data[i];
	}
	return *this;
  };
  ~circularqueue() = default;
  bool full() const{
	return (tail + 1) % N == head;
  }
  void push_back(T data) {
	this->data[tail] = data;
	tail = (tail + 1) % N;
  }
  void pop_back(){
	head = (head + 1) % N;
  };
  void clear(){
	head = tail = 0;
  };
  T& operator[](int index){
	return data[index];
  };
  bool empty(){
	return head == tail;
  }
  T& front(){
	return data[head];
  }
  int end_index(){
	return tail;
  }
  bool spare_two()const{
	return ((tail + 2) % N != head && (tail + 1) % N != head);
  }
  bool spare_three()const{
	return ((tail + 3) % N != head && (tail + 2) % N != head && (tail + 1) % N != head);
  }
  /* int size(); */
  T data[N];
  int head, tail;
};
}

