
#ifndef C_UNIT_REGISTERS_H_
#define C_UNIT_REGISTERS_H_
#include"tool/instruction.h"
namespace Komeiji {
class Registers {
 public:
  unsigned int Reg[32];
  int depend_rob_id[32];
  bool depend[32];
 public:
  unsigned int next_Reg[32];
  int next_depend_rob_id[32];
  bool next_depend[32];
 public:
  Registers() {
	for (int i = 0; i < 32; i++) {
	  Reg[i] = 0;
	  depend_rob_id[i] = -1;
	  depend[i] = false;
	  next_Reg[i] = 0;
	  next_depend_rob_id[i] = -1;
	  next_depend[i] = false;
	}
  }
  unsigned int operator[](int index) {
	if(index == 0) return 0;
	if(index >= 32) throw "Register index out of range";
	return Reg[index];
  }
  void set(int index, unsigned int value, unsigned int rob_id) {
	if(index == 0) return;
	if(index >= 32) throw "Register index out of range";
	next_Reg[index] = value;
	if(rob_id ==  depend_rob_id[index]){
	  next_depend[index] = false;
	  next_depend_rob_id[index] = -1;
	}
  }
  void set_depend(int index, unsigned int rob_id) {
	if(index == 0) return;
	if(index >= 32) throw "Register index out of range";
	next_depend_rob_id[index] = rob_id;
	next_depend[index] = true;
  }
  void update() {
	for (int i = 0; i < 32; i++) {
	  Reg[i] = next_Reg[i];
	  depend_rob_id[i] = next_depend_rob_id[i];
	  depend[i] = next_depend[i];
	}
  }


};
}
#endif //C_UNIT_REGISTERS_H_
