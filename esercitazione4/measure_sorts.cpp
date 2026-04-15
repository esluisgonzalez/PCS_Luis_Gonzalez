#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

#include "sorts.h"
#include "randfiller.h"
#include "timecounter.h"

int
main(void)
{
    randfiller rf(12345);
    timecounter tc;

    std::cout << "n bubble insertion selection std::sort" << std::endl;

    for (int n = 4; n <= 8192; n *= 2) {
        std::vector<int> base(n);
        rf.fill(base, -100000, 100000);

        std::vector<int> v;

        v = base;
        tc.tic();
        bubblesort(v);
        double tbubble = tc.toc();
        if (!issorted(v)) {
            return EXIT_FAILURE;
        }

        v = base;
        tc.tic();
        insertionsort(v);
        double tinsertion = tc.toc();
        if (!issorted(v)) {
            return EXIT_FAILURE;
        }

        v = base;
        tc.tic();
        selectionsort(v);
        double tselection = tc.toc();
        if (!issorted(v)) {
            return EXIT_FAILURE;
        }

        v = base;
        tc.tic();
        std::sort(v.begin(), v.end());
        double tstdsort = tc.toc();
        if (!issorted(v)) {
            return EXIT_FAILURE;
        }

        std::cout << n << " "
                  << tbubble << " "
                  << tinsertion << " "
                  << tselection << " "
                  << tstdsort << std::endl;
    }

    return EXIT_SUCCESS;
}