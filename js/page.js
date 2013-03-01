var OUTPUT_COUNT = 120;

$(document).ready(function() {
    $('#input').on('submit input', function(event) {
        event.preventDefault();
        var $output = $('#output').empty();
        try {
            var generator = compile($('#spec').val());
            for (var i = 0; i < OUTPUT_COUNT; i++) {
                $output.append($('<li>' + generator + '</li>'));
            }
            $('#spec').removeClass('invalid');
        } catch (e) {
            $('#spec').addClass('invalid');
        }
    });
});
