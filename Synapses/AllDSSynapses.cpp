#include "AllDSSynapses.h"

// Default constructor
AllDSSynapses::AllDSSynapses() : AllSpikingSynapses()
{
}

// Copy constructor
AllDSSynapses::AllDSSynapses(const AllDSSynapses &r_synapses) : AllSpikingSynapses(r_synapses)
{
    copyParameters(dynamic_cast<const AllDSSynapses &>(r_synapses));
}

AllDSSynapses::~AllDSSynapses()
{
    cleanupSynapses();
}

/*
 *  Assignment operator: copy synapses parameters.
 *
 *  @param  r_synapses  Synapses class object to copy from.
 */
IAllSynapses &AllDSSynapses::operator=(const IAllSynapses &r_synapses)
{
    copyParameters(dynamic_cast<const AllDSSynapses &>(r_synapses));

    return (*this);
}

/*
 *  Copy synapses parameters.
 *
 *  @param  r_synapses  Synapses class object to copy from.
 */
void AllDSSynapses::copyParameters(const AllDSSynapses &r_synapses)
{
    AllSpikingSynapses::copyParameters(r_synapses);
}

/*
 *  Setup the internal structure of the class (allocate memories and initialize them).
 *
 *  @param  sim_info  SimulationInfo class to read information from.
 *  @param  clr_info  ClusterInfo class to read information from.
 */
void AllDSSynapses::setupSynapses(SimulationInfo *sim_info, ClusterInfo *clr_info)
{
    setupSynapses(clr_info->totalClusterNeurons, sim_info->maxSynapsesPerNeuron, sim_info, clr_info);
}

/*
 *  Setup the internal structure of the class (allocate memories and initialize them).
 *
 *  @param  num_neurons   Total number of neurons in the network.
 *  @param  max_synapses  Maximum number of synapses per neuron.
 *  @param  sim_info      SimulationInfo class to read information from.
 *  @param  clr_info      ClusterInfo class to read information from.
 */
void AllDSSynapses::setupSynapses(const int num_neurons, const int max_synapses, SimulationInfo *sim_info, ClusterInfo *clr_info)
{
    setupSynapsesInternalState(sim_info, clr_info);

    // allocate synspses properties data
    m_pSynapsesProperties = new AllDSSynapsesProperties();
    m_pSynapsesProperties->setupSynapsesProperties(num_neurons, max_synapses, sim_info, clr_info);
}

/*
 *  Setup the internal structure of the class.
 *
 *  @param  sim_info  SimulationInfo class to read information from.
 *  @param  clr_info  ClusterInfo class to read information from.
 */
void AllDSSynapses::setupSynapsesInternalState(SimulationInfo *sim_info, ClusterInfo *clr_info)
{
    AllSpikingSynapses::setupSynapsesInternalState(sim_info, clr_info);
}

/*
 *  Cleanup the class (deallocate memories).
 */
void AllDSSynapses::cleanupSynapses()
{
     // deallocate neurons properties data
    delete m_pSynapsesProperties;
    m_pSynapsesProperties = NULL;

    cleanupSynapsesInternalState();
}

/*
 *  Deallocate all resources.
 */
void AllDSSynapses::cleanupSynapsesInternalState()
{
    AllSpikingSynapses::cleanupSynapsesInternalState();
}

/*
 *  Checks the number of required parameters.
 *
 * @return true if all required parameters were successfully read, false otherwise.
 */
bool AllDSSynapses::checkNumParameters()
{
    return (nParams >= 0);
}

/*
 *  Attempts to read parameters from a XML file.
 *
 *  @param  element TiXmlElement to examine.
 *  @return true if successful, false otherwise.
 */
bool AllDSSynapses::readParameters(const TiXmlElement& element)
{
    if (AllSpikingSynapses::readParameters(element)) {
        // this parameter was already handled
        return true;
    }

    return false;
}

/*
 *  Prints out all parameters of the neurons to ostream.
 *
 *  @param  output  ostream to send output to.
 */
void AllDSSynapses::printParameters(ostream &output) const
{
}

/*
 *  Sets the data for Synapse to input's data.
 *
 *  @param  input  istream to read from.
 *  @param  iSyn   Index of the synapse to set.
 */
void AllDSSynapses::readSynapse(istream &input, const BGSIZE iSyn)
{
    AllDSSynapsesProperties *pSynapsesProperties = dynamic_cast<AllDSSynapsesProperties*>(m_pSynapsesProperties);

    AllSpikingSynapses::readSynapse(input, iSyn);

    // input.ignore() so input skips over end-of-line characters.
    input >> pSynapsesProperties->lastSpike[iSyn]; input.ignore();
    input >> pSynapsesProperties->r[iSyn]; input.ignore();
    input >> pSynapsesProperties->u[iSyn]; input.ignore();
    input >> pSynapsesProperties->D[iSyn]; input.ignore();
    input >> pSynapsesProperties->U[iSyn]; input.ignore();
    input >> pSynapsesProperties->F[iSyn]; input.ignore();
}

