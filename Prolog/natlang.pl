sentence(S):- noun_phrase(NP), verb_phrase(VP), append(NP, VP, S).
 
noun_phrase(NP):- article(A), noun(N), append(A, N, NP). 

verb_phrase(V):- verb(V).
verb_phrase(VP):- verb(V), noun_phrase(NP), append(V, NP, VP).

% The Lexicon:

article([the]).
article([a]).
article([an]).

noun([grass]).
noun([cow]).
noun([girl]).
noun([boy]).
noun([apple]).
noun([song]).

verb([eats]).
verb([sings]).
verb([chews]).
verb([kicks]).

%Q1
% a) define count_sentences(Text, Count): every time append a sentence before 'and', and then C+1
count_sentences([], 0).
count_sentences(L, X):- sentence(L), X = 1.
count_sentences(L, C):- append(X1, [and|X2],L), sentence(X1), count_sentences(X2, C1), C is C1 +1.

% b) define actions(Actor, Text, As): A is Actor, and if the word after word is verb, and then get list
actions([], []).
actions(A, Text, []) :- \+ member(A, Text).
actions(A, Text, []) :- \+verb([V]), append(_, [A, V|_], Text).
actions(A, Text, Vs) :- findall(V, (verb([V]), append(_, [A, V|_], Text)), Vs).

% Q2  noun_phrase_better: define vowel firstly, and then append a/the/an with noun
vowel([a]).
vowel([e]).
vowel([i]).
vowel([o]).
vowel([u]).

noun_phrase_better(L) :- noun([N]), append([the], [N], L).
noun_phrase_better(L) :- noun([N]), append([an], [N], L), atom_chars(N, [H|_]), vowel([H]).
noun_phrase_better(L) :- append([a],[N], L), noun([N]), atom_chars(N, [H|_]), \+vowel([H]).

% Q3
adverb([slowly]).
adverb([deliberately]).
adverb([merrily]).
adverb([sweetly]).
adverb([fast]).

% a and b) define cadvs: define [X1, and, X2] firstly, H is the adverb list for making sure adverb didn't repeat.
cadvs(L):- adverb(L).
cadvs(L):- cadvs_up(L, []).
cadvs_up([X1, and, X2], H):- adverb([X1]), adverb([X2]), X1 \= X2, \+member(X1, H),\+member(X2, H).
cadvs_up([X1, ','|L], H):- adverb([X1]), \+member(X1, H), cadvs_up(L, [X1|H]).

% c) verb_phrase_better(V): the point is to the position of append
verb_phrase_better(V):- verb(V).
verb_phrase_better(V):- verb(V1),noun_phrase_better(N), append(V1, N, V).
verb_phrase_better(V):- cadvs(L), verb(V1), append(L, V1, V).
verb_phrase_better(V):- noun_phrase_better(N), verb(V1), append(V1, N, L1), cadvs(L),append(L, L1, V).

% d)sentence_better
sentence_better(S):- noun_phrase_better(NP), verb_phrase_better(VP), append(NP, VP, S).
