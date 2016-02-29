#lang planet neil/sicp

; 2.6
(define zero (lambda (f) (lambda (x) x)))

(define (add-1 n)
  (lambda (f) (lambda (x) (f ((n f) x)))))

(define one (lambda (f) (lambda (x) (f x))))

(define two (lambda (f) (lambda (x) (f (f x)))))

(define (add-v1 m n)
  (lambda (f) (lambda (x) ((m f) ((n f) x)))))

; from http://community.schemewiki.org/?sicp-ex-2.6
(define (add-v2 m n)
  ((m add-1) n))



