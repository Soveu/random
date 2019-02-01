(defun sum (a)
  (setq ret 0.0)
  (dolist (x a)
    (setq ret (+ ret x)))
  ret)

(defun len (a)
  (setq ret 0)
  (dolist (x a)
    (setq ret (+ ret 1)))
  ret)

(defun avg (&rest a)
  (/ (sum a) (len a)))


(format t "~a ~%" (avg 1 2 3 4))

(format t "A number ~a~%" (mapcar #'numberp '(1 2 3 f g)))

(defun dif (a b)
  (return-from dif(- a b)))
(format t "Return-from dif: ~a~%" (dif 5 2))

;;; You can define functions local only to the flet body
;;; (flet ((func-name (arguments)
;;;	... Function Body ...))
;;;	... Body ...)

(flet ((double-it (num)
		(* num 2)))
		(double-it 10))

;;; You can have multiple functions in flet
(flet ((double-it (num)
		(* num 2))
		(triple-it (num)
		(* num 3)))
		(format t "Double & Triple 10 = ~d~%" (triple-it (double-it 10)))
)

;;; labels is used when you want to have a function call itself, or if you want
;;; to be able to call another local function inside a function
(labels ((double-it (num)
			(* num 2))
		(triple-it (num)
			(* (double-it num) 3)))
		(format t "Double & Triple 3 = ~d~%" (triple-it 3))
)

;;; Return multiple values from a function
(defun squares (num)
	(values (expt num 2) (expt num 3)))

;;; Get multiple values from a function
(multiple-value-bind (a b) (squares 2)
	(format t "2^2 = ~d  2^3 = ~d~%" a b)
)

;;; Higher Order Functions
;;; You can use functions as data

(defun times-3 (x) (* 3 x))
(defun times-4 (x) (* 4 x))

;;; Pass in the function without attributes just like a variable
(defun multiples (mult-func max-num)

	;; Cycle through values up to the max supplied
	(dotimes (x max-num)

		;; funcall is used when you know the number of arguments
		(format t "~d : ~d~%" x (funcall mult-func x))
))

(multiples #'times-3 10)
(multiples #'times-4 10)

;;; ---------- LAMBDA ----------

;;; The lambda command allows you to create a function without giving it a name
;;; You can also pass this function just like you pass variables

;;; Multiply every item in a list
(mapcar (lambda (x) (* x 2)) '(1 2 3 4 5))

;;; ---------- MACROS ----------
;;; A function runs when it is called to execute, while a macro is compiled
;;; first and is available immediately like any other lisp built in function
;;; Macros are functions used to generate code rather then perform actions

(defvar *num* 2)
(defvar *num-2* 0)

;;; It can be irritating to have to use progn with if
(if (= *num* 2)
	(progn
		(setf *num-2* 2)
		(format t "*num-2* = ~d ~%" *num-2*)
	)
	(format t "Not equal to 2 ~%"))

(defmacro ifit (condition &rest body)

	;;; The backquote generates the code
	;;; The , changes the condition to code mode from data mode
	;;; The &rest body parameter will hold commands in a list
	;;; The "Can't Drive" Works as the else

	`(if ,condition (progn ,@body) (format t "Can't Drive ~%") ))

(setf *age* 16)

(ifit (>= *age* 16)
	(print "You are over 16")
	(print "Time to Drive")
	(terpri)
)

;;; let can also get confusing with its parentheses

(defun add (num1 num2)
	(let ((sum (+ num1 num2)))
		(format t "~a + ~a = ~a ~%" num1 num2 sum)))

;;; Define a macro to clean up let

(defmacro letx (var val &body body)
	`(let ((,var ,val)) ,@body))

(defun subtract (num1 num2)
	(letx dif (- num1 num2)
		(format t "~a - ~a = ~a ~%" num1 num2 dif)))

(subtract 10 6)
