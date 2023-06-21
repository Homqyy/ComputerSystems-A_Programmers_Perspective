#include "csapp.h"

#include "machine.h"
#include "opt/combine.h"

/* Implementation with maximum use of data abstraction */
void
combine1(vec_ptr v, data_t *dest)
{
    long i;

    *dest = IDENT;
    for (i = 0; i < vec_length(v); i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}

/*
 * Move call to vec_length out of loop
 * 优化：将vec_length的调用移出循环，称为代码移动（code motion）
 */
void
combine2(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);

    *dest = IDENT;
    for (i = 0; i < length; i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}

void count_cpe(const char *name, void (*func)(vec_ptr v, data_t *dest), vec_ptr v, data_t *dest)
{
    clock_t start = clock();
    func(v, dest);
    clock_t end = clock();

    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    double cycles_used = cpu_time_used * CPU_FREQUENCY;  // 你的CPU频率，单位为Hz
    double cpe = cycles_used / 1000;

    printf("%s CPE: %f\n", name, cpe);
}

int
main(int argc, char *argv[])
{
    vec_ptr v = new_vec(1000);
    data_t dest;

    count_cpe("combine1", combine1, v, &dest);
    count_cpe("combine2", combine2, v, &dest);

    return 0;
}