#ifndef PRINT_TYPE_H
#define PRINT_TYPE_H 

void print_type(auto const& a){
	std::cout<<typeid(a).name()<<std::endl;
}

#endif /* PRINT_TYPE_H */
