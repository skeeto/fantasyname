var OUTPUT_COUNT = 120;

var generator = null;

function clear() {
    $('#output').empty();
}

function append(n) {
    var $output = $('#output');
    for (var i = 0; i < n; i++) {
        $output.append($('<li>' + generator + '</li>'));
    }
}

function update(event) {
    if (event) event.preventDefault();
    clear();
    try {
        generator = NameGen.compile($('#spec').val());
        $('#spec').removeClass('invalid');
        append(OUTPUT_COUNT);
    } catch (e) {
        $('#spec').addClass('invalid');
    }
}

$(document).ready(function() {
    $('#input').on('submit input', update);
});
