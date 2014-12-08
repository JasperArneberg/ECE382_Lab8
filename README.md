ECE382_Lab8
===========

Lab 8: Robot Maze

C2C Jasper Arneberg  
T5 ECE 382  
Capt Trimble  

##Introduction
This lab requires combining the functionalites developed in Lab 6 and Lab 7. 

##Prelab
The strategy to complete this lab changes as the level of functionality increases. In order to get required functionality, only one left turn is required. To get B functionality, one left and one right turn is required. To get A functionality, however, the game changes. A minimum of four 90-degree turns are required, posing a problem. It is very hard to determine when to turn right versus left. For this functionality, perhaps a right edge-following strategy would work the best.

####Pseudocode for Required Functionality
```
infinite loop:
leftSignal = readADC(2);
centerSignal = readADC(3);
rightSignal = readADC(4);

if(centerWall == false) moveForward;
if (centerWall) {
  if (leftSignal > rightSignal) {
    turnRight90;
  }
  else {
    turnLeft90;
  }
}

```

####Schematic
![alt text](https://github.com/JasperArneberg/ECE382_Lab8/blob/master/schematic.png?raw=true "Schematic")

##A Functionality

##Bonus Functionality

##Debugging

##Conclusion

##Documentation
I used http://www.tablesgenerator.com/markdown_tables to generate markdown tables efficiently.  

