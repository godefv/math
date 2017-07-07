#ifndef SORTED_H
#define SORTED_H 

#include<boost/hana.hpp>

template<class Order, class A, class B> concept bool Sorted=static_cast<bool>(boost::hana::index_if(Order{}, boost::hana::equal.to(boost::hana::type_c<A>))>boost::hana::index_if(Order{}, boost::hana::equal.to(boost::hana::type_c<B>)));

#endif /* SORTED_H */
