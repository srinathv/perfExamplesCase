
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main().

#include "../../../include/catch.h"

#include "../../../include/util_base_lite.h"

#include "../v16.h"

// #define VPIC_TEST_VERBOSE

#include <iostream>

using namespace v16;

//============================================================================//
//
// Tests of accuracy for v16 class.
//
//============================================================================//

//============================================================================//
//
// Tests of accuracy for v16int class.
//
//============================================================================//

//============================================================================//
//
// Tests of accuracy for v16float class.
//
//============================================================================//

#define N_SIZE 1024

//----------------------------------------------------------------------------//
// TEST_CASE_v16float_sqrt_accuracy
//----------------------------------------------------------------------------//

TEST_CASE( "TEST_CASE_v16float_sqrt_accuracy", "[v16]" )
{
  DECLARE_ALIGNED_ARRAY( float, 256, inp, N_SIZE );
  DECLARE_ALIGNED_ARRAY( float, 256, res, N_SIZE );
  DECLARE_ALIGNED_ARRAY( float, 256, ans, N_SIZE );
  DECLARE_ALIGNED_ARRAY( float, 256, err, N_SIZE );

  v16float a( 9.9 );
  v16float b( 9.9 );

  float tol     = 0.0001;
  float max_err = 0.0;

  std::cout << "----------------------------------------------------------------" << std::endl;
  std::cout << "TEST_CASE_v16float_sqrt_accuracy"                                 << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;

  #ifdef VPIC_TEST_VERBOSE
  std::cout << "Initialize inp and ans."                                          << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;
  #endif

  for( int i = 0; i < N_SIZE; i++ )
  {
    inp[i] = (float) ( i + 1 );
    ans[i] = ::sqrt( inp[i] );

    #ifdef VPIC_TEST_VERBOSE
    std::cout << "   inp[" << i << "] = " << inp[i]
              << "   ans[" << i << "] = " << ans[i]
              << std::endl;
    #endif
  }

  #ifdef VPIC_TEST_VERBOSE
  std::cout << "Compute res."                                                     << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;
  #endif

  for( int i = 0; i < N_SIZE; i += 16 )
  {
    load_16x1( inp + i,
               a );

    b = sqrt( a );

    store_16x1( b,
                res + i );

    #ifdef VPIC_TEST_VERBOSE
    for( int j = 0; j < 16; j++ )
    {
      std::cout << "   res[" << i+j << "] = " << res[i+j]
                << std::endl;
    }
    #endif
  }

  #ifdef VPIC_TEST_VERBOSE
  std::cout << "Compute err and max_err."                                         << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;
  #endif

  for( int i = 0; i < N_SIZE; i++ )
  {
    err[i] = ::sqrt( ( ans[i] - res[i] ) *
                     ( ans[i] - res[i] ) );

    if ( err[i] > max_err )
    {
      max_err = err[i];
    }
  }

  std::cout << "max_err = " << max_err                                            << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;

  REQUIRE( max_err < tol );
}

//----------------------------------------------------------------------------//
// TEST_CASE_v16float_rsqrt_accuracy
//----------------------------------------------------------------------------//

