# =============== Variables for compiler options ===============

# Defaults

# Compiler choice
comp = gnu

# Optimization switch
opt  = no

# OpenMP threading switch
omp  = no

# MPI parallelization switch
mpi  = no

# Boost library switch
boost = no

# Archiver choice
AR = ar rcs


# GNU compiler
ifeq ($(comp),gnu)
    CXX = g++

    ifeq ($(opt),yes)
        OPTIONS := -O3
    else
        OPTIONS := -g -O0 -Wall -pedantic
    endif

    ifeq ($(omp),yes)
        OPTIONS += -fopenmp -DOMPYES
    endif

endif


# Intel compiler
ifeq ($(comp),intel)
    CXX = icpc

    ifeq ($(opt),yes)
        OPTIONS := -O3 # -fast
    else
        OPTIONS := -g -O0 -Wall
    endif

    ifeq ($(omp),yes)
        OPTIONS += -qopenmp -DOMPYES
    endif

    ifeq ($(mpi),yes)
        CXX = mpicxx
        OPTIONS += -DMPIYES
    endif

endif


# Portland compiler
ifeq ($(comp),pgi)
    CXX = pgc++

    ifeq ($(opt),yes)
        OPTIONS := -O3 # -Mipa=fast,inline
    else
        OPTIONS := -g -O0 -Mbounds
    endif

    ifeq ($(omp),yes)
        OPTIONS += -mp -DOMPYES
    endif

endif


# Extensive warnings with GNU compiler
ifeq ($(comp),full)
    CXX = g++

    OPTIONS := -g -O -Wall -Weffc++ -pedantic -pedantic-errors -Wextra -Wcast-align \
               -Wcast-qual -Wchar-subscripts -Wcomment -Wconversion \
               -Wdisabled-optimization -Wfloat-equal \
               -Wformat -Wformat=2 -Wformat-nonliteral -Wformat-security \
               -Wformat-y2k -Wimport -Winit-self -Winvalid-pch \
               -Wunsafe-loop-optimizations -Wlong-long -Wmissing-braces \
               -Wmissing-field-initializers -Wmissing-format-attribute \
               -Wmissing-include-dirs -Wmissing-noreturn -Wpacked \
               -Wparentheses -Wpointer-arith -Wredundant-decls -Wreturn-type \
               -Wsequence-point -Wshadow -Wsign-compare -Wstack-protector \
               -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch -Wswitch-default \
               -Wswitch-enum -Wtrigraphs -Wuninitialized \
               -Wunused-function -Wunused-label -Wunused-parameter \
               -Wunused-value -Wunused-variable -Wvariadic-macros \
               -Wvolatile-register-var -Wwrite-strings
endif

# =============== Variables for common paths ===================

UNITEST  =   $(COMPATH)/UniTest

#BOOST    =   $(COMPATH)/boost/boost_1_67_0
#OPTIONS +=   -I$(BOOST)

#GSL      =   $(COMPATH)/gsl/gsl-2.5
#OPTIONS +=   -I$(GSL)/include
GSLLINK :=    
#GSLLINK :=   -L$(GSL)/lib -lgsl -lgslcblas -lm

ifeq ($(mpi),yes)
    OPTIONS += -I$(COMPATH)/parallel/mpi
endif


# =============== Variables for paths and file names ===========

BUILDIR  =   build

PROGRAM  =   $(patsubst %_main.cpp,%,$(wildcard *_main.cpp))
PSRCLOC  =   src
PROGSRC  =   $(PROGRAM)_main.cpp
PROGOBJ  =   $(BUILDIR)/$(PROGRAM)_main.o
PROGLIB  =   lib$(PROGRAM).a
PROGEXE  =   $(PROGRAM)

TESTLOC  =   UniTest
TESTSRC  =   tests.cpp
TESTOBJ  =   $(BUILDIR)/tests.o
TESTLIB  =   libtest$(PROGRAM).a
TESTEXE  =   tests

CPPOBJ   =   $(patsubst $(PSRCLOC)/%.cpp, $(BUILDIR)/%.o, \
             $(wildcard $(PSRCLOC)/*.cpp))

TSTOBJ   =   $(BUILDIR)/Test.o \
             $(patsubst $(PSRCLOC)/%.cpp, $(BUILDIR)/test_%.o, \
             $(wildcard $(PSRCLOC)/*.cpp))

OPTIONS += -I./$(PSRCLOC)
LOGFILE  =   $(BUILDIR)/makelog.txt

$(eval CXXPATH = $(shell which $(CXX)))
$(eval CXXINFO = $(shell $(CXXPATH) --version))
define VERSION
$(CXXINFO)
endef
export VERSION

# =============== Rule for the main program ====================

$(PROGEXE) : $(PROGOBJ) $(PROGLIB)
	@echo
	$(CXX) $(OPTIONS) -L. -o $@ $< -l$(PROGRAM) $(GSLLINK)


# =============== Rules for the program sources ================

$(BUILDIR)/$(PROGRAM)_main.o : $(PROGRAM)_main.cpp
	@echo
	$(CXX) $(OPTIONS) -o $@ -c $^

$(BUILDIR)/%.o : $(PSRCLOC)/%.cpp
	@echo
	$(CXX) $(OPTIONS) -o $@ -c $^

lib$(PROGRAM).a : $(CPPOBJ)
	@echo
	@make log
	$(AR) lib$(PROGRAM).a $^


# =============== Rule for the unit-test program ===============

$(TESTEXE) : $(TESTOBJ) $(TESTLIB) $(PROGLIB)
	@echo
	$(CXX) $(OPTIONS) -I$(UNITEST) -L. -o $@ $< -ltest$(PROGRAM) -l$(PROGRAM) $(GSLLINK)


# =============== Rules for the unit-test sources ==============

$(TESTOBJ) : $(UNITEST)/$(TESTSRC) $(TESTLOC)/tests_headers.inc $(TESTLOC)/tests_runs.inc
	@echo
	@cp $< .
	$(CXX) $(OPTIONS) -I$(UNITEST) -o $@ -c $(TESTSRC)
	@rm -rf $(TESTSRC)

$(BUILDIR)/Test.o : $(UNITEST)/Test.cpp
	@echo
	$(CXX) $(OPTIONS) -I$(UNITEST) -o $@ -c $^

$(BUILDIR)/%.o : $(TESTLOC)/%.cpp
	@echo
	$(CXX) $(OPTIONS) -I$(UNITEST) -o $@ -c $^

libtest$(PROGRAM).a : $(TSTOBJ)
	@echo
	$(AR) libtest$(PROGRAM).a $^


# =============== Rule for the log file ========================

.PHONY : log
log :
	@echo CXX = $(CXX) > $(LOGFILE)
	@echo OPTIONS = $(OPTIONS) >> $(LOGFILE)
	@echo AR = $(AR) >> $(LOGFILE)
	@echo >> $(LOGFILE)
	@echo $(CXXPATH) --version >> $(LOGFILE)
	@echo $$VERSION >> $(LOGFILE)


# =============== Rules for cleanup ============================

.PHONY : clean_obj
clean_obj :
	@rm -f $(PROGOBJ) $(CPPOBJ) $(TSTOBJ) $(TESTOBJ)

.PHONY : clean
clean :
	@make clean_obj
	@rm -f lib$(PROGRAM).a libtest$(PROGRAM).a $(LOGFILE)

.PHONY : clean_exe
clean_exe :
	@rm -f $(PROGEXE) $(TESTEXE)

.PHONY : clean_all
clean_all :
	@make clean
	@make clean_exe

