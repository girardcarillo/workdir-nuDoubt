#!/bin/bash

Execute_RootMacro(){

    echo "Executing root macro..."
    echo

    root -b -q 'PlotNumberOfHits.cc("../DefineEventSize/Simus/", "0.547MeVpositron100")'
    root -b -q 'PlotNumberOfHits.cc("../DefineEventSize/Simus/", "1.821positron75")'
    root -b -q 'PlotNumberOfHits.cc("../DefineEventSize/Simus/", "1.274MeVgamma100")'
    
}

Execute_RootMacro
