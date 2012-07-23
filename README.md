Nutmeg
======

Nutmeg-Lime Union Engine

======
To build Newton on Linux:

    cd External/External/newton-dynamics-2.35/coreLibrary_200/projets/linux ${32 or 64}
    make

To build Nutmeg on Linux:

    mkdir Build
    cd Build
    cmake ..
    make

Ensure that libNewton.a is copied from External folder

To run a sample:

    ./EntitySample