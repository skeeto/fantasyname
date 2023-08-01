package namegen;

import java.util.*;

/**
 *
 * @file A fantasy name generator library.
 * @version 1.0.1
 * @license Public Domain
 * @author Edgar Alvarado (pe1uca)
 *
 * This library is designed after the RinkWorks Fantasy Name Generator.
 * @see https://www.rinkworks.com/namegen/
 *
 * @example
 * NameGen generator = new NameGen("sV'i");
 * generator.toString();  // Returns a new name each call with toString()
 * // => "entheu'loaf"
 *
 * ## Pattern Syntax
 *
 *   The ToString() function creates a name generator based on an input
 * pattern. The letters s, v, V, c, B, C, i, m, M, D, and d represent
 * different types of random replacements. Everything else is produced
 * literally.
 *
 *   s - generic syllable
 *   v - vowel
 *   V - vowel or vowel combination
 *   c - consonant
 *   B - consonant or consonant combination suitable for beginning a word
 *   C - consonant or consonant combination suitable anywhere in a word
 *   i - insult
 *   m - mushy name
 *   M - mushy name ending
 *   D - consonant suited for a stupid person's name
 *   d - syllable suited for a stupid person's name (begins with a vowel)
 *
 *   All characters between parenthesis () are produced literally. For
 * example, the pattern "S(dim)", produces a random generic syllable
 * followed by "dim".
 *
 *   Characters between angle brackets <> produce patterns from the table
 * above. Imagine the entire pattern is wrapped in one of these.
 *
 *   In both types of groupings, a vertical bar | denotes a random
 * choice. Empty groups are allowed. For example, "(foo|bar)" produces
 * either "foo" or "bar". The pattern "<c|v|>" produces a constant,
 * vowel, or nothing at all.
 *
 *   An exclamation point ! means to capitalize the component that
 * follows it. For example, "!(foo)" will produce "Foo" and "v!s" will
 * produce a lowercase vowel followed by a capitalized syllable, like
 * "eRod".
 *
 *   A tilde ~ means to reverse the letters of the component that
 * follows it. For example, "~(foo)" will produce "oof". To reverse an
 * entire template, wrap it in brackets. For example, to reverse
 * "sV'i" as a whole use "~<sV'i>". The template "~sV'i" will only
 * reverse the initial syllable.
 */

public class NameGen
{
    // Middle Earth
    public static String MIDDLE_EARTH = "(bil|bal|ban|hil|ham|hal|hol|hob|wil|me|or|ol|od|gor|for|fos|tol|ar|fin|ere|leo|vi|bi|bren|thor)(|go|orbis|apol|adur|mos|ri|i|na|ole|n)(|tur|axia|and|bo|gil|bin|bras|las|mac|grim|wise|l|lo|fo|co|ra|via|da|ne|ta|y|wen|thiel|phin|dir|dor|tor|rod|on|rdo|dis)";

    // Japanese Names (Constrained)
    public static String JAPANESE_NAMES_CONSTRAINED = "(aka|aki|bashi|gawa|kawa|furu|fuku|fuji|hana|hara|haru|hashi|hira|hon|hoshi|ichi|iwa|kami|kawa|ki|kita|kuchi|kuro|marui|matsu|miya|mori|moto|mura|nabe|naka|nishi|no|da|ta|o|oo|oka|saka|saki|sawa|shita|shima|i|suzu|taka|take|to|toku|toyo|ue|wa|wara|wata|yama|yoshi|kei|ko|zawa|zen|sen|ao|gin|kin|ken|shiro|zaki|yuki|asa)(||||||||||bashi|gawa|kawa|furu|fuku|fuji|hana|hara|haru|hashi|hira|hon|hoshi|chi|wa|ka|kami|kawa|ki|kita|kuchi|kuro|marui|matsu|miya|mori|moto|mura|nabe|naka|nishi|no|da|ta|o|oo|oka|saka|saki|sawa|shita|shima|suzu|taka|take|to|toku|toyo|ue|wa|wara|wata|yama|yoshi|kei|ko|zawa|zen|sen|ao|gin|kin|ken|shiro|zaki|yuki|sa)";

