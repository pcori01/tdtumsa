# TDTUMSA

**A GUI for FFMPEG and Opencaster to generate Transport Stream Packets according to D.S. 3152 of State Plurinational of Bolivia**

**IMPORTANT**: You need Install Opencaster and FFmpeg compiled with libx264 and libfdk_aac.

Any help and/or feedback is  welcome. 

**Build instructions**

Tested for Ubuntu 20.04

    git clone https://github.com/pcori01/tdtumsa.git  
    cd tdtumsa
    sudo apt install qt5-make qt5-default
    qmake tdtumsa.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug
    make -f Makefile qmake_all
    make -j16
    sudo mv tdtumsa /usr/local/bin

**Remarks**

- This Application was developed with QT Creator, and can be compiled and build this tool.

Please refer to the LICENSE file for contact information and further credits.   

