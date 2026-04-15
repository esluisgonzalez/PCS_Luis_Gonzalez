#include <cstdlib>
#include <vector>
#include <string>

#include "sorts.h"
#include "randfiller.h"

int
main(void)
{
    randfiller rf(12345);

    for (int k = 0; k < 100; k++) {
        std::vector<int> v(k + 1);
        rf.fill(v, -1000, 1000);
        bubblesort(v);

        if (!issorted(v)) {
            return EXIT_FAILURE;
        }
    }

    std::vector<std::string> vs = {
        "torino", "roma", "milano", "genova", "napoli",
        "firenze", "bari", "lecce", "aosta", "trento"
    };

    bubblesort(vs);

    if (!issorted(vs)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}