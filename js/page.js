var COLUMNS = 4,
    HEIGHT = 16;
var generator = null;

function clear() {
    $('#output').empty();
}

function fill() {
    var $output = $('#output'),
        $w = $(window),
        $b = $('body');
    while ($w.scrollTop() + $w.height() > $b.height() + HEIGHT) {
        for (var i = 0; i < COLUMNS; i++) {
            $output.append($('<li>' + generator + '</li>'));
        }
    }
}

function update(event) {
    if (event) event.preventDefault();
    clear();
    try {
        generator = NameGen.compile($('#spec').val());
        $('#spec').removeClass('invalid');
        fill();
    } catch (e) {
        $('#spec').addClass('invalid');
    }
}

$(document).ready(function() {
    $('#input').on('submit input', update);
    $(window).on('scroll', fill);
});
