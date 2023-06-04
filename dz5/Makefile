CFLAGS = -Wall
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

PROGRAM = a.out
SRCS = Connect4.cpp Menu.cpp PlayerMinMax.cpp main.cpp

$(PROGRAM): $(SRCS)
	g++ $(SRCS) $(CFLAGS) $(LDLIBS)

.PHONY: run del

run: $(PROGRAM)
	@./$(PROGRAM)

del:
	rm -rf $(PROGRAM)