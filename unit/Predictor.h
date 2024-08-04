#ifndef C_UNIT_PREDICTOR_H_
#define C_UNIT_PREDICTOR_H_
#ifndef PREDICT_UNIT_H
#define PREDICT_UNIT_H

#include <bitset>
#include <cstdint>

namespace conless {

constexpr int len = 100;

class Predictor {
 private:
  uint64_t global_history_{0};
  int8_t weight_[100][len + 1]{0};
  unsigned int success_count_{0}, failure_count_{0};

 public:
  Predictor() {};
  unsigned int GetPredictResult(unsigned int PC) {
	unsigned int i = HashPC(PC);
	int y_out = weight_[i][0];
	for (int j = 1; j < len + 1; j++) {
	  if (((global_history_ >> (i - 1)) & 1) == 1) {
		y_out += weight_[i][j];
	  } else {
		y_out -= weight_[i][j];
	  }
	}
	return y_out >= 0;
  };
  void PredictFeedBack(unsigned int PC, bool result, bool predict);
  void cout_predictLog();
  unsigned int HashPC(unsigned int PC){
	return PC % len;
  };
};

}  // namespace conless
#endif
#endif //C_UNIT_PREDICTOR_H_
