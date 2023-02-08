# PurePursuitSimulation
A simulated visualization of the **Pure Pursuit** path following algorithm I implemented for the VEX Robotics competition while in highschool. Using a set lookahead distance, it constantly calculates the arc necessary to return to a pre-set path, based on points inputted accordingly after running the executable. Grab the latest release [here](https://github.com/odepoint/PurePursuitSimulation/releases).


# General Recommendations
As this is a simulation of Pure Pursuit, the same limitations apply. It's generally required to start the robot close to the first point, and for its heading to not be in the opposite direction (negative movements are not inherently supported, and a path would have to be flipped to drive in reverse; I did this for the competition, but it isn't part of the fundamental algorithm). Additionally, excessively tight turns and precise stops likely require per-path tuning of the lookahead distance and stopping point. My eventual plan is to allow these to be tuned in an easily understood UI, but you can simply compile the program having changed these settings for now.

# Visualization
After running the executable, a csv file looking like this will be created![CSV file](https://i.imgur.com/OujDLYJ.png)
Running render.py and entering the name of your CSV file will then allow you to visualize this as a 2D graph.
![Graph](https://i.imgur.com/H0I5w2v.png)

# TODO
My eventual plan is to encapsulate the visualization and calculations into one interactive program, with toggleable settings for
1. Lookahead distance
2. Stopping point

and a rendering of it in real time

# Thanks

My friend [Liam](https://github.com/hpst3r) for bouncing ideas off with me, and refactoring the makefile to be multiplatform.