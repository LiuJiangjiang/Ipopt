// Copyright (C) 2008 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Common Public License.
//
// $Id$
//
// Authors:  Madan Sathe (University of Basel), Andreas Waechter (IBM)   2009-08-17
//
//           based on IpIterativePardisoSolverInterface.hpp rev 1535


#ifndef __IPITERATIVEPSPIKESOLVERINTERFACE_HPP__
#define __IPITERATIVEPSPIKESOLVERINTERFACE_HPP__

#include "IpSparseSymLinearSolverInterface.hpp"
#include "IpInexactCq.hpp"
#include "IpIterativeSolverTerminationTester.hpp"

namespace Ipopt
{

  /** Interface to the linear solver Pardiso, derived from
   *  SparseSymLinearSolverInterface.  For details, see description of
   *  SparseSymLinearSolverInterface base class.
   */
  class IterativePspikeSolverInterface: public SparseSymLinearSolverInterface
  {
  public:
    /** @name Constructor/Destructor */
    //@{
    /** Constructor */
    IterativePspikeSolverInterface(IterativeSolverTerminationTester& normal_tester,
                                    IterativeSolverTerminationTester& pd_tester);

    /** Destructor */
    virtual ~IterativePspikeSolverInterface();
    //@}

    /** overloaded from AlgorithmStrategyObject */
    bool InitializeImpl(const OptionsList& options,
                        const std::string& prefix);


    /** @name Methods for requesting solution of the linear system. */
    //@{
    /** Method for initializing internal stuctures. */
    virtual ESymSolverStatus InitializeStructure(Index dim, Index nonzeros,
        const Index *ia,
        const Index *ja);

    /** Method returing an internal array into which the nonzero
     *  elements are to be stored. */
    virtual double* GetValuesArrayPtr();

    /** Solve operation for multiple right hand sides. */
    virtual ESymSolverStatus MultiSolve(bool new_matrix,
                                        const Index* ia,
                                        const Index* ja,
                                        Index nrhs,
                                        double* rhs_vals,
                                        bool check_NegEVals,
                                        Index numberOfNegEVals);

    /** Number of negative eigenvalues detected during last
     *  factorization.
     */
    virtual Index NumberOfNegEVals() const;
    //@}

    //* @name Options of Linear solver */
    //@{
    /** Request to increase quality of solution for next solve.
     */
    virtual bool IncreaseQuality();

    /** Query whether inertia is computed by linear solver.
     *  Returns true, if linear solver provides inertia.
     */
    virtual bool ProvidesInertia() const
    {
      return true;
    }
    /** Query of requested matrix type that the linear solver
     *  understands.
     */
    EMatrixFormat MatrixFormat() const
    {
      return CSR_Format_1_Offset;
    }
    //@}

    /** Methods for IpoptType */
    //@{
    static void RegisterOptions(SmartPtr<RegisteredOptions> roptions);
    //@}

  private:
    /**@name Default Compiler Generated Methods
     * (Hidden to avoid implicit creation/calling).
     * These methods are not implemented and 
     * we do not want the compiler to implement
     * them for us, so we declare them private
     * and do not define them. This ensures that
     * they will not be implicitly created/called. */
    //@{
    /** Default Constructor */
    IterativePspikeSolverInterface();

    /** Copy Constructor */
    IterativePspikeSolverInterface(const IterativePspikeSolverInterface&);

    /** Overloaded Equals Operator */
    void operator=(const IterativePspikeSolverInterface&);
    //@}

    /** @name Information about the matrix */
    //@{
    /** Number of rows and columns of the matrix */
    Index dim_;

    /** Number of nonzeros of the matrix in triplet representation. */
    Index nonzeros_;

    /** Array for storing the values of the matrix. */
    double* a_;
    //@}
    
    /** @name Information about most recent factorization/solve */
    //@{
    /** Number of negative eigenvalues */
    Index negevals_;
    //@}

    /** @name Solver specific options */
    //@{
    //@}

    /** @name Initialization flags */
    //@{
    /** Flag indicating if internal data is initialized.
     *  For initialization, this object needs to have seen a matrix */
    bool initialized_;
    //@}

    /** @name Solver specific information */
    //@{
    //@}

    /**@name Some counters for debugging */
    //@{
    Index debug_last_iter_;
    Index debug_cnt_;
    //@}

    /** @name Internal functions */
    //@{
    /** Call Pardiso to do the analysis phase.
     */
    ESymSolverStatus SymbolicFactorization(const Index* ia,
                                           const Index* ja);

    /** Call Pardiso to factorize the Matrix.
     */
    ESymSolverStatus Factorization(const Index* ia,
                                   const Index* ja,
                                   bool check_NegEVals,
                                   Index numberOfNegEVals);

    /** Call Pardiso to do the Solve.
     */
    ESymSolverStatus Solve(const Index* ia,
                           const Index* ja,
                           Index nrhs,
                           double *rhs_vals);
    //@}

    /** Method to easily access Inexact data */
    InexactData& InexData()
    {
      InexactData& inexact_data =
        static_cast<InexactData&>(IpData().AdditionalData());
      DBG_ASSERT(dynamic_cast<InexactData*>(&IpData().AdditionalData()));
      return inexact_data;
    }

    /** Method to easily access Inexact calculated quantities */
    InexactCq& InexCq()
    {
      InexactCq& inexact_cq =
        static_cast<InexactCq&>(IpCq().AdditionalCq());
      DBG_ASSERT(dynamic_cast<InexactCq*>(&IpCq().AdditionalCq()));
      return inexact_cq;
    }

    /** Termination tester for normal step computation */
    SmartPtr<IterativeSolverTerminationTester> normal_tester_;

    /** Termination tester for primal-dual step computation */
    SmartPtr<IterativeSolverTerminationTester> pd_tester_;

    /** MPI rank */
    int my_rank_;

  };

} // namespace Ipopt
#endif