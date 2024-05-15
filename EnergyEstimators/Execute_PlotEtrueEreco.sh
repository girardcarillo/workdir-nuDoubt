#!/bin/bash

Execute_RootMacro(){

    echo "Executing root macro..."
    echo

    root -l -b  <<EOC
.L /uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/PlotEtrueEreco.cc
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","0.547MeVpositron100", "2", 200);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","1.821positron75", "2", 200);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","1.274MeVgamma100", "2", 200);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","0.547MeVpositron100", "2", 300);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","1.821positron75", "2", 300);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","1.274MeVgamma100", "2", 300);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","0.547MeVpositron100", "2", 500);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","1.821positron75", "2", 500);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","1.274MeVgamma100", "2", 500);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","0.547MeVpositron100", "2", 1000);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","1.821positron75", "2", 1000);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","1.274MeVgamma100", "2", 1000);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","0.547MeVpositron100", "1", 200);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","1.821positron75", "1", 200);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","1.274MeVgamma100", "1", 200);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","0.547MeVpositron100", "1", 300);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","1.821positron75", "1", 300);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","1.274MeVgamma100", "1", 300);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","0.547MeVpositron100", "1", 500);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","1.821positron75", "1", 500);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","1.274MeVgamma100", "1", 500);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","0.547MeVpositron100", "1", 1000);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","1.821positron75", "1", 1000);
PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","1.274MeVgamma100", "1", 1000);
.q
EOC

}

Execute_RootMacro

