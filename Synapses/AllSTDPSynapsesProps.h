/**
 *      @file AllSTDPSynapsesProps.h
 *
 *      @brief A container of the base class of all synapse data
 */

#pragma once

#include "AllSpikingSynapsesProps.h"

/**
 * cereal
 */
//#include <cereal/types/polymorphic.hpp> //for inheritance
//#include <cereal/types/base_class.hpp> //for inherit parent's data member
//#include <cereal/types/vector.hpp>
//#include <vector>

class AllSTDPSynapsesProps : public AllSpikingSynapsesProps
{
    public:
        AllSTDPSynapsesProps();
        virtual ~AllSTDPSynapsesProps();

        /**
         *  Setup the internal structure of the class (allocate memories and initialize them).
         *
         *  @param  num_neurons   Total number of neurons in the network.
         *  @param  max_synapses  Maximum number of synapses per neuron.
         *  @param  sim_info  SimulationInfo class to read information from.
         *  @param  clr_info  ClusterInfo class to read information from.
         */
        virtual void setupSynapsesProps(const int num_neurons, const int max_synapses, SimulationInfo *sim_info, ClusterInfo *clr_info);
        
        //! Cereal
        //template<class Archive>
        //void serialize(Archive & archive);

        /*template<class Archive>
        void save(Archive & archive) const;

        template<class Archive>
        void load(Archive & archive);*/

        /**
         *  Prints all SynapsesProps data.
         */
        virtual void printSynapsesProps();

#if defined(USE_GPU)
    public:
        /**
         *  Allocate GPU memories to store all synapses' states,
         *  and copy them from host to GPU memory.
         *
         *  @param  allSynapsesDeviceProps   Reference to the AllSTDPSynapsesProps class on device memory.
         *  @param  num_neurons              Number of neurons.
         *  @param  maxSynapsesPerNeuron     Maximum number of synapses per neuron.
         */
        virtual void setupSynapsesDeviceProps( void** allSynapsesDeviceProps, int num_neurons, int maxSynapsesPerNeuron );

        /**
         *  Delete GPU memories.
         *
         *  @param  allSynapsesDeviceProps  Reference to the AllSTDPSynapsesProps class on device memory.
         */
        virtual void cleanupSynapsesDeviceProps( void* allSynapsesDeviceProps );

        /**
         *  Copy all synapses' data from host to device.
         *
         *  @param  allSynapsesDeviceProps   Reference to the AllSTDPSynapsesProps class on device memory.
         *  @param  num_neurons              Number of neurons.
         *  @param  maxSynapsesPerNeuron     Maximum number of synapses per neuron.
         */
        virtual void copySynapseHostToDeviceProps( void* allSynapsesDeviceProps, int num_neurons, int maxSynapsesPerNeuron );

        /**
         *  Copy all synapses' data from device to host.
         *
         *  @param  allSynapsesDeviceProps   Reference to the AllSTDPSynapsesProps class on device memory.
         *  @param  num_neurons              Number of neurons.
         *  @param  maxSynapsesPerNeuron     Maximum number of synapses per neuron.
         */
        virtual void copySynapseDeviceToHostProps( void* allSynapsesDeviceProps, int num_neurons, int maxSynapsesPerNeuron );

        /**
         *  Prints all GPU SynapsesProps data.
         */
        virtual void printGPUSynapsesProps(void* allSynapsesDeviceProps);

    protected:
        /**
         *  Allocate GPU memories to store all synapses' states.
         *
         *  @param  allSynapsesProps      Reference to the AllSTDPSynapsesProps class.
         *  @param  num_neurons           Number of neurons.
         *  @param  maxSynapsesPerNeuron  Maximum number of synapses per neuron.
         */
        void allocSynapsesDeviceProps( AllSTDPSynapsesProps &allSynapsesProps, int num_neurons, int maxSynapsesPerNeuron);

        /**
         *  Delete GPU memories.
         *
         *  @param  allSynapsesProps  Reference to the AllSTDPSynapsesProps class.
         */
        void deleteSynapsesDeviceProps( AllSTDPSynapsesProps& allSynapsesProps );

