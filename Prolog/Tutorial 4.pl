%Question 1
article('the').
article('a').
article('an').

noun('boy').
noun('apple')..
noun('song').

verb('eats').
verb('sings').

sentence([H|T]):-
    [H1|T1] = T, noun_phrase([H,H1]), verb_phrase(T1).
noun_phrase([A,B]):-
    article(A), noun(B).
verb_phrase([T1]):-
    adverb(T1).
verb_phrase([H|T]):-
    adverb(H), [H1|T1] = T, noun_phrase(H1,T1).

%Question 2
