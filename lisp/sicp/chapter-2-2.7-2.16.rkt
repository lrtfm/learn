#lang planet neil/sicp

; suppose all number are positive

(define (make-interval a b) (cons a b))

(define (upper-bound x)
  (max (car x) (cdr x)))

(define (lower-bound x)
  (min (car x) (cdr x)))

(define (make-center-width c w)
  (make-interval (- c w) (+ c w)))

(define (make-center-percent c p)
  (let ((w (* c p)))
    (make-center-width c w)))

; test
;(make-center-percent 3 0.01)

(define (center i)
  (/ (+ (lower-bound i) (upper-bound i)) 2))

(define (width i)
  (/ (- (upper-bound i) (lower-bound i)) 2))

(define (percent i)
  (/ (width i) (center i)))

(define (add-interval x y)
  (make-interval (+ (lower-bound x) (lower-bound y))
                 (+ (upper-bound x) (upper-bound y))))

; test add-interval
;(add-interval (make-interval 1 3) (make-interval 2 4))
;test end

;#|
(define (mul-interval x y)
  (let ((p1 (* (lower-bound x) (lower-bound y)))
        (p2 (* (lower-bound x) (upper-bound y)))
        (p3 (* (upper-bound x) (lower-bound y)))
        (p4 (* (upper-bound x) (upper-bound y))))
    (make-interval (min p1 p2 p3 p4)
                   (max p1 p2 p3 p4))))
;|#
#|
(define (mul-interval x y)
  (let ((px (percent x))
        (cx (center x))
        (py (percent y))
        (cy (center y)))
    (make-center-percent (* cx cy) (+ px py))))
|#
; test mul-interval
;(percent (make-interval 1 3))
;(mul-interval (make-interval 1 3) (make-interval 2 4))
; test end

(define (div-interval x y)
  (mul-interval x
                (make-interval (/ 1.0 (upper-bound y))
                               (/ 1.0 (lower-bound y)))))

(define (par1 r1 r2)
  (div-interval (mul-interval r1 r2)
                (add-interval r1 r2)))

(define (par2 r1 r2)
  (let ((one (make-interval 1 1)))
    (div-interval one
                  (add-interval (div-interval one r1)
                                (div-interval one r2)))))


(par1 (make-center-percent 2 0.01)
      (make-center-percent 3 0.01))

(par2 (make-center-percent 2 0.01)
      (make-center-percent 3 0.01)) 


(par1 (make-center-percent 2 0.05)
      (make-center-percent 3 0.05))

(par2 (make-center-percent 2 0.05)
      (make-center-percent 3 0.05)) 
(par1 (make-center-percent 200 0.05)
      (make-center-percent 3 0.05))

(par2 (make-center-percent 200 0.05)
      (make-center-percent 3 0.05))

(par1 (make-center-percent 2000000000000000000 0.1)
      (make-center-percent 300 0.05))

(par2 (make-center-percent 2000000000000000000 0.1)
      (make-center-percent 300 0.05))

