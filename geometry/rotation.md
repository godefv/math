A rotation is a transformation on a set of points with the following properties :

* it does not change distances between points
* it does not change angles between directions
* it transforms at least one point to itself

The set of rotations is a group : 

* any sequence of rotations is itself a rotation
* any rotation can be undone by another rotation

This group is not commutative : changing the order in which rotations are applied can result in a different overall rotation.

It is not a finite group, but it can be represented by unit quaternions, which are a subset of a vector space over a finite set of 2k-blades. 

But what does "a subset of a vector space over a finite set of 2k-blades" mean in terms of geometry ? Nothing ?

However, the Lie algebra of the rotation group -- let's call it the rotation algebra -- is a vector space over a finite set of orthogonal planes, which is much more natural. 
Infinitesimal rotations are commutative, which allows the addition of rotations to commute in the rotation algebra.


