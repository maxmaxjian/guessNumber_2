#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <functional>
#include <algorithm>
#include <iterator>

namespace std {
    template<>
    struct hash<std::pair<int,int>> {
	size_t operator()(const std::pair<size_t,size_t> & p) const {
	    return std::hash<int>()(p.first)^std::hash<int>()(p.second);
	}
    };
}

class solution {
public:
    int getMoneyAmount(int n) {
        // std::vector<int> cands;
        // cands.push_back(1+compute(2,n));
        // for (int k = 2; k < n; k++)
        //     cands.push_back(k+std::max(compute(1,k-1),compute(k+1,n)));
        // cands.push_back(n+compute(1,n-1));
        // std::cout << "i = " << 1 << ", j = " << n << ":\t";
        // std::copy(cands.begin(), cands.end(), std::ostream_iterator<int>(std::cout, " "));
        // std::cout << std::endl;
        // return *std::min_element(cands.begin(), cands.end());
        return compute(1,n);
    }

private:
    int compute_impl(int i, int j) {
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
	    std::cout << "i = " << i << ", j = " << j << ":\t";
	    std::copy(cands.begin(), cands.end(), std::ostream_iterator<int>(std::cout, " "));
	    std::cout << std::endl;
	    return *std::min_element(cands.begin(), cands.end());
	}
    }

    int compute(int i, int j) {
        if (dict.find(std::make_pair(i,j)) == dict.end())
            dict[std::make_pair(i,j)] = compute_impl(i,j);
        return dict[std::make_pair(i,j)];
    }

  private:
    std::unordered_map<std::pair<int,int>,int> dict;
};

int main() {
    int num = 10;
    
    solution soln;
    int minmax = soln.getMoneyAmount(num);
    std::cout << "The amount of money to guarantee a win is:\n"
	      << minmax << std::endl;
}
