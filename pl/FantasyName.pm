#!/usr/bin/perl

package FantasyName;

use warnings;
use strict;

use Parse::RecDescent;

BEGIN {
    use Exporter   ();
    our ($VERSION, @ISA, @EXPORT, @EXPORT_OK, %EXPORT_TAGS);

    $VERSION     = 1.00;
 
    @ISA         = qw(Exporter);
    @EXPORT      = qw(&generate);
    %EXPORT_TAGS = ( );     # eg: TAG => [ qw!name1 name2! ],

    @EXPORT_OK   = qw(%templates);
}
our @EXPORT_OK;

# Load data
our %templates = (
    "'" => ["'"],
    "-" => ["-"],
    "s" => [qw(ach ack ad age ald ale an ang ar ard as ash at ath augh
               aw ban bel bur cer cha che dan dar del den dra dyn ech
               eld elm em en end eng enth er ess est et gar gha hat
               hin hon ia ight ild im ina ine ing ir is iss it kal kel
               kim kin ler lor lye mor mos nal ny nys old om on or orm
               os ough per pol qua que rad rak ran ray ril ris rod
               roth ryn sam say ser shy skel sul tai tan tas ther tia
               tin ton tor tur um und unt urn usk ust ver ves vor war
               wor yer)],
    "v" => [qw(a e i o u y)],
    "V" => [qw(a e i o u y ae ai au ay ea ee ei eu ey ia ie oe oi oo
               ou ui)],
    "c" => [qw(b c d f g h j k l m n p q r s t v w x y z)],
    "B" => [qw(b bl br c ch chr cl cr d dr f g h j k l ll m n p ph qu
               r rh s sch sh sl sm sn st str sw t th thr tr v w wh y z
               zh)],
    "C" => [qw(b c ch ck d f g gh h k l ld ll lt m n nd nn nt p ph q r
               rd rr rt s sh ss st t th v w y z )],
    "i" => [qw(air ankle ball beef bone bum bumble bump cheese clod
               clot clown corn dip dolt doof dork dumb face finger
               foot fumble goof grumble head knock knocker knuckle
               loaf lump lunk meat muck munch nit numb pin puff skull
               snark sneeze thimble twerp twit wad wimp wipe)],
    "m" => [qw(baby booble bunker cuddle cuddly cutie doodle foofie
               gooble honey kissie lover lovey moofie mooglie moopie
               moopsie nookum poochie poof poofie pookie schmoopie
               schnoogle schnookie schnookum smooch smoochie smoosh
               snoogle snoogy snookie snookum snuggy sweetie woogle
               woogy wookie wookum wuddle wuddly wuggy wunny)],
    "M" => [qw(boo bunch bunny cake cakes cute darling dumpling
               dumplings face foof goo head kin kins lips love mush
               pie poo pooh pook pums)],
    "D" => [qw(b bl br cl d f fl fr g gh gl gr h j k kl m n p th w)],
    "d" => [qw(elch idiot ob og ok olph olt omph ong onk oo oob oof
               oog ook ooz org ork orm oron ub uck ug ulf ult um umb
               ump umph un unb ung unk unph unt uzz)],
);

# Template grammar
my $parser = Parse::RecDescent->new(q(

lgroup : /[^|()<>]+/

tgroup : /[-svVcBCimMDd']/ 
         { FantasyName::randsel($FantasyName::templates{$item[1]}) }

lset : lgroup | template

tset : tgroup | template

lexp : lset lexp { $item[1] . $item[2] } | lset

texp : tset texp { $item[1] . $item[2] } | tset

llist : lexp "|" llist { push(@{$item[3]}, $item[1]); $item[3] } | 
        lexp "|" { [$item[1], ""] } |
        lexp { [$item[1]] }

tlist : texp "|" tlist { push(@{$item[3]}, $item[1]); $item[3] } | 
        texp "|" { [$item[1], ""] } |
        texp { [$item[1]] }

template : "<" tlist ">" { FantasyName::randsel($item[2]) } |
           "(" llist ")" { FantasyName::randsel($item[2]) }

name : tlist { FantasyName::randsel($item[1]) } |
            template { $item[1] }

)) or die "Uh... something bad happened to the grammar.";

# Randomly select element from given array
sub randsel {
    my @sel = @{shift()};
    my $index = rand @sel;
    return $sel[$index];
}

# Generate a name given the template
sub generate {
    return $parser->name(shift);
}

1;
