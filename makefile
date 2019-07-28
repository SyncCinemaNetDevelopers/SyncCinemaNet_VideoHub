P = src
CPPSRC = main.cpp rtsp.cpp utils/exception.cpp
CPPOBJ = $(CPPSRC:.cpp=.o)
CSRC = utils/rtsp-parser.c
COBJ = $(CSRC:.c=.o)
OBJDIR = obj
OBJ = $(addprefix $(OBJDIR)/,$(CPPOBJ) $(COBJ))

NAME = a.out

all:
	@echo 'run "make install" for start installation'
	@echo 'run "make build" for build'
	@echo 'run "make rmo" for remove all objects files after build'

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