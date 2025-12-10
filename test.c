
// apt install libxext-dev libbsd-dev
//  https://www.ibm.com/docs/en/i/7.6.0?topic=ssw_ibm_i_76%2Fapis%2Fusers_78.html
//  https://man7.org/linux//man-pages/man3/pthread_cond_init.3.html

#include <stdio.h>

union u_fmat4x4and16
{
	double mat4x4[4][4];
	double mat16[16];
} ;

typedef double	t_fmat4x4[4][4];

void test_print(t_fmat4x4 test)
{
    union u_fmat4x4and16 final = *(union u_fmat4x4and16 *)test;
    
    test[0][0] = 45.0;
    test[0][1] = 46.0;
    test[0][2] = 47.0;

    test[0][0] = 25.0;
    test[1][0] = 26.0;
    test[2][0] = 27.0;
    
    printf("%f %f %f\n", test[0][0], test[0][1], test[0][2]);
	printf("final %f %f %f\n", final.mat4x4[0][0], final.mat4x4[0][1], final.mat4x4[0][2]);
}

int main()
{
    t_fmat4x4 test;
    
    test_print(test);
    
    
    printf("end %f %f %f\n", test[0][0], test[0][1], test[0][2]);
    
    return 0;
}