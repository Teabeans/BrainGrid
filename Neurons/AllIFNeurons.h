/**
 *      @file AllIFNeurons.h
 *
 *      @brief A container of all Integate and Fire (IF) neuron data
 */

/** 
 ** @authors Aaron Oziel, Sean Blackbourn
 **
 ** @class AllIFNeurons AllIFNeurons.h "AllIFNeurons.h"
 **
 ** \latexonly  \subsubsection*{Implementation} \endlatexonly
 ** \htmlonly   <h3>Implementation</h3> \endhtmlonly
 **
 ** A container of all Integate and Fire (IF) neuron data.
 ** This is the base class of all Integate and Fire (IF) neuron classes.
 **
 ** The class uses a data-centric structure, which utilizes a structure as the containers of
 ** all neuron.
 **
 ** The container holds neuron parameters of all neurons.
 ** Each kind of neuron parameter is stored in a 1D array, of which length
 ** is number of all neurons. Each array of a neuron parameter is pointed by a
 ** corresponding member variable of the neuron parameter in the class.
 **
 ** This structure was originally designed for the GPU implementation of the
 ** simulator, and this refactored version of the simulator simply uses that design for
 ** all other implementations as well. This is to simplify transitioning from
 ** single-threaded to multi-threaded.
 **
 ** \latexonly  \subsubsection*{Credits} \endlatexonly
 ** \htmlonly   <h3>Credits</h3> \endhtmlonly
 **
 ** Some models in this simulator is a rewrite of CSIM (2006) and other
 ** work (Stiber and Kawasaki (2007?))
 **
 **/
#pragma once

#include "Global.h"
#include "AllSpikingNeurons.h"
#include "AllIFNeuronsProperties.h"

class AllIFNeurons : public AllSpikingNeurons
{
    public:
        AllIFNeurons();
        AllIFNeurons(const AllIFNeurons &r_neurons);
        virtual ~AllIFNeurons();

        /**
         *  Assignment operator: copy neurons parameters.
         *
         *  @param  r_neurons  Neurons class object to copy from.
         */
        virtual IAllNeurons &operator=(const IAllNeurons &r_neurons);

        /**
         *  Setup the internal structure of the class.
         *  Allocate memories to store all neurons' state.
         *
         *  @param  sim_info  SimulationInfo class to read information from.
         *  @param  clr_info  ClusterInfo class to read information from.
         */
        virtual void setupNeurons(SimulationInfo *sim_info, ClusterInfo *clr_info);

        /**
         *  Cleanup the class.
         *  Deallocate memories.
         */
        virtual void cleanupNeurons();  

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
         *  Creates all the Neurons and assigns initial data for them.
         *
         *  @param  sim_info    SimulationInfo class to read information from.
         *  @param  layout      Layout information of the neunal network.
         *  @param  clr_info    ClusterInfo class to read information from.
         */
        virtual void createAllNeurons(SimulationInfo *sim_info, Layout *layout, ClusterInfo *clr_info);

        /**
         *  Outputs state of the neuron chosen as a string.
         *
         *  @param  i   index of the neuron (in neurons) to output info from.
         *  @return the complete state of the neuron.
         */
        virtual string toString(const int i) const;

        /**
         *  Reads and sets the data for all neurons from input stream.
         *
         *  @param  input       istream to read from.
         *  @param  clr_info    used as a reference to set info for neuronss.
         */
        virtual void deserialize(istream &input, const ClusterInfo *clr_info);

        /**
         *  Writes out the data in all neurons to output stream.
         *
         *  @param  output      stream to write out to.
         *  @param  clr_info    used as a reference to set info for neuronss.
         */
        virtual void serialize(ostream& output, const ClusterInfo *clr_info) const;

    protected:
        /**
         *  Setup the internal structure of the class.
         *
         *  @param  sim_info  SimulationInfo class to read information from.
         *  @param  clr_info  ClusterInfo class to read information from.
         */
        void setupNeuronsInternalState(SimulationInfo *sim_info, ClusterInfo *clr_info);

