all:																		 @echo "Write this Makefile by your self."



sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!  cd ../Desktop/verilator/test_our && \
	verilator --cc --exe --trace-fst --build -j 0 -Wall top.v sim_main.cpp && \
	./obj_dir/Vtop && \
	gtkwave waveform.fst


include ../Makefile
