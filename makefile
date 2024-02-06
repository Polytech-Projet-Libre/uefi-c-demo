TARGET = helloworld.efi
include uefi/Makefile

run: helloworld.efi
	uefi-run -b res/OVMF.fd $<

.PHONY: run