// sarkoxed //

#include <gtest/gtest.h>
#include <cassert>

#include "../tesrc/template/vector.hpp"

TEST(container, iiiiii){
    int a[6] = {1,3,4,52,1,4};
    Vec<int> x(a, 6);
    
    int b;
    for(auto i: x){
        b = i;
    }

    for(auto i = x.begin(); i != x.end(); i++){
        b = *i;
    }
}


int main(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