        /**
         *  Deallocate all resources.
         */
        void cleanupNeuronsInternalState();

#if defined(USE_GPU)
    public:
        /**
         *  Update the state of all neurons for a time step
         *  Notify outgoing synapses if neuron has fired.
         *
         *  @param  synapses               Reference to the allSynapses struct on host memory.
         *  @param  allNeuronsDevice       Reference to the allNeurons struct on device memory.
         *  @param  allSynapsesDevice      Reference to the allSynapses struct on device memory.
         *  @param  sim_info               SimulationInfo to refer from.
         *  @param  randNoise              Reference to the random noise array.
         *  @param  synapseIndexMapDevice  Reference to the SynapseIndexMap on device memory.
         *  @param  clr_info               ClusterInfo to refer from.
         *  @param  iStepOffset            Offset from the current simulation step.
         */
        virtual void advanceNeurons(IAllSynapses &synapses, void* allNeuronsDevice, void* allSynapsesDevice, const SimulationInfo *sim_info, float* randNoise, SynapseIndexMap* synapseIndexMapDevice, const ClusterInfo *clr_info, int iStepOffset);

        /**
         *  Allocate GPU memories to store all neurons' states,
         *  and copy them from host to GPU memory.
         *
         *  @param  allNeuronsDevice   Reference to the allNeurons struct on device memory.
         *  @param  sim_info           SimulationInfo to refer from.
         *  @param  clr_info           ClusterInfo to refer from.
         */
        virtual void allocNeuronDeviceStruct( void** allNeuronsDevice, SimulationInfo *sim_info, ClusterInfo *clr_info );

        /**
         *  Delete GPU memories.
         *
         *  @param  allNeuronsDevice   Reference to the allNeurons struct on device memory.
         *  @param  clr_info           ClusterInfo to refer from.
         */
        virtual void deleteNeuronDeviceStruct( void* allNeuronsDevice, const ClusterInfo *clr_info );

        /**
         *  Copy all neurons' data from host to device.
         *
         *  @param  allNeuronsDevice   Reference to the allNeurons struct on device memory.
         *  @param  sim_info           SimulationInfo to refer from.
         *  @param  clr_info           ClusterInfo to refer from.
         */
        virtual void copyNeuronHostToDevice( void* allNeuronsDevice, const SimulationInfo *sim_info, const ClusterInfo *clr_info );

        /**
         *  Copy all neurons' data from device to host.
         *
         *  @param  allNeuronsDevice   Reference to the allNeurons struct on device memory.
         *  @param  sim_info           SimulationInfo to refer from.
         *  @param  clr_info           ClusterInfo to refer from.
         */
        virtual void copyNeuronDeviceToHost( void* allNeuronsDevice, const SimulationInfo *sim_info, const ClusterInfo *clr_info );

        /**
         *  Copy spike history data stored in device memory to host.
         *
         *  @param  allNeuronsDevice   Reference to the allNeurons struct on device memory.
         *  @param  sim_info           SimulationInfo to refer from.
         *  @param  clr_info           ClusterInfo to refer from.
         */
        virtual void copyNeuronDeviceSpikeHistoryToHost( void* allNeuronsDevice, const SimulationInfo *sim_info, const ClusterInfo *clr_info );

        /**
         *  Copy spike counts data stored in device memory to host.
         *
         *  @param  allNeuronsDevice   Reference to the allNeurons struct on device memory.
         *  @param  clr_info           ClusterInfo to refer from.
         */
        virtual void copyNeuronDeviceSpikeCountsToHost( void* allNeuronsDevice, const ClusterInfo *clr_info );

    protected:
        /**
         *  Allocate GPU memories to store all neurons' states.
         *  (Helper function of allocNeuronDeviceStruct)
         *
         *  @param  allNeuronsProperties         Reference to the AllIFNeuronsProperties struct.
         *  @param  sim_info           SimulationInfo to refer from.
         *  @param  clr_info           ClusterInfo to refer from.
         */
        void allocDeviceStruct( AllIFNeuronsProperties &allNeuronsProperties, SimulationInfo *sim_info, ClusterInfo *clr_info );

