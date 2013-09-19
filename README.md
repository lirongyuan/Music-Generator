Music Generator:
================

A song is a sequence of tones with different sequences and durations. The .freq files describe songs using pairs freq, msecs. For example the song "Happy Birthday" is described in the file songs/birthday.freq as:

1568 250

1568 187

1760 375

1568 375

2092 375

...

The program ``freq2wav``  read a file.freq file passed as argument and generate a file file.wav with the frequency tones indicated by the file.freq file.

http://www.cs.purdue.edu/homes/grr/cs240/lab5-sound/

Download
--------
```
$ git clone https://github.com/lirongyuan/Music-Generator.git
```

Setup
-----
```
$ make
```

Usage
-----
```
$ ./freq2wav freq-file
```

Tests
-----
```
$ ./testall
```


