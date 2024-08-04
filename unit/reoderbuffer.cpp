#include"reoderbuffer.h"
namespace Komeiji {
unsigned int ReorderBuffer::add(rob_ins to_rob,Registers & registers) {
  if (buffer_next.full()) {
	throw "ReorderBuffer is full";
  }
  rob_member entry;
  entry.busy = true;
  entry.ins = to_rob;
  entry.rob_id = buffer_next.end_index();
  buffer_next.push_back(entry);
  if(to_rob.type == instruction_type::B || to_rob.type == instruction_type::J || to_rob.type == instruction_type::E || to_rob.type == instruction_type::K || to_rob.type == instruction_type::JJ){
	lock_next = true;
  }
  return entry.rob_id;
}
void ReorderBuffer::execute(Registers & registers, ReservationStations & reservation_stations,unsigned int pc,unsigned int &pc_next,Decode & decoder) {
  commit(registers, reservation_stations,pc,pc_next,decoder);
}
void ReorderBuffer::commit(Registers &registers,ReservationStations &reservation_stations,unsigned int pc,unsigned int &pc_next,Decode &decoder) {
//  if(){
//	int i = 0;
//  }
  if (buffer.empty()) {
	return;
  }
  rob_member entry = buffer.front();
  if(!lock && decoder.old_ready_to_next){
	pc_next = pc + 4;
  }
  if (!entry.busy) {
	if (entry.ins.type == instruction_type::R || entry.ins.type == instruction_type::I|| entry.ins.type == instruction_type::U|| entry.ins.type == instruction_type::L) {
	  registers.set(entry.ins.rd, entry.value, entry.rob_id);
	  // update reservation stations
	  for(int i = 0; i < robsize; i++){
		if(reservation_stations.rs_buffer_next[i].Qj == entry.rob_id) {
		  reservation_stations.rs_buffer_next[i].Vj = entry.value;
		  reservation_stations.rs_buffer_next[i].Qj = 0;
		}
		if(reservation_stations.rs_buffer_next[i].Qk == entry.rob_id) {
		  reservation_stations.rs_buffer_next[i].Vk = entry.value;
		  reservation_stations.rs_buffer_next[i].Qk = 0;
		}
	  }
	} else if(entry.ins.type == instruction_type::S){
	  // do nothing
	} else if(entry.ins.type == instruction_type::B){
	  if(entry.ins.detail_type == opera::Beq && pc == 0x101c){
		int i = 0;
	  }
	  if(entry.value == 1){
		pc_next = entry.ins.imm+pc;
	  }else{
		pc_next = pc + 4;
	  }
	  lock_next = false;
	}else if(entry.ins.type == instruction_type::J){
	  pc_next = entry.ins.imm + pc;
	  registers.set(entry.ins.rd, pc+4, entry.rob_id);
	  lock_next = false;
	} else if(entry.ins.type == instruction_type::K){
	  std::cout<<std::dec<<(registers[10] & 0xff);
	  exit(0);
	} else if(entry.ins.type == instruction_type::JJ) {
	  unsigned int temp = pc + 4;
	  registers.set(entry.ins.rd, temp, entry.rob_id);
	  pc_next = entry.value;
	  lock_next = false;
	}
	buffer_next.pop_back();
  }
}


}