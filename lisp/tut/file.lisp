;;; ---------- FILE I O ----------

;;; Write text to a file
;;; A keyword symbol starts with a colon and it only means itself
(with-open-file (my-stream
				"test.txt"
				:direction :output ; We are writing to the file
				:if-exists :supersede) ; If the file exists delete it
	(princ "Some random Text" my-stream))

;;; Read data from a file
(let ((in (open "test.txt" :if-does-not-exist nil)))
   (when in
      (loop for line = (read-line in nil)
      while line do (format t "~a~%" line))
      (close in)
   )
)
