#include <iomanip>
#include"reservation_stations.h"
namespace Komeiji {
void ReservationStations::add(rob_ins &to_rs, Registers &registers, unsigned int index) {
//  if(to_rs.detail_type == opera::Xor){
//	int i = 0;
//  }
//  if(registers.next_depend_rob_id[10] == 1){
//	int i = 0;
//  }
  rs_member entry;
  entry.busy = true;
  entry.ins = to_rs;
  entry.rob_id = index;
  int i = 0;
  for (; i < robsize; i++) {
	if (!rs_buffer_next[i].busy) {
	  break;
	}
  }
  rs_buffer_next[i] = entry;
  // set depend
  if (to_rs.rd != -1) {
	registers.set_depend(to_rs.rd, entry.rob_id);
  }
  // set Vj Vk Qj Qk
  if (to_rs.rs1 != -1) {
	if (registers.depend[to_rs.rs1] && registers.next_depend_rob_id[to_rs.rs1] != entry.rob_id) {
	  rs_buffer_next[i].Qj = registers.depend_rob_id[to_rs.rs1];
	} else {
	  rs_buffer_next[i].Vj = registers[to_rs.rs1];
	  rs_buffer_next[i].Qj = -1;
	}
  } else {
	rs_buffer_next[i].Qj = -1;
  }
  if (to_rs.rs2 != -1) {
	if (registers.depend[to_rs.rs2] && registers.next_depend_rob_id[to_rs.rs2] != entry.rob_id) {
	  rs_buffer_next[i].Qk = registers.depend_rob_id[to_rs.rs2];
	} else {
	  rs_buffer_next[i].Vk = registers[to_rs.rs2];
	  rs_buffer_next[i].Qk = -1;
	}
  } else {
	rs_buffer_next[i].Qk = -1;
	rs_buffer_next[i].Vk = entry.ins.imm;
  }
  if (rs_buffer_next.full()) {
	throw "ReservationStations is full";
  }
//  for (int i = 14; i < 16; i++) {
//	std::cout << "x" << i << "=" << std::hex << std::uppercase << std::setw(8) << std::setfill
//		('0') << registers[i]
//			  << std::endl;
//  }
}
bool ReservationStations::isFull() const {
  for (int i = 0; i < robsize; i++) {
	if (!rs_buffer_next.data[i].busy) {
	  return false;
	}
  }
  return true;
}
void ReservationStations::execute(LoadStoreBuffer &load_store_buffer,
								  ReorderBuffer &reorder_buffer,
								  ALU &alu,
								  Memory &memory) {
  //从alu与lsb中取出结果进行更新
//  if (rs_buffer_next[0].ins.detail_type == opera::Bge) {
//	int i = 0;
//  }
  if (alu.old_busy) {
	unsigned int result = alu.output();
	for (int i = 0; i < robsize; i++) {
	  if (rs_buffer_next[i].busy) {
		if (rs_buffer_next.data[i].rob_id == alu.old_robid) {
		  if (rs_buffer_next[i].ins.type == instruction_type::R
			  || rs_buffer_next[i].ins.type == instruction_type::B
			  || rs_buffer_next[i].ins.type == instruction_type::I
			  || rs_buffer_next[i].ins.type == instruction_type::JJ) {
			rs_buffer_next.data[i].A = result;
			rs_buffer_next.data[i].busy = false;
			reorder_buffer.buffer_next[alu.old_robid].value = result;
			reorder_buffer.buffer_next[alu.old_robid].busy = false;
		  } else if (rs_buffer_next[i].ins.type == instruction_type::L
			  || rs_buffer_next[i].ins.type == instruction_type::S) {
			rs_buffer_next.data[i].A = result;
			rs_buffer_next.data[i].Qj = -1;
			rs_buffer_next.data[i].finished_first = true;
		  }
		}
	  }
	}
  }
  if (load_store_buffer.old_busy) {
	Lsb_to_rs lsb_to_rs;
	unsigned int result = load_store_buffer.output(lsb_to_rs, memory);
	for (int i = 0; i < robsize; i++) {
	  if (rs_buffer_next[i].busy) {
		if (rs_buffer_next.data[i].rob_id == lsb_to_rs.rob_id) {
		  //将结果写入rs其他位置
//		  for (int j = 0; j < robsize; j++) {
//			if (rs_buffer_next.data[j].Qj == lsb_to_rs.rob_id) {
//			  rs_buffer_next.data[j].Vj = result;
//			  rs_buffer_next.data[j].Qj = 0;
//			}
//			if (rs_buffer_next.data[j].Qk == lsb_to_rs.rob_id) {
//			  rs_buffer_next.data[j].Vk = result;
//			  rs_buffer_next.data[j].Qk = 0;
//			}
		  reorder_buffer.buffer_next[lsb_to_rs.rob_id].value = result;
		  reorder_buffer.buffer_next[lsb_to_rs.rob_id].busy = false;
		  rs_buffer_next.data[i].busy = false;
		}
	  }
	}
  }
  //寻找可执行的指令
  for (int i = 0; i < robsize; i++) {
	if (rs_buffer_next[i].busy) {
	  if (rs_buffer_next[i].ins.type == instruction_type::R || rs_buffer_next[i].ins.type == instruction_type::B
		  || rs_buffer_next[i].ins.type == instruction_type::I || rs_buffer_next[i].ins.type == instruction_type::JJ) {
		if (rs_buffer_next[i].Qj == -1 && rs_buffer_next[i].Qk == -1 && !flag_to_alu_next) {
		  flag_to_alu_next = true;
		  cal_ins to_alu_ins;
		  to_alu_ins.type = rs_buffer_next[i].ins.detail_type;
		  to_alu_ins.value1 = rs_buffer_next[i].Vj;
		  to_alu_ins.value2 = rs_buffer_next[i].Vk;
		  alu.input(to_alu_ins, rs_buffer_next[i].rob_id);
		}
	  } else if (rs_buffer_next[i].ins.type == instruction_type::L) {
		if (rs_buffer_next[i].finished_first && rs_buffer_next[i].Qj == -1 && rs_buffer_next[i].Qk == -1
			&& !flag_to_lsb_next) {
		  lsb to_lsb;
		  to_lsb.address = rs_buffer_next[i].A;
		  to_lsb.rob_id = rs_buffer_next[i].rob_id;
		  if (rs_buffer_next[i].ins.detail_type == opera::Lb) {
			to_lsb.type = lsb_type::Lb;
		  } else if (rs_buffer_next[i].ins.detail_type == opera::Lbu) {
			to_lsb.type = lsb_type::Lbu;
		  } else if (rs_buffer_next[i].ins.detail_type == opera::Lh) {
			to_lsb.type = lsb_type::Lh;
		  } else if (rs_buffer_next[i].ins.detail_type == opera::Lhu) {
			to_lsb.type = lsb_type::Lhu;
		  } else if (rs_buffer_next[i].ins.detail_type == opera::Lw) {
			to_lsb.type = lsb_type::Lw;
		  }
		  load_store_buffer.add(to_lsb);
		  flag_to_lsb_next = true;
		} else if (!rs_buffer_next[i].finished_first && rs_buffer_next[i].Qj == -1 && !flag_to_alu_next) {
		  flag_to_alu_next = true;
		  cal_ins to_alu_ins;
		  to_alu_ins.type = rs_buffer_next[i].ins.detail_type;
		  to_alu_ins.value1 = rs_buffer_next[i].Vj;
		  to_alu_ins.value2 = rs_buffer_next[i].ins.imm;
		  alu.input(to_alu_ins, rs_buffer_next[i].rob_id);
		}
	  } else if (rs_buffer_next[i].ins.type == instruction_type::S) {
		if (rs_buffer_next[i].finished_first && rs_buffer_next[i].Qj == -1 && rs_buffer_next[i].Qk == -1
			&& !flag_to_lsb_next) {
		  lsb to_lsb;
		  to_lsb.rob_id = rs_buffer_next[i].rob_id;
		  if (rs_buffer_next[i].ins.detail_type == opera::Sb) {
			to_lsb.type = lsb_type::Sb;
		  } else if (rs_buffer_next[i].ins.detail_type == opera::Sh) {
			to_lsb.type = lsb_type::Sh;
		  } else if (rs_buffer_next[i].ins.detail_type == opera::Sw) {
			to_lsb.type = lsb_type::Sw;
		  }
		  flag_to_alu_next = true;
		  to_lsb.address = rs_buffer_next[i].A;
		  to_lsb.value = rs_buffer_next[i].Vk;
		  load_store_buffer.add(to_lsb);
		} else if (!rs_buffer_next[i].finished_first && rs_buffer_next[i].Qj == -1 && !flag_to_alu_next) {
		  flag_to_alu_next = true;
		  cal_ins to_alu_ins;
		  to_alu_ins.type = rs_buffer_next[i].ins.detail_type;
		  to_alu_ins.value1 = rs_buffer_next[i].Vj;
		  to_alu_ins.value2 = rs_buffer_next[i].ins.imm;
		  alu.input(to_alu_ins, rs_buffer_next[i].rob_id);
		}
	  } else if (rs_buffer_next[i].ins.type == instruction_type::U) {
		rs_buffer_next[i].A = rs_buffer_next[i].ins.imm;
		rs_buffer_next[i].busy = false;
		reorder_buffer.buffer_next[rs_buffer_next[i].rob_id].value = rs_buffer_next[i].A;
		reorder_buffer.buffer_next[rs_buffer_next[i].rob_id].busy = false;
	  } else if (rs_buffer_next[i].ins.type == instruction_type::J) {
		rs_buffer_next[i].busy = false;
		reorder_buffer.buffer_next[rs_buffer_next[i].rob_id].busy = false;
	  } else if (rs_buffer_next[i].ins.type == instruction_type::K) {
		rs_buffer_next[i].busy = false;
		reorder_buffer.buffer_next[rs_buffer_next[i].rob_id].busy = false;
	  }
	}
  }
}
}