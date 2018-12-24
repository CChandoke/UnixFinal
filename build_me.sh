# build dealer
g++ -std=c++11 -o dealer dealer.cpp -I$HOME/local/gsl-2.5/include/

# build hand
gcc -o hand hand.c -L$HOME/local/gsl-2.5/lib/ -lgslcblas -lgsl -I$HOME/local/gsl-2.5/include/ -Wl,-rpath=$HOME/local/gsl-2.5/lib/

# build factorialApprox
g++ -o factorialApprox factorialApprox.cpp -L$HOME/local/gsl-2.5/lib/ -lgslcblas -lgsl -I$HOME/local/gsl-2.5/include/ -Wl,-rpath=$HOME/local/gsl-2.5/lib/

# build mighty
gcc -o mighty mighty.c -L$HOME/local/gsl-2.5/lib/ -lgslcblas -lgsl -I$HOME/local/gsl-2.5/include/ 

# build monte
gcc -std=gnu99 -o monte monte.c -L$HOME/local/gsl-2.5/lib/ -lgslcblas -lgsl -lm -I$HOME/local/gsl-2.5/include/ -Wl,-rpath=$HOME/local/gsl-2.5/lib/

# build signaler
g++ -o signaler signaler.cpp -L$HOME/local/gsl-2.5/lib/ -lgslcblas -lgsl -I$HOME/local/gsl-2.5/include/ 

# build uglyNums
g++ -o uglyNums uglyNums.cpp -I$HOME/local/gsl-2.5/include/ 

# build pitboss
g++ -o pitboss pitboss.cpp -I$HOME/local/gsl-2.5/include/ 

# build perfectNums
g++ -o perfectNums perfectNums.cpp -I$HOME/local/gsl-2.5/include/ 
