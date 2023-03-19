# Fantasy Name Generator

Five implementations -- JavaScript, Typescript, C++, Elisp, and Perl -- of the
[name generator described at RinkWorks](http://rinkworks.com/namegen/).
The Typescript and C++ implementations are by far the most mature.


## JavaScript

The JavaScript version uses an optimizing template-compiler to create
an efficient generator object.

```javascript
var generator = NameGen.compile("sV'i");
generator.toString();  // => "entheu'loaf"
generator.toString();  // => "honi'munch"
```

## Typescript

The Typescript version is based on the C++ version.

```typescript
import NameGen from "./utils/namegen";
let generator = new NameGen.Generator("sV'i");
generator.toString();  // => "entheu'loaf"
generator.toString();  // => "honi'munch"
```

## C++

The C++ version also uses a template-compiler (based on the one for JavaScript)
to create an efficient generator object. It requires C++11.

```c++
NameGen::Generator generator("sV'i");
generator.toString();  // => "drai'sneeze"
generator.toString();  // => "ardou'bumble"
```

## C

The C version generates names directly from the template in a single pass:

```c
char name[64];
unsigned long seed = 0xb9584b61UL;
namegen(name, sizeof(name), "sV'i", &seed);
```

This is the fastest implementation.

## Emacs Lisp

The Emacs Lisp version doesn't include a parser. It operates on
s-expressions.

```el
(fset 'generator (apply-partially #'namegen '(s V "'" i)))
(generator)  ; => "essei'knocker"
(generator)  ; => "tiaoe'nit"
```

## Perl

The Perl version has both a parser and a generator. It's possible to parse an
expression once with `parse` and then use the parsed abstract syntax tree for
multiple generations with `generate`. In any case, `generate` also accepts a
string as input, in which case parsing will happen behind the scenes.


```perl
generate("sV'i");  # => "echoi'bum"

# for "bulk" operations there's no need to re-parse the expression each time
my $ast = FantasyName::parse("sV'i");
print generate($ast) for 1 .. 10000;
```

The parser is not fast due to a different implementation, so there should not be
timeout issues any more.
