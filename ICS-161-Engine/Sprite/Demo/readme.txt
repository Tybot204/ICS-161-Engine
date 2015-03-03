/ This is an example of how to use the sprite control file

/ In your code, you can create a Sprite by saying
/ Sprite s = Sprite(initialX, initialY, "this file", renderer);

/ Slashes may be used for comments

/ You can create variables by using "?"
/ Operations such as /, *, +, and - are allowed but are evaluated in left to right order

? WIDTH = 32
? HEIGHT = 64

/ f= or file= or FILE= or F= will specify a file in the same directory
/ as the control file, additional backslashes and .. can be used to specify other directories
/ For example: ..\myimg.png will point to the image called myimg.png above
/ the folder of this file
/ 
/ The same image can be used for different sequences
/ All subsequent frames will use this file
/ It is possible to change the file by saying f= again

/ Quotes are optional but are required for files which start or end in whitespaces

f = "res\y01uPOi.png"

/ A colon (:) is used to specify a sequence name, it is possible to
/ reuse a sequence name in order add more frames to that sequence
/ For example, ":walk up" will make all subsequent frames map to the "walk up" sequence
/ Notice how the colon is not included in the sequence name
/ Leading and trailing spaces will be ignored so ":walk up" is the same as ": walk up "

: walk up