TEST_CASE( "TEST_CASE_v16float_rsqrt_accuracy", "[v16]" )
{
  DECLARE_ALIGNED_ARRAY( float, 256, inp, N_SIZE );
  DECLARE_ALIGNED_ARRAY( float, 256, res, N_SIZE );
  DECLARE_ALIGNED_ARRAY( float, 256, ans, N_SIZE );
  DECLARE_ALIGNED_ARRAY( float, 256, err, N_SIZE );

  v16float a( 9.9 );
  v16float b( 9.9 );

  float tol     = 0.0001;
  float max_err = 0.0;

  std::cout << "----------------------------------------------------------------" << std::endl;
  std::cout << "TEST_CASE_v16float_rsqrt_accuracy"                                << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;

  #ifdef VPIC_TEST_VERBOSE
  std::cout << "Initialize inp and ans."                                          << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;
  #endif

  for( int i = 0; i < N_SIZE; i++ )
  {
    inp[i] = 1.0f / (float) ( i + 1 );
    ans[i] = ::sqrt( 1.0f / inp[i] );

    #ifdef VPIC_TEST_VERBOSE
    std::cout << "   inp[" << i << "] = " << inp[i]
              << "   ans[" << i << "] = " << ans[i]
              << std::endl;
    #endif
  }

  #ifdef VPIC_TEST_VERBOSE
  std::cout << "Compute res."                                                     << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;
  #endif

  for( int i = 0; i < N_SIZE; i += 16 )
  {
    load_16x1( inp + i,
               a );

    b = rsqrt( a );

    store_16x1( b,
                res + i );

    #ifdef VPIC_TEST_VERBOSE
    for( int j = 0; j < 16; j++ )
    {
      std::cout << "   res[" << i+j << "] = " << res[i+j]
                << std::endl;
    }
    #endif
  }

  #ifdef VPIC_TEST_VERBOSE
  std::cout << "Compute err and max_err."                                         << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;
  #endif

  for( int i = 0; i < N_SIZE; i++ )
  {
    err[i] = ::sqrt( ( ans[i] - res[i] ) *
                     ( ans[i] - res[i] ) );

    if ( err[i] > max_err )
    {
      max_err = err[i];
    }
  }

  std::cout << "max_err = " << max_err                                            << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;

  REQUIRE( max_err < tol );
}

//----------------------------------------------------------------------------//
// TEST_CASE_v16float_rcp_accuracy
//----------------------------------------------------------------------------//

TEST_CASE( "TEST_CASE_v16float_rcp_accuracy", "[v16]" )
{
  DECLARE_ALIGNED_ARRAY( float, 256, inp, N_SIZE );
  DECLARE_ALIGNED_ARRAY( float, 256, res, N_SIZE );
  DECLARE_ALIGNED_ARRAY( float, 256, ans, N_SIZE );
  DECLARE_ALIGNED_ARRAY( float, 256, err, N_SIZE );

  v16float a( 9.9 );
  v16float b( 9.9 );

  float tol     = 0.0001;
  float max_err = 0.0;

  std::cout << "----------------------------------------------------------------" << std::endl;
  std::cout << "TEST_CASE_v16float_rcp_accuracy"                                  << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;

  #ifdef VPIC_TEST_VERBOSE
  std::cout << "Initialize inp and ans."                                          << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;
  #endif

  for( int i = 0; i < N_SIZE; i++ )
  {
    inp[i] = (float) ( i + 1 );
    ans[i] = 1.0f / inp[i];

    #ifdef VPIC_TEST_VERBOSE
    std::cout << "   inp[" << i << "] = " << inp[i]
              << "   ans[" << i << "] = " << ans[i]
              << std::endl;
    #endif
  }

  #ifdef VPIC_TEST_VERBOSE
  std::cout << "Compute res."                                                     << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;
  #endif

  for( int i = 0; i < N_SIZE; i += 16 )
  {
    load_16x1( inp + i,
               a );

    b = rcp( a );

    store_16x1( b,
                res + i );

    #ifdef VPIC_TEST_VERBOSE
    for( int j = 0; j < 16; j++ )
    {
      std::cout << "   res[" << i+j << "] = " << res[i+j]
                << std::endl;
    }
    #endif
  }

  #ifdef VPIC_TEST_VERBOSE
  std::cout << "Compute err and max_err."                                         << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;
  #endif

  for( int i = 0; i < N_SIZE; i++ )
  {
    err[i] = ::sqrt( ( ans[i] - res[i] ) *
                     ( ans[i] - res[i] ) );

    if ( err[i] > max_err )
    {
      max_err = err[i];
    }
  }

  std::cout << "max_err = " << max_err                                            << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;

  REQUIRE( max_err < tol );
}

//----------------------------------------------------------------------------//
// Done.
//----------------------------------------------------------------------------//
