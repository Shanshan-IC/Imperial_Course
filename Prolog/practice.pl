%Q1 
subList([], L2).
subList([H|T], L2):- member(H, L2), subList(T, L2).

%Q2
difference(L, [], L).
difference(L1, L2, L):- findall(L1s, (member(L1s, L1), \+member(L1s, L2)), L).

%Q3
sift(L, N, R):- findall(Ls, (member(Ls, L), Ls =< N), R).

%Q4
common(L1, L2, L):- setof(Ls, (member(Ls, L1), member(Ls, L2)), L).
common(L1, L2, []):- \+setof(Ls, (member(Ls, L1), member(Ls, L2)), L).

%Q5
delete(L, R):- delete_up(L, R, 2).
delete([], []).
delete_up([H], [H], 2).
delete_up([H, L], [H], 2).
delete_up([H|T], [H|T2], 2):- delete_up(T, T2, 1).
delete_up([H|T], R, 1):- delete_up(T, R, 2).
% another way
% delete([H],[H]).
% delete([H,_], H).
% delete([H,_|T],[H|R]):- delete(T, R).

%Q6
get_C(L1, L2, C):- findall((A, B, C), (member((A, B), L1), member((A, B, C), L2)), C).
get_I(L1, L2, I):- findall((A, B, C), (member((A, B, C), L2), \+member((A, B), L1)), I).
process(L1, L2, C, I):- get_C(L1, L2, C), get_I(L1, L2, I).

%Q7
split(L, N, L1, L2):- get_L1(L, N, L1), get_L2(L, N, L2).
split(L, N, L, []):- length(L, N1), N1 < N.
get_L1(L, 0, []).
get_L1([H|T], N, [H|T1]):- N > 0, N1 is (N-1), get_L1(T, N1, T1).
get_L2(L, N, L2):- findall(Ls, (member(Ls, L), get_L1(L, N, L1), \+member(Ls, L1)), L2).

%Q8
drop(T, N, T2):- drop_up(T, N, N, T2).
drop(T, 0, T).
drop_up([H|T], 1, N, T):- length(T, N1), N1 < N.
drop_up([H|T], 1, N, T2):- length(T, N1), N1 >= N, drop_up(T, N, N, T2). 
drop_up([H|T], N1, N, [H|T1]):- N > 1, N2 is (N1-1), drop_up(T, N2, N, T1).

%Q9
enrolment(L, S, D):- member((D, Ss), L), member(S, Ss).

%Q10
student_list(L, Meng, MSc):- get_Meng(L, Meng), get_MSc(L, MSc).
get_Meng(L, Meng):- findall(S, (member((meng, Ss), L), member(S, Ss)), Meng).
get_MSc(L, MSc):- findall(S, (member((msc, Ss), L), member(S, Ss)), MSc).
