forall(C1, C2):- \+(C1, \+C2).
%Q1
onboard(q(_, H)):- member(H, [1, 2, 3, 4, 5, 6, 7, 8]).
no_attack([q(M1, N1)|T], q(M, N)):-N1 \= N, D1 is M1 + N1, D2 is M + N, D1 \= D2, S1 is M1 + M, S2 is N1 + N, S1 \= S2.
%Q2
template([q(1, _), q(2, _), q(3, _), q(4, _), q(5, _), q(6, _), q(7, _), q(8, _)]).

% Q3
solution([]).
solution([q(X, Y)|Others]):-member(Y,[1,2,3,4,5,6,7,8]),solution(Others),no_attack(Others, q(X, Y)).

%Q4/Users/fushanshan/Downloads/prolog/queens.pl
print([]).
print(q(M1, 1)):- write(Q), write(' '),  print(M1, 
print_board([]).
print_board([q(M1, N1)|T]):- print(q(M1, N1)), print_board(T).
