%tut3
%1
%a)
min([Min], Min).
min([X|L], Min):- min(L, Min), Min =< X.
min([X|L], Min):- min(L, Min2), X < Min2, Min is X.
delete(Min, L, L1):- setof(X, (member(X, L), X \= Min), L1).
mysort([], []).
mysort([X], [X]).
mysort(L, [Min|T]):- length(L, N), N > 1, min(L, Min), delete(Min, L, L1), mysort(L1, T).
%b)
rev([],[]).
%rev([X],[X]).
rev([H|T], R):- rev(T, R1), append(R1, [H], R).
%c
followedBy(X, Y, [X|T]):- T = [Y|_].
followedBy(X, Y, [_|T]):-followedBy(X, Y, T).
%d
nextTo(X,Y,L):- followedBy(X,Y,L).
nextTo(X,Y,L):-followedBy(Y, X,L).
%e
sumList([], 0).
sumList([H|T], S):- sumList(T, S1), S is (H + S1).
%2
last(E, [E|T]):- T = [].
last(E, [H|T]):- last(E, T), T \= [].
%3
%a) edge(X,Y)
edge('a', 'b').
edge('a', 'e').
edge('b', 'c').
edge('e', 'f').
edge('c', 'd').
edge('f', 'd').
edge('f', 'c').
%b) path(X,Y)
path(X, Y):- edge(X, Y).
path(X, Y):- edge(X, Z), path(Z, Y).
%c
path3(X, Y, []):- \+ path(X, Y).
path3(X, Y, [X,Y]):- edge(X, Y).
path3(X, Y, [X|H]):- edge(X, Z), path(Z, Y), path3(Z, Y, H).
%d
max(E,[E]).
max(E, [H|T]):- max(E, T), H =< E.
max(E, [E|T]):- max(E2, T), E > E2.
%5
max_of_all(E, L):- findall(X, (member(L1, L), max(X, L1)), E_List), max(E, E_List).
