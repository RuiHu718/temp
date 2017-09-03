;; Function: celsius->fahrenheit
(define (celsius->fahrenheit celsius)
  (+ (* 1.8 celsius) 32))

;; Function: leap-year?
(define (leap-year? year)
  (or (and (zero? (remainder year 4))
	   (not (zero? (remainder year 100))))
      (zero? (remainder year 400))))

;; Function: factorial
(define (factorial n)
  (if (zero? n) 1
      (* n (factorial (- n 1)))))

;; Function: fibonacci
(define (fibonacci n)
  (if (< n 2) n
      (+ (fibonacci (- n 1))
	 (fibonacci (- n 2)))))

(define (fast-fibonacci-helper n base-0 base-1)
  (cond ((zero? n) base-0)
	((zero? (- n 1)) base-1)
	(else (fast-fibonacci-helper (- n 1) base-1 (+ base-0 base-1)))))

;; Function: fast-fibonacci
(define (fast-fibonacci n)
  (fast-fibonacci-helper n 0 1))

;; Function: sum
(define (sum ls)
  (if (null? ls) 0
      (+ (car ls) (sum (cdr ls)))))

;; Function: triple-everything
(define (triple-everything numbers)
  (if (null? numbers) '()
      (cons (* 3 (car numbers)) (triple-everything (cdr numbers)))))

(define (generate-concatenations-using strings accum)
  (if (null? strings) '()
      (cons (string-append accum (car strings))
	    (generate-concatenations-using (cdr strings)
					   (string-append accum (car strings))))))

;; Function: generate-partial-concatenations
(define (generate-concatenations strings)
  (generate-concatenations-using strings ""))

;; Function: pwr
;; using let
(define (pwr base exponent)
  (if (zero? exponent) 1
      (let ((root (pwr base (quotient exponent 2))))
	(if (zero? (remainder exponent 2))
	    (* root root)
	    (* root root base)))))

;; Function: flatten
(define (flatten sequence)
  (cond ((null? sequence) '())
	((list? (car sequence)) (append (flatten (car sequence))
					(flatten (cdr sequence))))
	 (else (cons (car sequence) (flatten (cdr sequence))))))

;; Function: partition
(define (partition pivot num-list)
  (if (null? num-list) '(() ())
      (let ((split-of-rest (partition pivot (cdr num-list))))
	(if (< (car num-list) pivot)
	    (list (cons (car num-list) (car split-of-rest))
		  (cadr split-of-rest))
	    (list (car split-of-rest)
		  (cons (car num-list) (car (cdr split-of-rest))))))))

;; Function: quicksort
(define (quicksort num-list)
  (if (<= (length num-list) 1) num-list
      (let ((split (partition (car num-list) (cdr num-list))))
	(append (quicksort (car split))
		(list (car num-list))
		(quicksort (cadr split))))))

;; Function: sorted?
;; demonstrates the use of function as data
(define (sorted? sequence comp)
  (or (< (length sequence) 2)
      (and (comp (car sequence) (cadr sequence))
	   (sorted? (cdr sequence) comp))))

;; Function: merge
(define (merge list1 list2 comp)
  (cond ((null? list1) list2)
	((null? list2) list1)
	((comp (car list1) (car list2))
	 (cons (car list1)
	       (merge (cdr list1) list2 comp)))
	 (else
	  (cons (car list2)
		(merge list1 (cdr list2) comp)))))

;; Function: prefix-of-list
(define (prefix-of-list ls k)
  (if (or (zero? k) (null? ls)) '()
      (cons (car ls) (prefix-of-list (cdr ls) (- k 1)))))

;; Function: mergesort
(define (mergesort ls comp)
  (if (<= (length ls) 1) ls
      (let ((front-length (quotient (length ls) 2))
	    (back-length (- (length ls) (quotient (length ls) 2))))
	(merge (mergesort (prefix-of-list ls front-length) comp)
	       (mergesort (prefix-of-list (reverse ls) back-length) comp)
	       comp))))

;; Function: distance-from-origin
(define (distance-from-origin pt)
  (sqrt (+ (* (car pt) (car pt))
	   (* (cadr pt) (cadr pt)))))

;; Function: distance-from-origin<?
(define (distance-from-origin<? pt1 pt2)
  (< (distance-from-origin pt1)
     (distance-from-origin pt2)))

;; Function: unary-map
(define (unary-map fn seq)
  (if (null? seq) '()
      (cons (fn (car seq)) (unary-map fn (cdr seq)))))

;; Function: average
(define (average num-list)
  (/ (apply + num-list) (length num-list)))

;; Function: depth
(define (depth tree)
  (if (or (not (list? tree)) (null? tree)) 0
      (+ 1 (apply max (map depth tree)))))

;; Function: flatten-list
(define (flatten-list ls)
  (cond ((null? ls) '())
	((not (list? ls)) (list ls))
	(else (apply append (map flatten-list ls)))))

;; Function: translate
(define (translate numbers delta)
  (define (shift number)
    (+ number delta))
  (map shift numbers))

;; Function: translate2
(define (translate2 numbers delta)
  (map (lambda (number) (+ number delta)) numbers))

;; Function: power-set
(define (power-set set)
  (if (null? set) '(())
      (let ((power-set-of-rest (power-set (cdr set))))
	(append power-set-of-rest
		(map (lambda (subset) (cons (car set) subset))
		     power-set-of-rest)))))

;; Function: remove
(define (remove ls elem)
  (cond ((null? ls) '())
	((equal? (car ls) elem) (remove (cdr ls) elem))
	(else (cons (car ls) (remove (cdr ls) elem)))))

;; Function: permutations
(define (permutations items)
  (if (null? items) '(())
      (apply append
	     (map (lambda (element)
		    (map (lambda (permutation)
			   (cons element permutation))
			 (permutations (remove items element))))
		  items))))

;; Function: generic-map
(define (generic-map fn primary-list . other-lists)
  (if (null? primary-list) '()
      (cons (apply fn (cons (car primary-list) (unary-map car other-lists)))
	    (apply generic-map (cons fn (cons (cdr primary-list)
				     (unary-map cdr other-lists)))))))







