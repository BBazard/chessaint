ifeq (${MAKELEVEL}, 0)
error:
	@echo "Error : this makefile must be called from another makefile"
else

OBJS=

all : $(OBJS)
.PHONY : all

# # # # # # # # # # # # #

# HERE THE OBJS TO MAKE #

# # # # # # # # # # # # #

clean :
	rm -f $(OBJS) ; echo "Cleaning debug directory"
.PHONY : clean

cleanbin :
	rm -f $(BIN) ; echo "Suppressing debug binaries"
.PHONY : cleanbin

endif