        /**
         *  Delete GPU memories.
         *  (Helper function of deleteNeuronDeviceStruct)
         *
         *  @param  allNeuronsProperties         Reference to the AllIFNeuronsProperties struct.
         *  @param  clr_info           ClusterInfo to refer from.
         */
        void deleteDeviceStruct( AllIFNeuronsProperties& allNeuronsProperties, const ClusterInfo *clr_info );

        /**
         *  Copy all neurons' data from host to device.
         *  (Helper function of copyNeuronHostToDevice)
         *
         *  @param  allNeuronsProperties         Reference to the AllIFNeuronsProperties struct.
         *  @param  sim_info           SimulationInfo to refer from.
         *  @param  clr_info           ClusterInfo to refer from.
         */
	void copyHostToDevice( AllIFNeuronsProperties& allNeuronsProperties, const SimulationInfo *sim_info, const ClusterInfo *clr_info );

        /**
         *  Copy all neurons' data from device to host.
         *  (Helper function of copyNeuronDeviceToHost)
         *
         *  @param  allNeuronsProperties         Reference to the AllIFNeuronsProperties struct.
         *  @param  sim_info           SimulationInfo to refer from.
         *  @param  clr_info           ClusterInfo to refer from.
         */
	void copyDeviceToHost( AllIFNeuronsProperties& allNeuronsProperties, const SimulationInfo *sim_info, const ClusterInfo *clr_info );

#endif // defined(USE_GPU)

    protected:
        /**
         *  Copy neurons parameters.
         *
         *  @param  r_neurons  Neurons class object to copy from.
         */
        void copyParameters(const AllIFNeurons &r_neurons);

        /**
         *  Creates a single Neuron and generates data for it.
         *
         *  @param  sim_info     SimulationInfo class to read information from.
         *  @param  neuron_index Index of the neuron to create.
         *  @param  layout       Layout information of the neunal network.
         *  @param  clr_info     ClusterInfo class to read information from.
         */
        void createNeuron(SimulationInfo *sim_info, int neuron_index, Layout *layoug, ClusterInfo *clr_info);

        /**
         *  Set the Neuron at the indexed location to default values.
         *
         *  @param  neuron_index    Index of the Neuron that the synapse belongs to.
         */
        void setNeuronDefaults(const int index);

        /**
         *  Initializes the Neuron constants at the indexed location.
         *
         *  @param  neuron_index    Index of the Neuron.
         *  @param  deltaT          Inner simulation step duration
         */
        virtual void initNeuronConstsFromParamValues(int neuron_index, const BGFLOAT deltaT);

        /**
         *  Sets the data for Neuron #index to input's data.
         *
         *  @param  input       istream to read from.
         *  @param  sim_info    used as a reference to set info for neurons.
         *  @param  i           index of the neuron (in neurons).
         */
        void readNeuron(istream &input, int i);

        /**
         *  Writes out the data in the selected Neuron.
         *
         *  @param  output      stream to write out to.
         *  @param  sim_info    used as a reference to set info for neuronss.
         *  @param  i           index of the neuron (in neurons).
         */
        void writeNeuron(ostream& output, int i) const;

    private:
        /**
         * Min/max values of Iinject.
         */
        BGFLOAT m_Iinject[2];

        /**
         * Min/max values of Inoise.
         */
        BGFLOAT m_Inoise[2];

        /**
         * Min/max values of Vthresh.
         */
        BGFLOAT m_Vthresh[2];

        /**
         * Min/max values of Vresting.
         */
        BGFLOAT m_Vresting[2];

        /**
         * Min/max values of Vreset.
         */
        BGFLOAT m_Vreset[2];

        /**
         * Min/max values of Vinit.
         */
        BGFLOAT m_Vinit[2];

        /**
         * Min/max values of Vthresh.
         */
        BGFLOAT m_starter_Vthresh[2];

        /**
         * Min/max values of Vreset.
         */
        BGFLOAT m_starter_Vreset[2];
};

