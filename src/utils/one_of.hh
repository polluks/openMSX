#ifndef ONE_OF_HH
#define ONE_OF_HH

#include <tuple>

template<typename... Ts>
class one_of {
public:
	one_of(Ts... ts) : tup(ts...) {}

	template<typename T>
	friend bool operator==(const T& t, const one_of& o) {
		return std::apply([&](const Ts& ... ts) { return (... || (t == ts)); }, o.tup);
	}

private:
	std::tuple<Ts...> tup;
};

#endif
