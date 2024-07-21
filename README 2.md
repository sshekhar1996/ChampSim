Steps to run the simulator

# Installing Champsim

Installation of Champsim requires following the README.md under https://github.com/ChampSim/ChampSim/blob/master/README.md

# Compile

Replace the installed ```branch``` folder under Champsim with the ```branch``` folder in this directory to include all the code additions made by our team.

In the file ```btb/basic_btb.cc``` change ```BTB_WAY = 2``` on line 27.

Edit the configuration file under ```/ChampSim/champsim_config.json``` as

```"branch_predictor": "gshare"``` or 
```"branch_predictor": "perceptron"``` or 
```"branch_predictor": "tage"``` or 
```"branch_predictor": "hybrid_pt"``` or 
```"branch_predictor": "hybrid_gp"``` or 
```"branch_predictor": "hybrid_tg"```

Run the following commands
```
$ ./config.sh champsim_config.json
$ make
```
Optional step to save terminal output to file:
```
$ script gshare_602.txt
```

# Download traces

Download the following traces from https://dpc3.compas.cs.stonybrook.edu/champsim-traces/speccpu/

```
$ 602.gcc_s-2226B.champsimtrace.xz
$ 605.mcf_s-472B.champsimtrace.xz
$ 625.x264_s-18B.champsimtrace.xz
```

Add them under the Champsim folder.

# Run simulation

Execute the binary directly. 

```
$ bin/champsim --warmup_instructions 200000000 --simulation_instructions 500000000 602.gcc_s-2226B.champsimtrace.xz
$ bin/champsim --warmup_instructions 200000000 --simulation_instructions 500000000 605.mcf_s-472B.champsimtrace.xz
$ bin/champsim --warmup_instructions 200000000 --simulation_instructions 500000000 625.x264_s-18B.champsimtrace.xz
```


# Evaluate Simulation

ChampSim gives results for Instructions per Cycle, MPKI, Prediction Accuracy and MPKI lost to various branch types. <br>
There are some other useful metrics printed out at the end of simulation. <br>
This folder also contains the output generated and saved from the terminal that were used by us in the report.
