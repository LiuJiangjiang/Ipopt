C /* IPOPT/include/config.h.  Generated by configure.  */
C /* IPOPT/include/config.h.in.  Generated from configure.ac by autoheader.  */
C
C
C This file configures the compilation of the Fortran files in IPOPT.
C You might have to edit it in order to adapt the configuration for your
C circumstances.  The provided version of the file works for
C Visual Studio 2003 (Standard) with the Intel Fortran 8.0 compiler,
C and would include the Harwell routines MA27 and MC19.
C
C 
C /* Define to 1 if CPU_TIME can be use to measure CPU time */
C /* #undef HAVE_CPU_TIME */
C 
C /* Define to 1 if ETIME can be use to measure CPU time */
#define HAVE_ETIME 
C 
C /* Define to 1 if MA27 is available */
#define HAVE_MA27 1
C 
C /* Define to 1 if MA28 is available */
C /* #undef HAVE_MA28 1 */
C 
C /* Define to 1 if MA47 is available */
C /* #undef HAVE_MA47 */
C 
C /* Define to 1 if MA48 is available */
C /* #undef HAVE_MA48 */
C 
C /* Define to 1 if MA57 is available */
C /* #undef HAVE_MA57 */
C 
C /* Define to 1 if MC19 is available */
#define HAVE_MC19 1
C 
C /* Define to 1 if MC29 is available */
C /* #undef HAVE_MC29 */
C 
C /* Define to 1 if MC30 is available */
C /* #undef HAVE_MC30 */
C 
C /* Define to 1 if MC35 is available */
C /* #undef HAVE_MC35 */
C 
C /* Define to 1 if MC39 is available */
C /* #undef HAVE_MC39 */
C 
C /* Define to 1 if TRON is available */
C /* #undef HAVE_TRON */
C 
C /* Define to 1 if you want to compile the AMPL executable with support for
C    MPECs */
C /* #undef INCLUDE_CC */
C 
C /* Define to 1 if MA27 is given in the old, non-threadsafe version */
C /* #undef OLD_MA27 */
C 
C /* Define to 1 if pointers consists of 4 bytes */
#define SIZEOF_INT_P_IS_4 1
C
C /* Define to 1 if pointers consists of 8 bytes */
C /* #undef SIZEOF_INT_P_IS_8 */
C 
C /* Define to 1 if Fortran compiler understand %VAL and malloc should be used
C    */
#define USE_MALLOC 1
C 
