#include <iostream>
#include <mpi.h>
#include <limits>

int mpi_rank = 0;
int mpi_size = 0;
int mpi_processor_name_length = 0;
char mpi_processor_name[MPI_MAX_PROCESSOR_NAME];

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    // mpi cluster info
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
    MPI_Get_processor_name(mpi_processor_name, &mpi_processor_name_length);
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

    long total_iterations = std::numeric_limits<int>::max();
    long iterations_per_process = total_iterations / mpi_size;
    if (mpi_rank == 0) {
        std::cout << "Total iterations: " << total_iterations << std::endl;

    }

    double start_time = MPI_Wtime();

    // calculate
    double current_result = 0.0, result = 0.0;
    long iteration_end = iterations_per_process * (mpi_rank + 1);
    for (long i = mpi_rank * iterations_per_process; i < iteration_end; i++) {
        current_result += 1.0 / (i * 4.0 + 1.0);
        current_result -= 1.0 / (i * 4.0 + 3.0);
    }
    MPI_Reduce(&current_result, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    if (mpi_rank == 0) {
        std::cout.precision(std::numeric_limits<double>::max_digits10);
        std::cout << "Time(ms): " << (end_time - start_time) * 1000 << std::endl;
        std::cout << "PI: " << result * 4 << std::endl;
    }

    MPI_Finalize();
    return 0;
}
