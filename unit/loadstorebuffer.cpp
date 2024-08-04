#include"tool/instruction.h"
#include"tool/circularqueue.h"
#include "loadstorebuffer.h"
namespace Komeiji {
void LoadStoreBuffer::add(lsb data) {
  lsb_content temp;
  temp.data = data;
  temp.busy = true;
  list_next.push_back(temp);
  busy = true;
}
unsigned int LoadStoreBuffer::output(Lsb_to_rs &lsb_to_rs, Memory &memory) {
  if (list.empty()) {
	lsb_to_rs.busy = false;
	return 0;
  }
  lsb_to_rs.busy = true;
  lsb_to_rs.rob_id = list.front().data.rob_id;
  busy = true;
  lsb_content first = list.front();
  if (first.data.type == lsb_type::Lb) {
	int8_t result;
	memory.load_byte(first.data.address, result);
	int transfer= static_cast<int>(result & 0xff);
	lsb_to_rs.data = static_cast<unsigned int>(transfer);
  } else if (first.data.type == lsb_type::Lbu) {
	int8_t result;
	memory.load_byte(first.data.address, result);
	lsb_to_rs.data = static_cast<unsigned int>(static_cast<uint8_t >((result & 0xff)));
  } else if (first.data.type == lsb_type::Lh) {
	int16_t result;
	memory.load_half(first.data.address, result);
	lsb_to_rs.data = static_cast<unsigned int>(result);
  } else if (first.data.type == lsb_type::Lhu) {
	int16_t result;
	memory.load_half(first.data.address, result);
	lsb_to_rs.data = static_cast<unsigned int>(static_cast<uint16_t>(result));
  } else if (first.data.type == lsb_type::Lw) {
	int result;
	memory.load_word(first.data.address, result);
	lsb_to_rs.data = static_cast<unsigned int>(result);
  } else if (first.data.type == lsb_type::Sw) {
	memory.store(first.data.address, first.data.value);
  } else if (first.data.type == lsb_type::Sb) {
	memory.store_byte(first.data.address, static_cast<int8_t>(first.data.value));
  } else if (first.data.type == lsb_type::Sh) {
	memory.store_half(first.data.address, static_cast<int16_t>(first.data.value));
  } else {
	lsb_to_rs.busy = false;
  }
  list_next.pop_back();
  return lsb_to_rs.data;
}

}