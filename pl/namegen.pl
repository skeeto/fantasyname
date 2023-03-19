#!/usr/bin/perl
# vim: et ai ts=4 sts=4 sw=4 :

use warnings;
use strict;

use FantasyName qw< generate parse %templates >;
use Getopt::Long qw(:config gnu_getopt);

# Options
my $pattern	   = "default";
my $template;
my $num_names	   = 1;
my $capitalize     = 1;
my $print_names    = 0;
my $print_patterns = 0;
my $print_vers     = 0;
my $print_help	   = 0;
my $version	   = "1.1.0";

# Parse arguments
my $res = GetOptions(
    "t|template=s"   => \$template,
    "n|num-names=i"  => \$num_names,
    "l|lowercase!"   => \$capitalize,
    "L|list"         => \$print_names,
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
  -L, --list               Print list of names of built-in patterns
  -s, --show               Print list of built-in patterns
  -v, --version            Print version information
  -h, --help               Print this help information
EOF
    exit(0);
}

# Patterns
if ($print_names) {
    print "$_\n" for sort { $a cmp $b } (keys %templates);
    exit(0);
}
if ($print_patterns) {
    print "$_\t($templates{$_})\n" for sort { $a cmp $b } (keys %templates);
    exit(0);
}

# Determine the template
if (!defined $template) {
    $pattern = shift if $#ARGV > -1;
    $template = $templates{$pattern};
    die "$pattern is not defined." if !defined $template;
}

my $ast = parse($template);
while ($num_names-- > 0) {
    my $name = generate($ast); # might also be generate($template)
    die "Invalid template: $template\n" if !defined $name;
    $name =~ s/(\w+)/\u\L$1/ if $capitalize;
    print "$name\n";
}


