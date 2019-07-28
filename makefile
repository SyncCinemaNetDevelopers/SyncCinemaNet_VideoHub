P = src
CPPSRC = main.cpp rtsp.cpp utils/exception.cpp
CPPOBJ = $(CPPSRC:.cpp=.o)
CSRC = utils/rtsp-parser.c
COBJ = $(CSRC:.c=.o)
OBJDIR = obj
OBJ = $(addprefix $(OBJDIR)/,$(CPPOBJ) $(COBJ))

# this one must be empty
TESTSSRC = 
TESTS = options

NAME = a.out

all:
	@echo 'run "make install" for start installation'
	@echo 'run "make build" for build'
	@echo 'run "make rmo" for remove all objects files after build'
	@echo 'run "make build_tests" for build tests'

build: mkdirs compile

mkdirs:
	@mkdir -p bin; true
	@mkdir -p $(OBJDIR); true
	@cd src && find . -type d >../$(OBJDIR)/dirs.txt
	@cd $(OBJDIR) && xargs mkdir -p <./dirs.txt; rm dirs.txt; true

$(OBJDIR)/%.o: src/%.cpp
	$(CXX) -c -I./$P $< -o $@

$(OBJDIR)/%.o: src/%.c
	$(CC) -c -I./$P $< -o $@

compile: $(OBJ)
	@$(CXX) $(OBJ) -o bin/$(NAME) && echo compile : success

rmo:
	@find ./ -name "*.o" | xargs rm && echo object remove : success

build_tests: compile_tests $(patsubst %,test_%,$(TESTS)) delete_aux_files
	
compile_tests:
	find ./tests/src -name "*.cpp" > ./tests/src/srcs.txt

test_%:
	echo $@ : $* 
	find ./tests/$@/src -name "*.cpp" > ./tests/$@/srcs.txt
	$(eval TESTSSRC := $(shell cat ./tests/$@/srcs.txt) $(shell cat ./tests/src/srcs.txt))
	$(CXX) $(TESTSSRC) -I./tests/$@ -I./tests/src -o ./tests/$@/$*.test;true
	rm ./tests/$@/srcs.txt

delete_aux_files:
	rm ./tests/src/srcs.txt