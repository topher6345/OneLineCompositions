One Line Compositions
=====================
With one line of C code, you can create interesting musical compositions. 

Like in the video [Experimental Music from very short C programs.](http://www.youtube.com/watch?v=GtQdIYUtAHg&feature=share&list=TLbvWv3pviCO4)

This program provides the Port Audio boilerplate for writing algorithmic music with this technique. 

[More information](http://countercomplex.blogspot.com/2011/10/algorithmic-symphonies-from-one-line-of.html)

##How it works

An equation such as this : 

```c 
t*((t>>12|t>>2)&63&t>>4)
````

with the variable 't' incrementing at the sample rate, 

and the results piped directly to the DAC,

sounds musical.

## To compile

``` bash
make
```

## To hear it

``` bash
./OneLineCompositions
```

## To edit composition:

open the file composition.c in your text editor, by default it looks like this:

``` c
#define COMPOSITION info->t*((info->t>>12|info->t>>2)&63&info->t>>4)
```

By adjusting the values of the integer constants, you achieve variation in the patterns.

#### Ex.
``` c
#define COMPOSITION info->t*((info->t>>22|info->t>>9)&33&info->t>>1)
```

After editing compositions.c run

``` bash
make clean && make

```
To compile the program with the new composition.

``` c
info->t
``` 
is a variable incremented every sample. If you leave it along you don't have to worry about what's in OneLineCompositions.c or callback.c.





