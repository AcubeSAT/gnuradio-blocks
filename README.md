# Error Correction Codes

This repository contains the implementation of Error Correction Codes applied to the transmitted and received streams of data between the AcubeSAT nanosatellite and the Ground Station. 

The applied error correction techniques are the following:
- BCH for TC packets 
- LDPC for the S-Band payload data TM
- Convolutional for the UHF TM data

Each implementation follows the specifications described in the [CCSDS 131.0-B-3](https://public.ccsds.org/Pubs/131x0b3e1.pdf).


### prototypes 

This folder includes prototypes of the above error correction codes implemented in python.

### gr-a3sat

This folder includes the `gr-a3sat` GNU Radio out-of-tree (OOT) modules implementing the CCSDS recommendations for telemetry and telecommand error correction techniques. 


## Build & Install

### Requirements

GNU Radio ( >= 3.8 )
CMake ( > 3.1.0 )
swig 
git 

### Installation 

`git clone https://gitlab.com/acubesat/comms/software/error-correction-codes.git`
`cd error-correction-codes/gr-a3sat`
`mkdir build`
`cd build`
`cmake ..`
`make`

If using GR v3.9 you will need to run: 

`sudo make install`

The first time installing the `gr-a3sat` module, you will have to run:

`sudo ldconfig`


### Advanced

By default, the gr-tutorial module will use the default installation prefix.
This highly depends on the Linux distribution. You can use the CMAKE_INSTALL_PREFIX
variable to alter the default installation path.
E.g:
cmake -DCMAKE_INSTALL_PREFIX=/usr ..
