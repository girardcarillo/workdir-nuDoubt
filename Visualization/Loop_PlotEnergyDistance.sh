#!/bin/bash

# Define function to execute root macro
Execute_RootMacro(){

    echo "Executing root macro..."
    echo
    
    # Execute the root macro
    root -l -b  <<EOC
.L /uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/Visualization/PlotEnergyDistance.cc
for (int i=0;i<75;i+=1){PlotEnergyDistance("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/DefineEventSize/Simus/","1.821positron75",i);}
for (int i=0;i<100;i+=1){PlotEnergyDistance("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/DefineEventSize/Simus/","0.547MeVpositron100",i);}
for (int i=0;i<100;i+=1){PlotEnergyDistance("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/DefineEventSize/Simus/","1.274MeVgamma100",i);}
.q
EOC

    echo

}

echo "Removing root files..."

rm histograms/*.root

echo "Removing text files..."

rm txtFiles/*.txt

Execute_RootMacro

echo
echo "Adding root files..."

hadd histograms/Distance_energy_1.821positron75.root histograms/1.821positron75/Distance_energy_1.821positron75_event*.root
hadd histograms/Distance_energy_0.547MeVpositron100.root histograms/0.547MeVpositron100/Distance_energy_0.547MeVpositron100_event*.root
hadd histograms/Distance_energy_1.274MeVgamma100.root histograms/1.274MeVgamma100/Distance_energy_1.274MeVgamma100_event*.root

hadd histograms/Distance_energyCum_1.821positron75.root histograms/1.821positron75/Distance_energyCum_1.821positron75_event*.root
hadd histograms/Distance_energyCum_0.547MeVpositron100.root histograms/0.547MeVpositron100/Distance_energyCum_0.547MeVpositron100_event*.root
hadd histograms/Distance_energyCum_1.274MeVgamma100.root histograms/1.274MeVgamma100/Distance_energyCum_1.274MeVgamma100_event*.root