/ The frame format is as follows:
/ All hitboxes for that frame
/ To denote a hitbox, use the ! symbol
/ The hitbox format is X, Y, W, H (X and Y are relative to the Sprite's upper-left corner)
/ All options are required

/ X, Y, W, H
! 8, 9,16,14
!13,20, 5,28
! 8,27,16, 8
! 8,44,15,12

/ After setting up the hitboxes, now you have to specify the dimensions and duration of the frame

/ The parameters in square brackets are optional
/ X, Y, [WIDTH, HEIGHT, [X OFFSET, Y OFFSET]], [DURATION OR LENGTH]
/ You must spcify a WIDTH and HEIGHT in order to specify an X OFFSET and Y OFFSET

/ You can leave options blank or leave them out entirely to use the default
/ The default WIDTH and HEIGHT will be the last used
/ The default X OFFSET and Y OFFSET will be the last used
/ The default LEN will be 1

/ X OFFSET and Y OFFSET are used to render the frame from a point other than it's center
/ For example, an X OFFSET of WIDTH/2 and a Y OFFSET of HEIGHT/2 will render the frame at its center

/ X    Y    W        H        OFFX         OFFY         LEN
   0,   0,   WIDTH,   HEIGHT,   WIDTH / 2,   HEIGHT / 2,  30

!9,10,14,13
!14,21,5,35
!11,39,6,9
!9,25,15,7
  32,   0,        ,         ,   WIDTH / 2,   HEIGHT / 2,   3

/ X    Y    W        H        LEN
!10,10,12,12
!6,20,18,8
!14,23,5,29
!11,37,5,7
  64,   0,   WIDTH,   HEIGHT,   3

!12,10,12,11
!16,18,4,21
!11,23,15,5
!13,35,10,12
  96,   0,        ,         ,   3

/ X    Y   LEN
!12,11,10,11
!10,21,13,9
!12,28,6,27
!16,34,5,14
 128,   0,   3

!171-160,10,10,11
!174-160,18,4,19
!8,23,16,7
!11,34,5,17
!17,34,5,12
 160,   0,   3

!204-192,11,10,10
!207-192,18,4,20
!202-192,23,12,7
!205-192,35,4,17
!210-192,33,4,10
 192,   0,   3

!10,11,13,10
!238-224,18,3,20
!232-224,25,9,6
!239-224,24,8,5
!235-224,35,4,12
!240-224,36,3,11
/ A LEN of 0 or lesser means that the frame lasts forever
 224,   0,   WIDTH,   HEIGHT,   WIDTH/2,   HEIGHT/2,   0
                  
                  / Leading and trailing whitespaces are allowed
     :walk down

/ As stated before, it is possible to change the file at any time
f = res\Untitled.png

0,192,WIDTH,HEIGHT,3
32,192,3
64,192,3
96,192,3

f = res\y01uPOi.png

!12,11-2,10,11
!10,21-2,13,9
!12,28-2,6,27
!16,34-2,5,14
128,192,3

!171-160,10-2,10,11
!174-160,18-2,4,19
!8,23-2,16,7
!11,34-2,5,17
!17,34-2,5,12
160,192,3

!204-192,11-2,10,10
!207-192,18-2,4,20
!202-192,23-2,12,7
!205-192,35-2,4,17
!210-192,33-2,4,10
192,192,3

!10,11-2,13,10
!238-224,18-2,3,20
!232-224,25-2,9,6
!239-224,24-2,8,5
!235-224,35-2,4,12
!240-224,36-2,3,11
224,192,3

/ A number by itself can be used to loop a smaller portion of the sequence
/ 
/ For example, a run sequence might have some startup frames before
/ the actual loop starts
/
/ The number that is put here tells the length of the loop
/ A value of 1 or lesser has the same effect as creating a frame with infinite length
12

/ ">" sign combined with a colon will create a transition sequence
/ A transition sequence will play when changing from the first sequence to the second
/ An example of this might be a running sequence to a standing sequence
/ The sprite may slide before reaching the standing sequence

> walk up : walk right

   0,   0,   ,   ,   15,   30
   0,   0,   ,   ,   14,   28
   0,   0,   ,   ,   13,   26
  32,   0,   ,   ,   12,   24
  32,   0,   ,   ,   11,   22
  64,   0,   ,   ,   10,   20
  64,   0,   ,   ,    9,   18
  96,   0,   ,   ,    8,   16
  96,   0,   ,   ,    7,   14
 128,   0,   ,   ,    6,   12
 128,   0,   ,   ,    5,   10
 160,   0,   ,   ,    4,    8
 160,   0,   ,   ,    3,    6
 192,   0,   ,   ,    2,    4
 192,   0,   ,   ,    1,    2

: walk left

0,128,,,0,0,3
32,128,3
64,128,3
96,128,3
128,128,3
160,128,3
192,128,3
224,128,3

: walk right

0,64,3
32,64,3
64,64,3
96,64,3
128,64,3
160,64,3
192,64,3
224,64,3

> walk down : walk right

   0,   0,   ,   ,   15,   30
   0,   0,   ,   ,   14,   28
   0,   0,   ,   ,   13,   26
  32,   0,   ,   ,   12,   24
  32,   0,   ,   ,   11,   22
  64,   0,   ,   ,   10,   20
  64,   0,   ,   ,    9,   18
  96,   0,   ,   ,    8,   16
  96,   0,   ,   ,    7,   14
 128,   0,   ,   ,    6,   12
 128,   0,   ,   ,    5,   10
 160,   0,   ,   ,    4,    8
 160,   0,   ,   ,    3,    6
 192,   0,   ,   ,    2,    4
 192,   0,   ,   ,    1,    2

> walk down : walk left

   0,   0,   ,   ,   15,   30
   0,   0,   ,   ,   14,   28
   0,   0,   ,   ,   13,   26
  32,   0,   ,   ,   12,   24
  32,   0,   ,   ,   11,   22
  64,   0,   ,   ,   10,   20
  64,   0,   ,   ,    9,   18
  96,   0,   ,   ,    8,   16
  96,   0,   ,   ,    7,   14
 128,   0,   ,   ,    6,   12
 128,   0,   ,   ,    5,   10
 160,   0,   ,   ,    4,    8
 160,   0,   ,   ,    3,    6
 192,   0,   ,   ,    2,    4
 192,   0,   ,   ,    1,    2

> walk up : walk left

   0,   0,   ,   ,   15,   30
   0,   0,   ,   ,   14,   28
   0,   0,   ,   ,   13,   26
  32,   0,   ,   ,   12,   24
  32,   0,   ,   ,   11,   22
  64,   0,   ,   ,   10,   20
  64,   0,   ,   ,    9,   18
  96,   0,   ,   ,    8,   16
  96,   0,   ,   ,    7,   14
 128,   0,   ,   ,    6,   12
 128,   0,   ,   ,    5,   10
 160,   0,   ,   ,    4,    8
 160,   0,   ,   ,    3,    6
 192,   0,   ,   ,    2,    4
 192,   0,   ,   ,    1,    2