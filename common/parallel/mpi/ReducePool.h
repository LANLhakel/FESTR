#ifndef REDUCEPOOL_H
#define REDUCEPOOL_H

/**
 * @file ReducePool.h
 * @brief Implements MPI parallelism for reduction operations.
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 1 June 2017\n
 * Last modified on 3 March 2019
 * @copyright (c) 2017, Triad National Security, LLC.
 * All rights reserved.\n
 */

#include "mpi.h"
#include <vector>
#include <cstdlib>
#include <iostream>

//-----------------------------------------------------------------------------

/// Framework for MPI parallelism for reduction operations

/** Assumptions and restrictions:\n
 * There are at least two processes.\n
 * The rank of the root process is 0.\n
 * All processes (ranks) run on chips of the same architecture.\n
 * \n
 * The user must initialize the partially-reduced array named vpartial in the
 * function ReducePool::initialize_partial and then compute vpartial in the
 * function ReducePool::perform_task in a manner that is consistent with the
 * chosen values for class members ReducePool::datatype and ReducePool::redop\n
 */

template <typename IT, typename VT> // IT: input type; VT: value type
class ReducePool
{
private:

    /// MPI communicator for *this task pool
    MPI_Comm comm;

    /// Number of MPI processes in *this communicator
    int nranks;

    /// Rank id of *this process
    int my_rank;

    /**
     * @brief Function pointer to the distributed intialization
     * @param[in] nvalues Size of the reduced array
     * @param[out] vpartial Partially reduced array from this process
     */
    void (*initialize_partial)(const int nvalues, VT *vpartial);

    /**
     * @brief Function pointer to the distributed task
     * @param[in] itobj Input for the distributed task
     * @param[in] nvalues Size of the reduced array
     * @param[out] vpartial Partially reduced array from this process
     */
    void (*perform_task)(const IT &itobj, const int nvalues, VT *vpartial);

    /**
     * @brief Function pointer to the root-process task
     * @param[in] nvalues Size of the reduced array
     * @param[in] vfinal Completely reduced array from all processes
     */
    void (*process_results)(const int nvalues, const VT *vfinal);

    /** List of data (tasks) to be processed;\n
     *  all ranks have a copy of this whole list, although each process only
     *  works on its own assigned portion using the ReducePool::perform_task
     *  function to find its own partially reduced answer vpartial;\n
     *  the root process (rank 0) assembles the final reduced result vfinal
     *  from these partially reduced results and dispatches it using the
     *  ReducePool::process_results function\n
     */
    std::vector<IT> v;

    /// The number of tasks ( ReducePool::v.size() )
    int ntasks;

    /// Number of reduced values (size of output data from each task)
    int nvalues;
    
    /// MPI Datatype (e.g., MPI_INT, MPI_FLOAT, MPI_DOUBLE, etc.)
    MPI_Datatype datatype;

    /** MPI reduce operation handle (takes the following values);\n
     * MPI_MAX - Returns the maximum element\n
     * MPI_MIN - Returns the minimum element\n
     * MPI_SUM - Sums the elements\n
     * MPI_PROD - Multiplies the elements\n
     * MPI_LAND - Performs a logical AND across the elements\n
     * MPI_LOR - Performs a logical OR across the elements\n
     * MPI_BAND - Performs a bitwise AND across the bits of the elements\n
     * MPI_BOR - Performs a bitwise OR across the bits of the elements\n
     * MPI_MAXLOC - Returns the maximum value and the rank of the process that
     *              owns it\n
     * MPI_MINLOC - Returns the minimum value and the rank of the process that
     *              owns it\n
     */
    MPI_Op redop;

    /// Constructor helper
    void init(void);

public:

    /// Default constructor
    ReducePool(void);

    /**
     * @brief Parametrized constructor: without task queue initialization
     * @param[in] comm_in MPI communicator for *this task pool
     * @param[in] fi Pointer to the distributed initialization function
     * @param[in] tf Pointer to the distributed task function
     * @param[in] rf Pointer to the root-process function
     * @param[in] nvalues_in Number of reduced values
     * @param[in] din MPI datatype
     * @param[in] opin MPI Reduce operation
     */
    ReducePool(const MPI_Comm comm_in,
               void (*fi)(const int, VT *),
               void (*tf)(const IT &, const int, VT *),
               void (*rf)(const int, const VT *),
               const int nvalues_in,
               const MPI_Datatype din,
               const MPI_Op opin);

    /**
     * @brief Parametrized constructor: with task queue initialization
     * @param[in] comm_in MPI communicator for *this task pool
     * @param[in] fi Pointer to the distributed initialization function
     * @param[in] tf Pointer to the distributed task function
     * @param[in] rf Pointer to the root-process function
     * @param[in] vin Task vector
     * @param[in] nvalues_in Number of reduced values
     * @param[in] din MPI datatype
     * @param[in] opin MPI Reduce operation
     */
    ReducePool(const MPI_Comm comm_in,
               void (*fi)(const int, VT *),
               void (*tf)(const IT &, const int, VT *),
               void (*rf)(const int, const VT *),
               const std::vector<IT> &vin,
               const int nvalues_in,
               const MPI_Datatype din,
               const MPI_Op opin);

