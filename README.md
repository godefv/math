# What is it ?
This is a c++ math library. It provides :

* **abstract mathematical objects**

  groups, vector spaces, algebras, etc.

* **some specific instances of such objects**

  geometric algebra, which includes complex numbers, quaternions, and much more.
  todo : geometric transformation groups (rotations, translations, isometries, similarities).

* **coordinate free geometry** 

  Never again write something like `Vector3d{1., 2., 0.}` and then the compiler doesn't know in which frame those coordinates are (and maybe you don't either).
  Instead, use meaningful directions like `1.*up+2.*east+0.*north`. But here `0.*north` is superfluous, so just write `up+2*east`. And if you have several frames, don't bother changing frame explicitly, just write `1.3*my_frame_x + 2.4*my_other_frame_z`. 

# Implementation

## strong typing
Mathematical objects and expressions are represented by c++ types. Operations on those types are made by constexpr functions.
It can effectively turn your compiler into a symbolic math software. The resulting program would only print the result that have been computed at compile time.

## extensible dimensions
No need to specify in advance a space in which to work, new types are generated if new dimensions appear in an expression. If you write `auto a=3*x+4*y`, `a` stores two values in a type generated from the expression `"double*x+double*y"`. Then, writing `a+2.5*z` will just generate a larger type holding three values (assuming `z` is not a combination of `x` and `y`).

## small and easy to read
It is small because it exploits centuries of work from mathematicians. They have put many concepts into the most beautiful form they could find : both as general and as simple as possible, which means factorized and simple code.
The library also uses c++17 with concepts, which provides human friendly template programming.

## unit tests
They are a good place to look for examples.
They make sure things work as intended.

