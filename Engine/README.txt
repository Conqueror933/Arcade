Stuff to add:

bitmap:
support different bmp formats
scaling of Text
kleinbuchstaben und satzzeichen
INCLUDE SPACE!   ---  currently done in GetLetterWidth

Menu:
	menu::label:
	add a "Style" Object for rounded corners and all that fancy stuff
make a checkbox-type button
make a slider-type button

Graphics:
BeginFrame()
removed clearing of sysbuffer for not having to redraw the background over and over again, if this causes problems, revert it
might actually be fine as long as you dont have moving stuff on the screen

Board.cpp:
Constructor, cellsize, problems with floating point math on ints and pixels and stuff
the recursion on Board::Cell::Update() might be going way deeper than it needs to
make Board adjust itself to screen center
Board.bottomright might just be terrible design, just define it by cellsize and cellcount, then let it adjust to the screen on its own
lastclicked happens to be drawn twice, board is designed shitty anyway, redesign in future

General:
maybe even just predefine some options in the optionsmenu
then i dont need to make the slider but just buttons, size: small, medium, big, done
it however is the cheap way out:
- then again to complex optionsmenu might be bad design for the game
- but its not actually about the game but to show my ability to program
	- could argue that that is a skill aswell, then again...


AI Levels:
1: just check for closed cell and pick random
2: previous working imperfect version of 3
3: make the best move possible