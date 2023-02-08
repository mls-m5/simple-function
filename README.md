# simple-function

What if you felt like you would like to debug a function call
one day, only to realize that std::function is so convoluted
with nested calls that it's almost impossible to step into
a function when debugging.

What if you could exchange std::function with another type
when debugging so that you could easier debug it?

It was with that thought in mind i created this library. It copies
and stores callable types to its own internal storage or on the
heap and calls just like std::function.



Features:
 - [x] Copy lambdas and call
 - [ ] Copy and move the simple::Function itself
 - [ ] Copy std::function
