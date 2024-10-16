person('Bhaskar').
person('Shila').
person('Ram').
person('Sakshi').

male('Bhaskar').
male('Ram').
female('Shila').
female('Sakshi').

parent('Bhaskar', 'Ram').
parent('Shila', 'Ram').
parent('Bhaskar', 'Sakshi').
parent('Shila', 'Sakshi').

father(X, Y) :- male(X), parent(X, Y).
mother(X, Y) :- female(X), parent(X, Y).
sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.
son(X, Y) :- male(X), parent(Y, X).
daughter(X, Y) :- female(X), parent(Y, X).