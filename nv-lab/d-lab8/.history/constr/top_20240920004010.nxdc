#include <verilated.h>
#include "Vtop.h"
#include <nvboard.h>

static TOP_NAME dut;
void nvboard_bind_all_pins(Vtop* top);
void single_cycle(){
	dut.eval();
	}
int main(){
	nvboard_bind_all_pins(&dut);
	nvboard_init();
	while(1){
		single_cycle();
		nvboard_update();
		}
	}