/*
 *  Write the synapse data to the stream.
 *
 *  @param  output  stream to print out to.
 *  @param  iSyn    Index of the synapse to print out.
 */
void AllDSSynapses::writeSynapse(ostream& output, const BGSIZE iSyn) const 
{
    AllDSSynapsesProperties *pSynapsesProperties = dynamic_cast<AllDSSynapsesProperties*>(m_pSynapsesProperties);

    AllSpikingSynapses::writeSynapse(output, iSyn);

    output << pSynapsesProperties->lastSpike[iSyn] << ends;
    output << pSynapsesProperties->r[iSyn] << ends;
    output << pSynapsesProperties->u[iSyn] << ends;
    output << pSynapsesProperties->D[iSyn] << ends;
    output << pSynapsesProperties->U[iSyn] << ends;
    output << pSynapsesProperties->F[iSyn] << ends;
}

/*
 *  Reset time varying state vars and recompute decay.
 *
 *  @param  iSyn            Index of the synapse to set.
 *  @param  deltaT          Inner simulation step duration
 */
void AllDSSynapses::resetSynapse(const BGSIZE iSyn, const BGFLOAT deltaT)
{
    AllDSSynapsesProperties *pSynapsesProperties = dynamic_cast<AllDSSynapsesProperties*>(m_pSynapsesProperties);

    AllSpikingSynapses::resetSynapse(iSyn, deltaT);

    pSynapsesProperties->u[iSyn] = DEFAULT_U;
    pSynapsesProperties->r[iSyn] = 1.0;
    pSynapsesProperties->lastSpike[iSyn] = ULONG_MAX;
}

/*
 *  Create a Synapse and connect it to the model.
 *
 *  @param  synapses    The synapse list to reference.
 *  @param  iSyn        Index of the synapse to set.
 *  @param  source      Coordinates of the source Neuron.
 *  @param  dest        Coordinates of the destination Neuron.
 *  @param  sum_point   Summation point address.
 *  @param  deltaT      Inner simulation step duration.
 *  @param  type        Type of the Synapse to create.
 */
void AllDSSynapses::createSynapse(const BGSIZE iSyn, int source_index, int dest_index, BGFLOAT *sum_point, const BGFLOAT deltaT, synapseType type)
{
    AllDSSynapsesProperties *pSynapsesProperties = dynamic_cast<AllDSSynapsesProperties*>(m_pSynapsesProperties);

    AllSpikingSynapses::createSynapse(iSyn, source_index, dest_index, sum_point, deltaT, type);

    pSynapsesProperties->U[iSyn] = DEFAULT_U;

    BGFLOAT U;
    BGFLOAT D;
    BGFLOAT F;
    switch (type) {
        case II:
            U = 0.32;
            D = 0.144;
            F = 0.06;
            break;
        case IE:
            U = 0.25;
            D = 0.7;
            F = 0.02;
            break;
        case EI:
            U = 0.05;
            D = 0.125;
            F = 1.2;
            break;
        case EE:
            U = 0.5;
            D = 1.1;
            F = 0.05;
            break;
        default:
            assert( false );
            break;
    }

    pSynapsesProperties->U[iSyn] = U;
    pSynapsesProperties->D[iSyn] = D;
    pSynapsesProperties->F[iSyn] = F;
}

#if !defined(USE_GPU)
/*
 *  Calculate the post synapse response after a spike.
 *
 *  @param  iSyn        Index of the synapse to set.
 *  @param  deltaT      Inner simulation step duration.
 *  @param  iStepOffset      Offset from the current simulation step.
 */
void AllDSSynapses::changePSR(const BGSIZE iSyn, const BGFLOAT deltaT, int iStepOffset)
{
    AllDSSynapsesProperties *pSynapsesProperties = dynamic_cast<AllDSSynapsesProperties*>(m_pSynapsesProperties);

    BGFLOAT &psr = pSynapsesProperties->psr[iSyn];
    BGFLOAT &W = pSynapsesProperties->W[iSyn];
    BGFLOAT &decay = pSynapsesProperties->decay[iSyn];
    uint64_t &lastSpike = pSynapsesProperties->lastSpike[iSyn];
    BGFLOAT &r = pSynapsesProperties->r[iSyn];
    BGFLOAT &u = pSynapsesProperties->u[iSyn];
    BGFLOAT &D = pSynapsesProperties->D[iSyn];
    BGFLOAT &F = pSynapsesProperties->F[iSyn];
    BGFLOAT &U = pSynapsesProperties->U[iSyn];

    // adjust synapse parameters
    uint64_t simulationStep = g_simulationStep + iStepOffset;
    if (lastSpike != ULONG_MAX) {
        BGFLOAT isi = (simulationStep - lastSpike) * deltaT ;
        r = 1 + ( r * ( 1 - u ) - 1 ) * exp( -isi / D );
        u = U + u * ( 1 - U ) * exp( -isi / F );
    }
    psr += ( ( W / decay ) * u * r );    // calculate psr
    lastSpike = simulationStep;          // record the time of the spike
}

#endif // !defined(USE_GPU)
