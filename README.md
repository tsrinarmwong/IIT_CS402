# IIT_CS402
Hello! My name is Thitipun Srinarmwong A20501320.
The code is for the assignment SP-Lab-1 for IIT course CS402 semester FALL2023.

This program take the set of values and print outthe 

  - mean _(average)_
  - mode _(if all numbers appear once, will print a message instead of all entries)_
  - geometric mean _(if negative value is found, will print INVALID)_
  - harmonic mean _(if negative value is found, will print INVALID)_
  - median _(the middle value)_
  - the standard deviation

## The program DOES NOT use math library for computation.

**to run the program please use the compile as follows:**
  `gcc basicstats.c -o basicstats`

**And to run the program, please input the text file that contains the data after the executable**
  `./basicstats small.txt`
  
  `./basicstats large.txt`
  
  `./basicstats Big.txt`
  
  `./basicstats really_big.txt`

The code are commented and organized. I also include the log file to reference the program behaviour.

### Limitations
  zero data loaded will result in program termination without any computation.
  
  negative value will result in certain functions skipped since it is mathematically invalid.
  
  If the loaded file exceed 1000 and all has unique number, meaning every number is mode. 
  The program would take exponentially longer time to process. This performance is according to my local computer Mac M1 16 GB ram.
  
## Reference

  computation are mostly studied and validated through
  https://www.gigacalculator.com/
