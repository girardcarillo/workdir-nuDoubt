#!/bin/bash

# Define function to execute root macro
Execute_RootMacro(){

    echo "Executing root macro..."
    echo

    # Execute the root macro

#     root -l -b  <<EOC
# .L /uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/Visualization_paper/VisualizeHits.cc
# for (int i=0;i<50;i+=1){VisualizeHits("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/Simus_DBD/","2.8MeVelectron1000",i);}
# .q
# EOC

#      root -l -b  <<EOC
# .L /uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/Visualization_paper/VisualizeHits.cc
# for (int i=0;i<1000;i+=1){VisualizeHits("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/Simus_DBD/","2.8MeVgamma1000",i);}
# .q
# EOC

#      root -l -b  <<EOC
# .L /uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/Visualization_paper/VisualizeHits.cc
# for (int i=0;i<1000;i+=1){VisualizeHits("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/Simus_DBD/","1.78MeVpositron1000",i);}
# .q
# EOC

     root -l -b  <<EOC
.L /uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/Visualization_paper/VisualizeHits.cc
for (int i=0;i<10;i+=1){VisualizeHits("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/Simus_DBD/","0.38MeV2xpositron1000",i);}
.q
EOC

    echo "\nEnd of macro"

}

Execute_RootMacro
