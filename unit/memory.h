#ifndef C_UNIT_MEMORY_H_
#define C_UNIT_MEMORY_H_
#include <cstdint>
namespace Komeiji {
class Memory {
 public:
  Memory() = default;
  void load_word(unsigned int address, int &data) {
	int pos = address;
	if (pos >= 0x100000) {
	  data = 0;
	  throw "Memory out of range";
	}
	uint8_t part1 = memory[pos];
	uint8_t part2 = memory[pos + 1];
	uint8_t part3 = memory[pos + 2];
	uint8_t part4 = memory[pos + 3];
	unsigned int a = (part1) | (static_cast<uint8_t>(part2) << 8) | (static_cast<uint8_t>(part3) <<16)
		| (static_cast<uint8_t>(part4) << 24);
	data = static_cast<int>(a);
  };
  void store(unsigned int address, int data) {
	int pos = address;
	if (pos >= 0x100000) {
	  throw "Memory out of range";
	}
//	memory[pos] = static_cast<int8_t>((data >> 24) & 0xff);
//	memory[pos + 1] = static_cast<int8_t>((data >> 16) & 0xff);
//	memory[pos + 2] = static_cast<int8_t>((data >> 8) & 0xff);
//	memory[pos + 3] = static_cast<int8_ut>(data & 0xff);
	memory[pos] = static_cast<uint8_t>(data & 0xff);
	memory[pos + 1] = static_cast<uint8_t>((data >> 8) & 0xff);
	memory[pos + 2] = static_cast<uint8_t>((data >> 16) & 0xff);
	memory[pos + 3] = static_cast<uint8_t>((data >> 24) & 0xff);
  };
  void load_half(unsigned int address, int16_t &data) {
	int pos = address;
	if (pos >= 0x100000) {
	  data = 0;
	  throw "Memory out of range";
	}
	uint8_t part1 = memory[pos+1];
	uint8_t part2 = memory[pos];
	uint16_t a= (static_cast<uint16_t>(part1) << 8) | static_cast<uint8_t>(part2);
	data = static_cast<int16_t>(a);
  }
  void load_byte(unsigned int address, int8_t &data) {
	int pos = address;
	if (pos >= 0x100000) {
	  data = 0;
	  throw "Memory out of range";
	}
	data = (memory[pos]);
  }
  void store_half(unsigned int address, int16_t data) {
	int pos = address;
	if (pos >= 0x100000) {
	  throw "Memory out of range";
	}
	memory[pos+1] = static_cast<int8_t>((data >> 8) & 0xff);
	memory[pos] = static_cast<int8_t>(data & 0xff);
  }
  void store_byte(unsigned int address, int8_t data) {
	int pos = address;
	if (pos >= 0x100000) {
	  throw "Memory out of range";
	}
	memory[pos] = data;
  }
  void update() {
  }
  void execute() {
  }
 public:
  uint8_t memory[0x100000];
};
}
#endif //C_UNIT_MEMORY_H_
