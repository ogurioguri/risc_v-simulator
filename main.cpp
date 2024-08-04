#include"tool/instruction.h"
#include"tool/circularqueue.h"
#include"alu.h"
#include"Decode.h"
#include"loadstorebuffer.h"
#include"reoderbuffer.h"
#include"registers.h"
#include"reservation_stations.h"
#include"memory.h"
#include"cpu.h"
int main(){
//  freopen("1.in","r",stdin);
//  freopen("1.out.2","w",stdout);
  Komeiji::CPU cpu;
  while(true){
	cpu.run();
  }
  return 0;
}