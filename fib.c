//
//  main.cpp
//  Assignment 9-6
//
//  Created by Eric Willoughby on 7/30/18.
//  Copyright © 2018 Eric Willoughby. All rights reserved.
//

#include <iostream>
using namespace std;


int foo2(int n) {
    int i, j, x = 0;
    for (i = 0; i <= n; i++)
        for (j = 0; j < i; j++)
            x++;
    return x;
}

int main(int argc, const char * argv[]) {
    cout << "Hello, World!\n";
    
    cout << foo2(9) << endl;
    return 0;
}
