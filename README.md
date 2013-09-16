Music Generator:
================

http://www.cs.purdue.edu/homes/grr/cs240/lab5-sound/

Files:
------
freq2wav.c:  read a file.freq file passed as argument and generate a file file.wav with the frequency tones indicated by the file.freq file.

A song is a sequence of tones with different sequences and durations. The .freq files describe songs using pairs freq, msecs. For example the song "Happhy Birthday" is described in the file songs/birthday.freq as:

1568 250

1568 187

1760 375

1568 375

2092 375

...


Setup:
------
```
make
```

Run test:
---------
```
testall
```


