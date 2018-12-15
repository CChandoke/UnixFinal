# build pitboss
g++ -w -std=c++11 -o pitboss pitboss.c -I$HOME/local/gsl-2.5/include/

# build dealer
g++ -w -std=c++11 -o dealer dealer.cpp -I$HOME/local/gsl-2.5/include/

# build hand
gcc -w -o hand hand.c -L$HOME/local/gsl-2.5/lib/ -lgsl -lgslcblas  -I$HOME/local/gsl-2.5/include/ -Wl,-rpath=$HOME/local/gsl-2.5/lib/

