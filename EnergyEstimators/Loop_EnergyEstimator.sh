#!/bin/bash

# Define function to execute root macro
Execute_RootMacro(){

    echo "Executing root macro..."
    echo
    
#     # Execute the root macro
#     root -l -b  <<EOC
# .L /uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/EnergyEstimator.cc
# for (int i=0;i<75;i+=1){EnergyEstimator("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/DefineEventSize/Simus/","1.821positron75",i, "2", 200);}
# for (int i=0;i<100;i+=1){EnergyEstimator("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/DefineEventSize/Simus/","0.547MeVpositron100",i, "2", 200);}
# for (int i=0;i<100;i+=1){EnergyEstimator("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/DefineEventSize/Simus/","1.274MeVgamma100",i, "2", 200);}
# .q
# EOC
    
#     # Execute the root macro
#     root -l -b  <<EOC
# .L /uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/EnergyEstimator.cc
# for (int i=0;i<75;i+=1){EnergyEstimator("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/DefineEventSize/Simus/","1.821positron75",i, "2", 300);}
# for (int i=0;i<100;i+=1){EnergyEstimator("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/DefineEventSize/Simus/","0.547MeVpositron100",i, "2", 300);}
# for (int i=0;i<100;i+=1){EnergyEstimator("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/DefineEventSize/Simus/","1.274MeVgamma100",i, "2", 300);}
# .q
# EOC
    
    # Execute the root macro
    root -l -b  <<EOC
.L /uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/EnergyEstimator.cc
for (int i=0;i<75;i+=1){EnergyEstimator("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/DefineEventSize/Simus/","1.821positron75",i, "2", 500);}
for (int i=0;i<100;i+=1){EnergyEstimator("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/DefineEventSize/Simus/","0.547MeVpositron100",i, "2", 500);}
for (int i=0;i<100;i+=1){EnergyEstimator("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/DefineEventSize/Simus/","1.274MeVgamma100",i, "2", 500);}
.q
EOC
    
    # Execute the root macro
    root -l -b  <<EOC
.L /uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/EnergyEstimator.cc
for (int i=0;i<75;i+=1){EnergyEstimator("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/DefineEventSize/Simus/","1.821positron75",i, "2", 1000);}
for (int i=0;i<100;i+=1){EnergyEstimator("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/DefineEventSize/Simus/","0.547MeVpositron100",i, "2", 1000);}
for (int i=0;i<100;i+=1){EnergyEstimator("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/DefineEventSize/Simus/","1.274MeVgamma100",i, "2", 1000);}
.q
EOC


    echo

}

echo
echo "Warning! Check that the file you want to write in is empty!!"
echo
# rm txtFiles/*/*.txt

Execute_RootMacro

echo "End of executable" 
