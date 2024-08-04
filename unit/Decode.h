#pragma once
#include"tool/instruction.h"
#include"registers.h"
#include "memory.h"
#include "op_queue.h"
#include"reoderbuffer.h"
#include"reservation_stations.h"
namespace Komeiji {
class ReservationStations;
class ReorderBuffer;
class op_queue;
class Decode {
 public:
  void decode_execute(unsigned int inst, unsigned int pc,instruction& output,instruction_type& type);
  void decode_run(op_queue& op_queue,unsigned int pc, ReorderBuffer& rob,Registers& registers, ReservationStations& reservation_stations);
  void update(){
//	old_instruction = next_instruction;
	old_ready_to_next = ready_to_next;
  };
 private:
  void func_add(unsigned int inst, unsigned int pc,instruction& output);
  void func_sub(unsigned int inst, unsigned int pc,instruction& output);
  void func_and(unsigned int inst, unsigned int pc,instruction& output);
  void func_or(unsigned int inst, unsigned int pc,instruction& output);
  void func_xor(unsigned int inst, unsigned int pc,instruction& output);
  void func_sll(unsigned int inst, unsigned int pc,instruction& output);
  void func_srl(unsigned int inst, unsigned int pc,instruction& output);
  void func_sra(unsigned int inst, unsigned int pc,instruction& output);
  void func_slt(unsigned int inst, unsigned int pc,instruction& output);
  void func_sltu(unsigned int inst, unsigned int pc,instruction& output);
  void func_addi(unsigned int inst, unsigned int pc,instruction& output);
  void func_andi(unsigned int inst, unsigned int pc,instruction& output);
  void func_ori(unsigned int inst, unsigned int pc,instruction& output);
  void func_xori(unsigned int inst, unsigned int pc,instruction& output);
  void func_slli(unsigned int inst, unsigned int pc,instruction& output);
  void func_srli(unsigned int inst, unsigned int pc,instruction& output);
  void func_srai(unsigned int inst, unsigned int pc,instruction& output);
  void func_slti(unsigned int inst, unsigned int pc,instruction& output);
  void func_sltiu(unsigned int inst, unsigned int pc,instruction& output);
  void func_lb(unsigned int inst, unsigned int pc,instruction& output);
  void func_lh(unsigned int inst, unsigned int pc,instruction& output);
  void func_lw(unsigned int inst, unsigned int pc,instruction& output);
  void func_lbu(unsigned int inst, unsigned int pc,instruction& output);
  void func_lhu(unsigned int inst, unsigned int pc,instruction& output);
  void func_sb(unsigned int inst, unsigned int pc,instruction& output);
  void func_sh(unsigned int inst, unsigned int pc,instruction& output);
  void func_sw(unsigned int inst, unsigned int pc,instruction& output);
  void func_beq(unsigned int inst, unsigned int pc,instruction& output);
  void func_bne(unsigned int inst, unsigned int pc,instruction& output);
  void func_blt(unsigned int inst, unsigned int pc,instruction& output);
  void func_bge(unsigned int inst, unsigned int pc,instruction& output);
  void func_bltu(unsigned int inst, unsigned int pc,instruction& output);
  void func_bgeu(unsigned int inst, unsigned int pc,instruction& output);
  void func_jal(unsigned int inst, unsigned int pc,instruction& output);
  void func_jalr(unsigned int inst, unsigned int pc,instruction& output);
  void func_lui(unsigned int inst, unsigned int pc,instruction& output);
  void func_auipc(unsigned int inst, unsigned int pc,instruction& output);
  void func_ebreak(unsigned int inst, unsigned int pc,instruction& output);
  void func_ecall(unsigned int inst, unsigned int pc,instruction& output);
  public:
  bool old_ready_to_next;
  bool ready_to_next;
//  instruction old_instruction;
//  instruction next_instruction;
};
}