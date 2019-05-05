Stuff to add:

*************************************GENERAL:*************************************
maybe even just predefine some options in the optionsmenu
then i dont need to make the slider but just buttons, size: small, medium, big, done
it however is the cheap way out:
- then again to complex optionsmenu might be bad design for the game
- but its not actually about the game but to show my ability to program
	- could argue that that is a skill aswell, then again...

*************************************FEATURES:*************************************
bitmap:
support different bmp formats
scaling of Text
kleinbuchstaben und satzzeichen
INCLUDE SPACE!   ---  currently done in GetLetterWidth

*************************************KAESEKAESTCHEN:*************************************
Board:
Square doesnt actually behave like it should, it should still adjust to screensize, just with keeping the cells...well square

AI:
while making Medium and part Hard AI broke the Easy AI somehow

AI Levels:
1: just check for closed cell and pick random
2: previous working imperfect version of 3
3: make the best move possible

tried adding a 'surrender'-button, turns out that would require a total rework

*************************************SNAKE:*************************************
Snake:
controls are weirdly delayed, super annoying
	- decouple input from timestep

*************************************MENU:*************************************
Menu:
	menu::label:
	add a "Style" Object for rounded corners and all that fancy stuff
make a checkbox-type button
make a slider-type button
Snake Button doesn't work after first time playing snake || mouse.Flush() could solve this
make hit detection more efficient

newMenu:
make Button (and Label) its on full class outside of Menu
	- should make buttons available everywhere, want a "concede" Button in your game, have one!
change Button behaviour away from gigantic switch
	- either via inheritance
	- or via Functors

public Menu : public Owner

i need the menu to be able to create a button and set its behaviour
	- have a base button, handling the drawing, with a templated Update() function in which the menu can stick its functor

	make in worldobject a worldowner interface class to then pass a pointer to that into the button Update
what if i make a public subclass in menu that implements the static Get...() and then inherit from that outside the class