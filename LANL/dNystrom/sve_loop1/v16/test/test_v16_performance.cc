
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main().

#include "../../../include/catch.h"

#include "../../../include/util_base_lite.h"

#include "../v16.h"

// #define VPIC_TEST_VERBOSE

#include <iostream>

#include <omp.h>

using namespace v16;

//============================================================================//
//
// Tests of performance for v16 class.
//
//============================================================================//

//============================================================================//
//
// Tests of performance for v16int class.
//
//============================================================================//

//============================================================================//
//
// Tests of performance for v16float class.
//
//============================================================================//

#define N_SIZE 1600
#define N_REPS 1000*1000*10

//----------------------------------------------------------------------------//
// TEST_CASE_v16float_sqrt_performance
//----------------------------------------------------------------------------//

TEST_CASE( "TEST_CASE_v16float_sqrt_performance", "[v16]" )
{
  int k = 76;

  //----------------------------------------------------------------------------//
  // Warm up the threads.
  //----------------------------------------------------------------------------//

  #pragma omp parallel
  {}

  //----------------------------------------------------------------------------//
  // Begin calculation.
  //----------------------------------------------------------------------------//

  std::cout << "----------------------------------------------------------------" << std::endl;
  std::cout << "TEST_CASE_v16float_sqrt_performance"                              << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;

  const double t0 = omp_get_wtime();
  #pragma omp parallel
  {
    DECLARE_ALIGNED_ARRAY( float, 256, inp, N_SIZE );
    DECLARE_ALIGNED_ARRAY( float, 256, res, N_SIZE );

    v16float a( 9.9f );
    v16float b( 9.9f );
    v16float c( 9.9f );

    for( int i = 0; i < N_SIZE; i++ )
    {
      inp[i] = (float) ( i + 1 );
    }

    int ii = 76;
    for( int i = 0; i < N_SIZE; i += 16 )
    {
      load_16x1( inp + i,
                 a );

      b = sqrt( a );

      for( ii = 0; ii < N_REPS; ii++ )
      {
	c = b * b;
	b = sqrt( c );
      }

      store_16x1( b,
                  res + i );
    }

    #ifdef VPIC_TEST_VERBOSE
    std::cout << "Compute res."                                                     << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;

    for( int j = 0; j < N_SIZE; j++ )
    {
      std::cout << "   res[" << j << "] = " << res[j]
                << std::endl;
    }
    #endif

    // Prevent dead code elimination.
    if ( res[76] == 0.0 )
    {
      exit(1);
    }
  }
  const double t1 = omp_get_wtime();

  long num_array_elements = N_SIZE;
  long num_reps           = N_REPS;
  long num_sqrt_calls     = num_array_elements * ( num_reps + 1 );

  std::cout << "   sqrt time:      " << t1 - t0
            << std::endl
            << "   num sqrt calls: " << num_sqrt_calls
            << std::endl;

  REQUIRE( k == 76 );
}

//----------------------------------------------------------------------------//
// TEST_CASE_v16float_rsqrt_performance
//----------------------------------------------------------------------------//

TEST_CASE( "TEST_CASE_v16float_rsqrt_performance", "[v16]" )
{
  int k = 76;

  //----------------------------------------------------------------------------//
  // Warm up the threads.
  //----------------------------------------------------------------------------//

  #pragma omp parallel
  {}

  //----------------------------------------------------------------------------//
  // Begin calculation.
  //----------------------------------------------------------------------------//

  std::cout << "----------------------------------------------------------------" << std::endl;
  std::cout << "TEST_CASE_v16float_rsqrt_performance"                             << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;

  const double t0 = omp_get_wtime();
  #pragma omp parallel
  {
    DECLARE_ALIGNED_ARRAY( float, 256, inp, N_SIZE );
    DECLARE_ALIGNED_ARRAY( float, 256, res, N_SIZE );

    v16float a( 9.9 );
    v16float b( 9.9 );
    v16float c( 9.9 );

    for( int i = 0; i < N_SIZE; i++ )
    {
      inp[i] = 1.0f / (float) ( i + 1 );
    }

    int ii = 76;
    for( int i = 0; i < N_SIZE; i += 16 )
    {
      load_16x1( inp + i,
                 a );

      b = rsqrt( a );

      for( ii = 0; ii < N_REPS; ii++ )
      {
	c = b * b;
	b = rsqrt( c );
      }

      store_16x1( b,
                  res + i );
    }

    #ifdef VPIC_TEST_VERBOSE
    std::cout << "Compute res."                                                     << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;

    for( int j = 0; j < N_SIZE; j++ )
    {
      std::cout << "   res[" << j << "] = " << res[j]
                << std::endl;
    }
    #endif

    // Prevent dead code elimination.
    if ( res[76] == 0.0 )
    {
      exit(1);
    }
  }
  const double t1 = omp_get_wtime();

  long num_array_elements = N_SIZE;
  long num_reps           = N_REPS;
  long num_rsqrt_calls    = num_array_elements * ( num_reps + 1 );

  std::cout << "   rsqrt time:      " << t1 - t0
            << std::endl
            << "   num rsqrt calls: " << num_rsqrt_calls
            << std::endl;

  REQUIRE( k == 76 );
}

