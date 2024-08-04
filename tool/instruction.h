#pragma once
#include<iostream>
//this file is used to define the instruction and the bus between the units
namespace Komeiji {
enum class opera {
  Add,
  Sub,
  And,
  Or,
  Xor,
  Sll,
  Srl,
  Sra,
  Slt,
  Sltu,
  Addi,
  Andi,
  Ori,
  Xori,
  Slli,
  Srli,
  Srai,
  Slti,
  Sltiu,
  Lb,
  Lh,
  Lw,
  Lbu,
  Lhu,
  Sb,
  Sh,
  Sw,
  Beq,
  Bne,
  Blt,
  Bge,
  Bltu,
  Bgeu,
  Jal,
  Jalr,
  Lui,
  Auipc,
  Ebreak,
  Ecall,
  Greater,
  Greateru,
  Equal,
  None,
  Halt
};

class instruction {
 public:
  opera op;
  int rd, rs1, rs2, imm;
  unsigned int pc;
  unsigned int address;
  instruction(unsigned int
			  inst,
			  unsigned int
			  pc,
			  opera
			  op,
			  int
			  rd,
			  int
			  rs1,
			  int
			  rs2,
			  int
			  imm) : address(inst), pc(pc), op(op), rd(rd), rs1(rs1), rs2(rs2), imm(imm) {};
  instruction() {
	op = opera::None;
	rd = -1;
	rs1 = -1;
	rs2 = -1;
	imm = 0;
	pc = 0;
	address = 0;
  };
};
enum class cal_type {
  add,
  sub,
  and_,
  or_,
  xor_,
  sll,
  srl,
  sra,
  slt,
  sltu,
  greater,
  greateru,
  equal
};
struct cal_ins {
  opera type;
  unsigned int value1, value2;
  cal_ins() =
  default;
};
//K is the end of the instruction
//L is the load instruction
//JJ is the jalr instruction
enum class instruction_type {
  R,
  I,
  S,
  B,
  U,
  J,
  E,
  K,
  L,
  JJ
};
class rob_ins {
 public:
  instruction_type type;
  opera detail_type;
  int rd, rs1, rs2;
  unsigned int imm;
  unsigned int pc;
  rob_ins() : type(instruction_type::K), detail_type(opera::None), rd(0), rs1(0), rs2(0), imm(0), pc(0) {};
  rob_ins(
	  const rob_ins &other) {
	if (this == &other) {
	  return;
	}
	type = other.type;
	detail_type = other.detail_type;
	rd = other.rd;
	rs1 = other.rs1;
	rs2 = other.rs2;
	imm = other.imm;
	pc = other.pc;
  };
  rob_ins &operator=(const rob_ins &other) {
	if (this == &other) {
	  return *this;
	}
	type = other.type;
	detail_type = other.detail_type;
	rd = other.rd;
	rs1 = other.rs1;
	rs2 = other.rs2;
	imm = other.imm;
	pc = other.pc;
	return *this;
  };
};
class rob_member {
 public:
  bool busy;
  rob_ins ins;
  unsigned int value;
  int rob_id;
  rob_member() =
  default;
  rob_member(
	  const rob_member &other) {
	if (this == &other) {
	  return;
	}
	busy = other.busy;
	ins = other.ins;
	value = other.value;
	rob_id = other.rob_id;
  };
  rob_member &operator=(const rob_member &other) {
	if (this == &other) {
	  return *this;
	}
	busy = other.busy;
	ins = other.ins;
	value = other.value;
	rob_id = other.rob_id;
	return *this;
  };
  ~rob_member() =
  default;
};
enum class lsb_type {
  Lb,
  Lh,
  Lw,
  Lbu,
  Lhu,
  Sb,
  Sh,
  Sw,
  Hang
};
//this is the rs to lsb bus
const int robsize = 3;
class lsb {
 public:
  lsb_type type;
  unsigned int rs1;
  unsigned int imm;
  unsigned int address;
  unsigned int value;
  int rob_id;
  bool wait;
  //the time of the instruction
  int time;
  lsb() : type(lsb_type::Hang), rs1(0), imm(0), address(0), value(0), rob_id(-1), wait(false), time(0) {};
  lsb &operator=(const lsb &lsb) {
	if (this == &lsb) {
	  return *this;
	}
	this->type = lsb.type;
	this->address = lsb.address;
	this->rs1 = lsb.rs1;
	this->imm = lsb.imm;
	this->value = lsb.value;
	this->rob_id = lsb.rob_id;
	this->time = lsb.time;
	this->wait = lsb.wait;
	return *this;
  }
};
class Lsb_to_rs {
 public:
  unsigned int data;
  unsigned int rob_id;
  int reg_index;
  bool busy;
  Lsb_to_rs() : data(0), rob_id(-1), reg_index(0), busy(false) {};
  Lsb_to_rs(
	  const Lsb_to_rs &other) {
	if (this == &other) {
	  return;
	}
	data = other.data;
	busy = other.busy;
	rob_id = other.rob_id;
	reg_index = other.reg_index;

  };
  Lsb_to_rs &operator=(const Lsb_to_rs &other) {
	if (this == &other) {
	  return *this;
	}
	data = other.data;
	busy = other.busy;
	rob_id = other.rob_id;
	reg_index = other.reg_index;
	return *this;
  };
  ~Lsb_to_rs() =
  default;
};
}


