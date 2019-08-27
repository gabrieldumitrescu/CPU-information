ASM:=nasm
ASMFLAGS:=-f elf64
CC:=gcc
CCFLAGS:=-O3
LINK:=ld
LDFLAGS:=-lc --entry main

APP:=CPU-info

CSRC=main.c
BRANDSRC=brandString.asm
IDSRC=vendorID.asm
FREQINFOSRC=getFrequencyInfo.asm
FEATUREINFOSRC=getFeatureInfo.asm
OBJS=main.o brandString.o vendorID.o getFrequencyInfo.o getFeatureInfo.o

all:$(APP)

$(APP):$(OBJS)
	$(CC) -o $@ $^

main.o:$(CSRC)
	$(CC) -c $(CCFLAGS) -o $@ $^

brandString.o:$(BRANDSRC)
	$(ASM) $(ASMFLAGS) -o $@ $^

getFrequencyInfo.o:$(FREQINFOSRC)
	$(ASM) $(ASMFLAGS) -o $@ $^

getFeatureInfo.o:$(FEATUREINFOSRC)
	$(ASM) $(ASMFLAGS) -o $@ $^

vendorID.o:$(IDSRC)
	$(ASM) $(ASMFLAGS) -o $@ $^

clean:
	rm -f $(APP) $(OBJS)
