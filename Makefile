PREFIX		= /usr/local/
BINDIR		= $(PREFIX)bin/
MANDIR		= $(PREFIX)man/

CC		= gcc
LINKER		= gcc
CFLAGS		= -g -O3 -Wall
LDFLAGS		= -g -O3 -Wall

COMMON_OBJ	= bogomips.o

386_DELAY	= delay_386.o
PORTABLE_DELAY	= delay_portable.o
PENTIUM_DELAY	= delay_586.o
ALPHA_DELAY	= delay_alpha.o
SPARC64_DELAY	= delay_sparc64.o
SPARC_DELAY	= delay_sparc.o
PPC_DELAY	= delay_ppc.c
PARISC_DELAY	= delay_parisc.o
IA64_DELAY	= delay_ia64.o
ARM_DELAY	= delay_arm.o

bogoport:	$(COMMON_OBJ) $(PORTABLE_DELAY)
		$(LINKER) $(LDFLAGS) $(COMMON_OBJ) $(PORTABLE_DELAY) -o bogoport

bogo586:	$(COMMON_OBJ) $(PENTIUM_DELAY)
		$(LINKER) $(LDFLAGS) $(COMMON_OBJ) $(PENTIUM_DELAY) -o bogo586

bogo386:	$(COMMON_OBJ) $(386_DELAY)
		$(LINKER) $(LDFLAGS) $(COMMON_OBJ) $(386_DELAY) -o bogo386

bogoAlpha:	$(COMMON_OBJ) $(ALPHA_DELAY)
		$(LINKER) $(LDFLAGS) $(COMMON_OBJ) $(ALPHA_DELAY) -o bogoAlpha

bogoSparc64:	$(COMMON_OBJ) $(SPARC64_DELAY)
		$(LINKER) $(LDFLAGS) $(COMMON_OBJ) $(SPARC64_DELAY) -o bogoSparc64

bogoSparc:	$(COMMON_OBJ) $(SPARC_DELAY)
		$(LINKER) $(LDFLAGS) $(COMMON_OBJ) $(SPARC_DELAY) -o bogoSparc

bogoPPC:	$(COMMON_OBJ) $(PPC_DELAY)
		$(LINKER) $(LDFLAGS) -Wa,-mregnames $(COMMON_OBJ) $(PPC_DELAY) -o bogoPPC

bogoparisc:	$(COMMON_OBJ) $(PARISC_DELAY)
		$(LINKER) $(LDFLAGS) $(COMMON_OBJ) $(PARISC_DELAY) -o bogoparisc

bogoia64:	$(COMMON_OBJ) $(IA64_DELAY)
		$(LINKER) $(LDFLAGS) $(COMMON_OBJ) $(IA64_DELAY) -o bogoia64

bogoarm-ipaq:	$(COMMON_OBJ)
		$(CC) $(CFLAGS) -o $(ARM_DELAY) -c delay_arm.S -DHZ_VALUE=100
		$(LINKER) $(LDFLAGS) $(COMMON_OBJ) $(ARM_DELAY) -o bogoarm-ipaq

bogoarm-shark:	$(COMMON_OBJ)
		$(CC) $(CFLAGS) -o delay_arm.o -c delay_arm.S -DHZ_VALUE=64
		$(LINKER) $(LDFLAGS) $(COMMON_OBJ) $(ARM_DELAY) -o bogoarm-shark

clean:;		
		rm -f core bogo386 bogoport bogo586 *.o bogoAlpha bogoSparc \
			bogoSparc64 bogoPPC bogoparisc bogoia64 bogoarm-shark \
			bogoarm-ipaq

mrproper:	clean
		rm -f *~

install:;
		install -sC `find -perm +1 -name "bogo*"`  $(BINDIR)
		install -sC bogomips.1 $(MANDIR)
		
