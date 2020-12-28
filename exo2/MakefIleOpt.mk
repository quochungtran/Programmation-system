OBJS = main.o explorer.o my_system.o premier.o
HEADERS = explorer.h my_system.h premier.h
Prog_premiers : $(OBJS)
	gcc -o $@ $(OBJS)
main.o : main.c explorer.h
explorer.o : explorer.h $(HEADERS)
my_system.o : my_system.h
premier.o : premier.h
.c.o :
		gcc -c $<
clean :
	rm -f Prog_premiers *.o
