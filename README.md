# Polynomial Regression
## About
Earlier this year, in the artificial intelligence paper I took, we created a Python application 
that used gradient descent to fit a first order polynomial to a set of points. I decided to re-visit 
the method in hopes of using it to fit any order of polynomial to a set of points and realized it got 
stuck on local minimums for polynomials of order greater than one ☹.  
I tried stochastic and mini-batch gradient descent to fit second order polynomials to no avail, 
so in the end I decided to do it analytically using the least squares method.
[Here](https://www.youtube.com/watch?v=TPKyT3hu71c) is a video explaining the method.

## Technologies
- C++
- QT Creator
- QCustomPlot
- Git

## How to Use
The latest version is in the folder 'V1.02' of the repository. Just download it and run 'Regress.exe'.  
There are four buttons in the top left corner:  
- Top-Left: Choose the order of polynomial you want to fit.
- Bottom-Left: Generate random values. There are initial values set, if any is left blank, it will choose the initial values by default. Otherwise, you can enter your own values directly on the table.
- Top-Right: Click to plot the values in the table.
- Bottom-Right: Click to fit a polynomial, of the chosen order, to the set of points and plot it.

## Status
Will add other functions like exponential and maybe trig functions later on. Currently working on adding an icon and will also add the calculated polynomial equation.



