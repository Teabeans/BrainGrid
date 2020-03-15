#include "AllDynamicSTDPSynapses.h"

AllDynamicSTDPSynapses::AllDynamicSTDPSynapses() : AllSTDPSynapses()
{
    lastSpike = NULL;
    r = NULL;
    u = NULL;
    D = NULL;
    U = NULL;
    F = NULL;
}

AllDynamicSTDPSynapses::AllDynamicSTDPSynapses(const int num_neurons, const int max_synapses) :
        AllSTDPSynapses(num_neurons, max_synapses)
{
    setupSynapses(num_neurons, max_synapses);
}

AllDynamicSTDPSynapses::~AllDynamicSTDPSynapses()
{
    cleanupSynapses();
}

/*
 *  Setup the internal structure of the class (allocate memories and initialize them).
 *
 *  @param  sim_info  SimulationInfo class to read information from.
 */
void AllDynamicSTDPSynapses::setupSynapses(SimulationInfo *sim_info)
{
    setupSynapses(sim_info->totalNeurons, sim_info->maxSynapsesPerNeuron);
}

/*
 *  Setup the internal structure of the class (allocate memories and initialize them).
 * 
 *  @param  num_neurons   Total number of neurons in the network.
 *  @param  max_synapses  Maximum number of synapses per neuron.
 */
void AllDynamicSTDPSynapses::setupSynapses(const int num_neurons, const int max_synapses)
{
    AllSTDPSynapses::setupSynapses(num_neurons, max_synapses);

    BGSIZE max_total_synapses = max_synapses * num_neurons;

    if (max_total_synapses != 0) {
        lastSpike = new uint64_t[max_total_synapses];
        r = new BGFLOAT[max_total_synapses];
        u = new BGFLOAT[max_total_synapses];
        D = new BGFLOAT[max_total_synapses];
        U = new BGFLOAT[max_total_synapses];
        F = new BGFLOAT[max_total_synapses];
    }
}

/*
 *  Cleanup the class (deallocate memories).
 */
void AllDynamicSTDPSynapses::cleanupSynapses()
{
    BGSIZE max_total_synapses = maxSynapsesPerNeuron * count_neurons;

    if (max_total_synapses != 0) {
        delete[] lastSpike;
        delete[] r;
        delete[] u;
        delete[] D;
        delete[] U;
        delete[] F;
    }

    lastSpike = NULL;
    r = NULL;
    u = NULL;
    D = NULL;
    U = NULL;
    F = NULL;

    AllSTDPSynapses::cleanupSynapses();
}

/*
 *  Checks the number of required parameters.
 *
 * @return true if all required parameters were successfully read, false otherwise.
 */
bool AllDynamicSTDPSynapses::checkNumParameters()
{
    return (nParams >= 0);
}

/*
 *  Attempts to read parameters from a XML file.
 *
 *  @param  element TiXmlElement to examine.
 *  @return true if successful, false otherwise.
 */
