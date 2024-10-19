// RAD
// !!! UPLOAD TO GITHUB NOW AND HAVE PROPER VERSION CONTROL TO SHOW PROGRESS

#include <stdio.h>

// Morning Aryan, this is what I figured out so far:
// Basically we calculate the xyz values of 1 point at a time
// R1 and R2 are fixed (maybe global?)
// theta is [0,2pi)
// phi is probably the same as theta idk
// If we run the program to go through the range of phi, with one set of A and B values then that's ONE FRAME
// Running through all A and B values is all our frames
// So we take the Torus, then spin it for however long we want. 
// Then we calculate the projection of our 3d points (x',y')
// Use his method of finding K1 and K2 offsets
// Now we have all the values we want
// Using his method for calculating normal and then mapping to certain ASCII characters you got the rendering part
// Then plot points with Z-Buffer onto the terminal

int main() {
  int a = 10;
  printf("%d", a);

  return 0;
}