    // Japanese Names (Diverse)
    public static String JAPANESE_NAMES_DIVERSE = "(a|i|u|e|o|||||)(ka|ki|ki|ku|ku|ke|ke|ko|ko|sa|sa|sa|shi|shi|shi|su|su|se|so|ta|ta|chi|chi|tsu|te|to|na|ni|ni|nu|nu|ne|no|no|ha|hi|fu|fu|he|ho|ma|ma|ma|mi|mi|mi|mu|mu|mu|mu|me|mo|mo|mo|ya|yu|yu|yu|yo|ra|ra|ra|ri|ru|ru|ru|re|ro|ro|ro|wa|wa|wa|wa|wo|wo)(ka|ki|ki|ku|ku|ke|ke|ko|ko|sa|sa|sa|shi|shi|shi|su|su|se|so|ta|ta|chi|chi|tsu|te|to|na|ni|ni|nu|nu|ne|no|no|ha|hi|fu|fu|he|ho|ma|ma|ma|mi|mi|mi|mu|mu|mu|mu|me|mo|mo|mo|ya|yu|yu|yu|yo|ra|ra|ra|ri|ru|ru|ru|re|ro|ro|ro|wa|wa|wa|wa|wo|wo)(|(ka|ki|ki|ku|ku|ke|ke|ko|ko|sa|sa|sa|shi|shi|shi|su|su|se|so|ta|ta|chi|chi|tsu|te|to|na|ni|ni|nu|nu|ne|no|no|ha|hi|fu|fu|he|ho|ma|ma|ma|mi|mi|mi|mu|mu|mu|mu|me|mo|mo|mo|ya|yu|yu|yu|yo|ra|ra|ra|ri|ru|ru|ru|re|ro|ro|ro|wa|wa|wa|wa|wo|wo)|(ka|ki|ki|ku|ku|ke|ke|ko|ko|sa|sa|sa|shi|shi|shi|su|su|se|so|ta|ta|chi|chi|tsu|te|to|na|ni|ni|nu|nu|ne|no|no|ha|hi|fu|fu|he|ho|ma|ma|ma|mi|mi|mi|mu|mu|mu|mu|me|mo|mo|mo|ya|yu|yu|yu|yo|ra|ra|ra|ri|ru|ru|ru|re|ro|ro|ro|wa|wa|wa|wa|wo|wo)(|(ka|ki|ki|ku|ku|ke|ke|ko|ko|sa|sa|sa|shi|shi|shi|su|su|se|so|ta|ta|chi|chi|tsu|te|to|na|ni|ni|nu|nu|ne|no|no|ha|hi|fu|fu|he|ho|ma|ma|ma|mi|mi|mi|mu|mu|mu|mu|me|mo|mo|mo|ya|yu|yu|yu|yo|ra|ra|ra|ri|ru|ru|ru|re|ro|ro|ro|wa|wa|wa|wa|wo|wo)))(|||n)";

    // Chinese Names
    public static String CHINESE_NAMES = "(zh|x|q|sh|h)(ao|ian|uo|ou|ia)(|(l|w|c|p|b|m)(ao|ian|uo|ou|ia)(|n)|-(l|w|c|p|b|m)(ao|ian|uo|ou|ia)(|(d|j|q|l)(a|ai|iu|ao|i)))";

    // Greek Names
    public static String GREEK_NAMES = "<s<v|V>(tia)|s<v|V>(os)|B<v|V>C(ios)|B<v|V><c|C>V(ios|os)>";

    // Hawaiian Names (1)
    public static String HAWAIIAN_NAMES_1 = "((h|k|l|m|n|p|w|')|)(a|e|i|o|u)((h|k|l|m|n|p|w|')|)(a|e|i|o|u)(((h|k|l|m|n|p|w|')|)(a|e|i|o|u)|)(((h|k|l|m|n|p|w|')|)(a|e|i|o|u)|)(((h|k|l|m|n|p|w|')|)(a|e|i|o|u)|)(((h|k|l|m|n|p|w|')|)(a|e|i|o|u)|)";

    // Hawaiian Names (2)
    public static String HAWAIIAN_NAMES_2 = "((h|k|l|m|n|p|w|)(a|e|i|o|u|a'|e'|i'|o'|u'|ae|ai|ao|au|oi|ou|eu|ei)(k|l|m|n|p|)|)(h|k|l|m|n|p|w|)(a|e|i|o|u|a'|e'|i'|o'|u'|ae|ai|ao|au|oi|ou|eu|ei)(k|l|m|n|p|)";

