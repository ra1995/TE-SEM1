(defvar A)
(defvar B)
(defvar C)
(defvar D)

(defun :bits(value &optional (size 64))
	(format t "~v,'~B ~%" size value))

(loop

(terpri)	
(write-line "Enter first num :")
(setq A (read))
(:bits A)

(terpri)
(write-line "Enter second num :")
(setq B (read))
(:bits B)

(sb-thread:make-thread (lambda () (progn (sleep 0)
(write-line "Addition :")
(setq C (+ A B))
(write C)
(terpri)
(:bits C))))

(sb-thread:make-thread (lambda () (progn (sleep 2)
(write-line "Subtraction :")
(setq C (- A B))
(write C)
(terpri)
(:bits C))))

(sb-thread:make-thread (lambda () (progn (sleep 4)
(write-line "Multiplication :")
(setq C (* A B))
(write C)
(terpri)
(:bits C))))

(sb-thread:make-thread (lambda () (progn (sleep 6)
(write-line "Division :")
(setq C (/ A B))
(write C)
(terpri)
(:bits C))))

(terpri)
(progn (sleep 8)
(write-line "Do you wan to continue (y=1/n=2) :")
(setq D (read))
(if (= D 2)(exit))
(when (= D 1)))
