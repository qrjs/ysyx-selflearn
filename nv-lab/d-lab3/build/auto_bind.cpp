#include <nvboard.h>
#include "Vtop.h"

void nvboard_bind_all_pins(Vtop* top) {
	nvboard_bind_pin( &top->a, 4, SW3, SW2, SW1, SW0);
	nvboard_bind_pin( &top->b, 4, SW7, SW6, SW5, SW4);
	nvboard_bind_pin( &top->alu_ch, 3, SW10, SW9, SW8);
	nvboard_bind_pin( &top->alu_f, 4, LD15, LD14, LD13, LD12);
	nvboard_bind_pin( &top->over_f, 1, LD0);
	nvboard_bind_pin( &top->zero_f, 1, LD1);
}
