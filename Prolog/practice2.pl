%Q1
remove_item(E, L, L):- \+member(E, L).
remove_item(E, [E|T], T2):- remove_item(E, T, T2).
remove_item(E, [H|T], [H|T2]):- H \= E, remove_item(E, T, T2).  
%Q2
drop_items(L, 0, L).
drop_items(L, N, []):- length(L, NL), NL =< N.
drop_items(L, N, L2):- length(L, NL), NL > N, append(L1, L2, L), length(L1, N).
%Q3
drop_more_items(L, N, []):- drop_items(L, N, []).
drop_more_items(L, N, NewL):- append(L1, L2, L), length(L1, N), remove_all(L1, L2, NewL).
remove_all([], L2, L2).
remove_all([H|T], L2, NewL):-remove_item(H, L2, NewL2), remove_all(T, NewL2, NewL).
%Q4
count(L, R):- setof((E, Num),(member(E, L), countNum(E, L, Num)), R).
countNum(E, L, Num):- remove_item(E, L, NewL), length(L, L1), length(NewL, L2), Num is (L1 - L2).
