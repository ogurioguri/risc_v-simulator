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
	int8_t part1 = memory[pos];
	int8_t part2 = memory[pos + 1];
	int8_t part3 = memory[pos + 2];
	int8_t part4 = memory[pos + 3];
	data = (part1 << 24) | (static_cast<uint8_t>(part2) << 16) | (static_cast<uint8_t>(part3) << 8)
		| static_cast<uint8_t>(part4);
  };
  void store(unsigned int address, int data) {
	int pos = address;
	if (pos >= 0x100000) {
	  throw "Memory out of range";
	}
	memory[pos] = static_cast<int8_t>((data >> 24) & 0xff);
	memory[pos + 1] = static_cast<int8_t>((data >> 16) & 0xff);
	memory[pos + 2] = static_cast<int8_t>((data >> 8) & 0xff);
	memory[pos + 3] = static_cast<int8_t>(data & 0xff);
  };
  void load_half(unsigned int address, int16_t &data) {
	int pos = address;
	if (pos >= 0x100000) {
	  data = 0;
	  throw "Memory out of range";
	}
	int8_t part1 = memory[pos];
	int8_t part2 = memory[pos + 1];
	data = (static_cast<int16_t>(part1) << 8) | static_cast<uint8_t>(part2);
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
	memory[pos] = static_cast<int8_t>((data >> 8) & 0xff);
	memory[pos + 1] = static_cast<int8_t>(data & 0xff);
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
 private:
  int8_t memory[0x100000];
};
}
#endif //C_UNIT_MEMORY_H_
