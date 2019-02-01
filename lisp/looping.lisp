;;;; Comment
;;; Comment
;; Comment
; Comment

#||
Multiline
||#

;;; prints newline

(print "Hello there")

(setq *print-case* :capitalize)

(loop for x from 1 to 10 do 
      (print x))

(terpri)

(setq x 1)
(loop
  (format t "~d~%" x)
  (setq x (+ x 1))
  (when (> x 10) (return x)))

(loop for x in '(Peter Mary Paul) do
      (format t "~s~%" x))
