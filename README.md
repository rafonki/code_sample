# code_sample
Brief Code sample developed for my application for Rapyuta Robotics

Rafael Gomez-Jordana - 26th April 2016.

This is a short code sample developed for my application to Rapyuta Robotics. Do not expect to find exceptionally advanced code, but rather some of the C++ structures that I am currently familiar with. It also shows some of the new cool features of C++11 that I know how to implement. Expect to find:

* Shared Pointers
* Templates
* STL Vectors
* Classes and Inheritance
* Other C++11 features like the new random generation library, automatic type deduction and the new range-based loops

The program dynamically allocates a number of objects of the class Shape which are randomly generated. Three vectors of shared pointers store these objects: One for all the shapes, one only for the shapes of type circle, and another for shapes of type square.

Then, the vector that contains all of the objects is cleared. Thanks to the capabilities of shared_pointers, the other two vectors keep the objects alive until those are cleared too.
