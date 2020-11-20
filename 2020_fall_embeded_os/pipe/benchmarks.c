#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "benchmarks.h"

bench_t now() {
#ifdef __MACH__
	return ((double)clock()) / CLOCKS_PER_SEC * 1e9;
#else
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);

	return ts.tv_sec * 1e9 + ts.tv_nsec;

#endif
}

void setup_benchmarks(Benchmarks* bench) {
	bench->minimum = INT32_MAX;
	bench->maximum = 0;
	bench->sum = 0;
	bench->squared_sum = 0;
	bench->total_start = now();
}

void benchmark(Benchmarks* bench) {
	const bench_t time = now() - bench->single_start;

	if (time < bench->minimum) {
		bench->minimum = time;
	}

	if (time > bench->maximum) {
		bench->maximum = time;
	}

	bench->sum += time;
	bench->squared_sum += (time * time);
}

void evaluate(Benchmarks* bench) {
	const bench_t total_time = now() - bench->total_start;
	printf("\n============ RESULTS ================\n");
	printf("Total duration:     %.3f\tms\n", total_time / 1e6);
	printf("=====================================\n");
}