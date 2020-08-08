using System;
using System.Collections.Generic;

/**
 *
 * @file A fantasy name generator library.
 * @version 1.0.1
 * @license Public Domain
 * @author Edgar Alvarado (pe1uca)
 *
 * This library is designed after the RinkWorks Fantasy Name Generator.
 * @see http://www.rinkworks.com/namegen/
 *
 * @example
 * using NameGen;
 * var generator = new Generator("sV'i");
 * generator.ToString();  // Returns a new name each call with ToString()
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

namespace NameGen
{
    public class Generator
    {
        // Middle Earth
        public static readonly string MIDDLE_EARTH = "(bil|bal|ban|hil|ham|hal|hol|hob|wil|me|or|ol|od|gor|for|fos|tol|ar|fin|ere|leo|vi|bi|bren|thor)(|go|orbis|apol|adur|mos|ri|i|na|ole|n)(|tur|axia|and|bo|gil|bin|bras|las|mac|grim|wise|l|lo|fo|co|ra|via|da|ne|ta|y|wen|thiel|phin|dir|dor|tor|rod|on|rdo|dis)";

        // Japanese Names (Constrained)
        public static readonly string JAPANESE_NAMES_CONSTRAINED = "(aka|aki|bashi|gawa|kawa|furu|fuku|fuji|hana|hara|haru|hashi|hira|hon|hoshi|ichi|iwa|kami|kawa|ki|kita|kuchi|kuro|marui|matsu|miya|mori|moto|mura|nabe|naka|nishi|no|da|ta|o|oo|oka|saka|saki|sawa|shita|shima|i|suzu|taka|take|to|toku|toyo|ue|wa|wara|wata|yama|yoshi|kei|ko|zawa|zen|sen|ao|gin|kin|ken|shiro|zaki|yuki|asa)(||||||||||bashi|gawa|kawa|furu|fuku|fuji|hana|hara|haru|hashi|hira|hon|hoshi|chi|wa|ka|kami|kawa|ki|kita|kuchi|kuro|marui|matsu|miya|mori|moto|mura|nabe|naka|nishi|no|da|ta|o|oo|oka|saka|saki|sawa|shita|shima|suzu|taka|take|to|toku|toyo|ue|wa|wara|wata|yama|yoshi|kei|ko|zawa|zen|sen|ao|gin|kin|ken|shiro|zaki|yuki|sa)";

        // Japanese Names (Diverse)
        public static readonly string JAPANESE_NAMES_DIVERSE = "(a|i|u|e|o|||||)(ka|ki|ki|ku|ku|ke|ke|ko|ko|sa|sa|sa|shi|shi|shi|su|su|se|so|ta|ta|chi|chi|tsu|te|to|na|ni|ni|nu|nu|ne|no|no|ha|hi|fu|fu|he|ho|ma|ma|ma|mi|mi|mi|mu|mu|mu|mu|me|mo|mo|mo|ya|yu|yu|yu|yo|ra|ra|ra|ri|ru|ru|ru|re|ro|ro|ro|wa|wa|wa|wa|wo|wo)(ka|ki|ki|ku|ku|ke|ke|ko|ko|sa|sa|sa|shi|shi|shi|su|su|se|so|ta|ta|chi|chi|tsu|te|to|na|ni|ni|nu|nu|ne|no|no|ha|hi|fu|fu|he|ho|ma|ma|ma|mi|mi|mi|mu|mu|mu|mu|me|mo|mo|mo|ya|yu|yu|yu|yo|ra|ra|ra|ri|ru|ru|ru|re|ro|ro|ro|wa|wa|wa|wa|wo|wo)(|(ka|ki|ki|ku|ku|ke|ke|ko|ko|sa|sa|sa|shi|shi|shi|su|su|se|so|ta|ta|chi|chi|tsu|te|to|na|ni|ni|nu|nu|ne|no|no|ha|hi|fu|fu|he|ho|ma|ma|ma|mi|mi|mi|mu|mu|mu|mu|me|mo|mo|mo|ya|yu|yu|yu|yo|ra|ra|ra|ri|ru|ru|ru|re|ro|ro|ro|wa|wa|wa|wa|wo|wo)|(ka|ki|ki|ku|ku|ke|ke|ko|ko|sa|sa|sa|shi|shi|shi|su|su|se|so|ta|ta|chi|chi|tsu|te|to|na|ni|ni|nu|nu|ne|no|no|ha|hi|fu|fu|he|ho|ma|ma|ma|mi|mi|mi|mu|mu|mu|mu|me|mo|mo|mo|ya|yu|yu|yu|yo|ra|ra|ra|ri|ru|ru|ru|re|ro|ro|ro|wa|wa|wa|wa|wo|wo)(|(ka|ki|ki|ku|ku|ke|ke|ko|ko|sa|sa|sa|shi|shi|shi|su|su|se|so|ta|ta|chi|chi|tsu|te|to|na|ni|ni|nu|nu|ne|no|no|ha|hi|fu|fu|he|ho|ma|ma|ma|mi|mi|mi|mu|mu|mu|mu|me|mo|mo|mo|ya|yu|yu|yu|yo|ra|ra|ra|ri|ru|ru|ru|re|ro|ro|ro|wa|wa|wa|wa|wo|wo)))(|||n)";

        // Chinese Names
        public static readonly string CHINESE_NAMES = "(zh|x|q|sh|h)(ao|ian|uo|ou|ia)(|(l|w|c|p|b|m)(ao|ian|uo|ou|ia)(|n)|-(l|w|c|p|b|m)(ao|ian|uo|ou|ia)(|(d|j|q|l)(a|ai|iu|ao|i)))";

        // Greek Names
        public static readonly string GREEK_NAMES = "<s<v|V>(tia)|s<v|V>(os)|B<v|V>C(ios)|B<v|V><c|C>V(ios|os)>";

        // Hawaiian Names (1)
        public static readonly string HAWAIIAN_NAMES_1 = "((h|k|l|m|n|p|w|')|)(a|e|i|o|u)((h|k|l|m|n|p|w|')|)(a|e|i|o|u)(((h|k|l|m|n|p|w|')|)(a|e|i|o|u)|)(((h|k|l|m|n|p|w|')|)(a|e|i|o|u)|)(((h|k|l|m|n|p|w|')|)(a|e|i|o|u)|)(((h|k|l|m|n|p|w|')|)(a|e|i|o|u)|)";

        // Hawaiian Names (2)
        public static readonly string HAWAIIAN_NAMES_2 = "((h|k|l|m|n|p|w|)(a|e|i|o|u|a'|e'|i'|o'|u'|ae|ai|ao|au|oi|ou|eu|ei)(k|l|m|n|p|)|)(h|k|l|m|n|p|w|)(a|e|i|o|u|a'|e'|i'|o'|u'|ae|ai|ao|au|oi|ou|eu|ei)(k|l|m|n|p|)";

        // Old Latin Place Names
        public static readonly string OLD_LATIN_PLACE_NAMES = "Sv(nia|lia|cia|sia)";

        // Dragons (Pern)
        public static readonly string DRAGONS_PERN = "<<s|ss>|<VC|vC|B|BVs|Vs>><v|V|v|<V(l|n|r)|vc>>(th)";

        // Dragon Riders
        public static readonly string DRAGON_RIDERS = "c'<s|cvc>";

        // Pokemon
        public static readonly string POKEMON = "<i|s>V(mon|chu|zard|rtle)";

        // Fantasy (Vowels, R, etc.)
        public static readonly string FANTASY_VOWELS_R = "(|(<B>|s|h|ty|ph|r))(i|ae|ya|ae|eu|ia|i|eo|ai|a)(lo|la|sri|da|dai|the|sty|lae|due|li|lly|ri|na|ral|sur|rith)(|(su|nu|sti|llo|ria|))(|(n|ra|p|m|lis|cal|deu|dil|suir|phos|ru|dru|rin|raap|rgue))";

        // Fantasy (S, A, etc.)
        public static readonly string FANTASY_S_A = "(cham|chan|jisk|lis|frich|isk|lass|mind|sond|sund|ass|chad|lirt|und|mar|lis|il|<BVC>)(jask|ast|ista|adar|irra|im|ossa|assa|osia|ilsa|<vCv>)(|(an|ya|la|sta|sda|sya|st|nya))";

        // Fantasy (H, L, etc.)
        public static readonly string FANTASY_H_L = "(ch|ch't|sh|cal|val|ell|har|shar|shal|rel|laen|ral|jh't|alr|ch|ch't|av)(|(is|al|ow|ish|ul|el|ar|iel))(aren|aeish|aith|even|adur|ulash|alith|atar|aia|erin|aera|ael|ira|iel|ahur|ishul)";

        // Fantasy (N, L, etc.)
        public static readonly string FANTASY_N_L = "(ethr|qil|mal|er|eal|far|fil|fir|ing|ind|il|lam|quel|quar|quan|qar|pal|mal|yar|um|ard|enn|ey)(|(<vc>|on|us|un|ar|as|en|ir|ur|at|ol|al|an))(uard|wen|arn|on|il|ie|on|iel|rion|rian|an|ista|rion|rian|cil|mol|yon)";

        // Fantasy (K, N, etc.)
        public static readonly string FANTASY_K_N = "(taith|kach|chak|kank|kjar|rak|kan|kaj|tach|rskal|kjol|jok|jor|jad|kot|kon|knir|kror|kol|tul|rhaok|rhak|krol|jan|kag|ryr)(<vc>|in|or|an|ar|och|un|mar|yk|ja|arn|ir|ros|ror)(|(mund|ard|arn|karr|chim|kos|rir|arl|kni|var|an|in|ir|a|i|as))";

        // Fantasy (J, G, Z, etc.)
        public static readonly string FANTASY_J_G_Z = "(aj|ch|etz|etzl|tz|kal|gahn|kab|aj|izl|ts|jaj|lan|kach|chaj|qaq|jol|ix|az|biq|nam)(|(<vc>|aw|al|yes|il|ay|en|tom||oj|im|ol|aj|an|as))(aj|am|al|aqa|ende|elja|ich|ak|ix|in|ak|al|il|ek|ij|os|al|im)";

        // Fantasy (K, J, Y, etc.)
        public static readonly string FANTASY_K_J_Y = "(yi|shu|a|be|na|chi|cha|cho|ksa|yi|shu)(th|dd|jj|sh|rr|mk|n|rk|y|jj|th)(us|ash|eni|akra|nai|ral|ect|are|el|urru|aja|al|uz|ict|arja|ichi|ural|iru|aki|esh)";

        // Fantasy (S, E, etc.)
        public static readonly string FANTASY_S_E = "(syth|sith|srr|sen|yth|ssen|then|fen|ssth|kel|syn|est|bess|inth|nen|tin|cor|sv|iss|ith|sen|slar|ssil|sthen|svis|s|ss|s|ss)(|(tys|eus|yn|of|es|en|ath|elth|al|ell|ka|ith|yrrl|is|isl|yr|ast|iy))(us|yn|en|ens|ra|rg|le|en|ith|ast|zon|in|yn|ys)";

        protected List<Generator> generators = new List<Generator>();

        public Generator(string pattern, bool collapseTriples = true, bool capitalizeFirst = true)
        {
            Generator last;
            Stack<Group> stack = new Stack<Group>();
            Group top = new GroupSymbol();

            for (var i = 0; i < pattern.Length; i++)
            {
                var chr = pattern[i];
                switch (chr)
                {
                    case '<':
                        stack.Push(top);
                        top = new GroupSymbol();
                        break;
                    case '(':
                        stack.Push(top);
                        top = new GroupLiteral();
                        break;
                    case '>':
                    case ')':
                        if (stack.Count == 0)
                            throw new ArgumentException("Unbalanced brackets");
                        else if (chr == '>' && top.type != GroupTypes.symbol)
                            throw new ArgumentException("Unexpected '>' in pattern");
                        else if (chr == ')' && top.type != GroupTypes.literal)
                            throw new ArgumentException("Unexpected ')' in pattern");

                        last = top.Produce();
                        top = stack.Pop();
                        top.Add(last);
                        break;
                    case '|':
                        top.Split();
                        break;
                    case '!':
                        if (top.type == GroupTypes.symbol)
                            top.Wrap(Wrappers.capitalizer);
                        else
                            top.Add(chr);
                        break;
                    case '~':
                        if (top.type == GroupTypes.symbol)
                            top.Wrap(Wrappers.reverser);
                        else
                            top.Add(chr);
                        break;
                    default:
                        top.Add(chr);
                        break;
                }
            }

            if (stack.Count != 0)
                throw new ArgumentException("Missing closing brackets");

            Generator g = top.Produce();
            if (collapseTriples)
                g = new Collapser(g);
			if (capitalizeFirst)
                g = new Capitalizer(g);
            this.Add(g);
        }

        internal Generator(List<Generator> generators)
        {
            this.generators = generators;
        }

        internal virtual int Combinations()
        {
            var total = 1;
            foreach (var g in this.generators)
                total *= g.Combinations();
            return total;
        }

        internal virtual int Min()
        {
            var final = 0;
            foreach (var g in this.generators)
                final += g.Min();
            return final;
        }

        internal virtual int Max()
        {
            var final = 0;
            foreach (var g in this.generators)
                final += g.Max();
            return final;
        }

        public override string ToString()
        {
            var str = "";
            foreach (var g in this.generators)
                str += g.ToString();
            return str;
        }

        internal void Add(Generator g)
        {
            this.generators.Add(g);
        }
    }

    internal enum Wrappers
    {
        capitalizer,
        reverser
    }

    internal enum GroupTypes
    {
        symbol,
        literal
    }

    internal class Group
    {
        private Stack<Wrappers> wrappers = new Stack<Wrappers>();
        private List<Generator> set = new List<Generator>();

        public GroupTypes type;

        public Group(GroupTypes type)
        {
            this.type = type;
        }

        public Generator Produce()
        {
            switch (this.set.Count)
            {
                case 0:
                    return new Literal("");
                case 1:
                    return this.set[0];
                default:
                    return new Random(this.set);
            }
        }

        public void Split()
        {
            if (this.set.Count == 0)
                this.set.Add(new Sequence(new List<Generator>()));
            this.set.Add(new Sequence(new List<Generator>()));
        }

        public void Wrap(Wrappers type)
        {
            this.wrappers.Push(type);
        }

        public virtual void Add(Generator g)
        {
            while (this.wrappers.Count > 0)
            {
                switch (this.wrappers.Pop())
                {
                    case Wrappers.reverser:
                        g = new Reverser(g);
                        break;
                    case Wrappers.capitalizer:
                        g = new Capitalizer(g);
                        break;
                }
            }
            if (this.set.Count == 0)
                this.set.Add(new Sequence(new List<Generator>()));
            this.set[this.set.Count - 1].Add(g);
            return;
        }

        public virtual void Add(char chr)
        {
            var g = new Random(new List<Generator>());
            g.Add(new Literal(chr.ToString()));
            this.Add(g);
        }
    }

    internal class GroupSymbol : Group
    {
        private static readonly Dictionary<char, string[]> symbolMap = new Dictionary<char, string[]>
        {
            { 's', new string[] { "ach", "ack", "ad", "age", "ald", "ale", "an", "ang", "ar", "ard",
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
                "ust", "ver", "ves", "vor", "war", "wor", "yer" } },
            { 'v', new string[] { "a", "e", "i", "o", "u", "y" } },
            { 'V', new string[] { "a", "e", "i", "o", "u", "y", "ae", "ai", "au", "ay", "ea", "ee",
                "ei", "eu", "ey", "ia", "ie", "oe", "oi", "oo", "ou", "ui" } },
            { 'c', new string[] { "b", "c", "d", "f", "g", "h", "j", "k", "l", "m", "n", "p", "q", "r",
                "s", "t", "v", "w", "x", "y", "z" } },
            { 'B', new string[] { "b", "bl", "br", "c", "ch", "chr", "cl", "cr", "d", "dr", "f", "g",
                "h", "j", "k", "l", "ll", "m", "n", "p", "ph", "qu", "r", "rh", "s",
                "sch", "sh", "sl", "sm", "sn", "st", "str", "sw", "t", "th", "thr",
                "tr", "v", "w", "wh", "y", "z", "zh" } },
            { 'C', new string[] { "b", "c", "ch", "ck", "d", "f", "g", "gh", "h", "k", "l", "ld", "ll",
                "lt", "m", "n", "nd", "nn", "nt", "p", "ph", "q", "r", "rd", "rr",
                "rt", "s", "sh", "ss", "st", "t", "th", "v", "w", "y", "z" } },
            { 'i', new string[] { "air", "ankle", "ball", "beef", "bone", "bum", "bumble", "bump",
                "cheese", "clod", "clot", "clown", "corn", "dip", "dolt", "doof",
                "dork", "dumb", "face", "finger", "foot", "fumble", "goof",
                "grumble", "head", "knock", "knocker", "knuckle", "loaf", "lump",
                "lunk", "meat", "muck", "munch", "nit", "numb", "pin", "puff",
                "skull", "snark", "sneeze", "thimble", "twerp", "twit", "wad",
                "wimp", "wipe" } },
            { 'm', new string[] { "baby", "booble", "bunker", "cuddle", "cuddly", "cutie", "doodle",
                "foofie", "gooble", "honey", "kissie", "lover", "lovey", "moofie",
                "mooglie", "moopie", "moopsie", "nookum", "poochie", "poof",
                "poofie", "pookie", "schmoopie", "schnoogle", "schnookie",
                "schnookum", "smooch", "smoochie", "smoosh", "snoogle", "snoogy",
                "snookie", "snookum", "snuggy", "sweetie", "woogle", "woogy",
                "wookie", "wookum", "wuddle", "wuddly", "wuggy", "wunny" } },
            { 'M', new string[] { "boo", "bunch", "bunny", "cake", "cakes", "cute", "darling",
                "dumpling", "dumplings", "face", "foof", "goo", "head", "kin",
                "kins", "lips", "love", "mush", "pie", "poo", "pooh", "pook", "pums" } },
            { 'D', new string[] { "b", "bl", "br", "cl", "d", "f", "fl", "fr", "g", "gh", "gl", "gr",
                "h", "j", "k", "kl", "m", "n", "p", "th", "w" } },
            { 'd', new string[] { "elch", "idiot", "ob", "og", "ok", "olph", "olt", "omph", "ong",
                "onk", "oo", "oob", "oof", "oog", "ook", "ooz", "org", "ork", "orm",
                "oron", "ub", "uck", "ug", "ulf", "ult", "um", "umb", "ump", "umph",
                "un", "unb", "ung", "unk", "unph", "unt", "uzz" } }
        };

        public GroupSymbol() : base(GroupTypes.symbol) { }

        public override void Add(char a)
        {
            var g = new Random(new List<Generator>());
            if (symbolMap.ContainsKey(a))
            {
                var symbols = symbolMap[a];
                foreach (var symbol in symbols)
                    g.Add(new Literal(symbol));
            }
            else
            {
                g.Add(new Literal(a.ToString()));
            }
            base.Add(g);
        }
    }

    internal class GroupLiteral : Group
    {
        public GroupLiteral() : base(GroupTypes.literal) { }
    }

    internal class Random : Generator
    {
        private System.Random random = new System.Random();

        public Random(List<Generator> generators) : base(generators) { }

        internal override int Combinations()
        {
            var total = 0;
            foreach (var g in this.generators)
                total += g.Combinations();
            return total > 0 ? total : 1;
        }

        internal override int Min()
        {
            var final = -1;
            foreach (var g in this.generators)
            {
                var curr = g.Min();
                if (curr < final)
                    final = curr;
            }
            return final;
        }

        internal override int Max()
        {
            var final = 0;
            foreach (var g in this.generators)
            {
                var curr = g.Max();
                if (curr > final)
                    final = curr;
            }
            return final;
        }

        public override string ToString()
        {
            if (this.generators.Count == 0)
                return "";

            var rnd = random.Next(this.generators.Count);
            return this.generators[rnd].ToString();
        }
    }

    internal class Sequence : Generator
    {
        public Sequence(List<Generator> generators) : base(generators) { }
    }

    internal class Literal : Generator
    {
        private string value;

        public Literal(string value) : base(new List<Generator>())
        {
            this.value = value;
        }

        internal override int Combinations()
        {
            return 1;
        }

        internal override int Min()
        {
            return this.value.Length;
        }

        internal override int Max()
        {
            return this.value.Length;
        }

        public override string ToString()
        {
            return this.value;
        }
    }

    internal class Reverser : Generator
    {
        public Reverser(Generator generator) : base(new List<Generator>() { generator }) { }

        public override string ToString()
        {
            char[] charArray = base.ToString().ToCharArray();
            Array.Reverse(charArray);
            return new String(charArray);
        }
    }

    internal class Capitalizer : Generator
    {
        public Capitalizer(Generator generator) : base(new List<Generator>() { generator }) { }

        public override string ToString()
        {
            var str = base.ToString();
            if (str == "") return "";
            return str.Substring(0, 1).ToUpper() + str.Substring(1).ToLower();
        }
    }

    internal class Collapser : Generator
    {
        public Collapser(Generator generator) : base(new List<Generator>() { generator }) { }

        public override string ToString()
        {
            var str = base.ToString();
            var result = "";
            var cnt = 0;
            var pch = '\0';
            for (var i = 0; i < str.Length; i++)
            {
                var chr = str[i];
                if (chr == pch)
                    cnt++;
                else
                    cnt = 0;
                var mch = 2;
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
