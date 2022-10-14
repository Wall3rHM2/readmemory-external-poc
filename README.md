# readmemory-external-poc
 Reads memory of another process externally (on Windows) Proof Of Concept
 
 
 ## What is this?
 What if you wanted to get values, strings, entire structs, and more data on ***ANY*** program?
 
 Well, this is exactly what this is all about.  This is *not a easy task*, because we have a huge problem which is *ASLR* (Address Space Layout Randomization). But here, I implemented a algorithm which takes care of this detail and we can get values and pointers using memory offsets. This method is **very hard to be detected**, because it *makes use of Windows functions externally*, so we don't actually need to inject any code. 
 
 ## What can i use this for?
 This has many uses that are quite unique. You could use this function to be used in a anticheat software for games (that way it detects possible cheats running externally or internally), read *hidden* data that is not acessible for the user but runs locally, debug a program, test memories offsets, use together with other programs to discover entire structs in reverse engineering, or even use it for game cheating.
 
 ## What is *ASLR* (Address Space Layout Randomization)?
 It's a security feature related to prevent memory corruption vulnerabilities. It makes sure that programs start at pseudorandom generated memory locations. If this didn't exist, we could for example just register the memory address of a value one time and after we close and open the software again, have the same location for the desired object. This is not possible with ASLR because everytime you start that software it changes the base address.
 
 
 This example works on the game GMod with offsets as of 2022
