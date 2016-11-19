#include <iostream>
#include <iterator>
#include <set>

typedef std::set<int> T_points;
typedef std::multiset<int> T_endpoints;

size_t GetSingleLayerLength(const T_endpoints& lefts, const T_endpoints& rights, const T_points& points) {
    size_t res{};
    size_t L{};
    int cur_seg_counter{};
 
    for (auto iter : points) {
    
        if (iter != *points.begin()) {
            cur_seg_counter += lefts.count(L);
            cur_seg_counter -= rights.count(L);
 
            res += cur_seg_counter == 1 ? iter - L : 0;
        }
        
        L = iter;
    }
    
    return  res;
}

int main() {
    int points_count;
    std::cin >> points_count;
    
    T_endpoints lefts;
    T_endpoints rights;
    T_points points;
 
    for (int i(0); i < points_count; ++i) {
        int left_coord, right_coord;
        std::cin >> left_coord >> right_coord;
        
        lefts.insert(left_coord);
        rights.insert(right_coord);
        
        points.insert(left_coord);
        points.insert(right_coord);
    }
    
//	copy(std::begin(lefts), std::end(lefts), std::ostream_iterator<int>(std::cout, " "));
//  	std::cout << std::endl;
//  	
//	copy(std::begin(rights), std::end(rights), std::ostream_iterator<int>(std::cout, " "));
//  	std::cout << std::endl;
//  	
//	copy(std::begin(points), std::end(points), std::ostream_iterator<int>(std::cout, " "));
//  	std::cout << std::endl;
    
    std::cout << GetSingleLayerLength(lefts, rights, points) << std::endl;
 
    return 0;
}
