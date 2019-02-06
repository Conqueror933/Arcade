Stuff to add:

bitmap:
support different bmp formats
scaling of Text
kleinbuchstaben und satzzeichen
INCLUDE SPACE!   ---  currently done in GetLetterWidth

menu::label:
add a "Style" Object for rounded corners and all that fancy stuff

Graphics:
BeginFrame()
removed clearing of sysbuffer for not having to redraw the background over and over again, if this causes problems, revert it
might actually be fine as long as you dont have moving stuff on the screen

Board.cpp:
Constructor, cellsize, problems with floating point math on ints and pixels and stuff
the recursion on Board::Cell::Update() might be going way deeper than it needs to
make Board adjust itself to screen center

AI Levels:
1: just check for closed cell and pick random
2: previous working imperfect version of 3
3: make the best move possible