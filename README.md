# FESTR
Finite-Element Spectral Transfer of Radiation
Peter Hakel
Los Alamos National Laboratory
hakel@lanl.gov

Version 0.1 -- June 2015
CODE NAME:  FESTR (C15068)
Classification Review Number: LA-CC-15-045
Export Control Classification Number (ECCN): EAR99
B&R Code:  DP1516090

Description:

FESTR is a modeling tool for calculating spectroscopic-quality synthetic
outputs (e.g., spectra and images) based on (in general) the time evolutions
of 3-D spatial distributions of materials characterized by their chemical
composition, temperature, and density conditions. FESTR performs raytracing
across unstructured meshes, builds intrinsic optical properties of mixed
materials by performing equation-of-state lookups in external data, and then
solves the radiation-transport equation along rays to obtain emergent time and
space resolved synthetic spectra. These results can be further processed into
time and/or space integrated spectra, as well as into spectral-band-integrated
synthetic images, radiated power histories, and total radiated energy values.
FESTR is also applicable to spatial reconstructions of material properties via
the analysis of experimental data.

===============================================================================


Version Log:

-------------------------------------------------------------------------------

0.1, June 2015
     Initial release:
     *) EOS and optical data lookups in pure-element databases (with
        ionization) and their mixing according to the chemical composition,
     *) 3-D raytracing across unstructured meshes
        (Face = Sphere, Cone, Polygon, Surface have been implemented),
     *) solution of the steady-state radiation-transport equation along Rays
        and calculation of space/time resolved/integrated spectra,
     *) Detectors using parallel Rays (infinite focus) coded and tested,
     *) non-parallel Rays (parallax effects) also coded, but not tested yet,
     *) tools for creating synthetic 2-D spectral-band-integrated images,
     *) a simple but general native unit test framework (class Test).

-------------------------------------------------------------------------------
