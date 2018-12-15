

# g++ -std=c++11 -o dealer dealer.cpp -lgslcblas -lgsl -L ~/local/gsl-2.5/lib/  -I ~/local/gsl-2.5/include/
# gcc -o hand hand.c -O2 -lgslcblas -lgsl -L ~/local/gsl-2.5/lib/  -I ~/local/gsl-2.5/include/

# Files
PATH = $$HOME/local/gsl-2.5
LPATH = $PATH/lib/
IPATH = $PATH/include/
LDLIBS := -lgsl -lgslcblas
# Options
CC = g++
CFLAGS = -g -std=c++11
# Rules
$(EXEC1): hand.o 
	$(CC) $(CFLAGS) -o $@ $< -I$(IPATH) -L$(LPATH) $(LDLIBS)
$(EXEC2): dealer.o 
	$(CC) $(CFLAGS) -o $@ $^ -I$(IPATH) -L$(LPATH) $(LDLIBS)
dealer.o: dealer.cpp
	$(CC) $(CFLAGS) -c $< -I$(IPATH) -L$(LPATH) $(LDLIBS)
hand.o: hand.c 
	$(CC) $(CFLAGS) -c $< -I$(IPATH) -L$(LPATH) $(LDLIBS)
clean:
	$(RM) $(EXEC) *.o

		
		