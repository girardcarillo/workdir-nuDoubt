#!/bin/bash

# Define function to execute root macro
Execute_RootMacro(){

    echo "Executing root macro..."
    echo

    # Execute the root macro

    root -l -b  <<EOC
.L /home/girardcarillo/Workdir/Workdir_TT/DefineCSratio/DefineCSratio.cc
for (int i=0;i<50;i+=1){DefineCSratio("/home/girardcarillo/Workdir/Workdir_TT/Simus_DBD/","2.8MeVelectron50",i);}
.q
EOC

     root -l -b  <<EOC
.L /home/girardcarillo/Workdir/Workdir_TT/DefineCSratio/DefineCSratio.cc
for (int i=0;i<50;i+=1){DefineCSratio("/home/girardcarillo/Workdir/Workdir_TT/Simus_DBD/","2.8MeVgamma50",i);}
.q
EOC

     root -l -b  <<EOC
.L /home/girardcarillo/Workdir/Workdir_TT/DefineCSratio/DefineCSratio.cc
for (int i=0;i<50;i+=1){DefineCSratio("/home/girardcarillo/Workdir/Workdir_TT/Simus_DBD/","1.78MeVpositron50",i);}
.q
EOC

     root -l -b  <<EOC
.L DefineCSratio.cc
for (int i=0;i<50;i+=1){DefineCSratio("/home/girardcarillo/Workdir/Workdir_TT/Simus_DBD/","0.38MeV2xpositron50",i);}
.q
EOC

     echo
     echo "End of macro"

}

Execute_RootMacro
