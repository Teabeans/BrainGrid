/**
 *      @file AllSynapses.h
 *
 *      @brief A container of all synapse data
 */

/** 
 * @authors Aaron Oziel, Sean Blackbourn
 * 
 * @class AllSynapses AllSynapses.h "AllSynapses.h"
 *
 * \latexonly  \subsubsection*{Implementation} \endlatexonly
 * \htmlonly   <h3>Implementation</h3> \endhtmlonly
 *
 *  The container holds synapse parameters of all synapses. 
 *  Each kind of synapse parameter is stored in a 2D array. Each item in the first 
 *  dimention of the array corresponds with each neuron, and each item in the second
 *  dimension of the array corresponds with a synapse parameter of each synapse of the neuron. 
 *  Bacause each neuron owns different number of synapses, the number of synapses 
 *  for each neuron is stored in a 1D array, synapse_counts.
 *
 *  For CUDA implementation, we used another structure, AllSynapsesDevice, where synapse
 *  parameters are stored in 1D arrays instead of 2D arrays, so that device functions
 *  can access these data less latency. When copying a synapse parameter, P[i][j],
 *  from host to device, it is stored in P[i * max_synapses_per_neuron + j] in 
 *  AllSynapsesDevice structure.
 *
 *  The latest implementation uses the identical data struture between host and CUDA;
 *  that is, synapse parameters are stored in a 1D array, so we don't need conversion 
 *  when copying data between host and device memory.
 *
 * \latexonly  \subsubsection*{Credits} \endlatexonly
 * \htmlonly   <h3>Credits</h3> \endhtmlonly
 *
 * Some models in this simulator is a rewrite of CSIM (2006) and other
 * work (Stiber and Kawasaki (2007?))
 */

#pragma once

#include "Global.h"
#include "SimulationInfo.h"
#include "IAllSynapses.h"
#include "AllSynapsesProps.h"

#ifdef _WIN32
typedef unsigned _int8 uint8_t;
#endif

class IAllNeurons;

class AllSynapses : public IAllSynapses
{
    public:
        AllSynapses();
        virtual ~AllSynapses();

        /**
         *  Assignment operator: copy synapses parameters.
         *
         *  @param  r_synapses  Synapses class object to copy from.
         */
        virtual IAllSynapses &operator=(const IAllSynapses &r_synapses);

        /**
         *  Setup the internal structure of the class (allocate memories and initialize them).
         *
         *  @param  sim_info  SimulationInfo class to read information from.
         *  @param  clr_info  ClusterInfo class to read information from.
         */
        virtual void setupSynapses(SimulationInfo *sim_info, ClusterInfo *clr_info);

        /**
         *  Setup the internal structure of the class (allocate memories and initialize them).
         *
         *  @param  num_neurons   Total number of neurons in the network.
         *  @param  max_synapses  Maximum number of synapses per neuron.
         *  @param  sim_info      SimulationInfo class to read information from.
         *  @param  clr_info      ClusterInfo class to read information from.
         */
        virtual void setupSynapses(const int num_neurons, const int max_synapses, SimulationInfo *sim_info, ClusterInfo *clr_info);

        /**
         *  Cleanup the class (deallocate memories).
         */
        virtual void cleanupSynapses();

        /**
         *  Checks the number of required parameters to read.
         *
         * @return true if all required parameters were successfully read, false otherwise.
         */
        virtual bool checkNumParameters();

        /**
         *  Attempts to read parameters from a XML file.
         *
         *  @param  element TiXmlElement to examine.
         *  @return true if successful, false otherwise.
         */
        virtual bool readParameters(const TiXmlElement& element);

        /**
         *  Prints out all parameters of the neurons to ostream.
         *
         *  @param  output  ostream to send output to.
         */
        virtual void printParameters(ostream &output) const;

        /**
         *  Reset time varying state vars and recompute decay.
         *
         *  @param  iSyn     Index of the synapse to set.
         *  @param  deltaT   Inner simulation step duration
         */
        virtual void resetSynapse(const BGSIZE iSyn, const BGFLOAT deltaT);

        /**
         *  Sets the data for Synapses to input's data.
         *
         *  @param  input  istream to read from.
         *  @param  clr_info  ClusterInfo class to read information from.
         */
        virtual void deserialize(istream& input, IAllNeurons &neurons, const ClusterInfo *clr_info);

        /**
         *  Write the synapses data to the stream.
         *
         *  @param  output  stream to print out to.
         *  @param  clr_info  ClusterInfo class to read information from.
         */
        virtual void serialize(ostream& output, const ClusterInfo *clr_info);

        /**
         *  Adds a Synapse to the model, connecting two Neurons.
         *
         *  @param  iSyn        Index of the synapse to be added.
         *  @param  type        The type of the Synapse to add.
         *  @param  src_neuron  The Neuron that sends to this Synapse.
         *  @param  dest_neuron The Neuron that receives from the Synapse.
         *  @param  sum_point   Summation point address.
         *  @param  deltaT      Inner simulation step duration
         *  @param  clr_info    ClusterInfo to refer from.
         */
        virtual void addSynapse(BGSIZE &iSyn, synapseType type, const int src_neuron, const int dest_neuron, BGFLOAT *sum_point, const BGFLOAT deltaT, const ClusterInfo *clr_info);

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
        int synSign(const synapseType type);

#if !defined(USE_GPU)
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
        virtual void advanceSynapses(const SimulationInfo *sim_info, IAllNeurons *neurons, SynapseIndexMap *synapseIndexMap, int iStepOffset);

        /**
         *  Remove a synapse from the network.
         *
         *  @param  neuron_index   Index of a neuron to remove from.
         *  @param  iSyn           Index of a synapse to remove.
         */
        virtual void eraseSynapse(const int neuron_index, const BGSIZE iSyn);
#endif // !defined(USE_GPU)
    public:
        // The factor to adjust overlapping area to synapse weight.
        static constexpr BGFLOAT SYNAPSE_STRENGTH_ADJUSTMENT = 1.0e-8;

        /**
         * Pointer to the synapses property data.
         */
        class AllSynapsesProps* m_pSynapsesProps;
};
