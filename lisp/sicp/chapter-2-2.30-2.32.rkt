#lang planet neil/sicp
(define (scale-tree tree factor)
  (map (lambda (sub-tree)
         (if (pair? sub-tree)
             (scale-tree sub-tree factor)
             (* sub-tree factor)))
       tree))

(define (tree-map proc tree)
  (map (lambda (sub-tree)
         (if (pair? sub-tree)
             (tree-map proc sub-tree)
             (proc sub-tree)))
  tree))
  

(define (squre-tree1 tree)
  (cond ((null? tree) nil)
        ((not (pair? tree)) (* tree tree))
        (else (cons (squre-tree1 (car tree))
                    (squre-tree1 (cdr tree))))))


(define (squre-tree2 tree)
  (map (lambda (sub-tree)
         (if (pair? sub-tree)
             (squre-tree2 sub-tree)
             (* sub-tree sub-tree)))
       tree))

(define (squre-tree3 tree) (tree-map (lambda (x) (* x x)) tree))

(define t (list 1 (list 2 (list 3 4) 5) (list 6 7)))

(squre-tree1 t)
(squre-tree2 t)
(squre-tree3 t)

(define (subsets s)
  (if (null? s)
      (list nil)
      (let ((rest (subsets (cdr s))))
        (append rest (map (lambda (sub) (cons (car s) sub))
                          rest)))))