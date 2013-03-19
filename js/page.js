var generator = null;

function clear() {
    $('#output').empty();
}

function fill() {
    var $output = $('#output'),
        $w = $(window),
        $b = $('body');
    while (generator && $w.scrollTop() + $w.height() > $b.height()) {
        $output.append($('<li>' + generator + '</li>'));
    }
}

function group(n) {
    var string = n.toString();
    if (/^\d+$/.test(string)) {
        return string.split('').reverse().join('')
            .split(/(\d\d\d)/).filter(function(s) {
                return s !== '';
            }).map(function(s) {
                return s.split('').reverse().join('');
            }).reverse().join(',');
    } else {
        return string;
    }
}

function update(event) {
    if (event) event.preventDefault();
    clear();
    try {
        generator = NameGen.compile($('#spec').val());
        $('#spec').removeClass('invalid');
        if (generator.max() === 0) {
            generator = null;
            $('#count').text('');
        } else {
            var count = group(generator.combinations());
            if (count === 1) {
                $('#count').text(count + ' possibility');
            } else {
                $('#count').text(count + ' possibilities');
            }
        }
        fill();
    } catch (e) {
        $('#spec').addClass('invalid');
        $('#count').text('invalid');
    }
}

$(document).ready(function() {
    $('#input').on('submit input change', update);
    $(window).on('scroll', fill);
    $('#help').on('click', function(event) {
        event.preventDefault();
        $('#reference').slideToggle();
    });
});
