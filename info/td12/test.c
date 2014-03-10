#include <stdio.h>
#include "hash.h"
#include "test.h"

int test()
{
    int number_error = 0;

    number_error += test_hash();

    if (number_error == 0) {
        printf("\n\nTEST SUCCESSFULL\n");
    } else {
        printf("\n\nECHEC\nNUMBER OF ERROR : %d\n", number_error);
    }

    return number_error;
}

int is_valid_ul(const char *test, unsigned long value, unsigned long result)
{
    static int test_number = 0;

    printf("Test n°%d : %s", test_number++, test);
    if (value == result) {
        printf("\t... OK\n");
        return 0;
    } else {
        printf("\t... NON OK (%d instead of %d)\n", value, result);
        return 1;
    }
}

int test_hash()
{
    int number_error = 0;

    char const *s1 = "aaaa";
    char const *s2 = "";
    char const *s3 = "ABCD";

    int dim_hash;

    printf ("\nTEST OF HASH\n");

    dim_hash = 32;
    printf ("DIM = %d\n", dim_hash);
    number_error += is_valid_ul(s1,hash(s1, dim_hash),0);
    number_error += is_valid_ul(s2,hash(s2, dim_hash),0);
    number_error += is_valid_ul(s3,hash(s3, dim_hash),2);

    dim_hash = 256;
    printf ("DIM = %d\n", dim_hash);
    number_error += is_valid_ul(s1,hash(s1, dim_hash),33);
    number_error += is_valid_ul(s2,hash(s2, dim_hash),0);
    number_error += is_valid_ul(s3,hash(s3, dim_hash),3);

    return number_error;
}

#ifndef main
int main(int argc, const char *argv[])
{
    test();
    return 0;
}
#endif