    // Old Latin Place Names
    public static String OLD_LATIN_PLACE_NAMES = "Sv(nia|lia|cia|sia)";

    // Dragons (Pern)
    public static String DRAGONS_PERN = "<<s|ss>|<VC|vC|B|BVs|Vs>><v|V|v|<V(l|n|r)|vc>>(th)";

    // Dragon Riders
    public static String DRAGON_RIDERS = "c'<s|cvc>";

    // Pokemon
    public static String POKEMON = "<i|s>V(mon|chu|zard|rtle)";

    // Fantasy (Vowels, R, etc.)
    public static String FANTASY_VOWELS_R = "(|(<B>|s|h|ty|ph|r))(i|ae|ya|ae|eu|ia|i|eo|ai|a)(lo|la|sri|da|dai|the|sty|lae|due|li|lly|ri|na|ral|sur|rith)(|(su|nu|sti|llo|ria|))(|(n|ra|p|m|lis|cal|deu|dil|suir|phos|ru|dru|rin|raap|rgue))";

    // Fantasy (S, A, etc.)
    public static String FANTASY_S_A = "(cham|chan|jisk|lis|frich|isk|lass|mind|sond|sund|ass|chad|lirt|und|mar|lis|il|<BVC>)(jask|ast|ista|adar|irra|im|ossa|assa|osia|ilsa|<vCv>)(|(an|ya|la|sta|sda|sya|st|nya))";

    // Fantasy (H, L, etc.)
    public static String FANTASY_H_L = "(ch|ch't|sh|cal|val|ell|har|shar|shal|rel|laen|ral|jh't|alr|ch|ch't|av)(|(is|al|ow|ish|ul|el|ar|iel))(aren|aeish|aith|even|adur|ulash|alith|atar|aia|erin|aera|ael|ira|iel|ahur|ishul)";

    // Fantasy (N, L, etc.)
    public static String FANTASY_N_L = "(ethr|qil|mal|er|eal|far|fil|fir|ing|ind|il|lam|quel|quar|quan|qar|pal|mal|yar|um|ard|enn|ey)(|(<vc>|on|us|un|ar|as|en|ir|ur|at|ol|al|an))(uard|wen|arn|on|il|ie|on|iel|rion|rian|an|ista|rion|rian|cil|mol|yon)";

    // Fantasy (K, N, etc.)
    public static String FANTASY_K_N = "(taith|kach|chak|kank|kjar|rak|kan|kaj|tach|rskal|kjol|jok|jor|jad|kot|kon|knir|kror|kol|tul|rhaok|rhak|krol|jan|kag|ryr)(<vc>|in|or|an|ar|och|un|mar|yk|ja|arn|ir|ros|ror)(|(mund|ard|arn|karr|chim|kos|rir|arl|kni|var|an|in|ir|a|i|as))";

    // Fantasy (J, G, Z, etc.)
    public static String FANTASY_J_G_Z = "(aj|ch|etz|etzl|tz|kal|gahn|kab|aj|izl|ts|jaj|lan|kach|chaj|qaq|jol|ix|az|biq|nam)(|(<vc>|aw|al|yes|il|ay|en|tom||oj|im|ol|aj|an|as))(aj|am|al|aqa|ende|elja|ich|ak|ix|in|ak|al|il|ek|ij|os|al|im)";

    // Fantasy (K, J, Y, etc.)
    public static String FANTASY_K_J_Y = "(yi|shu|a|be|na|chi|cha|cho|ksa|yi|shu)(th|dd|jj|sh|rr|mk|n|rk|y|jj|th)(us|ash|eni|akra|nai|ral|ect|are|el|urru|aja|al|uz|ict|arja|ichi|ural|iru|aki|esh)";

    // Fantasy (S, E, etc.)
    public static String FANTASY_S_E = "(syth|sith|srr|sen|yth|ssen|then|fen|ssth|kel|syn|est|bess|inth|nen|tin|cor|sv|iss|ith|sen|slar|ssil|sthen|svis|s|ss|s|ss)(|(tys|eus|yn|of|es|en|ath|elth|al|ell|ka|ith|yrrl|is|isl|yr|ast|iy))(us|yn|en|ens|ra|rg|le|en|ith|ast|zon|in|yn|ys)";

