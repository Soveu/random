;;;; Comment
;;; Comment
;; Comment this is indented with code
; Comment after a line of code

#||
Multiline
||#

;;; ~% prints newline

(print "What's your name")
(defvar *name* (read))
(defun hello-you (name)
  (format t "Hello ~a! ~%" name))

#||
~a shows value
~s shows quotes around the value
;;;(setq *print-case* :capitalize) ;;;;upcase downcase
||#

(hello-you *name*)

(defvar *num* (+ 5 4))
(setf *num* (+ *num* (+ 5 (- 3 2))))

(format t "Number with commas ~:d~%" 1000000)
(format t "Pi to 5 characters ~5f~%" 3.141593)
(format t "Pi to 4 decimals ~,4f~%" 3.141593)
(format t "10 Percent ~,,2f~%" .10)
(format t "Dollars ~$ ~%" *num*)

(defun increment (n)
  (+ n 1))
(format t "After increment: ~d~%" (increment *num*))

(defun add (a b)
  (+ a b))
(format t "(add 12 13) = ~d~%" (add 12 13))

(format t "(/ 5 4) = ~d~%" (/ 5 4))
(format t "(/ 5 4.0) = ~d~%" (/ 5 4.0))

(defparameter *name* *name*)
(format t "(eq *name* 'Soveu) = ~d~%" (eq *name* 'Soveu))
(format t "(eq \"Soveu\" \"SoVeU\") = ~d~%" (eq "Soveu" "SoVeU"))
(format t "(eq 'kkk \"kkk\") = ~d~%" (eq 'kkk "kkk"))
(format t "(equalp 'kkk \"kkk\") = ~d~%" (equalp 'kkk "kkk"))
(format t "(eq 1 1.0) = ~d~%" (eq 1 1.0))
(format t "(equalp 1 1.0) = ~d~%" (equalp 1 1.0))

(write '(* 2 3))

