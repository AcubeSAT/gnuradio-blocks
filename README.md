# Error Correction Codes

This repository contains the implementation of Error Correction Codes applied to the transmitted and received streams of data between the AcubeSAT nanosatellite and the Ground Station. 

The applied error correction techniques are the following:
- BCH for TC packets 
- LDPC for the S-Band payload data TM
- Convolutional for the UHF TM data

Each implementation follows the specifications described in the [CCSDS 131.0-B-3](https://public.ccsds.org/Pubs/131x0b3e1.pdf).


## prototypes 

This folder includes prototypes of the above error correction codes implemented in python.

## gr-a3sat

This folder includes the `gr-a3sat` GNU Radio out-of-tree (OOT) modules implementing the CCSDS recommendations for telemetry and telecommand error correction techniques. 
