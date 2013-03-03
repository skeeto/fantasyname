;;; namegen.el --- fantasy name generator

;; This is free and unencumbered software released into the public domain.

;;; Commentary:

;; This is mostly just some thoughts on an elisp name generator. Is it
;; based on the RinkWorks generator, though none of the syntax is
;; specifically used, only sexps. Symbols are replaced by a random
;; selection from its group,

;; s  syllable
;; v  single vowel
;; V  single vowel or vowel combination
;; c  single consonant
;; B  single consonant or consonant combination suitable for beginning a word
;; C  single consonant or consonant combination suitable anywhere in a word
;; i  an insult
;; m  a mushy name
;; M  a mushy name ending
;; D  consonant suited for a stupid person's name
;; d  syllable suited for a stupid person's name (always begins with a vowel)

;; Strings are literal and passed in verbatim. If a list is presented,
;; select one of it's elements of random to be generated.
;;
;; So, to generate a name beginning with a syllable, then "ith" or a '
;; followed by a constant, and ending in a vowel sound,

;;    (s ("ith" ("'" C)) V)

;; In the RinkWorks syntax it would be,

;;    s(ith|<'C>)V

;; Just call it with namegen,

;;    (namegen '(s ("ith" ("'" C)) V))

;; And it generates a string with a name. Someday I might write a
;; parser to create a sexp from a pattern string.

;;; Code:

(defvar namegen-subs
  '((s ach ack ad age ald ale an ang ar ard as ash at ath augh
       aw ban bel bur cer cha che dan dar del den dra dyn
       ech eld elm em en end eng enth er ess est et gar gha
       hat hin hon ia ight ild im ina ine ing ir is iss it
       kal kel kim kin ler lor lye mor mos nal ny nys old om
       on or orm os ough per pol qua que rad rak ran ray ril
       ris rod roth ryn sam say ser shy skel sul tai tan tas
       ther tia tin ton tor tur um und unt urn usk ust ver
       ves vor war wor yer)
    (v a e i o u y)
    (V a e i o u y ae ai au ay ea ee ei eu ey ia ie oe oi oo ou
       ui)
    (c b c d f g h j k l m n p q r s t v w x y z)
    (B b bl br c ch chr cl cr d dr f g h j k l ll m n p ph qu r
       rh s sch sh sl sm sn st str sw t th thr tr v w wh y z zh)
    (C b c ch ck d f g gh h k l ld ll lt m n nd nn nt p ph q r rd
       rr rt s sh ss st t th v w y z)
    (i air ankle ball beef bone bum bumble bump cheese clod clot
       clown corn dip dolt doof dork dumb face finger foot fumble
       goof grumble head knock knocker knuckle loaf lump lunk
       meat muck munch nit numb pin puff skull snark sneeze
       thimble twerp twit wad wimp wipe)
    (m baby booble bunker cuddle cuddly cutie doodle foofie
       gooble honey kissie lover lovey moofie mooglie moopie
       moopsie nookum poochie poof poofie pookie schmoopie
       schnoogle schnookie schnookum smooch smoochie smoosh
       snoogle snoogy snookie snookum snuggy sweetie woogle woogy
       wookie wookum wuddle wuddly wuggy wunny)
    (M boo bunch bunny cake cakes cute darling dumpling dumplings
       face foof goo head kin kins lips love mush pie poo pooh
       pook pums)
    (D b bl br cl d f fl fr g gh gl gr h j k kl m n p th w)
    (d elch idiot ob og ok olph olt omph ong onk oo oob oof oog
       ook ooz org ork orm oron ub uck ug ulf ult um umb ump umph
       un unb ung unk unph unt uzz))
  "Substitutions for the name generator.")

(defun randth (lst)
  "Select random element from the given list."
  (nth (random (length lst)) lst))

(defun namegen (sexp)
  "Generate a name from the given sexp generator."
  (cond
   ((null sexp) "")
   ((stringp sexp) sexp)
   ((symbolp sexp) (namegen-select sexp))
   ((listp sexp)
    (concat (if (listp (car sexp)) (namegen (randth (car sexp)))
              (namegen (car sexp)))
            (namegen (cdr sexp))))))

(defun namegen-select (sym)
  "Select a replacement for the given symbol."
  (if (null (assoc sym namegen-subs))
      (throw 'bad-symbol
             (concat "Invalid substitution symbol: " (format "%s" sym)))
    (symbol-name (randth (cdr (assoc sym namegen-subs))))))

(provide 'namegen)

;;; namegen.el ends here
