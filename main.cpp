#include <iostream>
#include <vector>
// #include <unordered_map>
// #include <utility>
// #include <functional>
#include <algorithm>
#include <iterator>

// namespace std {
//     template<>
//     struct hash<std::pair<size_t,size_t>> {
// 	size_t operator()(const std::pair<size_t,size_t> & p) {
// 	    return std::hash()(p.first)^std::hash()(p.second);
// 	}
//     };
// }

class solution {
public:
    int getMoneyAmount(int n) {
	return compute(1,n);
    }

private:
    int compute(int i, int j) {
	if (i == j)
	    return 0;
	else if (i == j-1)
	    return std::max(i,j);
	else {
	    std::vector<int> cands;
	    cands.push_back(i+compute(i+1,j));
	    for (int k = i+1; k < j; k++)
		cands.push_back(k+std::max(compute(i,k-1), compute(k+1,j)));
	    cands.push_back(j+compute(i,j-1));
	    std::cout << "i = " << i << ", j = " << j << ": ";
	    std::copy(cands.begin(), cands.end(), std::ostream_iterator<int>(std::cout, " "));
	    std::cout << std::endl;
	    return *std::min_element(cands.begin(), cands.end());
	}
    }
};

int main() {
    int num = 10;
    
    solution soln;
    int minmax = soln.getMoneyAmount(num);
    std::cout << "The amount of money to guarantee a win is:\n"
	      << minmax << std::endl;
}
