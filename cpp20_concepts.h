#ifndef CPP20_CONCEPTS_H
#define CPP20_CONCEPTS_H 

#include<functional>

template< class F, class... Args >
concept Invocable =
requires(F f, Args&&... args) {
	std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
	/* not required to be equality preserving */
};

#endif /* CPP20_CONCEPTS_H */