//----------------------------------------------------------------------------//
// TEST_CASE_v16float_rsqrt_performance_ur_02
//----------------------------------------------------------------------------//

TEST_CASE( "TEST_CASE_v16float_rsqrt_performance_ur_02", "[v16]" )
{
  int k = 76;

  //----------------------------------------------------------------------------//
  // Warm up the threads.
  //----------------------------------------------------------------------------//

  #pragma omp parallel
  {}

  //----------------------------------------------------------------------------//
  // Begin calculation.
  //----------------------------------------------------------------------------//

  std::cout << "----------------------------------------------------------------" << std::endl;
  std::cout << "TEST_CASE_v16float_rsqrt_performance_ur_02"                       << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;

  const double t0 = omp_get_wtime();
  #pragma omp parallel
  {
    DECLARE_ALIGNED_ARRAY( float, 256, inp, N_SIZE );
    DECLARE_ALIGNED_ARRAY( float, 256, res, N_SIZE );

    v16float a00( 9.9 ), a01( 9.9 );
    v16float b00( 9.9 ), b01( 9.9 );
    v16float c00( 9.9 ), c01( 9.9 );

    for( int i = 0; i < N_SIZE; i++ )
    {
      inp[i] = 1.0f / (float) ( i + 1 );
    }

    int ii = 76;
    for( int i = 0; i < N_SIZE; i += 32 )
    {
      load_16x1( inp + i,
                 a00 );
      load_16x1( inp + i + 16,
                 a01 );

      b00 = rsqrt( a00 );
      b01 = rsqrt( a01 );

      for( ii = 0; ii < N_REPS; ii++ )
      {
	c00 = b00 * b00;
	b00 = rsqrt( c00 );

	c01 = b01 * b01;
	b01 = rsqrt( c01 );
      }

      store_16x1( b00,
                  res + i );
      store_16x1( b01,
                  res + i + 16 );
    }

    #ifdef VPIC_TEST_VERBOSE
    std::cout << "Compute res."                                                     << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;

    for( int j = 0; j < N_SIZE; j++ )
    {
      std::cout << "   res[" << j << "] = " << res[j]
                << std::endl;
    }
    #endif

    // Prevent dead code elimination.
    if ( res[76] == 0.0 )
    {
      exit(1);
    }
  }
  const double t1 = omp_get_wtime();

  long num_array_elements = N_SIZE;
  long num_reps           = N_REPS;
  long num_rsqrt_calls    = num_array_elements * ( num_reps + 1 );

  std::cout << "   rsqrt time:      " << t1 - t0
            << std::endl
            << "   num rsqrt calls: " << num_rsqrt_calls
            << std::endl;

  REQUIRE( k == 76 );
}

//----------------------------------------------------------------------------//
// TEST_CASE_v16float_rsqrt_performance_ur_04
//----------------------------------------------------------------------------//

