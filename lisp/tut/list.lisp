(setq *print-case* :capitalize)

(format t "First = ~a~%" (car '(superman batman aquaman))) ;;;car cdr cadr
;;;a gets item, d 'deletes' it

(setq nums (list 2 4 6))
(push 3 nums)
;;(setq (nth 3 nums) 1) ;;does not work
(format t "Is 3 in list = ~a ~%" (if (member 3 nums) 't nil))

(defvar superman (list :name "Superman" :secret "Clark Kent"))
(defvar soveu (list :name "Soveu" :secret "Tomasz Marx"))
(defvar herolist nil)
(push superman herolist)
(push soveu herolist)
(dolist (hero herolist)
  (format t "~{~a : ~a ~}~%" hero))

(defparameter heroes
  '((Superman (Clark Kent))
    (Flash (Barry Allen))
    (Batman (Bruce Wayne))))

(format t "Superman Data ~a ~%" (cadr (assoc 'superman heroes)))


