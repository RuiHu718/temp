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




