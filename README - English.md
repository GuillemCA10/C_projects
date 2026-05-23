This is a selection of the programs I made during my learning of C.
Each program showcases a specific set of fundamental computer science skills, as described below:

1. CREDIT

A program that uses the Luhn algorithm to validate a credit card and identify the card provider.
The program will prompt the user to input their credit card number.
If it's a valid American Express, MasterCard, or Visa number, it will return the correct brand name.
If it's not, it will return "INVALID".

2. FILTER

Applies image processing filters to BMP files by directly manipulating raw pixel data.
The program takes an input BMP file and a filter flag, and outputs a new BMP file with the effect applied.
The available filters are grayscale (-g), sepia (-s), reflection (-r), and blur (-b).
Usage: ./filter -[flag] infile outfile

3. READABILITY

Readability calculates the approximate reading level of a text using the Coleman-Liau index,
a formula that calibrates reading difficulty based on parameters like word and sentence length.
The program will prompt the user to input a text. It counts the letters, words,
and sentences to compute a grade level, and returns a result such as "Grade 7" or "Grade 16+".

4. RECOVER

A program that recovers deleted JPEG files from a raw forensic memory image.
The program scans the image byte by byte, detects the binary signatures that mark the start of each JPEG file,
and reconstructs them as separate numbered files (001.jpg, 002.jpg, etc.).
Usage: ./recover image

5. RUNOFF

Simulates a ranked-choice election using the instant-runoff voting method.
Voters rank candidates in order of preference. The program eliminates the last-place candidate each round
and redistributes their votes until one candidate wins a majority.
Usage: ./runoff [candidate ...]

6. SPELLER

A program that spell-checks a text file against a dictionary using a hash table.
The program loads a dictionary into memory and checks each word in the input text,
reporting all misspellings along with timing benchmarks for each stage of the process.
Usage: ./speller [DICTIONARY] text

COMPILATION

```
gcc -o credit credit.c
gcc -o readability readability.c
gcc -o recover recover.c
gcc -o runoff runoff.c
For filter and speller, a Makefile is included, so you should run 'make' from their specific directory.
```
