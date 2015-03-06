ifeq ($(MAKELEVEL), 0)
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
	rm -f $(OBJS) ; echo "Cleaning tests directory"
.PHONY : clean

cleanbin :
	rm -f $(BINDIR)/$(TESTSNAME) ; echo "Suppressing tests binaries"
.PHONY : cleanbin

endif

