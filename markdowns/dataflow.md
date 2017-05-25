# Controlling the Data Flow

## The shared data flow issue

In linear programming there isn't any problem creating conditional branches, `if`, `switch`, `continue` and `break` for controlling the data flow.
You can have an infinite loop and just break when a condition is satisfied. 
But as we saw in the previous lesson, a vector has not only a condition result, but N condition results at the same time. Part of the vector can be ready to exit the loop (because the vector data has reached the exit condition), but the rest of data still has active work to do before exiting.

So if a part of the code has finished, and the other is still running, how to manage this issue?

## Using horizontal conditionals 





