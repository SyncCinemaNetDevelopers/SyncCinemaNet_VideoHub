P = src
CPPSRC = $P/main.cpp $P/rtsp.cpp $P/utils/exception.cpp
CPPOBJ = $(CPPSRC:.cpp=.o)
CSRC = $P/utils/rtsp-parser.c
COBJ = $(CSRC:.c=.o)
OBJDIR = obj

NAME = a.out

all:
	@echo 'run "make install" for start installation'
	@echo 'run "make build" for build'
	@echo 'run "make rmo" for remove all objects files after build'

build: makedirs compile

makedirs:
	@mkdir bin; true
	@mkdir $(OBJDIR); true

.cpp.o: 
	$(CXX) -c -I./$P $< -o $@

.c.o:
	$(CC) -c -I./$P $< -o $@

compile: $(CPPOBJ) $(COBJ)
	@$(CXX) $(CPPOBJ) $(COBJ) -o bin/$(NAME) && echo compile : success

rmo:
	@find ./ -name "*.o" | xargs rm && echo object remove : success