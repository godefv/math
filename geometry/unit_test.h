#ifndef GEOMETRY_UNIT_TEST_H
#define GEOMETRY_UNIT_TEST_H 

#include"algebra/unit_test.h"
#include"point.h"
#include"../symbolic/unit_test.h"

auto constexpr O=math::geometry::default_origin;
auto constexpr A=math::geometry::make_point(e0+e1);
auto constexpr B=math::geometry::make_point(e0+e1+e2);
auto constexpr C=math::geometry::make_point(math::ratio<-1,3>*e0+math::ratio<2,3>*e1+math::ratio<3,5>*e2);
auto constexpr D=math::geometry::make_point(24.0*e0-18.0*e1+1.5*e2);

#endif /* GEOMETRY_UNIT_TEST_H */