    protected ArrayList<NameGen> generators = new ArrayList<NameGen>();

    public NameGen(String pattern)
    {
        this(pattern, true, true);
    }

    public NameGen(String pattern, boolean collapseTriples, boolean capitalizeFirst)
    {
        NameGen last;
        Stack<Group> stack = new Stack<Group>();
        Random random = new Random();
        Group top = new GroupSymbol(random);

        for (int i = 0; i < pattern.length(); i++)
        {
            char chr = pattern.charAt(i);
            switch (chr)
            {
                case '<':
                    stack.add(top);
                    top = new GroupSymbol(random);
                    break;
                case '(':
                    stack.add(top);
                    top = new GroupLiteral(random);
                    break;
                case '>':
                case ')':
                    if (stack.size() == 0)
                        throw new IllegalArgumentException("Unbalanced brackets");
                    else if (chr == '>' && top.type != GroupTypes.SYMBOL)
                        throw new IllegalArgumentException("Unexpected '>' in pattern");
                    else if (chr == ')' && top.type != GroupTypes.LITERAL)
                        throw new IllegalArgumentException("Unexpected ')' in pattern");

                    last = top.produce();
                    top = stack.pop();
                    top.add(last);
                    break;
                case '|':
                    top.split();
                    break;
                case '!':
                    if (top.type == GroupTypes.SYMBOL)
                        top.wrap(Wrappers.CAPITALIZER);
                    else
                        top.add(chr);
                    break;
                case '~':
                    if (top.type == GroupTypes.SYMBOL)
                        top.wrap(Wrappers.REVERSER);
                    else
                        top.add(chr);
                    break;
                default:
                    top.add(chr);
                    break;
            }
        }

        if (stack.size() != 0)
            throw new IllegalArgumentException("Missing closing brackets");

        NameGen g = top.produce();
        if (collapseTriples)
            g = new Collapser(g);
        if (capitalizeFirst)
            g = new Capitalizer(g);
        this.add(g);
    }

    NameGen(ArrayList<NameGen> generators)
    {
        this.generators = generators;
    }

    public int combinations()
    {
        int total = 1;
        for (NameGen g : this.generators)
            total *= g.combinations();
        return total;
    }

    public int min()
    {
        int val = 0;
        for (NameGen g : this.generators)
            val += g.min();
        return val;
    }

    public int max()
    {
        int val = 0;
        for (NameGen g : this.generators)
            val += g.max();
        return val;
    }

    @Override
    public String toString()
    {
        String str = "";
        for (NameGen g : this.generators)
            str += g.toString();
        return str;
    }

    public void add(NameGen g)
    {
        this.generators.add(g);
    }

    enum Wrappers
    {
        CAPITALIZER,
        REVERSER
    }

    enum GroupTypes
    {
        SYMBOL,
        LITERAL
    }

    public abstract class Group
    {
        private Stack<Wrappers> wrappers = new Stack<Wrappers>();
        private ArrayList<NameGen> set = new ArrayList<NameGen>();

        public GroupTypes type;
        protected Random random;

        public Group(GroupTypes type, Random random)
        {
            this.type = type;
            this.random = random;
        }

        public NameGen produce()
        {
            switch (this.set.size())
            {
                case 0:
                    return new Literal("");
                case 1:
                    return this.set.get(0);
                default:
                    return new RandomPicker(this.set, random);
            }
        }

        public void split()
        {
            if (this.set.size() == 0)
                this.set.add(new Sequence(new ArrayList<NameGen>()));
            this.set.add(new Sequence(new ArrayList<NameGen>()));
        }

        public void wrap(Wrappers type)
        {
            this.wrappers.push(type);
        }

        public void add(NameGen g)
        {
            while (this.wrappers.size() > 0)
            {
                switch (this.wrappers.pop())
                {
                    case REVERSER:
                        g = new Reverser(g);
                        break;
                    case CAPITALIZER:
                        g = new Capitalizer(g);
                        break;
                }
            }
            if (this.set.size() == 0)
                this.set.add(new Sequence(new ArrayList<NameGen>()));

            this.set.get(this.set.size() - 1).add(g);
            return;
        }

        public void add(char chr)
        {
            RandomPicker g = new RandomPicker(new ArrayList<NameGen>(), random);
            g.add(new Literal(String.valueOf(chr)));
            this.add(g);
        }
    }

