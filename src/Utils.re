type action = unit => unit;

type func('a, 'b) = 'a => 'b;
type bifunc('a, 'b, 'c) = 'a => 'b => 'c;

type predicate('a) = 'a => bool;
type bipredicate('a, 'b) = 'a => 'b => bool;

type consumer('a) = 'a => unit;
type biconsumer('a, 'b) = 'a => 'b => unit;

type factory('a) = unit => 'a;

type option('a) = 
  | Some('a)
  | None
;