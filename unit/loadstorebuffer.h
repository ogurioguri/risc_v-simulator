#ifndef C_UNIT_LOADSTOREBUFFER_H_
#define C_UNIT_LOADSTOREBUFFER_H_
#include"tool/instruction.h"
#include"tool/circularqueue.h"
#include"Decode.h"

namespace Komeiji {
struct lsb_content {
  lsb data;
  bool busy;
 public:
  lsb_content() = default;
  lsb_content(const lsb_content &other) {
	if (this == &other) {
	  return;
	}
	data = other.data;
	busy = other.busy;
  };
  lsb_content &operator=(const lsb_content &other) {
	if (this == &other) {
	  return *this;
	}
	data = other.data;
	busy = other.busy;
	return *this;
  };
  ~lsb_content() = default;
};
class LoadStoreBuffer {
 public:
  circularqueue<lsb_content, 16> list;
  bool old_busy;
 private:
  circularqueue<lsb_content, 16> list_next;
  bool busy;
 public:
  LoadStoreBuffer() = default;
  void add(lsb data);
  bool full() {return list.full();};
  unsigned int output(Lsb_to_rs & lsb_to_rs,Memory & memory);
  void execute(){};
  void update() {
	list = list_next;
	old_busy = busy;
	busy = false;
  };
};
}
#endif //C_UNIT_LOADSTOREBUFFER_H_
