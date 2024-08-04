#include "instruction.h"
#include "Decode.h"
namespace Komeiji {
void Decode::decode_execute(unsigned int inst, unsigned int pc, instruction &output, instruction_type &type) {
  Komeiji::instruction instr;
  instr.pc = pc;
  int conduct = inst & 0b1111111;
  if(inst == 0xff00513){
	output.op = Komeiji::opera::Halt;
	type = instruction_type::K;
	return;
  }
  switch (conduct) {
	case 0b0110011: type = instruction_type::R;
	  switch (inst & 0b11111110000000000111000000000000) {
		case 0b00000000000000000000000000000000: func_add(inst, pc, instr);
		  break;
		case 0b01000000000000000000000000000000: func_sub(inst, pc, instr);
		  break;
		case 0b00000000000000000001000000000000: func_sll(inst, pc, instr);
		  break;
		case 0b00000000000000000010000000000000: func_slt(inst, pc, instr);
		  break;
		case 0b00000000000000000001100000000000: func_sltu(inst, pc, instr);
		  break;
		case 0b00000000000000000100000000000000: func_xor(inst, pc, instr);
		  break;
		case 0b00000000000000000101000000000000: func_srl(inst, pc, instr);
		  break;
		case 0b01000000000000000101000000000000: func_sra(inst, pc, instr);
		  break;
		case 0b00000000000000000110000000000000: func_or(inst, pc, instr);
		  break;
		case 0b00000000000000000111000000000000: func_and(inst, pc, instr);
		  break;
	  }
	  break;
	case 0b0010011: type = instruction_type::R;
	  switch (inst & 0b111000000000000) {
		case 0b0: func_addi(inst, pc, instr);
		  break;
		case 0b1000000000000: func_slli(inst, pc, instr);
		  break;
		case 0b10000000000000: func_slti(inst, pc, instr);
		  break;
		case 0b110000000000000: func_ori(inst, pc, instr);
		  break;
		case 0b111000000000000: func_andi(inst, pc, instr);
		  break;
		case 0b100000000000000: func_xori(inst, pc, instr);
		  break;
		case 0b11000000000000: func_sltiu(inst, pc, instr);
		  break;
		case 0b101000000000000:
		  if ((inst & 0b11111110000000000000000000000000) == 0b01000000000000000000000000000000) {
			func_srai(inst, pc, instr);
		  } else {
			func_srli(inst, pc, instr);
		  }
		  break;
	  }
	  break;
	case 0b0000011: type = instruction_type::L;
	  switch (inst & 0b111000000000000) {
		case 0b0: func_lb(inst, pc, instr);
		  break;
		case 0b1000000000000: func_lh(inst, pc, instr);
		  break;
		case 0b10000000000000: func_lw(inst, pc, instr);
		  break;
		case 0b100000000000000: func_lbu(inst, pc, instr);
		  break;
		case 0b101000000000000: func_lhu(inst, pc, instr);
		  break;
	  }
	  break;
	case 0b0100011: type = instruction_type::S;
	  switch (inst & 0b111000000000000) {
		case 0b0: func_sb(inst, pc, instr);
		  break;
		case 0b1000000000000: func_sh(inst, pc, instr);
		  break;
		case 0b10000000000000: func_sw(inst, pc, instr);
		  break;
	  }
	  break;
	case 0b1100011: type = instruction_type::B;
	  switch (inst & 0b111000000000000) {
		case 0b0: func_beq(inst, pc, instr);
		  break;
		case 0b1000000000000: func_bne(inst, pc, instr);
		  break;
		case 0b100000000000000: func_blt(inst, pc, instr);
		  break;
		case 0b101000000000000: func_bge(inst, pc, instr);
		  break;
		case 0b110000000000000: func_bltu(inst, pc, instr);
		  break;
		case 0b111000000000000: func_bgeu(inst, pc, instr);
		  break;
	  }
	  break;
	case 0b1101111: func_jal(inst, pc, instr);
	  type = instruction_type::J;
	  break;
	case 0b1100111: func_jalr(inst, pc, instr);
	  type = instruction_type::JJ;
	  break;
	case 0b0110111: func_lui(inst, pc, instr);
	  type = instruction_type::U;
	  break;
	case 0b0010111: func_auipc(inst, pc, instr);
	  type = instruction_type::U;
	  break;
	case 0b1110011:
	  if ((inst & 0b11111110000000000000000000000000) == 0b0) {
		type = instruction_type::E;
		func_ecall(inst, pc, instr);
	  } else {
		type = instruction_type::E;
		func_ebreak(inst, pc, instr);
	  }
  }
  output = instr;
//  std::cout<<"PC: "<<std::hex<<pc<<std::endl;
//  std::cout<<"csu is committing instruct "<<std::hex<<inst<<std::dec<<std::endl;
//  switch (instr.op) {
//	case opera::Add:
//	  std::cout << "Add ";
//	  break;
//	case opera::Sub:
//	  std::cout << "Sub ";
//	  break;
//	case opera::And:
//	  std::cout << "And ";
//	  break;
//	case opera::Or:
//	  std::cout << "Or ";
//	  break;
//	case opera::Xor:
//	  std::cout << "Xor ";
//	  break;
//	case opera::Sll:
//	  std::cout << "Sll ";
//	  break;
//	case opera::Srl:
//	  std::cout << "Srl ";
//	  break;
//	case opera::Sra:
//	  std::cout << "Sra ";
//	  break;
//	case opera::Slt:
//	  std::cout << "Slt ";
//	  break;
//	case opera::Sltu:
//	  std::cout << "Sltu ";
//	  break;
//	case opera::Addi:
//	  std::cout << "Addi ";
//	  break;
//	case opera::Andi:
//	  std::cout << "Andi ";
//	  break;
//	case opera::Ori:
//	  std::cout << "Ori ";
//	  break;
//	case opera::Xori:
//	  std::cout << "Xori ";
//	  break;
//	case opera::Slli:
//	  std::cout << "Slli ";
//	  break;
//	case opera::Srli:
//	  std::cout << "Srli ";
//	  break;
//	case opera::Srai:
//	  std::cout << "Srai ";
//	  break;
//	case opera::Slti:
//	  std::cout << "Slti ";
//	  break;
//	case opera::Sltiu:
//	  std::cout << "Sltiu ";
//	  break;
//	case opera::Lb:
//	  std::cout << "Lb ";
//	  break;
//	case opera::Lh:
//	  std::cout << "Lh ";
//	  break;
//	case opera::Lw:
//	  std::cout << "Lw ";
//	  break;
//	case opera::Lbu:
//	  std::cout << "Lbu ";
//	  break;
//	case opera::Lhu:
//	  std::cout << "Lhu ";
//	  break;
//	case opera::Sb:
//	  std::cout << "Sb ";
//	  break;
//	case opera::Sh:
//	  std::cout << "Sh ";
//	  break;
//	case opera::Sw:
//	  std::cout << "Sw ";
//	  break;
//	case opera::Beq:
//	  std::cout << "Beq ";
//	  break;
//	case opera::Bne:
//	  std::cout << "Bne ";
//	  break;
//	case opera::Blt:
//	  std::cout << "Blt ";
//	  break;
//	case opera::Bge:
//	  std::cout << "Bge ";
//	  break;
//	case opera::Bltu:
//	  std::cout << "Bltu ";
//	  break;
//	case opera::Bgeu:
//	  std::cout << "Bgeu ";
//	  break;
//	case opera::Jal:
//	  std::cout << "Jal ";
//	  break;
//	case opera::Jalr:
//	  std::cout << "Jalr ";
//	  break;
//	case opera::Lui:
//	  std::cout << "Lui ";
//	  break;
//	case opera::Auipc:
//	  std::cout << "Auipc ";
//	  break;
//	case opera::Ebreak:
//	  std::cout << "Ebreak ";
//	  break;
//	case opera::Ecall:
//	  std::cout << "Ecall ";
//	  break;
//	case opera::Halt:
//	  std::cout << "Halt ";
//	  break;
//  }
//  std::cout<<std::dec<<instr.rs1<<' '<<instr.rs2<<' '<<instr.rd<<' '<<instr.imm<<'\n';
}
void Decode::decode_run(Komeiji::op_queue &op_queue,
						unsigned int pc,
						Komeiji::ReorderBuffer &rob, Registers &registers,ReservationStations & reservation_station) {
  if (!rob.spare_two() || rob.lock) {
	ready_to_next = false;
	return;
  } else {
	ready_to_next = true;
  }
  if (old_ready_to_next) {
	instruction now;
	instruction_type type;
	decode_execute(op_queue.init_array[op_queue.old_pointer], pc, now, type);
	if (!rob.spare_two()) {
	  ready_to_next = false;
	} else {
//	  std::cout<<"add\n";
	  ready_to_next = true;
	  rob_ins to_rob;
	  to_rob.type = type;
	  to_rob.detail_type = now.op;
	  to_rob.rd = now.rd;
	  to_rob.rs1 = now.rs1;
	  to_rob.rs2 = now.rs2;
	  to_rob.imm = now.imm;
	  unsigned int rob_index = rob.add(to_rob, registers);
	  reservation_station.add(to_rob,registers,rob_index);
	}
  }
}
void Decode::func_add(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Add;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  instr.rs2 = (inst >> 20) & 0b11111;
  instr.imm = 0;
  output = instr;
}
void Decode::func_sub(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Sub;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  instr.rs2 = (inst >> 20) & 0b11111;
  instr.imm = 0;
  output = instr;
}
void Decode::func_and(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::And;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  instr.rs2 = (inst >> 20) & 0b11111;
  instr.imm = 0;
  output = instr;
}
void Decode::func_or(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Or;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  instr.rs2 = (inst >> 20) & 0b11111;
  instr.imm = 0;
  output = instr;
}
void Decode::func_xor(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Xor;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  instr.rs2 = (inst >> 20) & 0b11111;
  instr.imm = 0;
  output = instr;
}
void Decode::func_sll(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Sll;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  instr.rs2 = (inst >> 20) & 0b11111;
  instr.imm = 0;
  output = instr;
}
void Decode::func_srl(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Srl;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  instr.rs2 = (inst >> 20) & 0b11111;
  instr.imm = 0;
  output = instr;
}
void Decode::func_sra(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Sra;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  instr.rs2 = (inst >> 20) & 0b11111;
  instr.imm = 0;
  output = instr;
}
void Decode::func_slt(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Slt;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  instr.rs2 = (inst >> 20) & 0b11111;
  instr.imm = 0;
  output = instr;
}
void Decode::func_sltu(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Sltu;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  instr.rs2 = (inst >> 20) & 0b11111;
  instr.imm = 0;
  output = instr;
}
void Decode::func_addi(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Addi;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  int imm = (inst >> 20) & 0b111111111111;
  if (imm & 0b100000000000) {
	imm = imm | 0b11111111111111111111000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_andi(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Andi;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  int imm = (inst >> 20) & 0b111111111111;
  if (imm & 0b100000000000) {
	imm = imm | 0b11111111111111111111000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_ori(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Ori;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  int imm = (inst >> 20) & 0b111111111111;
  if (imm & 0b100000000000) {
	imm = imm | 0b11111111111111111111000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_xori(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Xori;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  int imm = (inst >> 20) & 0b111111111111;
  if (imm & 0b100000000000) {
	imm = imm | 0b11111111111111111111000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_slli(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Slli;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  int imm = (inst >> 20) & 0b1111111;
  instr.imm = imm;
  output = instr;
}
void Decode::func_srli(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Srli;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  int imm = (inst >> 20) & 0b1111111;
  instr.imm = imm;
  output = instr;
}
void Decode::func_srai(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Srai;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  int imm = (inst >> 20) & 0b1111111;
  instr.imm = imm;
  output = instr;
}
void Decode::func_slti(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Slti;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  int imm = (inst >> 20) & 0b111111111111;
  if (imm & 0b100000000000) {
	imm = imm | 0b11111111111111111111000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_sltiu(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Sltiu;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  int imm = (inst >> 20) & 0b111111111111;
  if (imm & 0b100000000000) {
	imm = imm | 0b11111111111111111111000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_lb(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Lb;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  int imm = (inst >> 20) & 0b111111111111;
  if (imm & 0b100000000000) {
	imm = imm | 0b11111111111111111111000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_lh(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Lh;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  int imm = (inst >> 20) & 0b111111111111;
  if (imm & 0b100000000000) {
	imm = imm | 0b11111111111111111111000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_lw(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Lw;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  int imm = (inst >> 20) & 0b111111111111;
  if (imm & 0b100000000000) {
	imm = imm | 0b11111111111111111111000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_lbu(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Lbu;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  int imm = (inst >> 20) & 0b111111111111;
  if (imm & 0b100000000000) {
	imm = imm | 0b11111111111111111111000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_lhu(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Lhu;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  int imm = (inst >> 20) & 0b111111111111;
  if (imm & 0b100000000000) {
	imm = imm | 0b11111111111111111111000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_sb(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Sb;
  instr.rs1 = (inst >> 15) & 0b11111;
  instr.rs2 = (inst >> 20) & 0b11111;
  int imm = ((inst >> 7) & 0b11111) | (((inst >> 25) & 0b111111111111) << 5);
  if (imm & 0b100000000000) {
	imm = imm | 0b11111111111111111111000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_sh(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Sh;
  instr.rs1 = (inst >> 15) & 0b11111;
  instr.rs2 = (inst >> 20) & 0b11111;
  int imm = ((inst >> 7) & 0b11111) | (((inst >> 25) & 0b111111111111) << 5);
  if (imm & 0b100000000000) {
	imm = imm | 0b11111111111111111111000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_sw(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Sw;
  instr.rs1 = (inst >> 15) & 0b11111;
  instr.rs2 = (inst >> 20) & 0b11111;
  int imm = ((inst >> 7) & 0b11111) | (((inst >> 25) & 0b111111111111) << 5);
  if (imm & 0b100000000000) {
	imm = imm | 0b11111111111111111111000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_beq(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Beq;
  instr.rs1 = (inst >> 15) & 0b11111;
  instr.rs2 = (inst >> 20) & 0b11111;
  int part1 = (inst >> 7) & 0b1;
  int part2 = (inst >> 8) & 0b1111;
  int part3 = (inst >> 25) & 0b111111;
  int part4 = (inst >> 31) & 0b1;
  int imm = (part4 << 12) | (part3 << 5) | (part2 << 1) | (part1 << 11);
  if (part4) {
	imm = imm | 0b11111111111111111110000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_bne(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Bne;
  instr.rs1 = (inst >> 15) & 0b11111;
  instr.rs2 = (inst >> 20) & 0b11111;
  int part1 = (inst >> 7) & 0b1;
  int part2 = (inst >> 8) & 0b1111;
  int part3 = (inst >> 25) & 0b111111;
  int part4 = (inst >> 31) & 0b1;
  int imm = (part4 << 12) | (part3 << 5) | (part2 << 1) | (part1 << 11);
  if (part4) {
	imm = imm | 0b11111111111111111110000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_blt(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Blt;
  instr.rs1 = (inst >> 15) & 0b11111;
  instr.rs2 = (inst >> 20) & 0b11111;
  int part1 = (inst >> 7) & 0b1;
  int part2 = (inst >> 8) & 0b1111;
  int part3 = (inst >> 25) & 0b111111;
  int part4 = (inst >> 31) & 0b1;
  int imm = (part4 << 12) | (part3 << 5) | (part2 << 1) | (part1 << 11);
  if (part4) {
	imm = imm | 0b11111111111111111110000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_bge(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Bge;
  instr.rs1 = (inst >> 15) & 0b11111;
  instr.rs2 = (inst >> 20) & 0b11111;
  int part1 = (inst >> 7) & 0b1;
  int part2 = (inst >> 8) & 0b1111;
  int part3 = (inst >> 25) & 0b111111;
  int part4 = (inst >> 31) & 0b1;
  int imm = (part4 << 12) | (part3 << 5) | (part2 << 1) | (part1 << 11);
  if (part4) {
	imm = imm | 0b11111111111111111110000000000000;;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_bltu(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Bltu;
  instr.rs1 = (inst >> 15) & 0b11111;
  instr.rs2 = (inst >> 20) & 0b11111;
  int part1 = (inst >> 7) & 0b1;
  int part2 = (inst >> 8) & 0b1111;
  int part3 = (inst >> 25) & 0b111111;
  int part4 = (inst >> 31) & 0b1;
  int imm = (part4 << 12) | (part3 << 5) | (part2 << 1) | (part1 << 11);
  if (part4) {
	imm = imm | 0b11111111111111111110000000000000;
  }
  instr.imm = imm;
  output = instr;

}
void Decode::func_bgeu(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Bgeu;
  instr.rs1 = (inst >> 15) & 0b11111;
  instr.rs2 = (inst >> 20) & 0b11111;
  int part1 = (inst >> 7) & 0b1;
  int part2 = (inst >> 8) & 0b1111;
  int part3 = (inst >> 25) & 0b111111;
  int part4 = (inst >> 31) & 0b1;
  int imm = (part4 << 12) | (part3 << 5) | (part2 << 1) | (part1 << 11);
  if (part4) {
	imm = imm | 0b11111111111111111110000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_jal(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Jal;
  instr.rd = (inst >> 7) & 0b11111;
  int part1 = (inst >> 21) & 0b1111111111;
  int part2 = (inst >> 20) & 0b1;
  int part3 = (inst >> 12) & 0b11111111;
  int part4 = (inst >> 31) & 0b1;
  int imm = (part4 << 20) | (part1 << 1) | (part2 << 11) | (part3 << 12);
  if (part4) {
	imm = imm | 0b11111111111100000000000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_jalr(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Jalr;
  instr.rd = (inst >> 7) & 0b11111;
  instr.rs1 = (inst >> 15) & 0b11111;
  int imm = (inst >> 20) & 0b111111111111;
  if (imm & 0b100000000000) {
	imm = imm | 0b11111111111111111111000000000000;
  }
  instr.imm = imm;
  output = instr;
}
void Decode::func_lui(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Lui;
  instr.rd = (inst >> 7) & 0b11111;
  int imm = ((inst >> 12) & 0b11111111111111111111) << 12;
  instr.imm = imm;
  output = instr;
}
void Decode::func_auipc(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Auipc;
  instr.rd = (inst >> 7) & 0b11111;
  int imm = ((inst >> 12) & 0b11111111111111111111) << 12;
  instr.imm = imm + pc;
  output = instr;
}
void Decode::func_ebreak(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Ebreak;
  output = instr;
}
void Decode::func_ecall(unsigned int inst, unsigned int pc, instruction &output) {
  Komeiji::instruction instr;
  instr.pc = pc;
  instr.op = Komeiji::opera::Ecall;
  output = instr;
}

}