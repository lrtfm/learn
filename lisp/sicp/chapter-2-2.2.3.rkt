#lang planet neil/sicp
(define square (lambda (x) (* x x)))

(define (sum-odd-squares tree)
  (cond ((null? tree) 0)
        ((not (pair? tree))
         (if (odd? tree) (square tree) 0))
        (else (+ (sum-odd-squares (car tree))
                 (sum-odd-squares (cdr tree))))))

(define (enumerate-tree tree)
  (cond ((null? tree) nil)
        ((not (pair? tree)) (cons tree nil))
        (else (append (enumerate-tree (car tree))
                      (enumerate-tree (cdr tree))))))

(define (filter predicate sequence)
  (cond ((null? sequence) nil)
        ((predicate (car sequence))
         (cons (car sequence)
               (filter predicate (cdr sequence))))
        (else (filter predicate (cdr sequence)))))

(define (accumulate op initial sequence)
  (if (null? sequence)
      initial
      (op (car sequence)
          (accumulate op initial (cdr sequence)))))

(accumulate + 0 (list 1 2 3 4))

(define (sum-odd-squares2 tree)
  (accumulate +
              0
              (map square
                   (filter odd?
                           (enumerate-tree tree)))))


(define (accumulate-n op init seqs)
  (if (null? (car seqs))
      nil
      (cons (accumulate op init (map car seqs))
            (accumulate-n op init (map cdr seqs)))))

(define s (list (list 1 2 3) (list 4 5 6) (list 7 8 9)))
(accumulate-n cons nil s)

(define (dot-product v w)
  (accumulate +
              0
              (accumulate-n * 1 (list v w))))

(define (matrix-*-vector m v)
  (map (lambda (w) (dot-product w v))
       m))

(define (matrix-*-matrix m n)
  (map (lambda (w)
         (matrix-*-vector (accumulate-n cons nil n) w))
       m))

(define (transpose m)
  (accumulate-n cons nil m))

(define x (list 1 2 3))
(define y (list 4 5 6))
(dot-product x y)
(matrix-*-vector s x)
(matrix-*-matrix s s)
(transpose (list x))

(define fold-right accumulate)
(define (fold-left op initial sequence)
  (define (iter result rest)
    (if (null? rest)
        result
        (iter (op result (car rest))
              (cdr rest))))
  (iter initial sequence))

(fold-right / 1 x)
(fold-left / 1 x)
(fold-right list nil x)
(fold-left list nil x)
(fold-right * 1 x)
(fold-left * 1 x)