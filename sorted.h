#ifndef SORTED_H
#define SORTED_H 

#include<boost/hana.hpp>

template<class Order, class A, class B> concept bool Sorted=static_cast<bool>(hana::index_if(Order{}, hana::equal.to(hana::type_c<A>))>hana::index_if(Order{}, hana::equal.to(hana::type_c<B>)));

#endif /* SORTED_H */
