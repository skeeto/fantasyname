#!/usr/bin/perl

use warnings;
use strict;

use CGI qw/:standard/;
use List::Util qw/min max/;
use File::Basename;
use FantasyName;

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
    my $test = gen($pattern);

    if (!$test) {
	print "Invalid pattern: ", escapeHTML($pattern), p;
	my $patterns_log;
	length($pattern) < $log_lenmax and
	    open $patterns_log, ">>invalid.log" and
	    print $patterns_log $pattern, "\n";
    } elsif ($test eq -1) {
 	print
 	    "Generation timeout: please enter a simpler pattern.", p,
 	    "If you want to generate this pattern, you can run ",
 	    "it on your own machine. You can clone the name generator ",
	    "project with git,", p,
 	    "<pre>git clone ", a({-href => $git_url}, $git_repo), "</pre>";
	my $patterns_log;
	length($pattern) < $log_lenmax and
	    open $patterns_log, ">>timeout.log"
	    and print $patterns_log $pattern, "\n";
    } else {
	my @list;
	push @list, gen($pattern) for (1..$count);
	@list = grep {$_ ne -1} @list;
	print ul(li(\@list));

	my $patterns_log;
	open $patterns_log, ">>patterns.log"
	    and print $patterns_log $pattern, "\n";
    }
}

print end_html;

# Generates a single name, but is careful not to spend more than
# $timeout seconds doing it.
sub gen {
    my $name;
    my $pattern = shift;
    eval {
	local $SIG{ALRM} = sub { die "timeout\n" };
	alarm $timeout;
	$name = generate($pattern);
	alarm 0;
    };
    if ($@) {
	die unless $@ eq "timeout\n";
	return -1;
    }
    return $name;
}
