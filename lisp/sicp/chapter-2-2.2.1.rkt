#lang planet neil/sicp
;(cons 1
;      (cons 2
;            (cons 3
;                  (cons 4 nil))))
;
(define one-through-four (list 1 2 3 4))
;
;(car one-through-four)
;
;(cons 10 one-through-four)
;
;(cons one-through-four 10)

(define (list-ref a n)
  (if (= n 0)
      (car a)
      (list-ref (cdr a) (- n 1))))

(define (length iterms)
  (define (iter s n)
    (if (null? s)
        n
        (iter (cdr s) (+ n 1))))
  (iter iterms 0))

(define squares (list 1 4 9 16 25))
(define odd (list 1  3 5 7))

(define (append list1 list2)
  (if (null? list1)
      list2
      (cons (car list1) (append (cdr list1) list2))))

(define (reverse items)
  (define (iter-reverse a b)
    (if (null? a)
        b
        (iter-reverse (cdr a) (cons (car a) b))))
  (iter-reverse items nil))

;(define (append-r list1 list2)
;  (define rlist1 (reverse list1))
;  (define (iter r l)
;    (if (null? r)
;        l
;        (iter (cdr r) (cons (car r) l))))
;  (iter rlist1 list2))
;(define (run n f x y)
;  (cond ((= n 0) 0)
;      (else (f x y) (run (- n 1) f x y))))
;
;(define (time-test f . x)
;  (define start-time (runtime))
;  (run 100000 f (car x) (cdr x))
;  (display (- (runtime) start-time))
;  (newline))
;(time-test append squares odd)
;(time-test append-r squares odd)

(define (last-pair items)
  (define (iter l s)
    (if (null? l)
        (cons s nil)
        (iter (cdr l) (car l))))
  (if (null? items)
      items
      (iter items nil)))

(define (same-parity a . b)
  (define (iter s r)
    (cond ((null? s) r)
          ((= (remainder (car s) 2) (remainder a 2)) (iter (cdr s) (cons (car s) r)))
          (else (iter (cdr s) r))))
  (reverse (iter b nil)))

(define (scale-list items factor)
  (if (null? items)
      nil
      (cons (* (car items) factor)
            (scale-list (cdr items) factor))))
      
(define (map proc items)
  (if (null? items)
      nil
      (cons (proc (car items))
            (map proc (cdr items)))))

(define (for-each proc items)
  (if (null? items)
      true
      (let ((x (car items)))
        (proc x)
        (for-each proc (cdr items)))))

;(define x (cons (list 1 2) (list 3 4)))

(define (count-leaves x)
  (cond ((null? x) 0)
        ((not (pair? x)) 1)
        (else (+ (count-leaves (car x))
                 (count-leaves (cdr x))))))
;(map abs (list -10 2.5 -11 17))


;(define x (list 1 2 3))
;(define y (list 4 5 6))
;
;(append x y)
;(cons x y)
;(list x y)

(define (deep-reverse tree)
  (cond ((not (pair? tree)) tree)
        ((null? (cdr tree)) (deep-reverse (car tree)))
        (else (cons (deep-reverse (cdr tree)) (deep-reverse (car tree))))))


(define x (list (list 1 2) (list 3 4)))
;(define x (list (list 1 2 3) (list 3 4 (list 5 6))))
;(deep-reverse x)

(define (fringe tree)
  (cond ((null? tree) nil)
        ((not (pair? tree)) (cons tree nil))
        (else (append (fringe (car tree)) (fringe (cdr tree))))))