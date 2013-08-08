CFLAGS = -arch x86_64 -iwithsysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.7.sdk

default: OneLineCompositions

OneLineCompositions: OneLineCompositions.o
	gcc $(CFLAGS) OneLineCompositions.o libportaudio.a -framework CoreAudio -framework AudioToolbox -framework AudioUnit -framework CoreServices -o OneLineCompositions

OneLineCompositions.o: OneLineCompositions.c
	gcc $(CFLAGS) -c -g -std=c99 -o OneLineCompositions.o OneLineCompositions.c

clean:
	/bin/rm -f *.o OneLineCompositions