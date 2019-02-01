(defclass Animal ()
  (name
   sound))

(defparameter dog (make-instance 'Animal))
(setf (slot-value dog 'name) "Spot")
(setf (slot-value dog 'sound) "Woof")
(format t "~a says ~a ~%"
	(slot-value dog 'name)
	(slot-value dog 'sound))

(defclass Mammal ()
  ((name
     :initarg :name
     :initform (error "Must provide a name"))
   (sound
     :initarg :sound
     :initform "No sound"
     :accessor mammal-sound)))

(defparameter *king-kong*
  (make-instance 'Mammal :name "King Kong" :sound "Rawwwr"))

(defgeneric make-sound (Mammal))
(defmethod make-sound((the-mammal Mammal))
  (format t "~a says ~a~%"
	  (slot-value the-mammal 'name)
	  (slot-value the-mammal 'sound)))

(make-sound *king-kong*)

;;; You can define your own getters and setters
;;; Define setter
(defgeneric (setf mammal-name) (value the-mammal))
(defmethod (setf mammal-name) (value (the-mammal mammal))
	(setf (slot-value the-mammal 'name) value))

;;; Define getter
(defgeneric mammal-name (the-mammal))
(defmethod mammal-name ((the-mammal mammal))
	(slot-value the-mammal 'name))
(setf (mammal-name *king-kong*) "Kong")
(format t "I am ~a ~%" (mammal-name *king-kong*))

;;; Use the auto generated sound getters and setters instead
(setf (mammal-sound *king-kong*) "Rawwwwwwwwr")
(format t "I say ~a ~%" (mammal-sound *king-kong*))

;; Inheritance
(defclass Dog (Mammal)
  ())
(defparameter rover
  (make-instance 'Dog :name "Rover" :sound "Woof"))
(make-sound rover)



;;; ---------- STRUCTURES ----------
;;; A user defined data type with multiple different data types
 
;;; Define the data names in the struct
(defstruct customer name address id)
 
;;; Store data in the struct
(setq paulsmith (make-customer 
	:name "Paul Smith"
	:address "123 Main St"
	:id 1000
))
 
;;; Get a value stored
(customer-name paulsmith)
 
;;; Change a value in the struct
(setf (customer-address paulsmith) "125 Main St")
(write paulsmith)
 
(setq sally-smith-1001 (make-customer 
	:name "Sally Smith"
	:address "123 Main St"
	:id 1001
))
