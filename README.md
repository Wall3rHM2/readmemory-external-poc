# readmemory-external-poc
 Reads memory of another process externally (on Windows) Proof Of Concept
 
 
 ## What is this?
 What if you wanted to get values, strings, entire structs, and more data on ***ANY*** program? That has many uses that are quite unique. You could use this function to be used in a anticheat software for games (that way it detects possible cheats running externally or internally), read *hidden* data that is not acessible for user but runs locally, debug a program, test memories offsets, use together with other programs to discover entire structs in reverse engineering, or even use it for game cheating. This method is **very hard to be detect**, because it *makes use of Windows functions externally*, so we don't actually need to inject any code.
 
 This is *not a easy task*, because we have a huge problem which is *ASLR* (Address Space Layout Randomization). But here, I implemented a algorithm which takes care of this detail and we can get values and pointers using memory offsets.
 
 ## What is *ASLR* (Address Space Layout Randomization)?
 TODO:finish this readme
 
 
 This example works on the game GMod with offsets as of 2022
