parents('jeanne', 'marc', 'bob').
parents('jeanne', 'marc', 'jean').
parents('jeanne', 'marc', 'eleonore').

parents('jeanne', 'julien', 'martine').
parents('jeanne', 'julien', 'patrick').

parents('sophie', 'julien', 'bastien').

half_siblings(Child, Siblings):- findall(Sibling, (parents(X, _, Child),parents(X, _, Sibling);parents(_, Y, Child),parents(_, Y, Sibling)), Siblings).
%half_siblings(Child, Siblings):- findall(Sibling, (parents(_, Y, Child),parents(_, Y, Sibling)), Siblings).