bool AllDynamicSTDPSynapses::readParameters(const TiXmlElement& element)
{
    if (AllSTDPSynapses::readParameters(element)) {
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
void AllDynamicSTDPSynapses::printParameters(ostream &output) const
{
}

/*
 *  Sets the data for Synapse to input's data.
 *
 *  @param  input  istream to read from.
 *  @param  iSyn   Index of the synapse to set.
 */
void AllDynamicSTDPSynapses::readSynapse(istream &input, const BGSIZE iSyn)
{
    AllSTDPSynapses::readSynapse(input, iSyn);

    // input.ignore() so input skips over end-of-line characters.
    input >> lastSpike[iSyn]; input.ignore();
    input >> r[iSyn]; input.ignore();
    input >> u[iSyn]; input.ignore();
    input >> D[iSyn]; input.ignore();
    input >> U[iSyn]; input.ignore();
    input >> F[iSyn]; input.ignore();
}

/*
 *  Write the synapse data to the stream.
 *
 *  @param  output  stream to print out to.
 *  @param  iSyn    Index of the synapse to print out.
 */
void AllDynamicSTDPSynapses::writeSynapse(ostream& output, const BGSIZE iSyn) const 
{
    AllSTDPSynapses::writeSynapse(output, iSyn);

    output << lastSpike[iSyn] << ends;
    output << r[iSyn] << ends;
    output << u[iSyn] << ends;
    output << D[iSyn] << ends;
    output << U[iSyn] << ends;
    output << F[iSyn] << ends;
}

/*
 *  Reset time varying state vars and recompute decay.
 *
 *  @param  iSyn            Index of the synapse to set.
 *  @param  deltaT          Inner simulation step duration
 */
void AllDynamicSTDPSynapses::resetSynapse(const BGSIZE iSyn, const BGFLOAT deltaT)
{
    AllSTDPSynapses::resetSynapse(iSyn, deltaT);

    u[iSyn] = DEFAULT_U;
    r[iSyn] = 1.0;
    lastSpike[iSyn] = ULONG_MAX;
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
void AllDynamicSTDPSynapses::createSynapse(const BGSIZE iSyn, int source_index, int dest_index, BGFLOAT *sum_point, const BGFLOAT deltaT, synapseType type)
{
    AllSTDPSynapses::createSynapse(iSyn, source_index, dest_index, sum_point, deltaT, type);

    U[iSyn] = DEFAULT_U;

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

    this->U[iSyn] = U;
    this->D[iSyn] = D;
    this->F[iSyn] = F;
}

#if !defined(USE_GPU)
/*
 *  Calculate the post synapse response after a spike.
 *
 *  @param  iSyn        Index of the synapse to set.
 *  @param  deltaT      Inner simulation step duration.
 */
void AllDynamicSTDPSynapses::changePSR(const BGSIZE iSyn, const BGFLOAT deltaT)
{
    BGFLOAT &psr = this->psr[iSyn];
    BGFLOAT &W = this->W[iSyn];
    BGFLOAT &decay = this->decay[iSyn];
    uint64_t &lastSpike = this->lastSpike[iSyn];
    BGFLOAT &r = this->r[iSyn];
    BGFLOAT &u = this->u[iSyn];
    BGFLOAT &D = this->D[iSyn];
    BGFLOAT &F = this->F[iSyn];
    BGFLOAT &U = this->U[iSyn];

    // adjust synapse parameters
    if (lastSpike != ULONG_MAX) {
        BGFLOAT isi = (g_simulationStep - lastSpike) * deltaT ;
        r = 1 + ( r * ( 1 - u ) - 1 ) * exp( -isi / D );
        u = U + u * ( 1 - U ) * exp( -isi / F );
    }
    psr += ( ( W / decay ) * u * r );    // calculate psr
    lastSpike = g_simulationStep;        // record the time of the spike
}

#endif // !defined(USE_GPU)


/*
 *  Prints SynapsesProps data.
 */
void AllDynamicSTDPSynapses::printSynapsesProps() const
{
    AllSTDPSynapses::printSynapsesProps();
    for(int i = 0; i < maxSynapsesPerNeuron * count_neurons; i++) {
        if (W[i] != 0.0) {
            cout << "lastSpike[" << i << "] = " << lastSpike[i];
            cout << " r: " << r[i];
            cout << " u: " << u[i];
            cout << " D: " << D[i];
            cout << " U: " << U[i];
            cout << " F: " << F[i] << endl;
        }
    }
}

#if defined(USE_GPU)
/*
 *  Prints GPU SynapsesProps data.
 * 
 *  @param  allSynapsesDeviceProps   Reference to the AllDynamicSTDPSynapsesProps class on device memory.
 */
void AllDynamicSTDPSynapses::printGPUSynapsesProps( void* allSynapsesDeviceProps ) const
{
    AllDynamicSTDPSynapsesDeviceProperties allSynapsesProps;

    //allocate print out data members
    BGSIZE size = maxSynapsesPerNeuron * count_neurons;
    if (size != 0) {
        BGSIZE *synapse_countsPrint = new BGSIZE[count_neurons];
        BGSIZE maxSynapsesPerNeuronPrint;
        BGSIZE total_synapse_countsPrint;
        int count_neuronsPrint;
        int *sourceNeuronIndexPrint = new int[size];
        int *destNeuronIndexPrint = new int[size];
        BGFLOAT *WPrint = new BGFLOAT[size];

        synapseType *typePrint = new synapseType[size];
        BGFLOAT *psrPrint = new BGFLOAT[size];
        bool *in_usePrint = new bool[size];

        for (BGSIZE i = 0; i < size; i++) {
            in_usePrint[i] = false;
        }

        for (int i = 0; i < count_neurons; i++) {
            synapse_countsPrint[i] = 0;
        }

        BGFLOAT *decayPrint = new BGFLOAT[size];
        int *total_delayPrint = new int[size];
        BGFLOAT *tauPrint = new BGFLOAT[size];

        int *total_delayPostPrint = new int[size];
        BGFLOAT *tauspostPrint = new BGFLOAT[size];
        BGFLOAT *tausprePrint = new BGFLOAT[size];
        BGFLOAT *tauposPrint = new BGFLOAT[size];
        BGFLOAT *taunegPrint = new BGFLOAT[size];
        BGFLOAT *STDPgapPrint = new BGFLOAT[size];
        BGFLOAT *WexPrint = new BGFLOAT[size];
        BGFLOAT *AnegPrint = new BGFLOAT[size];
        BGFLOAT *AposPrint = new BGFLOAT[size];
        BGFLOAT *muposPrint = new BGFLOAT[size];
        BGFLOAT *munegPrint = new BGFLOAT[size];
        bool *useFroemkeDanSTDPPrint = new bool[size];

        uint64_t *lastSpikePrint = new uint64_t[size];
        BGFLOAT *rPrint = new BGFLOAT[size];
        BGFLOAT *uPrint = new BGFLOAT[size];
        BGFLOAT *DPrint = new BGFLOAT[size];
        BGFLOAT *UPrint = new BGFLOAT[size];
        BGFLOAT *FPrint = new BGFLOAT[size];

        // copy everything
        checkCudaErrors( cudaMemcpy ( &allSynapsesProps, allSynapsesDeviceProps, sizeof( AllDynamicSTDPSynapsesDeviceProperties ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( synapse_countsPrint, allSynapsesProps.synapse_counts, count_neurons * sizeof( BGSIZE ), cudaMemcpyDeviceToHost ) );
        maxSynapsesPerNeuronPrint = allSynapsesProps.maxSynapsesPerNeuron;
        total_synapse_countsPrint = allSynapsesProps.total_synapse_counts;
        count_neuronsPrint = allSynapsesProps.count_neurons;

        // Set count_neurons to 0 to avoid illegal memory deallocation
        // at AllSynapsesProps deconstructor.
        allSynapsesProps.count_neurons = 0;

        checkCudaErrors( cudaMemcpy ( sourceNeuronIndexPrint, allSynapsesProps.sourceNeuronIndex, size * sizeof( int ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( destNeuronIndexPrint, allSynapsesProps.destNeuronIndex, size * sizeof( int ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( WPrint, allSynapsesProps.W, size * sizeof( BGFLOAT ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( typePrint, allSynapsesProps.type, size * sizeof( synapseType ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( psrPrint, allSynapsesProps.psr, size * sizeof( BGFLOAT ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( in_usePrint, allSynapsesProps.in_use, size * sizeof( bool ), cudaMemcpyDeviceToHost ) );

        checkCudaErrors( cudaMemcpy ( decayPrint, allSynapsesProps.decay, size * sizeof( BGFLOAT ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( tauPrint, allSynapsesProps.tau, size * sizeof( BGFLOAT ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( total_delayPrint, allSynapsesProps.total_delay,size * sizeof( int ), cudaMemcpyDeviceToHost ) );

        checkCudaErrors( cudaMemcpy ( total_delayPostPrint, allSynapsesProps.total_delayPost, size * sizeof( int ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( tauspostPrint, allSynapsesProps.tauspost, size * sizeof( BGFLOAT ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( tausprePrint, allSynapsesProps.tauspre, size * sizeof( BGFLOAT ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( tauposPrint, allSynapsesProps.taupos, size * sizeof( BGFLOAT ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( taunegPrint, allSynapsesProps.tauneg, size * sizeof( BGFLOAT ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( STDPgapPrint, allSynapsesProps.STDPgap, size * sizeof( BGFLOAT ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( WexPrint, allSynapsesProps.Wex, size * sizeof( BGFLOAT ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( AnegPrint, allSynapsesProps.Aneg, size * sizeof( BGFLOAT ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( AposPrint, allSynapsesProps.Apos, size * sizeof( BGFLOAT ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( muposPrint, allSynapsesProps.mupos, size * sizeof( BGFLOAT ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( munegPrint, allSynapsesProps.muneg, size * sizeof( BGFLOAT ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( useFroemkeDanSTDPPrint, allSynapsesProps.useFroemkeDanSTDP, size * sizeof( bool ), cudaMemcpyDeviceToHost ) );

        checkCudaErrors( cudaMemcpy ( lastSpikePrint, allSynapsesProps.lastSpike, size * sizeof( uint64_t ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( rPrint, allSynapsesProps.r, size * sizeof( BGFLOAT ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( uPrint, allSynapsesProps.u, size * sizeof( BGFLOAT ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( DPrint, allSynapsesProps.D, size * sizeof( BGFLOAT ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( UPrint, allSynapsesProps.U, size * sizeof( BGFLOAT ), cudaMemcpyDeviceToHost ) );
        checkCudaErrors( cudaMemcpy ( FPrint, allSynapsesProps.F, size * sizeof( BGFLOAT ), cudaMemcpyDeviceToHost ) );

        for(int i = 0; i < maxSynapsesPerNeuron * count_neurons; i++) {
            if (WPrint[i] != 0.0) {
                cout << "GPU W[" << i << "] = " << WPrint[i];
                cout << " GPU sourNeuron: " << sourceNeuronIndexPrint[i];
                cout << " GPU desNeuron: " << destNeuronIndexPrint[i];
                cout << " GPU type: " << typePrint[i];
                cout << " GPU psr: " << psrPrint[i];
                cout << " GPU in_use:" << in_usePrint[i];

                cout << " GPU decay: " << decayPrint[i];
                cout << " GPU tau: " << tauPrint[i];
                cout << " GPU total_delay: " << total_delayPrint[i];

                cout << " GPU total_delayPost: " << total_delayPostPrint[i];
                cout << " GPU tauspost: " << tauspostPrint[i];
                cout << " GPU tauspre: " << tausprePrint[i];
                cout << " GPU taupos: " << tauposPrint[i];
                cout << " GPU tauneg: " << taunegPrint[i];
                cout << " GPU STDPgap: " << STDPgapPrint[i];
                cout << " GPU Wex: " << WexPrint[i];
                cout << " GPU Aneg: " << AnegPrint[i];
                cout << " GPU Apos: " << AposPrint[i];
                cout << " GPU mupos: " << muposPrint[i];
                cout << " GPU muneg: " << munegPrint[i];
                cout << " GPU useFroemkeDanSTDP: " << useFroemkeDanSTDPPrint[i];

                cout << " GPU lastSpike: " << lastSpikePrint[i];
                cout << " GPU r: " << rPrint[i];
                cout << " GPU u: " << uPrint[i];
                cout << " GPU D: " << DPrint[i];
                cout << " GPU U: " << UPrint[i];
                cout << " GPU F: " << FPrint[i] << endl;
            }
        }

        for (int i = 0; i < count_neurons; i++) {
            cout << "GPU synapse_counts:" << "neuron[" << i  << "]" << synapse_countsPrint[i] << endl;
        }

        cout << "GPU total_synapse_counts:" << total_synapse_countsPrint << endl;
        cout << "GPU maxSynapsesPerNeuron:" << maxSynapsesPerNeuronPrint << endl;
        cout << "GPU count_neurons:" << count_neuronsPrint << endl;


        // Set count_neurons to 0 to avoid illegal memory deallocation
        // at AllDSSynapsesProps deconstructor.
        allSynapsesProps.count_neurons = 0;

        delete[] destNeuronIndexPrint;
        delete[] WPrint;
        delete[] sourceNeuronIndexPrint;
        delete[] psrPrint;
        delete[] typePrint;
        delete[] in_usePrint;
        delete[] synapse_countsPrint;
        destNeuronIndexPrint = NULL;
        WPrint = NULL;
        sourceNeuronIndexPrint = NULL;
        psrPrint = NULL;
        typePrint = NULL;
        in_usePrint = NULL;
        synapse_countsPrint = NULL;

        delete[] decayPrint;
        delete[] total_delayPrint;
        delete[] tauPrint;
        decayPrint = NULL;
        total_delayPrint = NULL;
        tauPrint = NULL;

        delete[] total_delayPostPrint;
        delete[] tauspostPrint;
        delete[] tausprePrint;
        delete[] tauposPrint;
        delete[] taunegPrint;
        delete[] STDPgapPrint;
        delete[] WexPrint;
        delete[] AnegPrint;
        delete[] AposPrint;
        delete[] muposPrint;
        delete[] munegPrint;
        delete[] useFroemkeDanSTDPPrint;
        total_delayPostPrint = NULL;
        tauspostPrint = NULL;
        tausprePrint = NULL;
        tauposPrint = NULL;
        taunegPrint = NULL;
        STDPgapPrint = NULL;
        WexPrint = NULL;
        AnegPrint = NULL;
        AposPrint = NULL;
        muposPrint = NULL;
        munegPrint = NULL;
        useFroemkeDanSTDPPrint = NULL;

        delete[] lastSpikePrint;
        delete[] rPrint;
        delete[] uPrint;
        delete[] DPrint;
        delete[] UPrint;
        delete[] FPrint;
        lastSpikePrint = NULL;
        rPrint = NULL;
        uPrint = NULL;
        DPrint = NULL;
        UPrint = NULL;
        FPrint = NULL;
    }
}
#endif // USE_GPU