    /// Destructor
    ~ReducePool(void);

    /**
     * @brief Setter for the task vector
     * @param[in] vin Task vector
     */
    void set_vector(const std::vector<IT> &vin);

    ///
    /**
     * @brief Adds a task to the vector
     * @param[in] itobj Input object for ReducePool::perform_task
     */
    void add_task(const IT &itobj);

    /// Processes the vector of parallel tasks and produces the reduced result
    void execute(void);
};

//-----------------------------------------------------------------------------

template <typename IT, typename VT>
void ReducePool<IT, VT>::init(void)
{
    MPI_Comm_size(comm, &nranks);
    MPI_Comm_rank(comm, &my_rank);
    if (my_rank != 0) process_results = NULL;
}

//-----------------------------------------------------------------------------

template <typename IT, typename VT>
ReducePool<IT, VT>::ReducePool(void):
    comm(MPI_COMM_WORLD), nranks(0), my_rank(0), initialize_partial(NULL),
    perform_task(NULL), process_results(NULL), v(), ntasks(0),
    nvalues(0), datatype(MPI_INT), redop(MPI_MAX)
{}

//-----------------------------------------------------------------------------

template <typename IT, typename VT>
ReducePool<IT, VT>::ReducePool(const MPI_Comm comm_in,
                               void (*fi)(const int, VT *),
                               void (*tf)(const IT &, const int, VT *),
                               void (*rf)(const int, const VT *),
                               const int nvalues_in,
                               const MPI_Datatype din,
                               const MPI_Op opin):
    comm(comm_in), nranks(0), my_rank(0), initialize_partial(fi),
    perform_task(tf), process_results(rf), v(), ntasks(0),
    nvalues(nvalues_in), datatype(din), redop(opin)
{
    init();
}

//-----------------------------------------------------------------------------

template <typename IT, typename VT>
ReducePool<IT, VT>::ReducePool(const MPI_Comm comm_in,
                               void (*fi)(const int, VT *),
                               void (*tf)(const IT &, const int, VT *),
                               void (*rf)(const int, const VT *),
                               const std::vector<IT> &vin,
                               const int nvalues_in,
                               const MPI_Datatype din,
                               const MPI_Op opin):
    comm(comm_in), nranks(0), my_rank(0), initialize_partial(fi),
    perform_task(tf), process_results(rf), v(vin), ntasks(0),
    nvalues(nvalues_in), datatype(din), redop(opin)
{
    init();
    set_vector(vin);
}

//-----------------------------------------------------------------------------

template <typename IT, typename VT>
ReducePool<IT, VT>::~ReducePool(void)
{
    comm = MPI_COMM_WORLD;
    nranks = 0;
    my_rank = 0;
    initialize_partial = NULL;
    perform_task = NULL;
    process_results = NULL;
    v.clear();
    ntasks = 0;
    nvalues = 0;
    datatype = MPI_INT;
    redop = MPI_MAX;
}

//-----------------------------------------------------------------------------

template <typename IT, typename VT>
void ReducePool<IT, VT>::set_vector(const std::vector<IT> &vin)
{
    v = vin;
    ntasks = static_cast<int>(v.size());
}

//-----------------------------------------------------------------------------

template <typename IT, typename VT>
void ReducePool<IT, VT>::add_task(const IT &itobj)
{
    v.push_back(itobj);
    ++ntasks;
}

//-----------------------------------------------------------------------------

template <typename IT, typename VT>
void ReducePool<IT, VT>::execute(void)
{
    if (nranks < 2)
    {
        if (my_rank == 0)
        {
            std::cerr << "Error: at least two MPI processes are required "
                      << "in order to use ReducePool.\nnranks = " << nranks
                      << std::endl;
        }
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }

    size_t nbytes( static_cast<size_t>(nvalues) * sizeof(VT) );

    VT *vfinal = (VT *)malloc(nbytes); // final reduced array from all ranks
    if (vfinal == NULL)
    {
        std::cerr << "Error in vfinal malloc" << std::endl;
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }

    VT *vpartial = (VT *)malloc(nbytes); // partial reduced array from this rank
    if (vpartial == NULL)
    {
        std::cerr << "Error in vpartial malloc" << std::endl;
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }
    (*initialize_partial)(nvalues, vpartial);

    int quotient(ntasks / nranks);
    int remainder(ntasks % nranks);

    int my_offset( my_rank * quotient );
    for (int k = 0; k < quotient; ++k) // equal distribution of tasks
        (*perform_task)(v.at(my_offset + k), nvalues, vpartial);

    int offset( nranks * quotient );
    if (my_rank < remainder) // distribution of leftover tasks
        (*perform_task)(v.at(offset + my_rank), nvalues, vpartial);

    MPI_Reduce(vpartial, vfinal, nvalues, datatype, redop, 0, comm);
    if (my_rank == 0) (*process_results)(nvalues, vfinal);
    free(vpartial);
    free(vfinal);
    MPI_Barrier(comm);
}

//-----------------------------------------------------------------------------

#endif // REDUCEPOOL_H
