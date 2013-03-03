var NameGen = NameGen || {};

NameGen.symbols = {
    s: ['ach', 'ack', 'ad', 'age', 'ald', 'ale', 'an', 'ang', 'ar', 'ard',
        'as', 'ash', 'at', 'ath', 'augh', 'aw', 'ban', 'bel', 'bur', 'cer',
        'cha', 'che', 'dan', 'dar', 'del', 'den', 'dra', 'dyn', 'ech', 'eld',
        'elm', 'em', 'en', 'end', 'eng', 'enth', 'er', 'ess', 'est', 'et',
        'gar', 'gha', 'hat', 'hin', 'hon', 'ia', 'ight', 'ild', 'im', 'ina',
        'ine', 'ing', 'ir', 'is', 'iss', 'it', 'kal', 'kel', 'kim', 'kin',
        'ler', 'lor', 'lye', 'mor', 'mos', 'nal', 'ny', 'nys', 'old', 'om',
        'on', 'or', 'orm', 'os', 'ough', 'per', 'pol', 'qua', 'que', 'rad',
        'rak', 'ran', 'ray', 'ril', 'ris', 'rod', 'roth', 'ryn', 'sam',
        'say', 'ser', 'shy', 'skel', 'sul', 'tai', 'tan', 'tas', 'ther',
        'tia', 'tin', 'ton', 'tor', 'tur', 'um', 'und', 'unt', 'urn', 'usk',
        'ust', 'ver', 'ves', 'vor', 'war', 'wor', 'yer'],
    v: ['a', 'e', 'i', 'o', 'u', 'y'],
    V: ['a', 'e', 'i', 'o', 'u', 'y', 'ae', 'ai', 'au', 'ay', 'ea', 'ee',
        'ei', 'eu', 'ey', 'ia', 'ie', 'oe', 'oi', 'oo', 'ou', 'ui'],
    c: ['b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r',
        's', 't', 'v', 'w', 'x', 'y', 'z'],
    B: ['b', 'bl', 'br', 'c', 'ch', 'chr', 'cl', 'cr', 'd', 'dr', 'f', 'g',
        'h', 'j', 'k', 'l', 'll', 'm', 'n', 'p', 'ph', 'qu', 'r', 'rh', 's',
        'sch', 'sh', 'sl', 'sm', 'sn', 'st', 'str', 'sw', 't', 'th', 'thr',
        'tr', 'v', 'w', 'wh', 'y', 'z', 'zh'],
    C: ['b', 'c', 'ch', 'ck', 'd', 'f', 'g', 'gh', 'h', 'k', 'l', 'ld', 'll',
        'lt', 'm', 'n', 'nd', 'nn', 'nt', 'p', 'ph', 'q', 'r', 'rd', 'rr',
        'rt', 's', 'sh', 'ss', 'st', 't', 'th', 'v', 'w', 'y', 'z'],
    i: ['air', 'ankle', 'ball', 'beef', 'bone', 'bum', 'bumble', 'bump',
        'cheese', 'clod', 'clot', 'clown', 'corn', 'dip', 'dolt', 'doof',
        'dork', 'dumb', 'face', 'finger', 'foot', 'fumble', 'goof',
        'grumble', 'head', 'knock', 'knocker', 'knuckle', 'loaf', 'lump',
        'lunk', 'meat', 'muck', 'munch', 'nit', 'numb', 'pin', 'puff',
        'skull', 'snark', 'sneeze', 'thimble', 'twerp', 'twit', 'wad',
        'wimp', 'wipe'],
    m: ['baby', 'booble', 'bunker', 'cuddle', 'cuddly', 'cutie', 'doodle',
        'foofie', 'gooble', 'honey', 'kissie', 'lover', 'lovey', 'moofie',
        'mooglie', 'moopie', 'moopsie', 'nookum', 'poochie', 'poof',
        'poofie', 'pookie', 'schmoopie', 'schnoogle', 'schnookie',
        'schnookum', 'smooch', 'smoochie', 'smoosh', 'snoogle', 'snoogy',
        'snookie', 'snookum', 'snuggy', 'sweetie', 'woogle', 'woogy',
        'wookie', 'wookum', 'wuddle', 'wuddly', 'wuggy', 'wunny'],
    M: ['boo', 'bunch', 'bunny', 'cake', 'cakes', 'cute', 'darling',
        'dumpling', 'dumplings', 'face', 'foof', 'goo', 'head', 'kin',
        'kins', 'lips', 'love', 'mush', 'pie', 'poo', 'pooh', 'pook', 'pums'],
    D: ['b', 'bl', 'br', 'cl', 'd', 'f', 'fl', 'fr', 'g', 'gh', 'gl', 'gr',
        'h', 'j', 'k', 'kl', 'm', 'n', 'p', 'th', 'w'],
    d: ['elch', 'idiot', 'ob', 'og', 'ok', 'olph', 'olt', 'omph', 'ong',
        'onk', 'oo', 'oob', 'oof', 'oog', 'ook', 'ooz', 'org', 'ork', 'orm',
        'oron', 'ub', 'uck', 'ug', 'ulf', 'ult', 'um', 'umb', 'ump', 'umph',
        'un', 'unb', 'ung', 'unk', 'unph', 'unt', 'uzz']
};

