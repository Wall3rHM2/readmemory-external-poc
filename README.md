# readmemory-external-poc
 Reads memory of another process externally (on Windows) Proof Of Concept
 
 
 
 ## What is this?
 What if you wanted to get values, strings, entire structs, and more data on ***ANY*** program?
 
 Well, this is exactly what this is all about.  This is *not a easy task*, because we have a huge problem which is *ASLR* (Address Space Layout Randomization). But here, I implemented a algorithm which takes care of this detail and we can get values and pointers using memory offsets. This method is **very hard to be detected**, because it *makes use of Windows functions **externally***, so we don't actually need to inject any code. 
 
 
 ## What can i use this for?
 This has many uses that are quite unique. You could use this function to be used in a anticheat software for games (that way it detects possible cheats running externally or internally), read *hidden* data that is not acessible for the user but runs locally, debug a program, test memories offsets, use together with other programs to discover entire structs in reverse engineering, or even use it for game cheating.
 
 
 ## What is *ASLR* (Address Space Layout Randomization)?
 It's a security feature related to prevent memory corruption vulnerabilities. It makes sure that programs start at pseudorandom generated memory locations. If this didn't exist, we could for example just register the memory address of a value one time and after we close and open the software again, have the same location for the desired object. This is not possible with ASLR because everytime you start that software it changes the base address.
 
 
## What are memory offsets?
Memory offsets are memory addresses that are relative to another memory address being used by the software. If you had the address for a software task running, you could get the memory address pointers of your desired variables and subtract that to the current base address of the task, that way you can get the same pointers to the same variables every time you start the software, because all you have to do is sum the current base address with the memory offset.


## How this works?
First we get the base address of the desired software to use. Next you use the memory offsets summed with the task base address, then we read the memory location result and read the necessary size of data so we can get the pointer to a variable. Finally, after we have the pointer, we read the memory of the desired variable by getting the address between the one given by the pointer and the same address summed with the data type size of what we want. For 32-bit applications and using the data type int, that would be 4 bytes.
 
 
 This example is configured to be executed on the game GMod with offsets as of 2022, you can easilly change the desired task and the memory offsets to fit another purpose.
