#ifndef C_UNIT_OP_QUEUE_H_
#define C_UNIT_OP_QUEUE_H_
#include"tool/instruction.h"
#include"registers.h"
#include"memory.h"
#include"Decode.h"
namespace Komeiji {
class Decode;
class Memory;
class op_queue {
 public:
  op_queue();
  void execute(unsigned int &pc, const Decode &decode);
  void update();
  void init(Memory &memory);
  unsigned int init_array[0x10000];
  unsigned int old_pointer;
  unsigned int pointer;
};
}
#endif //C_UNIT_OP_QUEUE_H_
