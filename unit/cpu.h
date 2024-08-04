#pragma once
#include"memory.h"
#include"registers.h"
#include"alu.h"
#include"Decode.h"
#include"reoderbuffer.h"
#include"reservation_stations.h"
#include"loadstorebuffer.h"
#include"op_queue.h"
#include"tool/instruction.h"
#include<iostream>
namespace Komeiji {
class CPU {
 private:
  // The following are the components of the CPU
  Memory memory;
  Registers registers;
  ALU alu;
  Decode decoder;
  ReorderBuffer reorder_buffer;
  ReservationStations reservation_stations;
  LoadStoreBuffer load_store_buffer;
  op_queue Op_queue;


  int clock;
  // The following are the old values of the components of the CPU,which will be used by the other components
  unsigned int old_PC;

  //the following are the new values of the components of the CPU,whic  h will update the old values

 public:
  unsigned int pc;

  CPU(){
	clock = 0;
	pc = 0;
	old_PC = 0;
	alu = ALU();
	memory = Memory();
	registers = Registers();
	decoder = Decode();
	reorder_buffer = ReorderBuffer();
	reservation_stations = ReservationStations();
	load_store_buffer = LoadStoreBuffer();
	Op_queue.init(memory);
  };
  void update(){
	old_PC = pc;
	memory.update();
	registers.update();
	alu.update();
	reorder_buffer.update();
	reservation_stations.update();
	load_store_buffer.update();
	Op_queue.update();
	decoder.update();
  }
  void run(){
	++clock;
	memory.execute();
	decoder.decode_run(Op_queue, old_PC, reorder_buffer, registers,reservation_stations);
	reorder_buffer.execute(registers, reservation_stations, old_PC,pc,decoder);
	reservation_stations.execute(load_store_buffer, reorder_buffer, alu, memory);
	load_store_buffer.execute();
	Op_queue.execute(old_PC, decoder);
	update();
  };
};
}