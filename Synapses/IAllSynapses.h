/**
 *      @file IAllSynapses.h
 *
 *      @brief An interface for synapse classes.
 */

#pragma once

#include "Global.h"
#include "SimulationInfo.h"
#include "ClusterInfo.h"

class IAllNeurons;
class IAllSynapses;
class SynapseIndexMap;

typedef void (*fpCreateSynapse_t)(void*, const int, const int, int, int, BGFLOAT*, const BGFLOAT, synapseType);

// enumerate all non-abstract synapse classes.
enum enumClassSynapses {classAllSpikingSynapses, classAllDSSynapses, classAllSTDPSynapses, classAllDynamicSTDPSynapses, undefClassSynapses};

class IAllSynapses
{
    public:
        virtual ~IAllSynapses() {};

        /**
         *  Create and setup synapses properties.
         */
        virtual void createSynapsesProps() = 0;

        /**
         *  Assignment operator: copy synapses parameters.
         *
         *  @param  r_synapses  Synapses class object to copy from.
         */
        virtual IAllSynapses &operator=(const IAllSynapses &r_synapses) = 0;

        /**
         *  Setup the internal structure of the class (allocate memories and initialize them).
         *
         *  @param  sim_info  SimulationInfo class to read information from.
         *  @param  clr_info  ClusterInfo class to read information from.
         */
        virtual void setupSynapses(SimulationInfo *sim_info, ClusterInfo *clr_info) = 0;

        /**
         *  Setup the internal structure of the class (allocate memories and initialize them).
         *
         *  @param  num_neurons   Total number of neurons in the network.
         *  @param  max_synapses  Maximum number of synapses per neuron.
         *  @param  sim_info      SimulationInfo class to read information from.
         *  @param  clr_info      ClusterInfo class to read information from.
         */
        virtual void setupSynapses(const int num_neurons, const int max_synapses, SimulationInfo *sim_info, ClusterInfo *clr_info) = 0;

        /**
         *  Cleanup the class (deallocate memories).
         */
        virtual void cleanupSynapses() = 0;

        /**
         *  Reset time varying state vars and recompute decay.
         *
         *  @param  iSyn     Index of the synapse to set.
         *  @param  deltaT   Inner simulation step duration
         */
        virtual void resetSynapse(const BGSIZE iSyn, const BGFLOAT deltaT) = 0;

        /**
         *  Checks the number of required parameters to read.
         *
         * @return true if all required parameters were successfully read, false otherwise.
         */
        virtual bool checkNumParameters() = 0;

        /**
         *  Attempts to read parameters from a XML file.
         *
         *  @param  element TiXmlElement to examine.
         *  @return true if successful, false otherwise.
         */
        virtual bool readParameters(const TiXmlElement& element) = 0;

        /**
         *  Prints out all parameters of the neurons to ostream.
         *
         *  @param  output  ostream to send output to.
         */
        virtual void printParameters(ostream &output) const = 0;

        /**
         *  Sets the data for Synapses to input's data.
         *
         *  @param  input  istream to read from.
         *  @param clr_info  ClusterInfo class to read information from.
         */
        virtual void deserialize(istream& input, IAllNeurons &neurons, const ClusterInfo *clr_info) = 0;

        /**
         *  Write the synapses data to the stream.
         *
         *  @param  output  stream to print out to.
         *  @param  clr_info  ClusterInfo class to read information from.
         */
        virtual void serialize(ostream& output, const ClusterInfo *clr_info) = 0;

#if !defined(USE_GPU)
        /**
         *  Adds a Synapse to the model, connecting two Neurons.
         *
         *  @param  iSyn        Index of the synapse to be added.
         *  @param  type        The type of the Synapse to add.
         *  @param  src_neuron  The Neuron that sends to this Synapse.
         *  @param  dest_neuron The Neuron that receives from the Synapse.
         *  @param  sum_point   Summation point address.
         *  @param  deltaT      Inner simulation step duration
         *  @param  clr_info    ClusterInfo class to read information from.
         */
        virtual void addSynapse(BGSIZE &iSyn, synapseType type, const int src_neuron, const int dest_neuron, BGFLOAT *sum_point, const BGFLOAT deltaT, const ClusterInfo *clr_info) = 0;
#endif // !USE_GPU

        /**
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
        virtual void createSynapse(const BGSIZE iSyn, int source_index, int dest_index, BGFLOAT* sp, const BGFLOAT deltaT, synapseType type) = 0;

        /**
         *  Get the sign of the synapseType.
         *
         *  @param    type    synapseType I to I, I to E, E to I, or E to E
         *  @return   1 or -1, or 0 if error
         */
        virtual int synSign(const synapseType type) = 0;

#if defined(USE_GPU)
    public:
        /**
         *  Advance all the Synapses in the simulation.
         *  Update the state of all synapses for a time step.
         *
         *  @param  allSynapsesProps      Reference to the allSynapses struct on device memory.
         *  @param  allNeuronsProps       Reference to the allNeurons struct on device memory.
         *  @param  synapseIndexMapDevice  Reference to the SynapseIndexMap on device memory.
         *  @param  sim_info               SimulationInfo class to read information from.
         *  @param  clr_info               ClusterInfo to refer from.
         *  @param  iStepOffset            Offset from the current simulation step.
         */
        virtual void advanceSynapses(void* allSynapsesProps, void* allNeuronsProps, void* synapseIndexMapDevice, const SimulationInfo *sim_info, const ClusterInfo *clr_info, int iStepOffset) = 0;

        /**
         *  Set some parameters used for advanceSynapsesDevice.
         */
        virtual void setAdvanceSynapsesDeviceParams() = 0;

        /**
         *  Set synapse class ID defined by enumClassSynapses for the caller's Synapse class.
         *  The class ID will be set to classSynapses_d in device memory,
         *  and the classSynapses_d will be referred to call a device function for the
         *  particular synapse class.
         *  Because we cannot use virtual function (Polymorphism) in device functions,
         *  we use this scheme.
         *  Note: we used to use a function pointer; however, it caused the growth_cuda crash
         *  (see issue#137).
         */
        virtual void setSynapseClassID() = 0;

#else // !defined(USE_GPU)
    public:
        /**
         *  Advance all the Synapses in the simulation.
         *  Update the state of all synapses for a time step.
         *
         *  @param  sim_info         SimulationInfo class to read information from.
         *  @param  neurons          The Neuron list to search from.
         *  @param  synapseIndexMap  Pointer to the synapse index map.
         *  @param  iStepOffset      Offset from the current simulation step.
         */
        virtual void advanceSynapses(const SimulationInfo *sim_info, IAllNeurons *neurons, SynapseIndexMap *synapseIndexMap, int iStepOffset) = 0;

        /**
         *  Advance one specific Synapse.
         *
         *  @param  iSyn      Index of the Synapse to connect to.
         *  @param  sim_info  SimulationInfo class to read information from.
         *  @param  neurons   The Neuron list to search from.
         *  @param  iStepOffset      Offset from the current simulation step.
         */
        virtual void advanceSynapse(const BGSIZE iSyn, const SimulationInfo *sim_info, IAllNeurons *neurons, int iStepOffset) = 0;

        /**
         *  Remove a synapse from the network.
         *
         *  @param  neuron_index   Index of a neuron to remove from.
         *  @param  iSyn           Index of a synapse to remove.
         */
        virtual void eraseSynapse(const int neuron_index, const BGSIZE iSyn) = 0;
#endif // defined(USE_GPU)
};
