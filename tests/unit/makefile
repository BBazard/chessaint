ifeq (${MAKELEVEL}, 0)
error:
	@echo "Error : this makefile must be called from another makefile"
else

OBJS=

all : $(OBJS)

.PHONY : all clean cleanbin

# # # # # # # # # # # # #

# HERE THE OBJS TO MAKE #

# # # # # # # # # # # # #

clean :
	rm $(OBJS) 2> /dev/null ; echo "Cleaning debug directory" || true

cleanbin :
	rm $(BIN) 2> /dev/null ; echo "Suppressing debug binaries" || true

endif

