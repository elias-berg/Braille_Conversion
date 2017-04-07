README.txt

This project is code portion of the the Braille Pad Senior Project, contributions from Eli Berg.
All code in this project is the intellectual property of Eli Berg but is completely free for use.

The code is to be stored on-board a Raspberry-Pi microcontroller which will be
responsible for producing a text file for the code to read in and convert the
raw text to braille encodings.

All that is needed to run the code is the 'make' command. This will compile the code and store 'translate.exe' into the bin/ directory. The '.exe' ending is just to give all executables a common extension for potential future makefile use. Making the tests does not currently work.

Run the program with bin/translate.exe. This will take the document image "document.png" and parse it with Tesserace-OCR. Then, the resulting text file will get converted into Braille ASCII with Liblouis*.
