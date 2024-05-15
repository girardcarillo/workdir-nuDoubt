#!/bin/bash

# Define function to execute root macro
Execute_RootMacro(){

    echo "Executing root macro..."
    echo

    # Execute the root macro

    root -l -b  <<EOC
.L /uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/Visualization_paper/VisualizeHits.cc
for (int i=0;i<50;i+=1){VisualizeHits("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/Simus_DBD/Basic_LiquidO_geometry/","2.8MeVelectron50",i);}
.q
EOC

#      root -l -b  <<EOC
# .L /uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/Visualization_paper/VisualizeHits.cc
# for (int i=0;i<50;i+=1){VisualizeHits("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/Simus_DBD/","2.8MeVgamma50",i);}
# .q
# EOC

#      root -l -b  <<EOC
# .L /uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/Visualization_paper/VisualizeHits.cc
# for (int i=0;i<50;i+=1){VisualizeHits("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/Simus_DBD/","1.78MeVpositron50",i);}
# .q
# EOC

#      root -l -b  <<EOC
# .L VisualizeHits.cc
# for (int i=0;i<50;i+=1){VisualizeHits("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/Simus_DBD/","0.38MeV2xpositron50",i);}
# .q
# EOC

    echo "\nEnd of macro"

}

Execute_RootMacro
