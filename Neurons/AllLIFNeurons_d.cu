#include "AllLIFNeurons.h"
#include "AllNeuronsDeviceFuncs.h"

#include <helper_cuda.h>

/*
 *  Update the state of all neurons for a time step
 *  Notify outgoing synapses if neuron has fired.
 *
 *  @param  synapses               Reference to the allSynapses struct on host memory.
 *  @param  allNeuronsProperties       Reference to the allNeuronsProperties struct 
 *                                 on device memory.
 *  @param  allSynapsesProperties      Reference to the allSynapsesProperties struct 
 *                                 on device memory.
 *  @param  sim_info               SimulationInfo to refer from.
 *  @param  randNoise              Reference to the random noise array.
 *  @param  synapseIndexMapDevice  Reference to the SynapseIndexMap on device memory.
 *  @param  clr_info               ClusterInfo to refer from.
 *  @param  iStepOffset            Offset from the current simulation step.
 */
void AllLIFNeurons::advanceNeurons( IAllSynapses &synapses, void* allNeuronsProperties, void* allSynapsesProperties, const SimulationInfo *sim_info, float* randNoise, SynapseIndexMap* synapseIndexMapDevice, const ClusterInfo *clr_info, int iStepOffset )
{
    DEBUG (
    int deviceId;
    checkCudaErrors( cudaGetDevice( &deviceId ) );
    assert(deviceId == clr_info->deviceId);
    ); // end DEBUG

    int neuron_count = clr_info->totalClusterNeurons;
    int maxSpikes = (int)((sim_info->epochDuration * sim_info->maxFiringRate));

    // CUDA parameters
    const int threadsPerBlock = 256;
    int blocksPerGrid = ( neuron_count + threadsPerBlock - 1 ) / threadsPerBlock;

    // Advance neurons ------------->
    advanceLIFNeuronsDevice <<< blocksPerGrid, threadsPerBlock >>> ( neuron_count, sim_info->maxSynapsesPerNeuron, maxSpikes, sim_info->deltaT, g_simulationStep, randNoise, (AllIFNeuronsProperties *)allNeuronsProperties, (AllSpikingSynapsesProperties*)allSynapsesProperties, synapseIndexMapDevice, m_fAllowBackPropagation, iStepOffset );
}

