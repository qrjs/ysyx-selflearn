#include <nvboard.h>
#include "Vtop.h"

void nvboard_bind_all_pins(Vtop* top) {
	nvboard_bind_pin( &top->din, 9, SW7, SW7, SW6, SW5, SW4, SW3, SW2, SW1, SW0);
	nvboard_bind_pin( &top->shamt, 3, SW10, SW9, SW8);
	nvboard_bind_pin( &top->LR, 1, SW11);
	nvboard_bind_pin( &top->AL, 1, SW12);
	nvboard_bind_pin( &top->dout, 8, LD7, LD6, LD5, LD4, LD3, LD2, LD1, LD0);
}
