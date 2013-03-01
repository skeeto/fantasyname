#!/usr/bin/perl

use warnings;
use strict;

use FantasyName;
use Getopt::Long qw(:config gnu_getopt);

# Options
my $pattern	   = "default";
my $template;
my $num_names	   = 1;
my $capitalize     = 1;
my $print_patterns = 0;
my $print_vers     = 0;
my $print_help	   = 0;
my $version	   = "1.0.0";

# Parse arguments
my $res = GetOptions(
    "t|template=s"   => \$template,
    "n|num-names=i"  => \$num_names,
    "l|lowercase!"   => \$capitalize,
    "s|show"         => \$print_patterns,
    "v|version"      => \$print_vers,
    "h|help"         => \$print_help,
    );

if ($print_vers) {
    print <<EOF;
namegen, version $version
Copyright (C) 2008 Christopher Wellons
This is free software; you can redistribute it and/or modify it under
the same terms as Perl itself.
EOF
    exit(0) if (!$print_help);
}

if ($print_help or !$res) {
    print <<EOF;
Usage $0 [options] [pattern-name]

  -n  --num-names  num     Set number of names to generate
  -t, --template   str     Manually specify a template
  -l, --lowercase          Do not capitalize names
  -s, --show               Print list of built-in patterns
  -v, --version            Print version information
  -h, --help               Print this help information
EOF
    exit(0);
}

# Patterns
my %patterns = (
    "default" => "<s|B|Bv|v><V|s|'|V><s|V|C>",
    "idiot"   => "<i|Cd>D<d|i>",
    "short"   => "<V|B><V|vs|Vs>",
    );
if ($print_patterns) {
    print "$_\t($patterns{$_})\n" for (keys %patterns);
    exit(0);
}

# Determine the template
if (!defined $template) {
    $pattern = shift if $#ARGV > -1;
    $template = $patterns{$pattern};
    die "$pattern is not defined." if !defined $template;
}

while ($num_names-- > 0) {
    my $name = generate($template);
    die "Invalid template: $template\n" if !defined $name;
    $name =~ s/(\w+)/\u\L$1/ if $capitalize;
    print "$name\n";
}
