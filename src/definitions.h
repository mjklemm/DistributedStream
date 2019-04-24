#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <string.h>


#ifndef STREAM_TYPE
#define STREAM_TYPE double
#endif

# ifndef MIN
# define MIN(x,y) ((x)<(y)?(x):(y))
# endif
# ifndef MAX
# define MAX(x,y) ((x)>(y)?(x):(y))
# endif



#define ROOT 0
#define MAX_FILE_NAME_LENGTH 500

typedef struct performance_result {
	double avg;
	double min;
	double max;
} performance_result;

typedef struct benchmark_results {
	struct performance_result Copy;
	struct performance_result Scale;
	struct performance_result Add;
	struct performance_result Triad;
	char name[MPI_MAX_PROCESSOR_NAME];
} benchmark_results;

typedef struct aggregate_results {
	struct performance_result Copy;
	struct performance_result Scale;
	struct performance_result Add;
	struct performance_result Triad;
	char copy_max[MPI_MAX_PROCESSOR_NAME];
	char scale_max[MPI_MAX_PROCESSOR_NAME];
	char add_max[MPI_MAX_PROCESSOR_NAME];
	char triad_max[MPI_MAX_PROCESSOR_NAME];
} aggregate_results;

int stream_memory_task(benchmark_results *b_results, int psize, int prank, int node_size, int *array_size);
int stream_persistent_memory_task(benchmark_results *b_results, int psize, int prank, int node_size, int *array_size);
void collect_results(benchmark_results result, aggregate_results *agg_result, aggregate_results *node_results, int psize, int prank, int node_comm, int node_size, int node_rank);
void initialise_benchmark_results(benchmark_results *b_results);
void collect_individual_result(performance_result indivi, performance_result *result, performance_result *node_result, char *max_name, int psize, int prank, char *name, int node_comm, int node_size, int node_rank);
void print_results(aggregate_results a_results, int psize, int array_size, int processes_per_node);
