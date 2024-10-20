#include <stdio.h>
#include <math.h>
#include <windows.h>
#define π 3.14159265358979323846

// SOURCE: https://www.a1k0n.net/2011/07/20/donut-math.html
// Morning, this is what I figured out so far:
// Basically we calculate the xyz values of 1 point at a time
// R1 and R2 are fixed (maybe global?)
// theta,phi is [0,2pi)
// If we run the program to go through the range of phi, with one set of A and B values then that's ONE FRAME
// Running through all A and B values is all our frames
// So we take the Torus, then spin it for however long we want. 
// Then we calculate the projection of our 3d points (x',y')
// Use his method of finding K1 and K2 offsets
// Now we have all the values we want
// Using his method for calculating normal and then mapping to certain ASCII characters you got the rendering part
// Then plot points with Z-Buffer onto the terminal

void render_frame(float A, float B){
  
  // spacing ripped from Andy Sloane, not sure why he chose these values exactly
  const float theta_spacing = 0.07;
  const float phi_spacing   = 0.02;
  const float R1 = 1;
  const float R2 = 2;
  const float screen_width = 35;
  const float screen_height = 35;
  const float K2 = 5;
  const float K1 = screen_width*K2*3/(8*(R1 + R2));

  // Pre-compute subexpressions
  float cosa = cos(A);
  float cosb = cos(B);
  float sina = sin(A);
  float sinb = sin(B);

  // Buffers
  char output[35][35];
  float zbuffer[35][35];

  // Allocate output with blank spaces
  for (int i = 0; i < 35; i++)
  {
    for (int j = 0; j < 35; j++)
    {
      output[j][i] = ' ';
    }
  }

  // Allocate z-buffer with 0 values
  for (int k = 0; k < 35; k++)
  {
    for (int l = 0; l < 35; l++)
    {
      zbuffer[l][k] = 0;
    }
  }
  
  // Creating the cross sectional circle --> o | o
  for (float theta = 0; theta < 2*π; theta += theta_spacing)
  {
    float costheta = cos(theta);
    float sintheta = sin(theta);

    // Creating the solid of revolution, counterclockwise --> O
    for (float phi = 0; phi < 2*π; phi += phi_spacing)
    {
      /// Pre-calculate subexpressions
      float cosphi = cos(phi);
      float sinphi = sin(phi);
      // From the parametric equation of the cross sectional circle
      float circlex = R2 + R1 * costheta;
      float circley = R1 * sintheta;

      float x = circlex * (cosb * cosphi + sina * sinb * sinphi) - circley * cosa * sinb;
      float y = circlex * (cosphi * sinb - cosb * sina * sinphi) + circley * cosa * cosb;
      float z = K2 + cosa*circlex*sinphi + circley*sina;

      float z_inv = 1/z; // needed for projection

      // Projection, note that floats are cast to integer because screen pixels need whole numbers
      int xp = (int) (screen_width/2 + K1*z_inv*x);
      int yp = (int) (screen_height/2 - K1*z_inv*y);

      // Luminance
      float length = cosphi*costheta*sinb - cosa*costheta*sinphi - sina*sintheta + cosb*(cosa*sintheta - costheta*sina*sinphi);

      // Now for lengths that are positve (facing us, negative values would face into the screen)
      if (length > 0)
      {
        if(z_inv > zbuffer[xp][yp]){
          zbuffer[xp][yp] = z_inv;
          int luminance_index = length*8;
          output[xp][yp] = ".,-~:;=!*#$@"[luminance_index]; // This is cool, based on the luminance index it will pick a value from this string
        }
      }
    }
  }

  // Bring our cursors home
  printf("\033[H");

  for (int q = 0; q < screen_height; q++)
  {
    for (int p = 0; p < screen_width; p++)
    {
      putchar(output[p][q]);
    }
    putchar('\n');
  }
}

int main() {

  float A = 0, B = 0;
  
  while (1)
  {
    render_frame(A,B);

    A += 0.04;
    B += 0.02;

    Sleep(30); // sleeper to aid in animation
  }
  
  return 0;
}