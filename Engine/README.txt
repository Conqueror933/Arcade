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