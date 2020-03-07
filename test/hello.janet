(use ../build/termbox)


(defer (shutdown)
	(init)	
	
	(def- row 20)
	(def- msg "hello world")
	
	(cell 0 row 0x2591 white red)

	(for col 0 (length msg)
		(cell (+ 1 col) row (msg col) black green))

	(cell (+ 1 (length msg)) row 0x2591 white red)

	(present)
	(poll-event (event))
	(poll-event (event))) #WHY???