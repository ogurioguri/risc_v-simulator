
#ifndef C_UNIT_RESERVATION_STATIONS_H_
#define C_UNIT_RESERVATION_STATIONS_H_
#include"registers.h"
#include"reoderbuffer.h"
#include"tool/circularqueue.h"
#include"tool/instruction.h"
#include"alu.h"
#include"Decode.h"
#include"loadstorebuffer.h"
namespace Komeiji {
class ReorderBuffer;
class LoadStoreBuffer;
struct rs_member{
  rob_ins ins;
  bool busy;
  unsigned int Vj;
  unsigned int Vk;
  int Qj;int Qk;
  unsigned int A;
  unsigned int rob_id;
  bool finished_first;//for l and s
  rs_member() : ins(), busy(false), Vj(0), Vk(0), Qj(-1), Qk(-1), A(0), rob_id(-1),finished_first(false) {}
};
class ReservationStations {
 public:
  circularqueue<rs_member, robsize> rs_buffer;
  circularqueue<rs_member, robsize> rs_buffer_next;
  bool flag_to_alu;
  bool flag_to_alu_next;
  bool flag_to_lsb;
  bool flag_to_lsb_next;
 public:
  ReservationStations() = default;
  ~ReservationStations() = default;
  void add(rob_ins & to_rs,Registers & registers,unsigned int index);
  void execute(LoadStoreBuffer & load_store_buffer, ReorderBuffer & reorder_buffer,ALU & alu,Memory&memory);
  bool isFull() const;
  void update() {
	rs_buffer = rs_buffer_next;
	flag_to_alu = flag_to_alu_next;
	flag_to_lsb = flag_to_lsb_next;
	flag_to_alu_next = false;
	flag_to_lsb_next = false;
  };
};
}
#endif //C_UNIT_RESERVATION_STATIONS_H_
