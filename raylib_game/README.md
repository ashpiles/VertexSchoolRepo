# The game.exe likely will not run on your machine because...
## This repository is not meant to be built!
This project was made in a bizarre environment mostly for learning purposes and establishing my nvim editor for raylib and C++

If you wish to build this from source regardless you will likely need to adjust the Makefile on unix-like machines or secure a copy
of the tdm-gcc compiler and make on a windows machine.
You will also need to supply compiled raylib object files for the lib folder.

Once the prerequisites have been fulfilled simply run make and it should build correctly.

---

Due to the project lacking a reliable build process the game.exe is unlikely to run on machines different from my own.
In order to easily allow for compatability the project will likely be converted to a visual studios solution for sharing.
