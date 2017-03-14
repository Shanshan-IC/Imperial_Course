:-use_module(library(lists)).


% child_mother(C, M) means C is a child of mother M.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

child_mother(amy, mary).
child_mother(arthur, mary).
child_mother(angel, jane).
child_mother(anton, rita).
child_mother(alan, rita).
child_mother(axel, susan).
child_mother(ann, tina).    


% age(C, A) means C is of age A.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

age(amy, 6).
age(arthur, 15).
age(angel, 16).
age(anton, 4).
age(alan, 8).
age(axel, 16).
age(ann, 4).

% employed(X) means X is employed.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

employed(susan).
employed(rita).

%Q1 
%i) ecb(M)
ecb(M):- child_mother(C, M), age(C, A), A =< 14.
ecb(M):- child_mother(C, M), \+ employed(M), age(C, A), A > 14, A =< 16.

%ii) mother_of_the_youngest(M)
age_up(A):- age(C,A).
age_list(L):- setof(A, age_up(A), L).
min([Min], Min).
min([X|L], Min):- min(L, Min), Min =< X.
min([X|L], Min):- min(L, Min2), X < Min2, Min is X.
mother_of_the_youngest(M):- age_list(L), min(L, A), age(C, A), child_mother(C, M).

%iii) mothers_of_young(LM)
mothers_of_young(Ms):- setof(M,C^A^(child_mother(C,M), age(C,A), A =< 10), Ms).

%Q2
% i)merge(L1, L2, L)
merge([],[],[]).
merge([], X, X).
merge(X, [], X).
merge([H1|T1], [H2|T2], [H1|T3]):- H1 =< H2, merge(T1, [H2|T2], T3).
merge([H1|T1], [H2|T2], [H2|T3]):- H2 < H1, merge([H1|T1], T2, T3).

%ii) findElement(N, L, E).
findElement(1, [H|T], H).
findElement(N, [H|T], E):- N>1, N1 is N-1, findElement(N1, T, E).
