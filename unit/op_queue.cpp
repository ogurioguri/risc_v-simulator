#include"op_queue.h"
#include<string>
namespace Komeiji {
op_queue::op_queue() : old_pointer(0), pointer(0) {
  for (int i = 0; i < 0x10000; i++) {
	init_array[i] = 0;
  }
}
void op_queue::execute(unsigned int &pc,
					   const Komeiji::Decode &decode) {
  pointer = pc / 4;
}
void op_queue::update() {
  old_pointer = pointer;
}
void op_queue::init() {
  std::string input;
  int len = 0;
  int rear = 0;
  unsigned int input_ins = 0;
  while (std::cin >> input) {
	if (input[0] == '@') {
	  rear = std::stoi(input.substr(1), nullptr, 16) /4;
	  continue;
	} else {
	  input_ins = input_ins | static_cast<unsigned int>(std::stoi(input, nullptr, 16)) << (8 * len);
	  len++;
	  if (len == 4) {
		init_array[rear] = input_ins;
		len = 0;
		input_ins = 0;
		rear++;
	  }
	}
  }
  pointer = 0;
}
}




