# 3. Quickstart

## 3.1 Quick Sanity Test

As a quick start and sanity test, let's run a small, prepackaged simulation to make sure everything is good to go. 

1. In a terminal window, navigate to the main project folder

   ```shell
   $ cd YOUR_PATH_TO_BRAINGRID/BrainGrid
   ```

2. Unless you have the necessary **HDF5** stuff installed, go into the Makefile and set the conditional flag **CUSEHDF5** to "no" to use default XML output. Set to "yes" if you wish to use HDF5. See the snippet of Makefile below:

   ```cmake
   ################################################################################
   # Conditional Flags
   # -----------------------------------------------------------------------------
   # CUSEHDF5:	 yes - use hdf5 file format 
   #		 	 no  - use default xml 
   # CPMETRICS: yes - see performance of large function calls  
   #		 	 no  - not showing performance results
   ################################################################################
   CUSEHDF5 = no
   CPMETRICS = yes
   ```

   - HDF5 is useful for making the data analysis easier for Matlab, which has native HDF5 support, after a simulation - especially a very long one; but it is fine to use the default XML output.
   - If you like to use HDF5 or have issues with using HDF5, see [Using BrainGrid with HDF5](https://github.com/UWB-Biocomputing/BrainGrid/wiki/Using-BrainGrid-with-HDF5)

   **!!!** Note: Make sure your output file extension in the configuration file (under BrainGrid/configfiles/) matches your choice of **CUSEHDF5** flag. Otherwise an error will be thrown upon compilation. 

   For example, if you are using HDF5, the output file extension should be **.h5** instead of **.xml**. 

   ```xml
   <OutputParams name="OutputParams">
     <stateOutputFileName name="stateOutputFileName">results/static_izh_historyDump.h5
     </stateOutputFileName>
   </OutputParams>
   ```

   The details of configuration file will be discussed in the next section [4. Configuration](braingrid_configuration).

3. Compile the single threaded version

   ```shell
   $ make growth
   ```

   Compile the GPU version:

   ```shell
   $ make growth_cuda
   ```

4. Run it with one of our numerous test files 

   ```shell
   $ ./growth -t ./configfiles/test-small.xml
   ```

   or run with GPU support:

   ```shell
   $ ./growth_cuda -t ./configfiles/test-small.xml
   ```
   
   or run in multithreaded mode:
   
   ```shell
   $ ./growth -c # ./configfiles/test-small.xml
   ```

5. The program will then run and display the current step and epoch of the simulation. The output of the simulation (after the end of the simulation) will be saved in the ```output``` folder.

The run time of this test is small-ish on a fast computer (maybe a couple minutes), but this particular test also doesn't do much. The output will be mostly nothing - but it shouldn't crash or give you anything weird. 

If you want to run a real test, you could use test-small-connected.xml, but be noted that using the single threaded version of this (or any larger test) will result in hours of waiting, but the output will be much more interesting. You can take a look at the next section on **Screen** for how to deal with these wait times.

## 3.2 Use of Screen 

When you run a simulation with BrainGrid, you may not want to wait around for it to run to completion. This is especially true if running it remotely. To help with this, you can use the built in ```screen``` command in Linux.

The `screen` command will essentially allow you to start a simulation and then detach it so that it runs in the background.  This has the huge advantage of allowing you to log out of the server you are remotely connected to.  Here is how:

1. Before running the simulation, start a screen by typing:

   ````shell
   $ screen
   ````

2. Start the Simulation

   ```shell
   $ ./growth -t ./configfiles/test-small-connected.xml
   ```

3. Detach the screen by pressing the following key combinations:
   `"Ctrl+A"`  then `"Ctrl+D"`

4. Allow the simulation to run as long as you want. During this time, you can log out without any problem.

5. Reattach the screen whenever you want to check in on it.

   ```shell
   $ screen -r
   ```

6. If it isn't done yet, detach again and come back later.


-------------
[>> Next: 4. Configuration](http://uwb-biocomputing.github.io/BrainGrid/4_configuration)

-------------
[<< Go back to BrainGrid Home page](http://uwb-biocomputing.github.io/BrainGrid/)
