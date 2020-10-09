#ifndef LANL_ASC_PEM_TASKPOOL_H_
#define LANL_ASC_PEM_TASKPOOL_H_

/**
 * @file TaskPool.h
 * @brief Implements MPI parallelism using dynamic load balancing.
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 3 February 2016\n
 * Last modified on 27 February 2020
 * @copyright (c) 2016, Triad National Security, LLC.
 * All rights reserved.\n
 */

#include <mpi.h>

#include <algorithm>
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
 * Type IT must contain public members: char *b,\n
 * and public methods: void allocate_buffer(const int), \n
 * void clear_buffer(), int pack(), void unpack().\n
 * \n
 * Type OT must contain public members: char *b, int case_id, int rank,\n
 * and public methods: void allocate_buffer(const int), \n
 * void clear_buffer(), int pack(), void unpack().\n
 */

template <typename IT, typename OT> // IT: input type; OT: output type
class TaskPool
{
public:

    /// Default constructor
    TaskPool();

    /**
     * @brief Parametrized constructor: without task queue initialization
     * @param[in] comm_in MPI communicator for *this task pool
     * @param[in] tf Pointer to the distributed task function
     * @param[in] rf Pointer to the root-process function
     */
    TaskPool(const MPI_Comm comm_in,
             void (*tf)(const IT &, OT &),
             void (*rf)(const OT &));

    /**
     * @brief Parametrized constructor: with task queue initialization
     * @param[in] comm_in MPI communicator for *this task pool
     * @param[in] tf Pointer to the distributed task function
     * @param[in] rf Pointer to the root-process function
     * @param[in] qin Task queue
     */
    TaskPool(const MPI_Comm comm_in,
             void (*tf)(const IT &, OT &),
             void (*rf)(const OT &),
             const std::queue<IT> &qin);

    /// Destructor
    ~TaskPool();

    /**
     * @brief Setter for the task queue
     * @param[in] qin Task queue
     */
    void set_queue(const std::queue<IT> &qin);

    ///
    /**
     * @brief Adds a task to the queue
     * @param[in] itobj Input object for TaskPool::perform_task
     */
    void add_task(const IT &itobj);

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
    void (*perform_task)(const IT &itobj, OT &otobj);

    /**
     * @brief Function pointer to the root-process task
     * @param[in] otobj Output from the distributed task;
     * used as input for the root-process task
     */
    void (*process_results)(const OT &otobj);

    /// Pool of tasks to be done
    std::queue<IT> q;

    /// Constructor helper
    void init();
};

//-----------------------------------------------------------------------------

template <typename IT, typename OT>
void TaskPool<IT, OT>::init()
{
    MPI_Comm_size(comm, &nranks);
    MPI_Comm_rank(comm, &my_rank);

    if (my_rank == 0)
        perform_task = NULL; // root process does not call perform_task()
    else
        process_results = NULL; // only root process calls process_results()
}

//-----------------------------------------------------------------------------

template <typename IT, typename OT>
TaskPool<IT, OT>::TaskPool():
    comm(MPI_COMM_WORLD), nranks(0), my_rank(0),
    perform_task(NULL), process_results(NULL), q()
{}

//-----------------------------------------------------------------------------

template <typename IT, typename OT>
TaskPool<IT, OT>::TaskPool(const MPI_Comm comm_in,
                           void (*tf)(const IT &, OT &),
                           void (*rf)(const OT &)):
    comm(comm_in), nranks(0), my_rank(0),
    perform_task(tf), process_results(rf), q()
{
    init();
}

//-----------------------------------------------------------------------------

template <typename IT, typename OT>
TaskPool<IT, OT>::TaskPool(const MPI_Comm comm_in,
                           void (*tf)(const IT &, OT &),
                           void (*rf)(const OT &),
                           const std::queue<IT> &qin):
    comm(comm_in), nranks(0), my_rank(0),
    perform_task(tf), process_results(rf), q()
{
    init();
    set_queue(qin);
}

//-----------------------------------------------------------------------------

