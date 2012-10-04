#include <cstdlib>
#include <iostream>
#include <ctime>

#include "mpi.h"

using namespace std;

class communicator
{

    private:
        MPI::Intracomm  even_comm_id;
        MPI::Group even_group_id;
        int even_id;
        int even_id_sum;
        int even_p;
        int *even_rank;

        int i;
        int id;
        int ierr;
        int j;

        MPI::Intracomm odd_comm_id;
        MPI::Group odd_group_id;
        int odd_id;
        int odd_id_sum;
        int odd_p;
        int *odd_rank;

        int p;
        MPI::Group world_group_id;
        double wtime;
    public:
        communicator(int argc, char *argv[]) {
            MPI::Init(argc, argv);
        }

        void process_communicator();
        ~communicator() {
            MPI::Finalize();

            if ( id == 0 ) {
                cout << "\n";
                cout << "COMMUNICATOR_MPI:\n";
                cout << "  Normal end of execution.\n";
                cout << "\n";
                timestamp ( );
            }

        }
        void timestamp();
};

void communicator::process_communicator()
{

    p = MPI::COMM_WORLD.Get_size ( );

    id = MPI::COMM_WORLD.Get_rank ( );

    if ( id == 0 ) {
        timestamp ( );
        cout << "\n";
        cout << "COMMUNICATOR_MPI - Master process:\n";
        cout << "  C++/MPI version\n";
        cout << "  An MPI example program.\n";
        cout << "\n";
        cout << "  The number of processes is " << p << "\n";
        cout << "\n";
    }

    cout << "  Process " << id << " says 'Hello, world!'\n";

    world_group_id = MPI::COMM_WORLD.Get_group ( );

    even_p = ( p + 1 ) / 2;
    even_rank = new int[even_p];
    j = 0;

    for ( i = 0; i < p; i = i + 2 ) {
        even_rank[j] = i;
        j = j + 1;
    }

    even_group_id = world_group_id.Incl ( even_p, even_rank );

    even_comm_id = MPI::COMM_WORLD.Create ( even_group_id );

    odd_p = p / 2;
    odd_rank = new int[odd_p];
    j = 0;

    for ( i = 1; i < p; i = i + 2 ) {
        odd_rank[j] = i;
        j = j + 1;
    }

    odd_group_id = world_group_id.Incl ( odd_p, odd_rank );

    odd_comm_id = MPI::COMM_WORLD.Create ( odd_group_id );

    if ( id % 2 == 0 ) {
        even_id = even_comm_id.Get_rank ( );
        odd_id = -1;
    } else {
        odd_id = odd_comm_id.Get_rank ( );
        even_id = -1;
    }

    if ( even_id != -1 ) {
        even_comm_id.Reduce ( &id, &even_id_sum, 1, MPI::INT, MPI::SUM, 0 );
    }

    if ( even_id == 0 ) {
        cout << "  Number of processes in even communicator = " << even_p << "\n";
        cout << "  Sum of global ID's in even communicator  = " << even_id_sum << "\n";
    }

    if ( odd_id != -1 ) {
        odd_comm_id.Reduce ( &id, &odd_id_sum,  1, MPI::INT, MPI::SUM, 0 );
    }

    if ( odd_id == 0 ) {
        cout << "  Number of processes in odd communicator  = " << odd_p  << "\n";
        cout << "  Sum of global ID's in odd communicator   = " << odd_id_sum << "\n";
    }


}


void communicator::timestamp ( )
{
# define TIME_SIZE 40

    static char time_buffer[TIME_SIZE];
    const struct std::tm *tm_ptr;
    size_t len;
    std::time_t now;

    now = std::time ( NULL );
    tm_ptr = std::localtime ( &now );

    len = std::strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm_ptr );

    std::cout << time_buffer << "\n";

    return;
# undef TIME_SIZE
}

int main(int argc, char *argv[])
{

    communicator communicator_test(argc, argv);
    communicator_test.process_communicator();
}