/**
 * Selects a random generator from the given when generating.
 */
NameGen.Random = function(generators) {
    if (!(this instanceof NameGen.Random)) {
        switch (generators.length) {
        case 0:
            return '';
        case 1:
            return generators[0];
        default:
            return new NameGen.Random(generators);
        }
    }
    this.sub = generators;
    return this;
};

NameGen.Random.prototype.toString = function() {
    if (this.sub.length > 0) {
        var i = Math.floor(Math.random() * this.sub.length);
        return this.sub[i].toString();
    } else {
        return '';
    }
};

/**
 * Runs each provided generator in turn when generating.
 */
NameGen.Sequence = function(generators) {
    if (!(this instanceof NameGen.Sequence)) {
        switch (generators.length) {
        case 0:
            return '';
        case 1:
            return generators[0];
        default:
            return new NameGen.Sequence(generators);
        }
    }
    this.sub = generators;
    return this;
};

NameGen.Sequence.prototype.toString = function() {
    return this.sub.join('');
};

/**
 * List of symbol NameGen.generators.
 */
NameGen.generators = (function() {
    var generators = {};
    for (var symbol in NameGen.symbols) {
        generators[symbol] = NameGen.Random(NameGen.symbols[symbol]);
    }
    return generators;
}());

/**
 * Return the last element of the Array.
 */
Array.prototype.last = function() { return this[this.length - 1]; };

/**
 * Compile a generator specification string into a generator.
 */
NameGen.compile = function(input) {
    var SYMBOL = 0, LITERAL = 1;
    var stack = [];

    function push(mode) {
        stack.push({mode: mode, set: [[]]});
    }
    function pop() {
        return NameGen.Random(stack.pop().set.map(NameGen.Sequence));
    }

    push(SYMBOL);
    for (var i = 0; i < input.length; i++) {
        var c = input[i];
        switch (c) {
        case '<':
            push(SYMBOL);
            break;
        case '(':
            push(LITERAL);
            break;
        case '>':
        case ')':
            if (stack.length === 1) {
                throw new Error('Unbalanced brackets.');
            }
            var top = pop();
            stack.last().set.last().push(top);
            break;
        case '|':
            stack.last().set.push([]);
            break;
        default:
            if (stack.last().mode === LITERAL) {
                stack.last().set.last().push(c);
            } else {
                stack.last().set.last().push(NameGen.generators[c] || c);
            }
            break;
        }
    }
    if (stack.length !== 1) {
        throw new Error('Missing closing bracket.');
    }
    return pop();
};
