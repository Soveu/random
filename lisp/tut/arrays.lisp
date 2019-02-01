
;;; ---------- ARRAYS ----------

;;; Create an array with 3 storage areas
(defparameter names (make-array 3))
;;; Add a value to an array
(setf (aref names 1) 'Bob)
;;; Get a value in an index
(aref names 1)
;;; Make a 3 by 3 array
(setf num-array (make-array '(3 3)
	:initial-contents '((0 1 2) (3 4 5) (6 7 8))))
;;; Cycle through and print the array
(dotimes (x 3)
	(dotimes (y 3)
		(print (aref num-array x y))
	)
)

;;; ---------- HASH TABLE ----------
;;; A collection of key value pairs

;;; Create a hash table
(defparameter people (make-hash-table))
;;; Set the key as 102 and the value to Paul Smith
(setf (gethash '102 people) '(Paul Smith))
(setf (gethash '103 people) '(Sam Smith))
;;; Get the value stored in the key 102
(gethash '102 people)
;;; maphash executes a function on each item
;;; ~% = newline
(maphash #'(lambda (k v) (format t "~a = ~a~%" k v)) people)
;;; Remove an entry with the key
(remhash '103 people)
