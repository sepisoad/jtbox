(use ../build/termbox)


(var col 1)

(init)
(clear)

(cell 0 20 0x2591 white red)

(each ch "hello world" 
	(cell col 20 ch black green)
	(set col (+ 1 col)))

(cell 12 20 0x2591 white red)

(present)
(poll-event (event))
(poll-event (event)) #WHY???


(shutdown)
