#!/bin/bash

Execute_RootMacro(){

    echo "Executing root macro..."
    echo

    root -l -b  <<EOC
.L /uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/PlotRatioEtrueEreco.cc
PlotRatioEtrueEreco("2", 200);
PlotRatioEtrueEreco("2", 300);
PlotRatioEtrueEreco("2", 500);
PlotRatioEtrueEreco("2", 1000);
PlotRatioEtrueEreco("1", 200);
PlotRatioEtrueEreco("1", 300);
PlotRatioEtrueEreco("1", 500);
PlotRatioEtrueEreco("1", 1000);
.q
EOC

}

Execute_RootMacro
