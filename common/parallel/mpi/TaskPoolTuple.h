#ifndef LANL_ASC_PEM_TASKPOOLTUPLE_H_
#define LANL_ASC_PEM_TASKPOOLTUPLE_H_

/**
 * @file TaskPoolTuple.h
 * @brief Implements MPI parallelism using dynamic load balancing.
 * @author Peter Hakel
 * @version 0.0
 * @date Created on 3 February 2016\n
 * Last modified on 9 January 2021
 * @copyright (c) 2016, Triad National Security, LLC.
 * All rights reserved.\n
 */

#include <mpi.h>

#include <bytes.h>

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <queue>

//-----------------------------------------------------------------------------

/// Framework for a dynamic distribution of parallel tasks using MPI

/** Assumptions and restrictions:\n
 * There are at least two processes.\n
 * The rank of the root process is 0.\n
 * All processes (ranks) run on chips of the same architecture.\n
 * \n
 * Type IT must be a std::tuple supported by bytes.h\n
 * \n
 * Type OT must be a std::tuple supported by bytes.h, with members:\n
 * 0: int = case_id, 1: int = rank,\n
 */

template <typename IT, typename OT> // IT: input type; OT: output type
class TaskPoolTuple
{
public:

    /// Default constructor
    TaskPoolTuple();

    /**
     * @brief Parametrized constructor: without task queue initialization
     * @param[in] comm_in MPI communicator for *this task pool
     * @param[in] tf Pointer to the distributed task function
     * @param[in] rf Pointer to the root-process function
     */
    TaskPoolTuple(const MPI_Comm comm_in,
             void (*tf)(const IT&, OT&),
             void (*rf)(const OT&));

    /**
     * @brief Parametrized constructor: with task queue initialization
     * @param[in] comm_in MPI communicator for *this task pool
     * @param[in] tf Pointer to the distributed task function
     * @param[in] rf Pointer to the root-process function
     * @param[in] qin Task queue
     */
    TaskPoolTuple(const MPI_Comm comm_in,
             void (*tf)(const IT&, OT&),
             void (*rf)(const OT&),
             const std::queue<IT>& qin);

    /// Destructor
    ~TaskPoolTuple();

    /**
     * @brief Setter for the task queue
     * @param[in] qin Task queue
     */
    void set_queue(const std::queue<IT>& qin);

    ///
    /**
     * @brief Adds a task to the queue
     * @param[in] itobj Input object for TaskPoolTuple::perform_task
     */
    void add_task(const IT& itobj);

    /// Processes the queue of parallel tasks
    void execute();


private:

    /// MPI communicator for *this task pool
    MPI_Comm comm;

    /// Number of MPI processes in *this communicator
    int nranks;

    /// Rank id of *this process
    int my_rank;

    /**
     * @brief Function pointer to the distributed task
     * @param[in] itobj Input for the distributed task
     * @param[out] otobj Output from the distributed task
     */
    void (*perform_task)(const IT& itobj, OT& otobj);

    /**
     * @brief Function pointer to the root-process task
     * @param[in] otobj Output from the distributed task;
     * used as input for the root-process task
     */
    void (*process_results)(const OT& otobj);

    /// Pool of tasks to be done
    std::queue<IT> q;

    /// Constructor helper
    void init();
};

//-----------------------------------------------------------------------------

template <typename IT, typename OT>
void TaskPoolTuple<IT, OT>::init()
{
    MPI_Comm_size(comm, &nranks);
    MPI_Comm_rank(comm, &my_rank);

    if (my_rank == 0)
        perform_task = nullptr; // root process does not call perform_task()
    else
        process_results = nullptr; // only root process calls process_results()
}

//-----------------------------------------------------------------------------

template <typename IT, typename OT>
TaskPoolTuple<IT, OT>::TaskPoolTuple():
    comm(MPI_COMM_WORLD), nranks(0), my_rank(0),
    perform_task(nullptr), process_results(nullptr), q()
{}

//-----------------------------------------------------------------------------

template <typename IT, typename OT>
TaskPoolTuple<IT, OT>::TaskPoolTuple(const MPI_Comm comm_in,
                           void (*tf)(const IT&, OT&),
                           void (*rf)(const OT&)):
    comm(comm_in), nranks(0), my_rank(0),
    perform_task(tf), process_results(rf), q()
{
    init();
}

//-----------------------------------------------------------------------------

template <typename IT, typename OT>
TaskPoolTuple<IT, OT>::TaskPoolTuple(const MPI_Comm comm_in,
                           void (*tf)(const IT&, OT&),
                           void (*rf)(const OT&),
                           const std::queue<IT>& qin):
    comm(comm_in), nranks(0), my_rank(0),
    perform_task(tf), process_results(rf), q()
{
    init();
    set_queue(qin);
}

//-----------------------------------------------------------------------------

template <typename IT, typename OT>
TaskPoolTuple<IT, OT>::~TaskPoolTuple()
{
    comm = MPI_COMM_WORLD;
    nranks = 0;
    my_rank = 0;
    perform_task = nullptr;
    process_results = nullptr;
    while (!q.empty()) q.pop();
}

//-----------------------------------------------------------------------------

template <typename IT, typename OT>
void TaskPoolTuple<IT, OT>::set_queue(const std::queue<IT>& qin)
{
    if (my_rank == 0) q = qin; // only root process maintains the queue
}

