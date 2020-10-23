/**
 *      @file ISInput.h
 *
 *      @brief An interface for stimulus input classes.
 */

/**
 ** \class ISInput ISInput.h "ISInput.h"
 **
 ** \latexonly  \subsubsection*{Implementation} \endlatexonly
 ** \htmlonly   <h3>Implementation</h3> \endhtmlonly
 **
 ** The ISInput provides an interface for stimulus input classes.
 **
 ** \latexonly  \subsubsection*{Credits} \endlatexonly
 ** \htmlonly   <h3>Credits</h3> \endhtmlonly
 **
 ** Some models in this simulator is a rewrite of CSIM (2006) and other 
 ** work (Stiber and Kawasaki (2007?))
 **
 **
 **     @author Fumitaka Kawasaki
 **/

#pragma once

#ifndef _ISINPUT_H_
#define _ISINPUT_H_

#include "Global.h"
#include "SimulationInfo.h"
#include "IModel.h"
#include "tinyxml.h"

class ISInput
{
public:
    virtual ~ISInput() {}

    /**
     * Initialize data
     *
     * @param[in] psi             Pointer to the simulation information.
     * @param[in] vtClrInfo       Vector of ClusterInfo.
     */
    virtual void init(SimulationInfo* psi, vector<ClusterInfo *> &vtClrInfo) = 0;

    /**
     * Terminate process
     */
    virtual void term(SimulationInfo* psi, vector<ClusterInfo *> const&vtClrInfo) = 0;

    /**
     * Process input stimulus for each time step
     *
     * @param[in] psi             Pointer to the simulation information.
     * @param[in] pci             Pointer to the ClusterInfo class to read information from.
     * @param[in] iStepOffset     Offset from the current simulation step.
     */
    virtual void inputStimulus(const SimulationInfo* psi, ClusterInfo *pci, int iStepOffset) = 0;

    /**
     * Advance input stimulus state.
     *
     * @param[in] pci             Poiter to the ClusterInfo class to read information from.
     * @param[in] iStep           Simulation steps to advance.
     */
    virtual void advanceSInputState(const ClusterInfo *pci, int iStep) = 0;
};

#endif // _ISINPUT_H_
