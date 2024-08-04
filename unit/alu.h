#ifndef C_UNIT_ALU_H_
#define C_UNIT_ALU_H_
#include"tool/instruction.h"
namespace Komeiji {
class ALU {
 public:
  bool old_busy;
  cal_ins old_cal_instruction;
  int old_robid;
  //old_index is used to store which rs1, rs2 ,rd is used in the instruction
  int old_index;
 private:
  bool busy;
  cal_ins cal_instruction;
  int robid;
  int index;
 public:
  ALU() = default;
  ~ALU() = default;
  void input(cal_ins cal_instruction, int robid) {
	this->cal_instruction = cal_instruction;
	this->robid = robid;
	busy = true;
  };
  void update() {
	old_busy = busy;
	old_cal_instruction = cal_instruction;
	old_robid = robid;
	busy = false;
  }
  unsigned int output() {
	if (old_cal_instruction.type == opera::Add || old_cal_instruction.type == opera::Addi) {
	  return old_cal_instruction.value1 + old_cal_instruction.value2;
	} else if (old_cal_instruction.type == opera::Sub ) {
	  return old_cal_instruction.value1 - old_cal_instruction.value2;
	} else if (old_cal_instruction.type == opera::And || old_cal_instruction.type == opera::Andi) {
	  return old_cal_instruction.value1 & old_cal_instruction.value2;
	} else if (old_cal_instruction.type == opera::Or || old_cal_instruction.type == opera::Ori) {
	  return old_cal_instruction.value1 | old_cal_instruction.value2;
	} else if (old_cal_instruction.type == opera::Xor || old_cal_instruction.type == opera::Xori) {
	  return old_cal_instruction.value1 ^ old_cal_instruction.value2;
	} else if (old_cal_instruction.type == opera::Sll || old_cal_instruction.type == opera::Slli) {
	  return old_cal_instruction.value1 << (old_cal_instruction.value2 & 0x1f);
	} else if (old_cal_instruction.type == opera::Srl || old_cal_instruction.type == opera::Srli) {
	  return old_cal_instruction.value1 >> (old_cal_instruction.value2 & 0x1f);
	} else if (old_cal_instruction.type == opera::Sra || old_cal_instruction.type == opera::Srai) {
	  return static_cast<int>(old_cal_instruction.value1) >> (old_cal_instruction.value2 & 0x1f);
	} else if (old_cal_instruction.type == opera::Slt || old_cal_instruction.type == opera::Slti) {
	  return static_cast<int>(old_cal_instruction.value1) < static_cast<int>(old_cal_instruction.value2);
	} else if (old_cal_instruction.type == opera::Sltu || old_cal_instruction.type == opera::Sltiu) {
	  return old_cal_instruction.value1 < old_cal_instruction.value2;
	} else if (old_cal_instruction.type == opera::Bge) {
	  return static_cast<int>(old_cal_instruction.value1) >= static_cast<int>(old_cal_instruction.value2);
	} else if (old_cal_instruction.type == opera::Bgeu) {
	  return old_cal_instruction.value1 >= old_cal_instruction.value2;
	} else if (old_cal_instruction.type == opera::Beq) {
	  return old_cal_instruction.value1 == old_cal_instruction.value2;
	} else if (old_cal_instruction.type == opera::Bne) {
	  return old_cal_instruction.value1 != old_cal_instruction.value2;
	} else if (old_cal_instruction.type == opera::Blt) {
	  return static_cast<int>(old_cal_instruction.value1) < static_cast<int>(old_cal_instruction.value2);
	} else if (old_cal_instruction.type == opera::Bltu) {
	  return old_cal_instruction.value1 < old_cal_instruction.value2;
	}else if (old_cal_instruction.type == opera::Jalr) {
	  return old_cal_instruction.value1 + old_cal_instruction.value2;
	}else if (old_cal_instruction.type == opera::Sb||old_cal_instruction.type == opera::Sh||old_cal_instruction.type == opera::Sw) {
	  return old_cal_instruction.value1 + old_cal_instruction.value2;
	}else if(old_cal_instruction.type == opera::Lb||old_cal_instruction.type == opera::Lbu||old_cal_instruction.type == opera::Lh||old_cal_instruction.type == opera::Lhu||old_cal_instruction.type == opera::Lw) {
	  return old_cal_instruction.value1 + old_cal_instruction.value2;
	}
  }
};
}

#endif //C_UNIT_ALU_H_
