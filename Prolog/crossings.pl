%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                  %
%         276 Introduction to Prolog               %
%                                                  %
%         Coursework 2013-14 (crossings)           %
%                                                  %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



%% ------------  (utilities) DO NOT EDIT

fees(2,3).   


forall(P,Q) :- \+ (P, \+ Q).


app_remove(X,List,Remainder) :-
  append(Front, [X|Back], List),
  append(Front, Back, Remainder).


% The following might be useful for testing.
% You may edit it if you want to adjust
% the layout. DO NOT USE it in your submitted code.

write_list(List) :-
  forall(member(X, List),
         (write('  '), write(X), nl)
        ).


%% step 1
unsafe(L):- member(w, L), member(g, L).
unsafe(L):- member(g, L), member(c, L).
safe([]).
safe([f|T]).
safe(L):- \+member(f, L), \+ unsafe(L).

%% step 2
safe_state(N-S):- safe(N), safe(S).

%% step 3
%another way
perm(A, B):- sort(A, X), sort(B, X).
equiv(N1-S1, N2-S2):- perm(N1, N2), perm(S1, S2).

%% step 4
%goal([f|S]):- equiv([]- [f, c, w, g, b], [f|S]).
goal([]-[f|T]) :-
  equiv([]-[f, w, g, b, c], []-[f|T]).

%% step 5
visited(State, [S|H]) :- equiv(State, S); visited(State, H).

%% step 6
remove(X, [X|T], T).
remove(X, [H|T], [H|R]):- remove(X, T, R).

%% step 7
%crossing([f|N1]-S1, f, N1-[f|S1]).
%crossing([f|N1]-S1, M2, N2-S2):- member(M, N1), M \= f, M2= f(M), remove(M, N1, N2), append([f|S1], [M], S2).
crossing([f|N1]-S1 , Move, N2-[f|S2]) :- 
    remove(X, N1, N2), S2 = [X|S1], Move = f(X);
  N1 = N2,
  S1 = S2, 
  Move = f. 

crossing(N1-[f|S1], Move, [f|N2]-S2) :-
    remove(X, S1, S2), N2 = [X|N1], Move = f(X);
  N1 = N2,
  S1 = S2,
  Move = f. 
%% step 8
succeeds(Seq) :-
  journey([f, w, g, c, b]-[], [], [], Seq).

journey(State, H, A, A) :-
  goal(State), \+length(H, 0).

journey(State, History, A, Seq) :-
  safe_state(State),
  \+ visited(State, History),
  crossing(State, Move, NewState),
  journey(NewState, [State|History], [Move|A], Seq).

%% step 9
fee(f, 2).
fee(f(_), 3).
journey_cost(S, C):- succeeds(S), calculate(S, C).
calculate([], 0).
calculate([M|T], C):- fee(M, F), NewA is C+ F, calculate(T, NewA).
%journey_cost(Seq, Cost):-
 % succeeds(Seq),
  %calculate(Seq, 0, Cost).
%calculate([], A, A).
%calculate([M|T], A, C):-
 % fee(M, F),
  %NewA is A + F,
  %calculate(T, NewA, C).
