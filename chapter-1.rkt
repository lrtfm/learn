#lang planet neil/sicp
; 1.30
(define (sum term a next b)
  (define (iter a result)
    (if (> a b) 
        result
        (iter (next a) (+ (term a) result))))
  (iter a 0))

(define (simpson f a b n)
  (define h (/ (- b a) n))
  (define (s-term i)
    (cond ((= i 0) (f (+ a (* i h))))
          ((= i n) (f b))
          ((even? i) (* 2 (f (+ a (* i h)))))
          (else (* 4 (f (+ a (* i h)))))))
  (* (/ h 3) (sum s-term 0 (lambda (x) (+ x 1)) n)))

; 1.31                   
(define (product term a next b)
  (define (iter a result)
    (if (> a b) 
        result
        (iter (next a) (* (term a) result))))
  (iter a 1))

;(define (product term a next b)
;  (if (> a b)
;      0
;      (+ (term a)
;         (product term (next a) next b))))

; 1.32
(define (accumulate combiner null-value term a next b)
  (define (iter a result)
    (if (> a b) 
        result
        (iter (next a) (combiner (term a) result))))
  (iter a null-value))

;(define (accumulate combiner null-value term a next b)
;  (define (accum a)
;    (if (> a b) 
;        null-value 
;        (combiner (term a)
;                  (accum (next a) next b))))
;  (accum a))

; 1.33
;(define (accumulate combiner null-value filter term a next b)
;  (define (iter a result)
;    (cond ((> a b) result)
;          ((filter a) (iter (next a) (combiner (term a) result)))
;          (else (iter (next a) result))))
;  (iter a null-value))

; 1.41
(define (double f)
  (lambda (x) (f (f x))))

; 1.42
(define (compose f g)
  (lambda (x) (f (g x))))

; 1.43
(define (repeated f n)
  (define (iter result f n)
    (cond ((= n 0) result)
          (even? (iter result (compose f) (/ n 2)))
          (else (iter (compose f result) (compose f) (/ (- n 1) 2)))))
  (iter (lambda (x) x) f n))

; 1.46
(define (iterative-improve good? imporve)
  (define (iter guess)
    (if (good? guess)
        guess
        (iter (imporve guess))))
  iter)  ; or (lambda (guess) (iter guess))

; chapter 1.2.5
(define (gcd a b)
  (if (= b 0)
      a
      (gcd b (remainder a b))))

(define (make-rat n d)
  (let ((g (gcd n d)))
    (cond ((and (< n 0) (> d 0)) (cons (- (/ n g)) (- (/ d g))))
          (else (cons (/ n g) (/ d g))))))


