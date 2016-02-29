#lang planet neil/sicp

(define (make-mobile left right)
  (list left right))

(define (make-branch length structure)
  (list length structure))

(define (left-branch mobile)
  (car mobile))
(define (right-branch mobile)
  (car (cdr mobile)))

(define (branch-length branch)
  (car branch))
(define (branch-structure branch)
  (car (cdr branch)))


(define (total-weight mobile)
  (if (not (pair? mobile))
      mobile
      (+ (total-weight (branch-structure (left-branch mobile)))
         (total-weight (branch-structure (right-branch mobile))))))

(define (balance? mobile)
  (if (not (pair? mobile))
      true
      (let ((l (branch-structure (left-branch mobile)))
            (r (branch-structure (right-branch mobile))))
        (and (balance? l)
             (balance? r)
             (= (* (total-weight l) (branch-length (left-branch mobile)))
                (* (total-weight r) (branch-length (right-branch mobile))))))))


(define x (make-mobile (make-branch 6 3) (make-branch 9 2)))

(define y (make-branch 4 5))
(define z (make-branch 4 x)) 
(balance? x)
(balance? (make-mobile y z))