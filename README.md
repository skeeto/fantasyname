# Fantasy Name Generator

Three implementations -- JavaScript, Elisp, and Perl -- of the
[name generator described at RinkWorks](http://rinkworks.com/namegen/).
The JavaScript implementation is by far the most mature.

## JavaScript

The JavaScript version uses an optimizing template-compiler to create
an efficient generator object.

```javascript
var generator = NameGen.compile("sV'i");
generator.toString();  // => "entheu'loaf"
generator.toString();  // => "honi'munch"
```

## Emacs Lisp

The Emacs Lisp version doesn't include a parser. It operates on
s-expressions.

```el
(fset 'generator (apply-partially #'namegen '(s V "'" i)))
(generator)  ; => "essei'knocker"
(generator)  ; => "tiaoe'nit"
```

## Perl

The Perl version is exceptionally slow, due to a slow parser.

```perl
generate("sV'i");  # => "echoi'bum"
```
