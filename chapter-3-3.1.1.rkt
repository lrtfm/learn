#lang planet neil/sicp

(define balance 100)

(define (withdraw amount)
  (if (>= balance amount)
      (begin (set! balance (- balance amount))
             balance)
      "Insufficient funds"))

(withdraw 20)

(withdraw 90)

(define balance 20)
(define (new-withdraw sum)
  (let ((balance sum))
    (lambda (amount)
      (if (>= balance amount)
      (begin (set! balance (- balance amount))
             balance)
      "Insufficient funds"))))

