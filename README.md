# Polynomial Regression
## About
Earlier this year, in the artificial intelligence paper I took, we created a Python application 
that used gradient descent to fit a first order polynomial to a set of points. I decided to re-visit 
the method in hopes of using it to fit any order of polynomial to a set of points and realized it got 
stuck on local minimums for polynomials of order greater than one ☹.  
I tried stochastic and mini-batch gradient descent to fit second order polynomials to no avail, 
so in the end I decided to do it analytically using the Least Squares method.
[Here](https://www.youtube.com/watch?v=TPKyT3hu71c) is a video explaining the method.  
  
My implementation for the Least Squares method is found in the regress.cpp source file in the leastSquares function. I used Gauss Jordan Elimination to find the inverse of the A^T.A matrix. Also note that I combined the Identity matrix to the A^T.A matrix so row operations could be done more easily.  
  
I am currently using xorshf96() to generate the random values and seeding it with time(). It seems to be working better than rand().

## Technologies
- C++
- QT Creator
- QCustomPlot
- Git

## How to Use
The latest version can be found [here](https://github.com/Alcantara98/Regress_Latest_Version). Just download the repository and run 'Regress.exe'.  
There are four buttons in the top left corner:  
- Top-Left: Choose the order of polynomial you want to fit.
- Bottom-Left: Generate random values. There are initial values set, if any is left blank, it will choose the initial values by default. Otherwise, you can enter your own values directly on the table.
- Top-Right: Click to plot the values in the table.
- Bottom-Right: Click to fit a polynomial, of the chosen order, to the set of points and plot it.

## Status
Will add other functions like exponential and maybe trig functions later on. 
- Currently working on adding an icon and will also add the calculated polynomial equation : Finished.
- Next is for the app to able to read .xslx files (the first two columns) for the X & Y values.
- Will also add methods the user could choose to calculate the error (for example, the Mean Squared Error).



