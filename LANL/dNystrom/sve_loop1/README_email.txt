Hi Srinath and John,

I recently got some performance results from a VPIC kernel that is of intereste to me.
It is the simplest and most straightforward kernel and from my analysis requires the
implementation of 10 of my light weight wrapper functions with SVE intrinsics.  I have
implemented all 10 of those with SVE intrinsics and have run it on our A64FX nodes
using a GCC 11 build.  I am getting about 80 percent of the performance that I get on
a KNL node for a problem that fits within HBM and the KNL version is highly optimized
using AVX512 intrinsics.  BTW, that is about 2x the performance I can get from the
compiler when it vectorizes the reference, non-intrinsic version of this kernel.

I am not sure what a reasonable expectation is for performance but my expectation
is for it to perform about 1.5x - 2.0x faster than KNL because of the higher memory
bandwidth of the A64FX relative to KNL.  I have looked at the assembly code for this
kernel which is attached and nothing looks bad to me - however, I am a novice at best
at understanding assembly code.  I have also attached the source code for this kernel
and the source code for my intrinsics wrapper functions that I am using for this case.

In the source code, "#if defined(VPIC_USE_AOSOA_P)" is true so that the version of
center_p_pipeline_v16 in the top half is what I am measuring the performance of.
All the loads and stores are contiguous vector loads and there are no shuffle or permute
instructions used because of the AoSoA data structure used for the particles and the
sorted particles assumption.  There is a double loop over cells and over all the particles
in a cell.  The average number of particles in a cell is 1024 - so, the majority of the work
done by the function is in the inner loop over the particles in a cell.

I have a few questions.

1. Does the assembly for the inner particle loop look optimal or close to optimal?

2. Are there any obvious things to try to get better performance?  For instance, is
it possible that things like zero fill, use of sector cache, prefetching, non-temporal
loads or stores, different intrinsics implementations, etc could help and should be
tried?

On my end, I plan to instrument the code with Caliper and collect some hardware
counter data to try and better understand performance.

Thanks,

Dave

--
Dave Nystrom
LANL HPC-ENV
Phone: 505-667-7913 (work office)
             505-661-9943 (home office)
             505-310-3757 (personal cell)
Email: wdn@lanl.gov
Smail: Mail Stop B272
       Group HPC-ENV
       Los Alamos National Laboratory
       Los Alamos, NM 87545
