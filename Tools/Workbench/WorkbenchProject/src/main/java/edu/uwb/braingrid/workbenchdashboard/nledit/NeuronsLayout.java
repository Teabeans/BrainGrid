package edu.uwb.braingrid.workbenchdashboard.nledit;

import java.util.ArrayList;
import java.util.Collections;

public class NeuronsLayout {
	// neuron type index
	/** neuron type index for other neurons */
	public static final int OTR = 0;
	/** neuron type index for inhibitory neurons */
	public static final int INH = 1;
	/** neuron type index for active neurons */
	public static final int ACT = 2;
	/** neuron type index for probed neurons */
	public static final int PRB = 3;
	/** neuron type index for overlapping INH and ACT neurons */
	public static final int OVP = 4;
	
	/** an array to store index of active neurons */
	public ArrayList<Integer> activeNList = new ArrayList<Integer>();
	/** an array to store index of inhibitory neurons */
	public ArrayList<Integer> inhNList = new ArrayList<Integer>();
	/** an array to store index of probed neurons */
	public ArrayList<Integer> probedNList = new ArrayList<Integer>();
	
	public NeuronsLayout() {
		
	}
	
	public int getNeuronType(int index) {
		int cIndex = OTR;
		if (activeNList.contains(index)
				&& inhNList.contains(index)) {
			cIndex = OVP;
		} else if (activeNList.contains(index)) {
			cIndex = ACT;
		} else if (inhNList.contains(index)) {
			cIndex = INH;
		}
		return cIndex;
	}
	
	public boolean isProbed(int index) {
		return probedNList.contains(index);
	}
	
	public void changeIndex(int neuronType, int index) {
		switch (neuronType) {
		case INH: // inhibitory neurons edit mode
			if (!inhNList.contains(index)) {
				inhNList.add(index);
				Collections.sort(inhNList);
				if (activeNList.contains(index)) {
					activeNList.remove(index);
				}
			} else {
				inhNList.remove(index);
			}
			break;

		case ACT: // active neurons edit mode
			if (!activeNList.contains(index)) {
				activeNList.add(index);
				Collections.sort(activeNList);
				if (inhNList.contains(index)) {
					inhNList.remove(index);
				}
			} else {
				activeNList.remove(index);
			}
			break;

		case PRB: // probed neurons edit mode
			if (!probedNList.contains(index)) {
				probedNList.add(index);
				Collections.sort(probedNList);
			} else {
				probedNList.remove(index);
			}
			break;
		}
	}
}