        /**
         *  Copy all synapses' data from host to device.
         *  (Helper function of copySynapseHostToDeviceProps)
         *
         *  @param  allSynapsesDeviceProps   Reference to the AllSTDPSynapsesProps class on device memory.
         *  @param  allSynapsesProps         Reference to the AllSTDPSynapsesProps class.
         *  @param  num_neurons              Number of neurons.
         *  @param  maxSynapsesPerNeuron     Maximum number of synapses per neuron.
         */
        void copyHostToDeviceProps( void* allSynapsesDeviceProps, AllSTDPSynapsesProps& allSynapsesProps, int num_neurons, int maxSynapsesPerNeuron );

        /**
         *  Copy all synapses' data from device to host.
         *  (Helper function of copySynapseDeviceToHostProps)
         *
         *  @param  allSynapsesProps         Reference to the AllSTDPSynapsesProps class.
         *  @param  num_neurons              Number of neurons.
         *  @param  maxSynapsesPerNeuron     Maximum number of synapses per neuron.
         */
        void copyDeviceToHostProps( AllSTDPSynapsesProps& allSynapsesProps, int num_neurons, int maxSynapsesPerNeuron);

        /**
         *  Prints all GPU SynapsesProps data.
         * (Helper function of printGPUSynapsesProps)
         */
        void printGPUSynapsesPropsHelper( AllSynapsesProps& allSynapsesProps);
#endif // USE_GPU

        /**
         *  Sets the data for Synapse to input's data.
         *
         *  @param  input  istream to read from.
         *  @param  iSyn   Index of the synapse to set.
         */
        virtual void readSynapseProps(istream &input, const BGSIZE iSyn);

        /**
         *  Write the synapse data to the stream.
         *
         *  @param  output  stream to print out to.
         *  @param  iSyn    Index of the synapse to print out.
         */
        virtual void writeSynapseProps(ostream& output, const BGSIZE iSyn) const;

    private:
        /**
         *  Cleanup the class.
         *  Deallocate memories.
         */
        void cleanupSynapsesProps();

    public:
        /**
         *  The synaptic transmission delay (delay of dendritic backpropagating spike),
         *  descretized into time steps.
         */
        int *total_delayPost;

        /**
         *  Used for extended rule by Froemke and Dan. See Froemke and Dan (2002).
         *  Spike-timing-dependent synaptic modification induced by natural spike trains.
         *  Nature 416 (3/2002).
         */
        BGFLOAT *tauspost;

        /**
         *  sed for extended rule by Froemke and Dan.
         */
        BGFLOAT *tauspre;

        /**
         *  Timeconstant of exponential decay of positive learning window for STDP.
         */
        BGFLOAT *taupos;

        /**
         *  Timeconstant of exponential decay of negative learning window for STDP.
         */
        BGFLOAT *tauneg;

        /**
         *  No learning is performed if \f$|Delta| = |t_{post}-t_{pre}| < STDPgap\f$
         */
        BGFLOAT *STDPgap;
        /**
         *  The maximal/minimal weight of the synapse [readwrite; units=;]
         */
        BGFLOAT *Wex;

        /**
         *  Defines the peak of the negative exponential learning window.
         */
        BGFLOAT *Aneg;

        /**
         *  Defines the peak of the positive exponential learning window.
         */
        BGFLOAT *Apos;

        /**
         *  Extended multiplicative positive update:
         *  \f$dw = (Wex-W)^{mupos} * Apos * exp(-Delta/taupos)\f$.
         *  Set to 0 for basic update. See Guetig, Aharonov, Rotter and Sompolinsky (2003).
         *  Learning input correlations through non-linear asymmetric Hebbian plasticity.
         *  Journal of Neuroscience 23. pp.3697-3714.
         */
        BGFLOAT *mupos;

        /**
         *  Extended multiplicative negative update:
         *  \f$dw = W^{mupos} * Aneg * exp(Delta/tauneg)\f$. Set to 0 for basic update.
         */
        BGFLOAT *muneg;

