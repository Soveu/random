(defvar *age* 17)
(format t "Your can")
(if (not (< *age* 18))
  (format t " vote~%")
  (format t "'t vote~%"))

(if (and (<= *age* 14) (>= *age* 67))
  (format t "Time for work~%")
  (format t "Work if u want~%"))

(if T
  (progn
    (format t "Multiple")
    (format t "Instructions"))
  (format t "Lorem ipsum"))

(defun get-school (age)
  (case age
    (5 (print "Kindergarten"))
    (6 (print "First Grade"))
    (otherwise (print "Middle School"))))

(terpri)

(cond ((>= *age* 18)
       (setf *college-ready* 'yes)
       (format t "Ready for college ~%"))
      ((< *age* 18)
       (setf *college-ready* 'no)
       (format t "Not ready~%"))
      (t
	(format t "Dont know ~%")))


