#Definitions
* A **point** is an abstract object. It will be represented by a ,`math::geometry::point_t` or a transformation of another point. It is assumed that a **distance** function exists between any two points.
* A **path** is the image of a continuous funtion of one parameter. This object has no representation in the library.
* A **direction** is a partition of all points by a continuous set of **paths** p~i~ such that distance(p~i~(x),p~i~(y))=|y-x|. It is represented by a `math::geometry::direction_positive_t` or `math::geometry::direction_negative_t`, or a transformation of another direction. Two directions represented by two different types are assumed to be orthogonal.
* A **translation** is a transformation which moves points some **distance** along a **direction**. It is represented by `math::geometry::translation_t`.
* A **direction simple rotation** is a transformation which turns a **direction** some **angle** toward another **direction**. More precisely: at each point P, the two directions define a set of other points accessible by translating P along the two directions ; this set can be partitionned by circles centered on P ; locally around P, the transformation moves each point of one path toward the other along the circle passing through it. It can be applied to a translation by transforming its direction.
* A **direction rotation** is a composition of several **direction simple rotations**.
* An **isotropic scaling** is a transformation which changes all **distances** by some **factor**. It can be applied to a translation by transforming its distance.
* An **homothecy** is a transformation which fixes a **point** P, takes all other points T~i~(P) that can be obtained by transforming P through a translation T~i~, and moves them to S(T~i~)(P), S being an **isotropic scaling**. It is represented by `math::geometry::homothecy_t`.
* A **(simple) rotation** is a transformation which fixes a **point** P, takes all other points T~i~(P) that can be obtained by transforming P through a translation T~i~, and  moves them to R(T~i~)(P), R being a **direction (simple) rotation**. It is represented by `math::geometry::simple_rotation_t`.

