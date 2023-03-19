#!/usr/bin/perl
# vim: et ai ts=4 sts=4 sw=4 :

package FantasyName;

use warnings;
use strict;

BEGIN {
    use Exporter   ();
    our ($VERSION, @ISA, @EXPORT, @EXPORT_OK, %EXPORT_TAGS);

    $VERSION     = 1.00;

    @ISA         = qw(Exporter);
    @EXPORT      = qw(&generate);
    %EXPORT_TAGS = ( );     # eg: TAG => [ qw!name1 name2! ],

    @EXPORT_OK   = qw(&parse %templates);
}

our %templates = (

    # These are the original patters in namegen.pl
    "default" => "<s|B|Bv|v><V|s|'|V><s|V|C>",
    "idiot"   => "<i|Cd>D<d|i>",
    "short"   => "<V|B><V|vs|Vs>",

    # The following patterns are from Rinkworks
    # Middle Earth
    MIDDLE_EARTH =>
q{(bil|bal|ban|hil|ham|hal|hol|hob|wil|me|or|ol|od|gor|for|fos|tol|ar|fin|ere|leo|vi|bi|bren|thor)(|go|orbis|apol|adur|mos|ri|i|na|ole|n)(|tur|axia|and|bo|gil|bin|bras|las|mac|grim|wise|l|lo|fo|co|ra|via|da|ne|ta|y|wen|thiel|phin|dir|dor|tor|rod|on|rdo|dis)},

    # Japanese Names (Constrained)
    JAPANESE_NAMES_CONSTRAINED =>
q{(aka|aki|bashi|gawa|kawa|furu|fuku|fuji|hana|hara|haru|hashi|hira|hon|hoshi|ichi|iwa|kami|kawa|ki|kita|kuchi|kuro|marui|matsu|miya|mori|moto|mura|nabe|naka|nishi|no|da|ta|o|oo|oka|saka|saki|sawa|shita|shima|i|suzu|taka|take|to|toku|toyo|ue|wa|wara|wata|yama|yoshi|kei|ko|zawa|zen|sen|ao|gin|kin|ken|shiro|zaki|yuki|asa)(||||||||||bashi|gawa|kawa|furu|fuku|fuji|hana|hara|haru|hashi|hira|hon|hoshi|chi|wa|ka|kami|kawa|ki|kita|kuchi|kuro|marui|matsu|miya|mori|moto|mura|nabe|naka|nishi|no|da|ta|o|oo|oka|saka|saki|sawa|shita|shima|suzu|taka|take|to|toku|toyo|ue|wa|wara|wata|yama|yoshi|kei|ko|zawa|zen|sen|ao|gin|kin|ken|shiro|zaki|yuki|sa)},

    # Japanese Names (Diverse)
    JAPANESE_NAMES_DIVERSE =>
q{(a|i|u|e|o|||||)(ka|ki|ki|ku|ku|ke|ke|ko|ko|sa|sa|sa|shi|shi|shi|su|su|se|so|ta|ta|chi|chi|tsu|te|to|na|ni|ni|nu|nu|ne|no|no|ha|hi|fu|fu|he|ho|ma|ma|ma|mi|mi|mi|mu|mu|mu|mu|me|mo|mo|mo|ya|yu|yu|yu|yo|ra|ra|ra|ri|ru|ru|ru|re|ro|ro|ro|wa|wa|wa|wa|wo|wo)(ka|ki|ki|ku|ku|ke|ke|ko|ko|sa|sa|sa|shi|shi|shi|su|su|se|so|ta|ta|chi|chi|tsu|te|to|na|ni|ni|nu|nu|ne|no|no|ha|hi|fu|fu|he|ho|ma|ma|ma|mi|mi|mi|mu|mu|mu|mu|me|mo|mo|mo|ya|yu|yu|yu|yo|ra|ra|ra|ri|ru|ru|ru|re|ro|ro|ro|wa|wa|wa|wa|wo|wo)(|(ka|ki|ki|ku|ku|ke|ke|ko|ko|sa|sa|sa|shi|shi|shi|su|su|se|so|ta|ta|chi|chi|tsu|te|to|na|ni|ni|nu|nu|ne|no|no|ha|hi|fu|fu|he|ho|ma|ma|ma|mi|mi|mi|mu|mu|mu|mu|me|mo|mo|mo|ya|yu|yu|yu|yo|ra|ra|ra|ri|ru|ru|ru|re|ro|ro|ro|wa|wa|wa|wa|wo|wo)|(ka|ki|ki|ku|ku|ke|ke|ko|ko|sa|sa|sa|shi|shi|shi|su|su|se|so|ta|ta|chi|chi|tsu|te|to|na|ni|ni|nu|nu|ne|no|no|ha|hi|fu|fu|he|ho|ma|ma|ma|mi|mi|mi|mu|mu|mu|mu|me|mo|mo|mo|ya|yu|yu|yu|yo|ra|ra|ra|ri|ru|ru|ru|re|ro|ro|ro|wa|wa|wa|wa|wo|wo)(|(ka|ki|ki|ku|ku|ke|ke|ko|ko|sa|sa|sa|shi|shi|shi|su|su|se|so|ta|ta|chi|chi|tsu|te|to|na|ni|ni|nu|nu|ne|no|no|ha|hi|fu|fu|he|ho|ma|ma|ma|mi|mi|mi|mu|mu|mu|mu|me|mo|mo|mo|ya|yu|yu|yu|yo|ra|ra|ra|ri|ru|ru|ru|re|ro|ro|ro|wa|wa|wa|wa|wo|wo)))(|||n)},

    # Chinese Names
    CHINESE_NAMES =>
q{(zh|x|q|sh|h)(ao|ian|uo|ou|ia)(|(l|w|c|p|b|m)(ao|ian|uo|ou|ia)(|n)|-(l|w|c|p|b|m)(ao|ian|uo|ou|ia)(|(d|j|q|l)(a|ai|iu|ao|i)))},

    # Greek Names
    GREEK_NAMES => q{<s<v|V>(tia)|s<v|V>(os)|B<v|V>c(ios)|B<v|V><c|C>v(ios|os)>},

    # Hawaiian Names (1)
    HAWAIIAN_NAMES_1 =>
q{((h|k|l|m|n|p|w|')|)(a|e|i|o|u)((h|k|l|m|n|p|w|')|)(a|e|i|o|u)(((h|k|l|m|n|p|w|')|)(a|e|i|o|u)|)(((h|k|l|m|n|p|w|')|)(a|e|i|o|u)|)(((h|k|l|m|n|p|w|')|)(a|e|i|o|u)|)(((h|k|l|m|n|p|w|')|)(a|e|i|o|u)|)},

    # Hawaiian Names (2)
    HAWAIIAN_NAMES_2 =>
q{((h|k|l|m|n|p|w|)(a|e|i|o|u|a'|e'|i'|o'|u'|ae|ai|ao|au|oi|ou|eu|ei)(k|l|m|n|p|)|)(h|k|l|m|n|p|w|)(a|e|i|o|u|a'|e'|i'|o'|u'|ae|ai|ao|au|oi|ou|eu|ei)(k|l|m|n|p|)},

    # Old Latin Place Names
    OLD_LATIN_PLACE_NAMES => q{sv(nia|lia|cia|sia)},

    # Dragons (Pern)
    DRAGONS_PERN => q{<<s|ss>|<VC|vC|B|BVs|Vs>><v|V|v|<v(l|n|r)|vc>>(th)},

    # Dragon Riders
    DRAGON_RIDERS => q{c'<s|cvc>},

    # Pokemon
    POKEMON => q{<i|s>v(mon|chu|zard|rtle)},

    # Fantasy (Vowels, R, etc.)
    FANTASY_VOWELS_R =>
q{(|(<B>|s|h|ty|ph|r))(i|ae|ya|ae|eu|ia|i|eo|ai|a)(lo|la|sri|da|dai|the|sty|lae|due|li|lly|ri|na|ral|sur|rith)(|(su|nu|sti|llo|ria|))(|(n|ra|p|m|lis|cal|deu|dil|suir|phos|ru|dru|rin|raap|rgue))},

    # Fantasy (S, A, etc.)
    FANTASY_S_A =>
q{(cham|chan|jisk|lis|frich|isk|lass|mind|sond|sund|ass|chad|lirt|und|mar|lis|il|<BVC>)(jask|ast|ista|adar|irra|im|ossa|assa|osia|ilsa|<vCv>)(|(an|ya|la|sta|sda|sya|st|nya))},

    # Fantasy (H, L, etc.)
    FANTASY_H_L =>
q{(ch|ch't|sh|cal|val|ell|har|shar|shal|rel|laen|ral|jh't|alr|ch|ch't|av)(|(is|al|ow|ish|ul|el|ar|iel))(aren|aeish|aith|even|adur|ulash|alith|atar|aia|erin|aera|ael|ira|iel|ahur|ishul)},

    # Fantasy (N, L, etc.)
    FANTASY_N_L =>
q{(ethr|qil|mal|er|eal|far|fil|fir|ing|ind|il|lam|quel|quar|quan|qar|pal|mal|yar|um|ard|enn|ey)(|(<vc>|on|us|un|ar|as|en|ir|ur|at|ol|al|an))(uard|wen|arn|on|il|ie|on|iel|rion|rian|an|ista|rion|rian|cil|mol|yon)},

    # Fantasy (K, N, etc.)
    FANTASY_K_N =>
q{(taith|kach|chak|kank|kjar|rak|kan|kaj|tach|rskal|kjol|jok|jor|jad|kot|kon|knir|kror|kol|tul|rhaok|rhak|krol|jan|kag|ryr)(<vc>|in|or|an|ar|och|un|mar|yk|ja|arn|ir|ros|ror)(|(mund|ard|arn|karr|chim|kos|rir|arl|kni|var|an|in|ir|a|i|as))},

    # Fantasy (J, G, Z, etc.)
    FANTASY_J_G_Z =>
q{(aj|ch|etz|etzl|tz|kal|gahn|kab|aj|izl|ts|jaj|lan|kach|chaj|qaq|jol|ix|az|biq|nam)(|(<vc>|aw|al|yes|il|ay|en|tom||oj|im|ol|aj|an|as))(aj|am|al|aqa|ende|elja|ich|ak|ix|in|ak|al|il|ek|ij|os|al|im)},

    # Fantasy (K, J, Y, etc.)
    FANTASY_K_J_Y =>
q{(yi|shu|a|be|na|chi|cha|cho|ksa|yi|shu)(th|dd|jj|sh|rr|mk|n|rk|y|jj|th)(us|ash|eni|akra|nai|ral|ect|are|el|urru|aja|al|uz|ict|arja|ichi|ural|iru|aki|esh)},

    # Fantasy (S, E, etc.)
    FANTASY_S_E =>
q{(syth|sith|srr|sen|yth|ssen|then|fen|ssth|kel|syn|est|bess|inth|nen|tin|cor|sv|iss|ith|sen|slar|ssil|sthen|svis|s|ss|s|ss)(|(tys|eus|yn|of|es|en|ath|elth|al|ell|ka|ith|yrrl|is|isl|yr|ast|iy))(us|yn|en|ens|ra|rg|le|en|ith|ast|zon|in|yn|ys)},
);

# Generate a name given the template expression
sub generate {
    my $expression = shift;
    my $ast = ref($expression) ? $expression : parse($expression);

    # Allow the same letter to appear at most two times in a row
    (my $name = nayme_generate_r($ast)) =~ s{(.)\1+}{$1$1}gmxs;

    return $name;
}

{
    my $parser;
    sub parse {
        my $expression = shift;
        $parser ||= nayme_parser();
        return $parser->($expression)->[0];
    }
}


{ # recursive visit of the Abstract Syntax Tree to generate a name
    my %alternatives_for;  # "state" variable surrogate

    sub nayme_generate_r {
        my $ast = shift;

        # ensure the "state" variable is initialized
        init_alternatives_for() unless scalar keys %alternatives_for;

        return $ast unless ref $ast;
        return join '', map { nayme_generate_r($_) } @$ast
            if ref($ast) eq 'ARRAY';
        die "unexpected ast<$ast>" unless ref($ast) eq 'HASH';

        my ($operation, $operand) = $ast->%*;
        my $aref =
            $operation eq 'alternatives' ? $operand
            : $operation eq 'template'     ? $alternatives_for{$operand}
            :                                die "unexpected ast<$ast>";
        return nayme_generate_r($aref->[rand @$aref]);
    } ## end sub nayme_generate_r ($ast)

    sub init_alternatives_for {
        %alternatives_for = (
            q{'} => [q{'}],
            '-'  => ["-"],
            s    => [
                qw<
                ach ack ad age ald ale an ang ar ard as ash at ath augh aw
                ban bel bur cer cha che dan dar del den dra dyn ech eld elm
                em en end eng enth er ess est et gar gha hat hin hon ia ight
                ild im ina ine ing ir is iss it kal kel kim kin ler lor lye
                mor mos nal ny nys old om on or orm os ough per pol qua que
                rad rak ran ray ril ris rod roth ryn sam say ser shy skel sul
                tai tan tas ther tia tin ton tor tur um und unt urn usk ust
                ver ves vor war wor yer
                >
            ],
            v => [qw< a e i o u y >],
            V => [
                qw< a e i o u y ae ai au ay ea ee ei eu ey ia ie oe oi oo ou ui >
            ],
            c => [qw< b c d f g h j k l m n p q r s t v w x y z >],
            B => [
                qw<
                b bl br c ch chr cl cr d dr f g h j k l ll m n p ph qu r rh s
                sch sh sl sm sn st str sw t th thr tr v w wh y z zh
                >
            ],
            C => [
                qw<
                b c ch ck d f g gh h k l ld ll lt m n nd nn nt p ph q r rd rr
                rt s sh ss st t th v w y z
                >
            ],
            i => [
                qw<
                air ankle ball beef bone bum bumble bump cheese clod clot
                clown corn dip dolt doof dork dumb face finger foot fumble
                goof grumble head knock knocker knuckle loaf lump lunk meat
                muck munch nit numb pin puff skull snark sneeze thimble twerp
                twit wad wimp wipe
                >
            ],
            m => [
                qw<
                baby booble bunker cuddle cuddly cutie doodle foofie gooble
                honey kissie lover lovey moofie mooglie moopie moopsie nookum
                poochie poof poofie pookie schmoopie schnoogle schnookie
                schnookum smooch smoochie smoosh snoogle snoogy snookie
                snookum snuggy sweetie woogle woogy wookie wookum wuddle
                wuddly wuggy wunny
                >
            ],
            M => [
                qw<
                boo bunch bunny cake cakes cute darling dumpling dumplings
                face foof goo head kin kins lips love mush pie poo pooh pook
                pums
                >
            ],
            D => [qw< b bl br cl d f fl fr g gh gl gr h j k kl m n p th w >],
            d => [
                qw<
                elch idiot ob og ok olph olt omph ong onk oo oob oof oog ook
                ooz org ork orm oron ub uck ug ulf ult um umb ump umph un unb
                ung unk unph unt uzz
                >
            ],
        );
    }
}

=begin grammar

LITERAL  ::= /[^|()<>]+/
TEMPLATE ::= /[-svVcBCimMDd']+/

literal_set  ::= LITERAL  | group
literal_exp  ::= literal_set*
literal_list  ::= literal_exp  ("|" literal_exp)*

template_set ::= TEMPLATE | group
template_exp ::= template_set*
template_list ::= template_exp ("|" template_exp)*

group ::= "<" template_list ">" | "(" literal_list ")"

name ::= template_list | group

=end grammar

=cut

sub nayme_parser {
    my $realgroup;
    my $group = sub { goto $realgroup };
    my $literal = pf_match_and_filter(
        pf_regexp(qr{([^|()<>]+)}),
        sub { return shift->[0] },
    );
    my $literal_set = pf_alternatives($literal, $group);
    my $literal_exp =
        pf_match_and_filter(pf_repeated($literal_set, 0, -1), \&flatten_exp,);
    my $literal_list = pf_match_and_filter(pf_list($literal_exp, '|'),
        \&flatten_literal_list);
    my $literal_group = pf_match_and_filter(
        pf_sequence('(', $literal_list, ')'),
        sub { shift->[1] },
    );

    my $template = pf_match_and_filter(
        pf_regexp(qr{([-BcCdDimMsvV'])}),
        sub { return {template => shift->[0]} },
    );
    my $template_set = pf_alternatives($template, $group);
    my $template_exp = pf_match_and_filter(pf_repeated($template_set, 0, -1),
        \&flatten_exp);
    my $template_list = pf_list($template_exp, '|');
    my $template_group = pf_match_and_filter(
        pf_sequence('<', $template_list, '>'),
        sub { return shift->[1] },
    );

    $realgroup = pf_match_and_filter(
        pf_alternatives($template_group, $literal_group),
        sub {
            my $match = shift;
            return @$match > 1 ? {alternatives => $match} : $match->[0];
        },
    );
    my $name = pf_alternatives($template_list, $realgroup);
    return pf_PARSE($name);
} ## end sub nayme_parse ($expression)

sub flatten_literal_list {
    my $match = shift;
    my @retval = map {
        if (ref $_ eq 'ARRAY') {
            my @portion;
            for my $item (@$_) {
                if (ref($item) || (@portion == 0) || ref($portion[-1])) {
                    push @portion, $item;
                }
                else { # note: @portion > 0 for sure if we get here
                    $portion[-1] .= $item;
                }
            } ## end for my $item (@$_)
            @portion > 1 ? \@portion : $portion[0];
        } ## end if (ref $_ eq 'ARRAY')
        else {
            $_;
        }
    } @$match;
    return @retval ? \@retval : '';
} ## end sub flatten_literal_list ($match)

sub flatten_exp {
    my $match = shift;
    my @retval = map { ref $_ eq 'ARRAY' ? @$_ : $_ } @$match;
    return @retval ? \@retval : '';
}

# Copy (with adaptation) from
# https://github.com/polettix/cglib-perl/blob/9540fccc404b058660f34b933e84e067a6eb6d65/Parsing.pm

sub pf_alternatives {
   my (@A, $r) = @_;
   return sub { (defined($r = $_->($_[0])) && return $r) for @A; return };
}

sub pf_exact {
   my ($wlen, $what, @retval) = (length($_[0]), @_);
   unshift @retval, $what unless scalar @retval;
   return sub {
      my ($rtext, $pos) = ($_[0], pos(${$_[0]}) || 0);
      return if length($$rtext) - $pos < $wlen;
      return if substr($$rtext, $pos, $wlen) ne $what;
      pos($$rtext) = $pos + $wlen;
      return [@retval];
   };
} ## end sub pf_exact

sub pf_list {
   my ($w, $s, $sep_as_last) = @_;    # (what, separator, sep_as_last)
   $s = pf_exact($s) if defined($s) && !ref($s);
   return sub {
      defined(my $base = $w->($_[0])) or return;
      my $rp = sub { return ($s && !($s->($_[0])) ? () : $w->($_[0])) };
      my $rest = pf_repeated($rp)->($_[0]);
      $s->($_[0]) if $s && $sep_as_last;    # attempt last separator?
      unshift @$rest, $base;
      return $rest;
   };
} ## end sub pf_list

sub pf_match_and_filter {
   my ($matcher, $filter) = @_;
   return sub {
      my $match = $matcher->($_[0]) or return;
      return $filter->($match);
   };
} ## end sub pf_match_and_filter

sub pf_PARSE {
   my ($expression) = @_;
   return sub {
      my $rtext = ref $_[0] ? $_[0] : \$_[0];    # avoid copying
      my $ast = $expression->($rtext) or die "nothing parsed\n";
      my $pos = pos($$rtext) || 0;
      my $delta = length($$rtext) - $pos;
      return $ast if $delta == 0;
      my $offending = substr $$rtext, $pos, 72;
      substr $offending, -3, 3, '...' if $delta > 72;
      die "unknown sequence starting at $pos <$offending>\n";
   };
} ## end sub pf_PARSE

sub pf_regexp {
   my ($rx, @forced_retval) = @_;
   return sub {
      scalar(${$_[0]} =~ m{\G()$rx}cgmxs) or return;
      return scalar(@forced_retval) ? [@forced_retval] : [$2];
   };
} ## end sub pf_regexp

sub pf_repeated {    # *(0,-1) ?(0,1) +(1,-1) {n,m}(n,m)
   my ($w, $m, $M) = ($_[0], $_[1] || 0, (defined($_[2]) ? $_[2] : -1));
   return sub {
      my ($rtext, $pos, $lm, $lM, @retval) = ($_[0], pos ${$_[0]}, $m, $M);
      while ($lM != 0) {    # lm = local minimum, lM = local maximum
         defined(my $piece = $w->($rtext)) or last;
         $lM--;
         push @retval, $piece;
         if   ($lm > 0) { --$lm }                 # no success yet
         else           { $pos = pos $$rtext }    # ok, advance
      } ## end while ($lM != 0)
      pos($$rtext) = $pos if $lM != 0;    # maybe "undo" last attempt
      return if $lm > 0;                  # failed to match at least $min
      return \@retval;
   };
} ## end sub pf_repeated

sub pf_sequence {
   my @items = map { ref $_ ? $_ : pf_exact($_) } @_;
   return sub {
      my ($rtext, $pos, @rval) = ($_[0], pos ${$_[0]});
      for my $item (@items) {
         if (defined(my $piece = $item->($rtext))) { push @rval, $piece }
         else { pos($$rtext) = $pos; return }    # failure, revert back
      }
      return \@rval;
   };
} ## end sub pf_sequence

{
    my $r;
    sub pf_ws  { $r ||= pf_regexp(qr{(\s+)}) }
}

{
    my $r;
    sub pf_wso { $r ||= pf_regexp(qr{(\s*)}) }
}

1;
