#ifndef _v16_h_
#define _v16_h_

#define IN_v16_h

#ifdef __cplusplus

# if defined USE_V16_PORTABLE
#   include "v16_portable.h"

# elif defined USE_V16_PORTABLE_V0
#   include "v16_portable_v0.h"

# elif defined USE_V16_PORTABLE_V1
#   include "v16_portable_v1.h"

# elif defined USE_V16_AVX512
#   include "v16_avx512.h"

# elif defined USE_V16_SVE
#   include "v16_sve.h"

# endif

#endif

#undef IN_v16_h

#endif // _v16_h_
