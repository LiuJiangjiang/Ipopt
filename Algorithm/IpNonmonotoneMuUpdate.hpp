// Copyright (C) 2004, International Business Machines and others.
// All Rights Reserved.
// This code is published under the Common Public License.
//
// $Id$
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-08-13

#ifndef __IPNONMONOTONEMUUPDATE_HPP__
#define __IPNONMONOTONEMUUPDATE_HPP__

#include "IpMuUpdate.hpp"
#include "IpLineSearch.hpp"
#include "IpMuOracle.hpp"

namespace Ipopt
{

  /** Non-monotone mu update.
   */
  class NonmonotoneMuUpdate : public MuUpdate
  {
  public:
    /**@name Constructors/Destructors */
    //@{
    /** Constructor */
    NonmonotoneMuUpdate(const SmartPtr<LineSearch>& linesearch,
                        const SmartPtr<MuOracle>& free_mu_oracle,
                        const SmartPtr<MuOracle>& fix_mu_oracle=NULL);
    /** Default destructor */
    virtual ~NonmonotoneMuUpdate();
    //@}

    /** Initialize method - overloaded from AlgorithmStrategyObject */
    virtual bool InitializeImpl(const OptionsList& options,
                                const std::string& prefix);

    /** Method for determining the barrier parameter for the next iteration.
     *  When the optimality error for the current barrier parameter is less than
     *  a tolerance, the barrier parameter is reduced, and the Reset method of the
     *  LineSearch object linesearch is called.
     *  TODO: MORE DETAILS HERE */
    virtual void UpdateBarrierParameter();

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
    NonmonotoneMuUpdate();

    /** Copy Constructor */
    NonmonotoneMuUpdate(const NonmonotoneMuUpdate&);

    /** Overloaded Equals Operator */
    void operator=(const NonmonotoneMuUpdate&);
    //@}

    /** @name Algorithmic parameters */
    //@{
    Number mu_max_;
    Number mu_min_;
    Number tau_min_;
    Number tau_max_;
    //@}

    /** @name Strategy objects */
    //@{
    /** Pointer to strategy object that is to be used for computing a
     *  suggested value of the barrier parameter in the free mu mode.
     */
    SmartPtr<MuOracle> free_mu_oracle_;
    /** Line search object of the Ipopt algorithm.  */
    SmartPtr<LineSearch> linesearch_;
    /** Pointer to strategy object that is to be used for computing a
     *  suggested value for the fixed mu mode.  If NULL, the current
     *  average complementarity is used.
     */
    SmartPtr<MuOracle> fix_mu_oracle_;
    //@}

    /** @name Methods and data defining the outer globalization
     *  strategy (might be a strategy object later). */
    //@{
    void InitializeFixedMuGlobalization();
    /** Check whether the point in the "current" fields offers
     *  sufficient reduction in order to remain in or switch to the
     *  free mu mode. */
    bool CheckSufficientProgress();
    /** Include the current point in internal memory to as accepted
     *  point */
    void RememberCurrentPointAsAccepted();
    /** Compute the value of the fixed mu that should be used in a new
     *  fixed mu phase.  This method is called at the beginning of a
     *  new fixed mu phase. */
    Number NewFixedMu();
    /** Compute value for the fraction-to-the-boundary parameter given
     *  mu */
    Number Compute_tau(Number mu);

    /** Method for computing the 1-norm of the primal dual system at
     *  the current point.  The individual components (dual
     *  infeasibility, primal infeasibility, complementarity) are
     *  scaled to each other. */
    Number curr_norm_pd_system();

    /** Maximal number of reference values (algorithmic parameter) */
    Index num_refs_max_;
    /** Values of the currently stored reference values (norm of pd
     *  equations) */
    std::list<Number> refs_vals_;
    /** Factor requested to reduce the reference values */
    Number refs_red_fact_;
    /** Flag indicating whether the barrier parameter should never be
     *  fixed (no globalization) */
    bool mu_never_fix_;
    //@}

    /** Flag indicating whether the problem has any inequality constraints */
    bool no_bounds_;
    /** Flag indicating whether no_bounds_ has been initialized */
    bool check_if_no_bounds_;
  };

} // namespace Ipopt

#endif
