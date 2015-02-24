/ This is an example of how to use the sprite control file

/ In your code, you can create a Sprite by saying
/ Sprite s = Sprite("this file", renderer);

/ Slashes may be used for comments

/ You can create variables by using "?"
/ Arithmetic is not allowed on these variables so expressions like WIDTH/2 are invalid
/ However you can define WIDTH/2
/ I might add operations such as /, *, +, and - in the future

? WIDTH = 32
? WIDTH/2 = 16
? HEIGHT = 64
? HEIGHT/2 = 32

/ f= or file= or FILE= or F= will specify a file in the same directory
/ as the control file, additional backslashes and .. can be used to specify other directories
/ For example: ..\myimg.png will point to the image called myimg.png above
/ the folder of this file
/ 
/ The same image can be used for different sequences
/ All subsequent frames will use this file
/ It is possible to change the file by saying f= again

/ Quotes are optional are are needed for files which start or end in whitespaces

f = "res\y01uPOi.png"

/ A colon (:) is used to specify a sequence name, it is possible to
/ reuse a sequence name in order add more frames to that sequence
/ For example, ":walk up" will make all subsequent frames map to the "walk up" sequence
/ Notice how the colon is not included in the sequence name
/ Leading and trailing spaces will be ignored so ":walk up" is the same as ": walk up "

: walk up

/ The frame format is as follows:
/ The parameters in square brackets are optional
/ X, Y, WIDTH, HEIGHT, [X OFFSET, Y OFFSET], [DURATION OR LENGTH]
/ X OFFSET and Y OFFSET are used to render the frame from a point other than it's center
/ For example, an X OFFSET of WIDTH/2 and a Y OFFSET of HEIGHT/2 will render the frame at its center

/ X    Y    W        H        OFFX       OFFY        LEN
   0,   0,   WIDTH,   HEIGHT,   WIDTH/2,   HEIGHT/2,  30
  32,   0,   WIDTH,   HEIGHT,   WIDTH/2,   HEIGHT/2,   3
  64,   0,   WIDTH,   HEIGHT,   WIDTH/2,   HEIGHT/2,   3
  96,   0,   WIDTH,   HEIGHT,   WIDTH/2,   HEIGHT/2,   3
 128,   0,   WIDTH,   HEIGHT,   WIDTH/2,   HEIGHT/2,   3
 160,   0,   WIDTH,   HEIGHT,   WIDTH/2,   HEIGHT/2,   3
 192,   0,   WIDTH,   HEIGHT,   WIDTH/2,   HEIGHT/2,   3

/ A LEN of 0 or lesser means that the frame lasts forever
 224,   0,   WIDTH,   HEIGHT,   WIDTH/2,   HEIGHT/2,   0
                  
                  / Leading and trailing whitespaces are allowed
     :walk down

/ As stated before, it is possible to change the file at any time
f = res\Untitled.png

0,192,WIDTH,HEIGHT,3
32,192,WIDTH,HEIGHT,3
64,192,WIDTH,HEIGHT,3
96,192,WIDTH,HEIGHT,3


f = res\y01uPOi.png

128,192,WIDTH,HEIGHT,3
160,192,WIDTH,HEIGHT,3
192,192,WIDTH,HEIGHT,3
224,192,WIDTH,HEIGHT,3

/ A number by itself can be used to loop a smaller portion of the sequence
/ 
/ For example, a run sequence might have some startup frames before
/ the actual loop starts
/
/ The number that is put here tells the length of the loop
/ A value of 0 has no effect
/ A value of 1 or lesser has the same effect as creating a frame with infinite length
12

/ ">" sign combined with a colon will create a transition sequence
/ A transition sequence will play when changing from the first sequence to the second
/ An example of this might be a running sequence to a standing sequence
/ The sprite may slide before reaching the standing sequence

> walk up : walk right

   0,   0,   WIDTH,   HEIGHT,   15,   30
   0,   0,   WIDTH,   HEIGHT,   14,   28
   0,   0,   WIDTH,   HEIGHT,   13,   26
  32,   0,   WIDTH,   HEIGHT,   12,   24
  32,   0,   WIDTH,   HEIGHT,   11,   22
  64,   0,   WIDTH,   HEIGHT,   10,   20
  64,   0,   WIDTH,   HEIGHT,    9,   18
  96,   0,   WIDTH,   HEIGHT,    8,   16
  96,   0,   WIDTH,   HEIGHT,    7,   14
 128,   0,   WIDTH,   HEIGHT,    6,   12
 128,   0,   WIDTH,   HEIGHT,    5,   10
 160,   0,   WIDTH,   HEIGHT,    4,    8
 160,   0,   WIDTH,   HEIGHT,    3,    6
 192,   0,   WIDTH,   HEIGHT,    2,    4
 192,   0,   WIDTH,   HEIGHT,    1,    2

: walk left

	0,128,WIDTH,HEIGHT,3
	32,128,WIDTH,HEIGHT,3
	64,128,WIDTH,HEIGHT,3
	96,128,WIDTH,HEIGHT,3
	128,128,WIDTH,HEIGHT,3
	160,128,WIDTH,HEIGHT,3
	192,128,WIDTH,HEIGHT,3
	224,128,WIDTH,HEIGHT,3

: walk right

0,64,WIDTH,HEIGHT,3
32,64,WIDTH,HEIGHT,3
64,64,WIDTH,HEIGHT,3
96,64,WIDTH,HEIGHT,3
128,64,WIDTH,HEIGHT,3
160,64,WIDTH,HEIGHT,3
192,64,WIDTH,HEIGHT,3
224,64,WIDTH,HEIGHT,3