#!/usr/bin/perl
# vim: et ai sw=4 ts=4 sts=4 :

use warnings;
use strict;

use CGI qw/:standard/;
use List::Util qw/min max/;
use File::Basename;
use FantasyName qw/generate parse/;

# Options
my $counts   = [1, 5, 10, 25];
my $default_count = 10;
my $timeout  = 1; # Seconds
my $git_repo = 'http://git.nullprogram.com/fantasyname.git';
my $git_url  = 'http://git.nullprogram.com/?p=fantasyname.git;a=summary';
my $log_lenmax = 1000;

# Print form
print header,
    start_html('Fantasy Name Generator'),
    h2('Fantasy Name Generator'),
    a({-href => "quick-reference.html"}, "Quick Reference"), p
    start_form(-method => 'GET', -action => (fileparse($0))[0]),
    "Pattern ", textfield(-name => 'pattern', -size => 60), p,
    "Count: ",
    popup_menu(-name    => 'count',
           -values  => $counts,
               -default => $default_count), p,
    submit('Generate'),
    end_form,
    hr;

# Generate names
if (param()) {
    my $pattern = param('pattern');
    my $count   = param('count') || $default_count;
    $count = min($count, max(@$counts));

    # Test the pattern
    if (my $ast = eval { parse($pattern) }) {
        my @list = map { generate($ast) } (1 .. $count);
        print ul(li(\@list));

        my $patterns_log;
        open $patterns_log, ">>patterns.log"
            and print $patterns_log $pattern, "\n";
    } else {
        print "Invalid pattern: ", escapeHTML($pattern), p;

        my $patterns_log;
        length($pattern) < $log_lenmax and
            open $patterns_log, ">>invalid.log" and
            print $patterns_log $pattern, "\n";
    }
}

print end_html;