    private final static HashMap<Character, String[]> symbolMap = new HashMap<Character, String[]>()
    {{
        put('s', new String[]{"ach", "ack", "ad", "age", "ald", "ale", "an", "ang", "ar", "ard",
                "as", "ash", "at", "ath", "augh", "aw", "ban", "bel", "bur", "cer",
                "cha", "che", "dan", "dar", "del", "den", "dra", "dyn", "ech", "eld",
                "elm", "em", "en", "end", "eng", "enth", "er", "ess", "est", "et",
                "gar", "gha", "hat", "hin", "hon", "ia", "ight", "ild", "im", "ina",
                "ine", "ing", "ir", "is", "iss", "it", "kal", "kel", "kim", "kin",
                "ler", "lor", "lye", "mor", "mos", "nal", "ny", "nys", "old", "om",
                "on", "or", "orm", "os", "ough", "per", "pol", "qua", "que", "rad",
                "rak", "ran", "ray", "ril", "ris", "rod", "roth", "ryn", "sam",
                "say", "ser", "shy", "skel", "sul", "tai", "tan", "tas", "ther",
                "tia", "tin", "ton", "tor", "tur", "um", "und", "unt", "urn", "usk",
                "ust", "ver", "ves", "vor", "war", "wor", "yer"});
        put('v', new String[]{"a", "e", "i", "o", "u", "y"});
        put('V', new String[]{"a", "e", "i", "o", "u", "y", "ae", "ai", "au", "ay", "ea", "ee",
                "ei", "eu", "ey", "ia", "ie", "oe", "oi", "oo", "ou", "ui"});
        put('c', new String[]{"b", "c", "d", "f", "g", "h", "j", "k", "l", "m", "n", "p", "q", "r",
                "s", "t", "v", "w", "x", "y", "z"});
        put('B', new String[]{"b", "bl", "br", "c", "ch", "chr", "cl", "cr", "d", "dr", "f", "g",
                "h", "j", "k", "l", "ll", "m", "n", "p", "ph", "qu", "r", "rh", "s",
                "sch", "sh", "sl", "sm", "sn", "st", "str", "sw", "t", "th", "thr",
                "tr", "v", "w", "wh", "y", "z", "zh"});
        put('C', new String[]{"b", "c", "ch", "ck", "d", "f", "g", "gh", "h", "k", "l", "ld", "ll",
                "lt", "m", "n", "nd", "nn", "nt", "p", "ph", "q", "r", "rd", "rr",
                "rt", "s", "sh", "ss", "st", "t", "th", "v", "w", "y", "z"});
        put('i', new String[]{"air", "ankle", "ball", "beef", "bone", "bum", "bumble", "bump",
                "cheese", "clod", "clot", "clown", "corn", "dip", "dolt", "doof",
                "dork", "dumb", "face", "finger", "foot", "fumble", "goof",
                "grumble", "head", "knock", "knocker", "knuckle", "loaf", "lump",
                "lunk", "meat", "muck", "munch", "nit", "numb", "pin", "puff",
                "skull", "snark", "sneeze", "thimble", "twerp", "twit", "wad",
                "wimp", "wipe"});
        put('m', new String[]{"baby", "booble", "bunker", "cuddle", "cuddly", "cutie", "doodle",
                "foofie", "gooble", "honey", "kissie", "lover", "lovey", "moofie",
                "mooglie", "moopie", "moopsie", "nookum", "poochie", "poof",
                "poofie", "pookie", "schmoopie", "schnoogle", "schnookie",
                "schnookum", "smooch", "smoochie", "smoosh", "snoogle", "snoogy",
                "snookie", "snookum", "snuggy", "sweetie", "woogle", "woogy",
                "wookie", "wookum", "wuddle", "wuddly", "wuggy", "wunny"});
        put('M', new String[]{"boo", "bunch", "bunny", "cake", "cakes", "cute", "darling",
                "dumpling", "dumplings", "face", "foof", "goo", "head", "kin",
                "kins", "lips", "love", "mush", "pie", "poo", "pooh", "pook", "pums"});
        put('D', new String[]{"b", "bl", "br", "cl", "d", "f", "fl", "fr", "g", "gh", "gl", "gr",
                "h", "j", "k", "kl", "m", "n", "p", "th", "w"});
        put('d', new String[]{"elch", "idiot", "ob", "og", "ok", "olph", "olt", "omph", "ong",
                "onk", "oo", "oob", "oof", "oog", "ook", "ooz", "org", "ork", "orm",
                "oron", "ub", "uck", "ug", "ulf", "ult", "um", "umb", "ump", "umph",
                "un", "unb", "ung", "unk", "unph", "unt", "uzz"});
    }};

