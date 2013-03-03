var COLUMNS = 4;
var generator = null;

function clear() {
    $('#output').empty();
}

function fill() {
    var $output = $('#output'),
        $w = $(window),
        $b = $('body');
    while (generator && $w.scrollTop() + $w.height() > $b.height()) {
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
        if ($('#reverse').prop('checked')) {
            generator = NameGen.Reverser(generator);
        }
        if ($('#capitalize').prop('checked')) {
            generator = NameGen.Capitalizer(generator);
        }
        if (generator === '') generator = null;
        $('#spec').removeClass('invalid');
        fill();
    } catch (e) {
        $('#spec').addClass('invalid');
    }
}

$(document).ready(function() {
    $('#input').on('submit input change', update);
    $(window).on('scroll', fill);
});
