# Identify the debug probe used
export DEBUG_ADAPTER=$(shell ./id_probe.sh)

marble:
	make -f makefile.board BOARD=marble all

marble_download:
	make -f makefile.board BOARD=marble download

marble_clean:
	make -f makefile.board BOARD=marble clean

marble_mini:
	make -f makefile.board BOARD=marble_mini all

marble_mini_download:
	make -f makefile.board BOARD=marble_mini download

marble_mini_clean:
	make -f makefile.board BOARD=marble_mini clean

marble_gdb:
	make -f makefile.board BOARD=marble gdb

# This command can be used to erase the flash memory
# associated with the 'EEPROM0' sector and hopefully
# unstall the firmware.
marble_recover:
	make -f makefile.board BOARD=marble recover download

.PHONY: sim
sim:
	make -f makefile.sim BOARD=sim all

sim_clean:
	make -f makefile.sim BOARD=sim clean

.PHONY: run
run:
	make -f makefile.sim BOARD=sim run

clean: marble_mini_clean marble_clean sim_clean
