# Controlling the Data Flow

## The shared data flow issue

In linear programming there isn't any problem creating conditional branches, `if`, `switch`, `continue` and `break` for controlling the data flow.
You can have an infinite loop and just break when a condition is satisfied. 
But as we saw in the previous lesson, a vector has not only a condition result, but N condition results at the same time. Part of the vector can be ready to exit the loop (because the vector data has reached the exit condition), but the rest of data still has active work to do before exiting.

## Avoiding the execution of computationally expensive branches 

The simplest approach to save CPU time is by checking if all values inside a mask are the same, either all `TRUE` or all `FALSE`.
When all values inside the mask are the same we indeed have a simple boolean, either true or false. This can be used to skip parts of the code, or using the normal conditional branches:  `if`, `switch`, `continue` and `break`...

In my wrapper classes I use the `horizontal_or(mask)` function (that wraps `_xxx_testz_xx` intrinsics) . "Horizontal OR" checks if any value inside the mask is `true`, and in that case returns a single boolean with the `true` value, and `false` in any other case.

The next exercise has some timeout problems due to a computationally expensive function that is only needed on some corner cases. Optimize the code to aboid the timeout:
@[Skipping Code Execution]({"stubs": ["skip/skip.cpp","skip/vrandom.h","skip/vconvert.h","skip/v8i.h","skip/v8f.h"], "command": "./mycompile.sh skip ./skip"})


## Controlling the Data Flow

By using `horizontal_or` you can also break a loop early. With autovectorization you can't get this optimization, but with manual vectorization it's possible, and preferred.

On this exercise you are calculating some combo Score, you want to end the simulation once your reach 1700 points on any of the parallel simulations, and return that max score.
@[Early exiting a loop]({"stubs": ["exitloop/exitloop.cpp","exitloop/vrandom.h","exitloop/vconvert.h","exitloop/v8i.h","exitloop/v8f.h"], "command": "./mycompile.sh exitloop ./exitloop"})




