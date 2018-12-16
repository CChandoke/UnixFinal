
# build hand
gcc -w -o hand hand.c -L$HOME/local/gsl-2.5/lib/ -lgsl -lgslcblas  -I$HOME/local/gsl-2.5/include/ -Wl,-rpath=$HOME/local/gsl-2.5/lib/

