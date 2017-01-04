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

        // return compute(1,n);

        std::vector<int> result = compute(1,n);
        return *std::min_element(result.begin(), result.end());
    }

private:
    std::vector<int> compute_impl(int i, int j) {
        std::vector<int> result;
	if (i >= j)
	    result.push_back(0);
	else {
	    std::vector<int> cands;
	    for (int k = i; k <= j; k++) {
                auto v1 = compute(i,k-1), v2 = compute(k+1,j);
		cands.push_back(k+std::max(*std::max_element(v1.begin(), v1.end()), *std::max_element(v2.begin(), v2.end())));
            }
	    // std::cout << "i = " << i << ", j = " << j << ":\t";
	    // std::copy(cands.begin(), cands.end(), std::ostream_iterator<int>(std::cout, " "));
	    // std::cout << std::endl;
	    // return *std::min_element(cands.begin(), cands.end());
            result = cands;
	}
        if (i < j) {
            std::cout << "i = " << i << ", j = " << j << ":\t";
            std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        }
        return result;
    }

    std::vector<int> compute(int i, int j) {
        if (dict.find(std::make_pair(i,j)) == dict.end())
            dict[std::make_pair(i,j)] = compute_impl(i,j);
        return dict[std::make_pair(i,j)];
    }

  private:
    std::unordered_map<std::pair<int,int>,std::vector<int>> dict;
};

int main() {
    int num = 10;
    
    solution soln;
    int minmax = soln.getMoneyAmount(num);
    std::cout << "The amount of money to guarantee a win is:\n"
	      << minmax << std::endl;
}