TEST_CASE( "TEST_CASE_v16float_rsqrt_performance_ur_04", "[v16]" )
{
  int k = 76;

  //----------------------------------------------------------------------------//
  // Warm up the threads.
  //----------------------------------------------------------------------------//

  #pragma omp parallel
  {}

  //----------------------------------------------------------------------------//
  // Begin calculation.
  //----------------------------------------------------------------------------//

  std::cout << "----------------------------------------------------------------" << std::endl;
  std::cout << "TEST_CASE_v16float_rsqrt_performance_ur_04"                       << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;

  const double t0 = omp_get_wtime();
  #pragma omp parallel
  {
    DECLARE_ALIGNED_ARRAY( float, 256, inp, N_SIZE );
    DECLARE_ALIGNED_ARRAY( float, 256, res, N_SIZE );

    v16float a00( 9.9 ), a01( 9.9 ), a02( 9.9 ), a03( 9.9 );
    v16float b00( 9.9 ), b01( 9.9 ), b02( 9.9 ), b03( 9.9 );
    v16float c00( 9.9 ), c01( 9.9 ), c02( 9.9 ), c03( 9.9 );

    for( int i = 0; i < N_SIZE; i++ )
    {
      inp[i] = 1.0f / (float) ( i + 1 );
    }

    int ii = 76;
    for( int i = 0; i < N_SIZE; i += 64 )
    {
      load_16x1( inp + i,
                 a00 );
      load_16x1( inp + i + 16,
                 a01 );
      load_16x1( inp + i + 32,
                 a02 );
      load_16x1( inp + i + 48,
                 a03 );

      b00 = rsqrt( a00 );
      b01 = rsqrt( a01 );
      b02 = rsqrt( a02 );
      b03 = rsqrt( a03 );

      for( ii = 0; ii < N_REPS; ii++ )
      {
	c00 = b00 * b00;
	b00 = rsqrt( c00 );

	c01 = b01 * b01;
	b01 = rsqrt( c01 );

	c02 = b02 * b02;
	b02 = rsqrt( c02 );

	c03 = b03 * b03;
	b03 = rsqrt( c03 );
      }

      store_16x1( b00,
                  res + i );
      store_16x1( b01,
                  res + i + 16 );
      store_16x1( b02,
                  res + i + 32 );
      store_16x1( b03,
                  res + i + 48 );
    }

    #ifdef VPIC_TEST_VERBOSE
    std::cout << "Compute res."                                                     << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;

    for( int j = 0; j < N_SIZE; j++ )
    {
      std::cout << "   res[" << j << "] = " << res[j]
                << std::endl;
    }
    #endif

    // Prevent dead code elimination.
    if ( res[76] == 0.0 )
    {
      exit(1);
    }
  }
  const double t1 = omp_get_wtime();

  long num_array_elements = N_SIZE;
  long num_reps           = N_REPS;
  long num_rsqrt_calls    = num_array_elements * ( num_reps + 1 );

  std::cout << "   rsqrt time:      " << t1 - t0
            << std::endl
            << "   num rsqrt calls: " << num_rsqrt_calls
            << std::endl;

  REQUIRE( k == 76 );
}

//----------------------------------------------------------------------------//
// TEST_CASE_v16float_rsqrt_performance_ur_08
//----------------------------------------------------------------------------//

TEST_CASE( "TEST_CASE_v16float_rsqrt_performance_ur_08", "[v16]" )
{
  int k = 76;

  //----------------------------------------------------------------------------//
  // Warm up the threads.
  //----------------------------------------------------------------------------//

  #pragma omp parallel
  {}

  //----------------------------------------------------------------------------//
  // Begin calculation.
  //----------------------------------------------------------------------------//

  std::cout << "----------------------------------------------------------------" << std::endl;
  std::cout << "TEST_CASE_v16float_rsqrt_performance_ur_08"                       << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;

  const double t0 = omp_get_wtime();
  #pragma omp parallel
  {
    DECLARE_ALIGNED_ARRAY( float, 256, inp, N_SIZE );
    DECLARE_ALIGNED_ARRAY( float, 256, res, N_SIZE );

    v16float a00( 9.9 ), a01( 9.9 ), a02( 9.9 ), a03( 9.9 );
    v16float a04( 9.9 ), a05( 9.9 ), a06( 9.9 ), a07( 9.9 );

    v16float b00( 9.9 ), b01( 9.9 ), b02( 9.9 ), b03( 9.9 );
    v16float b04( 9.9 ), b05( 9.9 ), b06( 9.9 ), b07( 9.9 );

    v16float c00( 9.9 ), c01( 9.9 ), c02( 9.9 ), c03( 9.9 );
    v16float c04( 9.9 ), c05( 9.9 ), c06( 9.9 ), c07( 9.9 );

    for( int i = 0; i < N_SIZE; i++ )
    {
      inp[i] = 1.0f / (float) ( i + 1 );
    }

    int ii = 76;
    for( int i = 0; i < N_SIZE; i += 128 )
    {
      load_16x1( inp + i,
                 a00 );
      load_16x1( inp + i +  16,
                 a01 );
      load_16x1( inp + i +  32,
                 a02 );
      load_16x1( inp + i +  48,
                 a03 );
      load_16x1( inp + i +  64,
                 a04 );
      load_16x1( inp + i +  80,
                 a05 );
      load_16x1( inp + i +  96,
                 a06 );
      load_16x1( inp + i + 112,
                 a07 );

      b00 = rsqrt( a00 );
      b01 = rsqrt( a01 );
      b02 = rsqrt( a02 );
      b03 = rsqrt( a03 );
      b04 = rsqrt( a04 );
      b05 = rsqrt( a05 );
      b06 = rsqrt( a06 );
      b07 = rsqrt( a07 );

      for( ii = 0; ii < N_REPS; ii++ )
      {
	c00 = b00 * b00;
	b00 = rsqrt( c00 );

	c01 = b01 * b01;
	b01 = rsqrt( c01 );

	c02 = b02 * b02;
	b02 = rsqrt( c02 );

	c03 = b03 * b03;
	b03 = rsqrt( c03 );

	c04 = b04 * b04;
	b04 = rsqrt( c04 );

	c05 = b05 * b05;
	b05 = rsqrt( c05 );

	c06 = b06 * b06;
	b06 = rsqrt( c06 );

	c07 = b07 * b07;
	b07 = rsqrt( c07 );
      }

      store_16x1( b00,
                  res + i );
      store_16x1( b01,
                  res + i +  16 );
      store_16x1( b02,
                  res + i +  32 );
      store_16x1( b03,
                  res + i +  48 );
      store_16x1( b04,
                  res + i +  64 );
      store_16x1( b05,
                  res + i +  80 );
      store_16x1( b06,
                  res + i +  96 );
      store_16x1( b07,
                  res + i + 112 );
    }

    #ifdef VPIC_TEST_VERBOSE
    std::cout << "Compute res."                                                     << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;

    for( int j = 0; j < N_SIZE; j++ )
    {
      std::cout << "   res[" << j << "] = " << res[j]
                << std::endl;
    }
    #endif

    // Prevent dead code elimination.
    if ( res[76] == 0.0 )
    {
      exit(1);
    }
  }
  const double t1 = omp_get_wtime();

  long num_array_elements = N_SIZE;
  long num_reps           = N_REPS;
  long num_rsqrt_calls    = num_array_elements * ( num_reps + 1 );

  std::cout << "   rsqrt time:      " << t1 - t0
            << std::endl
            << "   num rsqrt calls: " << num_rsqrt_calls
            << std::endl;

  REQUIRE( k == 76 );
}

