                                                          
%Q1
%andgate, orgate, xorgate
andgate('And').
orgate('Or').
xorgate('Xor').
%input	
input1('And', 1).
input2('And', 0).
input1('Or', 1).
input2('Or', 0).
input1('Xor', 1).
input2('Xor', 0).
%output
%and gate
outgate(G, 1):- andgate(G), input1(G, 1), input2(G, 1).
outgate(G, 0):-	andgate(G), \+ outgate(G, 1).
%orgate
orgate(G, 0):- orgate(G), input1(G, 0),	input(G, 0).
orgate(G, 1):- orgate(G), \+orgate(G, 0).
%xorgate
output(G,1):- xorgate(G),(input1(G,1), input2(G,0);
	                        input1(G,0), input2(G,1)).
output(G,0):- xorgate(G), \+ output(G,1).

%Q2
fib(1, 1).
fib(2, 1).
fib(N, R):- N > 2, N1 is (N-1), N2 is (N-2), fib(N1, R1), fib(N2, R2), R is R1+R2.