    class GroupSymbol extends Group
    {
        public GroupSymbol(Random random)
        {
            super(GroupTypes.SYMBOL, random);
        }

        public void add(char a)
        {
            NameGen g = new RandomPicker(new ArrayList<NameGen>(), random);
            if (symbolMap.containsKey(a))
            {
                String[] symbols = symbolMap.get(a);
                for (String symbol : symbols)
                    g.add(new Literal(symbol));
            } else
            {
                g.add(new Literal(String.valueOf(a)));
            }
            super.add(g);
        }
    }

    class GroupLiteral extends Group
    {
        public GroupLiteral(Random random)
        {
            super(GroupTypes.LITERAL, random);
        }
    }

    class RandomPicker extends NameGen
    {
        private Random random;

        public RandomPicker(ArrayList<NameGen> generators, Random random)
        {
            super(generators);
            this.random = random;
        }

        @Override
        public int combinations()
        {
            int total = 0;
            for (NameGen g : this.generators)
                total += g.combinations();
            return total > 0 ? total : 1;
        }

        @Override
        public int min()
        {
            int val = -1;
            for (NameGen g : this.generators)
            {
                int curr = g.min();
                if (curr < val)
                    val = curr;
            }
            return val;
        }

        @Override
        public int max()
        {
            int val = 0;
            for (NameGen g : this.generators)
            {
                int curr = g.max();
                if (curr > val)
                    val = curr;
            }
            return val;
        }

        @Override
        public String toString()
        {
            if (this.generators.size() == 0)
                return "";

            int rnd = random.nextInt(this.generators.size());
            return this.generators.get(rnd).toString();
        }
    }

    class Sequence extends NameGen
    {
        public Sequence(ArrayList<NameGen> generators)
        {
            super(generators);
        }
    }

    class Literal extends NameGen
    {
        private String value;

        public Literal(String value)
        {
            super(new ArrayList<NameGen>());
            this.value = value;
        }

        @Override
        public int combinations()
        {
            return 1;
        }

        @Override
        public int min()
        {
            return this.value.length();
        }

        @Override
        public int max()
        {
            return this.value.length();
        }

        @Override
        public String toString()
        {
            return this.value;
        }
    }

    class Reverser extends NameGen
    {
        public Reverser(NameGen generator)
        {
            super(new ArrayList<NameGen>()
            {{
                add(generator);
            }});
        }

        @Override
        public String toString()
        {
            char[] charArray = super.toString().toCharArray();
            Collections.reverse(Arrays.asList(charArray));
            return new String(charArray);
        }
    }

    class Capitalizer extends NameGen
    {
        public Capitalizer(NameGen generator)
        {
            super(new ArrayList<NameGen>()
            {{
                add(generator);
            }});
        }

        @Override
        public String toString()
        {
            String str = super.toString();
            if (str == "") return "";
            return str.substring(0, 1).toUpperCase() + str.substring(1).toLowerCase();
        }
    }

    class Collapser extends NameGen
    {
        public Collapser(NameGen generator)
        {
            super(new ArrayList<NameGen>()
            {{
                add(generator);
            }});
        }

        @Override
        public String toString()
        {
            String str = super.toString();
            String result = "";
            int cnt = 0;
            char pch = '\0';
            for (int i = 0; i < str.length(); i++)
            {
                char chr = str.charAt(i);
                if (chr == pch)
                    cnt++;
                else
                    cnt = 0;
                int mch = 2;
                switch (chr)
                {
                    case 'a':
                    case 'h':
                    case 'i':
                    case 'j':
                    case 'q':
                    case 'u':
                    case 'v':
                    case 'w':
                    case 'x':
                    case 'y':
                        mch = 1;
                        break;
                }

                if (cnt < mch)
                    result += chr;
                pch = chr;
            }
            return result;
        }
    }
}