template <typename IT, typename OT>
TaskPool<IT, OT>::~TaskPool()
{
    comm = MPI_COMM_WORLD;
    nranks = 0;
    my_rank = 0;
    perform_task = NULL;
    process_results = NULL;
    IT itobj;
    while (!q.empty())
    {
        itobj = q.front();
        if (itobj.b != NULL) itobj.clear_buffer();
        q.pop();
    }
}

//-----------------------------------------------------------------------------

template <typename IT, typename OT>
void TaskPool<IT, OT>::set_queue(const std::queue<IT> &qin)
{
    if (my_rank == 0) q = qin; // only root process maintains the queue
}

//-----------------------------------------------------------------------------

template <typename IT, typename OT>
void TaskPool<IT, OT>::add_task(const IT &itobj)
{
    if (my_rank == 0) q.push(itobj); // only root process maintains the queue
}

//-----------------------------------------------------------------------------

template <typename IT, typename OT>
void TaskPool<IT, OT>::execute()
{
    if (nranks < 2)
    {
        if (my_rank == 0)
        {
            std::cerr << "Error: at least two MPI processes are required "
                      << "in order to use TaskPool.\nnranks = " << nranks
                      << std::endl;
        }
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }

    int rank;   // communicating process
    int tag;    // message tag
    MPI_Status st;
    IT itobj;   // parallel input
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
            itobj = q.front();
            nbytes = itobj.pack();
            MPI_Send(&nbytes, 1, MPI_INT, rank, tag, comm);
                
            // send distributed task
            tag = j + nranks;
            MPI_Send(itobj.b, nbytes, MPI_BYTE, rank, tag, comm);
            itobj.clear_buffer();
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
            MPI_Recv(&nbytes, 1, MPI_INT,
                     MPI_ANY_SOURCE, MPI_ANY_TAG, comm, &st);
            rank = otobj.rank = st.MPI_SOURCE;
            tag = rank + 3*nranks;
            otobj.allocate_buffer(nbytes);
            MPI_Recv(otobj.b, nbytes, MPI_BYTE, rank, tag, comm, &st);

            // send continuation message to the available rank
            tag = rank;
            itobj = q.front();
            nbytes = itobj.pack();
            MPI_Send(&nbytes, 1, MPI_INT, rank, tag, comm);
            
            // send next distributed task and update task queue
            tag = rank + nranks;
            MPI_Send(itobj.b, nbytes, MPI_BYTE, rank, tag, comm);
            itobj.clear_buffer();
            q.pop();
            --nq;

            // process task results
            otobj.unpack();
            ++case_id;
            otobj.case_id = case_id;
            (*process_results)(otobj);
        }

        for (j = 1; j <= ninit; ++j) // final collection of results
        {
            // receive the next completed task
            MPI_Recv(&nbytes, 1, MPI_INT,
                     MPI_ANY_SOURCE, MPI_ANY_TAG, comm, &st);
            rank = otobj.rank = st.MPI_SOURCE;
            tag = rank + 3*nranks;
            otobj.allocate_buffer(nbytes);
            MPI_Recv(otobj.b, nbytes, MPI_BYTE, rank, tag, comm, &st);

            // send termination message
            tag = rank;
            nbytes = 0;
            MPI_Send(&nbytes, 1, MPI_INT, rank, tag, comm);

            // process task results
            otobj.unpack();
            ++case_id;
            otobj.case_id = case_id;
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
            itobj.allocate_buffer(nbytes);
            MPI_Recv(itobj.b, nbytes, MPI_BYTE, rank, tag, comm, &st);
            itobj.unpack();

            // perform the distributed task
            (*perform_task)(itobj, otobj);

            // send results of completed task back to the root process
            tag = my_rank + 2*nranks;
            nbytes = otobj.pack();
            MPI_Send(&nbytes, 1, MPI_INT, rank, tag, comm);
            tag = my_rank + 3*nranks;
            MPI_Send(otobj.b, nbytes, MPI_BYTE, rank, tag, comm);
            otobj.clear_buffer();
        }
    }   // if (my_rank == 0)

    MPI_Barrier(comm);
}

//-----------------------------------------------------------------------------

#endif  // LANL_ASC_PEM_TASKPOOL_H_
