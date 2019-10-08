# physics-scaler
An electron app I made just for the excitement of making an electron app.
https://electronjs.org/

As a part of a university course we're supposed to simulate a planetary body orbiting
another planetary body. However, since the mass of the earth is about 6*10^24, you can't
really use single floating-point numbers very well if you wish to represent a "real" simulation.
I wrote a C++ program to scale the values freely so they become usable with single floating-point numbers, 
and figured I'd share it with my other students.

So what better way than to use Electron as the front-end? None! Except it took a while to get it working!

I would have loved to put this up on a website instead, but it needs the C++ to handle the really big numbers...