        /**
         *  True if use the rule given in Froemke and Dan (2002).
         */
        bool *useFroemkeDanSTDP;

        /**
         * The collection of synaptic transmission delay queue.
         */
        EventQueue *postSpikeQueue;
};

//! Cereal Serialization/Deserialization Method
/*template<class Archive>
void AllSTDPSynapsesProps::serialize(Archive & archive) {
    archive(cereal::base_class<AllSpikingSynapsesProps>(this));
}*/

/*template<class Archive>
void AllSTDPSynapsesProps::save(Archive & archive) const
{
    vector<int> total_delayPostVector;
    vector<BGFLOAT> tauspostVector;
    vector<BGFLOAT> tauspreVector;
    vector<BGFLOAT> tauposVector;
    vector<BGFLOAT> taunegVector;
    vector<BGFLOAT> STDPgapVector;
    vector<BGFLOAT> WexVector;
    vector<BGFLOAT> AnegVector;
    vector<BGFLOAT> AposVector;
    vector<BGFLOAT> muposVector;
    vector<BGFLOAT> munegVector;
    vector<bool> useFroemkeDanSTDPVector;

    for(int i = 0; i < maxSynapsesPerNeuron * count_neurons; i++) {
        total_delayPostVector.push_back(total_delayPost[i]);
        tauspostVector.push_back(tauspost[i]);
        tauspreVector.push_back(tauspre[i]);
        tauposVector.push_back(taupos[i]);
        taunegVector.push_back(tauneg[i]);
        STDPgapVector.push_back(STDPgap[i]);
        WexVector.push_back(Wex[i]);
        AnegVector.push_back(Aneg[i]);
        AposVector.push_back(Apos[i]);
        muposVector.push_back(mupos[i]);
        munegVector.push_back(muneg[i]);
        useFroemkeDanSTDPVector.push_back(useFroemkeDanSTDP[i]);
    }

    archive(cereal::base_class<AllSpikingSynapsesProps>(this),
    total_delayPostVector, tauspostVector, tauspreVector,
    tauposVector, taunegVector, STDPgapVector,
    WexVector, AnegVector, AposVector,
    muposVector, munegVector, useFroemkeDanSTDPVector,*postSpikeQueue
    );
}

template<class Archive>
void AllSTDPSynapsesProps::load(Archive & archive) 
{
    vector<int> total_delayPostVector;
    vector<BGFLOAT> tauspostVector;
    vector<BGFLOAT> tauspreVector;
    vector<BGFLOAT> tauposVector;
    vector<BGFLOAT> taunegVector;
    vector<BGFLOAT> STDPgapVector;
    vector<BGFLOAT> WexVector;
    vector<BGFLOAT> AnegVector;
    vector<BGFLOAT> AposVector;
    vector<BGFLOAT> muposVector;
    vector<BGFLOAT> munegVector;
    vector<bool> useFroemkeDanSTDPVector;

    archive(cereal::base_class<AllSpikingSynapsesProps>(this),
    total_delayPostVector, tauspostVector, tauspreVector,
    tauposVector, taunegVector, STDPgapVector,
    WexVector, AnegVector, AposVector,
    muposVector, munegVector, useFroemkeDanSTDPVector, *postSpikeQueue
    );

    for(int i = 0; i < maxSynapsesPerNeuron * count_neurons; i++) {
        total_delayPost[i] = total_delayPostVector[i];
        tauspost[i] = tauspostVector[i];
        tauspre[i] = tauspreVector[i];
        taupos[i] = tauposVector[i];
        tauneg[i] = taunegVector[i];
        STDPgap[i] = STDPgapVector[i];
        Wex[i] = WexVector[i];
        Aneg[i] = AnegVector[i];
        Apos[i] = AposVector[i];
        mupos[i] = muposVector[i];
        muneg[i] = munegVector[i];
        useFroemkeDanSTDP[i] = useFroemkeDanSTDPVector[i];
    }
}*/

//! Cereal
//CEREAL_REGISTER_TYPE(AllSTDPSynapsesProps)