//-----------------------------------------------------------------------------

template <typename IT, typename OT>
void TaskPoolTuple<IT, OT>::add_task(const IT& itobj)
{
    if (my_rank == 0) q.push(itobj); // only root process maintains the queue
}

//-----------------------------------------------------------------------------

template <typename IT, typename OT>
void TaskPoolTuple<IT, OT>::execute()
{
    if (nranks < 2)
    {
        if (my_rank == 0)
        {
            std::cerr << "Error: at least two MPI processes are required "
                      << "in order to use TaskPoolTuple.\nnranks = " << nranks
                      << std::endl;
        }
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }

    int rank;   // communicating process
    int tag;    // message tag
    MPI_Status st;
    OT otobj;   // parallel output
    int nbytes; // size of next message: > 0 to continue; = 0 to terminate

    if (my_rank == 0) // root process path
    {
        int j; // indexes worker ranks
        int nq = q.size(); // number of to-do tasks in the queue
        int ninit = std::min(nq, nranks-1); // number of initial tasks

        for (j = 1; j <= ninit; ++j) // initial distribution of tasks
        {
            // send continuation message
            rank = tag = j;
            nbytes = bytes::size_of_tuple(q.front());
            MPI_Send(&nbytes, 1, MPI_INT, rank, tag, comm);
                
            // send distributed task
            tag = j + nranks;
            char *bi = (char *)malloc(nbytes);
            bytes::pack_tuple(bi, q.front());
            MPI_Send(bi, nbytes, MPI_BYTE, rank, tag, comm);
            free(bi);
            q.pop();
        }
        nq -= ninit;

        // send termination messages to unused ranks
        nbytes = 0;
        for (j = ninit+1; j < nranks; ++j)
        {
            rank = tag = j;
            MPI_Send(&nbytes, 1, MPI_INT, rank, tag, comm);
        }

        // listener and task-pool distribution loop
        int case_id = 0;
        while (nq > 0)
        {
            // receive the next completed task
            MPI_Recv(&nbytes, 1, MPI_INT,
                     MPI_ANY_SOURCE, MPI_ANY_TAG, comm, &st);
            rank = st.MPI_SOURCE;
            tag = rank + 3*nranks;
            char *bo = (char *)malloc(nbytes);
            MPI_Recv(bo, nbytes, MPI_BYTE, rank, tag, comm, &st);

            // send continuation message to the available rank
            tag = rank;
            nbytes = bytes::size_of_tuple(q.front());
            MPI_Send(&nbytes, 1, MPI_INT, rank, tag, comm);

            // send next distributed task and update task queue
            tag = rank + nranks;
            char *bi = (char *)malloc(nbytes);
            bytes::pack_tuple(bi, q.front());
            MPI_Send(bi, nbytes, MPI_BYTE, rank, tag, comm);
            free(bi);
            q.pop();
            --nq;

            // process task results
            bytes::unpack_tuple(otobj, bo);
            free(bo);
            std::get<0>(otobj) = ++case_id;
            std::get<1>(otobj) = rank;
            (*process_results)(otobj);
        }

        for (j = 1; j <= ninit; ++j) // final collection of results
        {
            // receive the next completed task
            MPI_Recv(&nbytes, 1, MPI_INT,
                     MPI_ANY_SOURCE, MPI_ANY_TAG, comm, &st);
            rank = st.MPI_SOURCE;
            tag = rank + 3*nranks;
            char *bo = (char *)malloc(nbytes);
            MPI_Recv(bo, nbytes, MPI_BYTE, rank, tag, comm, &st);

            // send termination message
            tag = rank;
            nbytes = 0;
            MPI_Send(&nbytes, 1, MPI_INT, rank, tag, comm);

            // process task results
            bytes::unpack_tuple(otobj, bo);
            free(bo);
            std::get<0>(otobj) = ++case_id;
            std::get<1>(otobj) = rank;
            (*process_results)(otobj);
        }
    }   // end root process path

    else // my_rank != 0
    {
        rank = 0; // communication with the root process
        IT itobj; // parallel input
        while (true)
        {
            // continuation/termination
            tag = my_rank;
            MPI_Recv(&nbytes, 1, MPI_INT, rank, tag, comm, &st);
            if (nbytes == 0) break; // no more tasks for this rank

            // receive new task from root process
            tag = my_rank + nranks;
            char *bi = (char *)malloc(nbytes);
            MPI_Recv(bi, nbytes, MPI_BYTE, rank, tag, comm, &st);
            bytes::unpack_tuple(itobj, bi);
            free(bi);

            // perform the distributed task
            (*perform_task)(itobj, otobj);

            // send results of completed task back to the root process
            tag = my_rank + 2*nranks;
            nbytes = bytes::size_of_tuple(otobj);
            MPI_Send(&nbytes, 1, MPI_INT, rank, tag, comm);
            tag = my_rank + 3*nranks;
            char *bo = (char *)malloc(nbytes);
            bytes::pack_tuple(bo, otobj);
            MPI_Send(bo, nbytes, MPI_BYTE, rank, tag, comm);
            free(bo);
        }
    }   // if (my_rank == 0)

    MPI_Barrier(comm);
}

//-----------------------------------------------------------------------------

#endif  // LANL_ASC_PEM_TASKPOOLTUPLE_H_
