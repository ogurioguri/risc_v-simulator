#ifndef C_UNIT_REODERBUFFER_H_
#define C_UNIT_REODERBUFFER_H_
#include"tool/instruction.h"
#include"tool/circularqueue.h"
#include"registers.h"
#include"reservation_stations.h"
#include<iostream>
#include"Decode.h"
namespace Komeiji {
class ReservationStations;
class Decode;
class ReorderBuffer {
 public:
  circularqueue<rob_member, robsize> buffer;
  circularqueue<rob_member, robsize> buffer_next;
  bool lock = false;
  bool lock_next = false;
 public:
  ReorderBuffer() {
	for (int i = 0; i < robsize; ++i) {
	  buffer.data[i].rob_id = i;
	  buffer_next.data[i].rob_id = i;
	  buffer_next.data[i].busy = false;
	  buffer.data[i].busy = false;
	  buffer.data[i].ins = rob_ins();
	  buffer_next.data[i].ins = rob_ins();
	  buffer.data[i].value = 0;
	  buffer_next.data[i].value = 0;
	}
	buffer.head = 0;
	buffer.tail = 0;
	buffer_next.head = 0;
	buffer_next.tail = 0;
  }
  ~ReorderBuffer() = default;
  bool isFull() const{
	return buffer.full();
  };
  unsigned int add(rob_ins to_rob,Registers & registers);
  void commit(Registers & registers, ReservationStations & reservation_stations,unsigned int pc,unsigned int &pc_next,Decode & decoder);
  void execute(Registers & registers, ReservationStations & reservation_stations,unsigned int pc,unsigned int &pc_next,Decode & decoder);
  void update(){
	buffer = buffer_next;
	lock = lock_next;
  };
  bool spare_two() const{
	return buffer.spare_two();
  }
};
}
#endif //C_UNIT_REODERBUFFER_H_