//----------------------------------------------------------------------------//
// TEST_CASE_v16float_rcp_performance
//----------------------------------------------------------------------------//

TEST_CASE( "TEST_CASE_v16float_rcp_performance", "[v16]" )
{
  int k = 76;

  //----------------------------------------------------------------------------//
  // Warm up the threads.
  //----------------------------------------------------------------------------//

  #pragma omp parallel
  {}

  //----------------------------------------------------------------------------//
  // Begin calculation.
  //----------------------------------------------------------------------------//

  std::cout << "----------------------------------------------------------------" << std::endl;
  std::cout << "TEST_CASE_v16float_rcp_performance"                               << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;

  const double t0 = omp_get_wtime();
  #pragma omp parallel
  {
    DECLARE_ALIGNED_ARRAY( float, 256, inp, N_SIZE );
    DECLARE_ALIGNED_ARRAY( float, 256, res, N_SIZE );

    v16float a( 9.9 );
    v16float b( 9.9 );
    v16float c( 9.9 );

    for( int i = 0; i < N_SIZE; i++ )
    {
      inp[i] = (float) ( i + 1 );
    }

    int ii = 76;
    for( int i = 0; i < N_SIZE; i += 16 )
    {
      load_16x1( inp + i,
                 a );

      b = rcp( a );

      for( ii = 0; ii < N_REPS; ii++ )
      {
	c = b;
	b = rcp( c );
      }

      store_16x1( b,
                  res + i );
    }

    #ifdef VPIC_TEST_VERBOSE
    std::cout << "Compute res."                                                     << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;

    for( int j = 0; j < N_SIZE; j++ )
    {
      std::cout << "   res[" << j << "] = " << res[j]
                << std::endl;
    }
    #endif

    // Prevent dead code elimination.
    if ( res[76] == 0.0 )
    {
      exit(1);
    }
  }
  const double t1 = omp_get_wtime();

  long num_array_elements = N_SIZE;
  long num_reps           = N_REPS;
  long num_rcp_calls      = num_array_elements * ( num_reps + 1 );

  std::cout << "   rcp time:      " << t1 - t0
            << std::endl
            << "   num rcp calls: " << num_rcp_calls
            << std::endl;

  REQUIRE( k == 76 );
}

//----------------------------------------------------------------------------//
// Done.
//----------------------------------------------------------------------------//
