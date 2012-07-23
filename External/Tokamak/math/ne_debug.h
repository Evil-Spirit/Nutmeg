/*************************************************************************
 *                                                                       *
 * Tokamak Physics Engine, Copyright (C) 2002-2007 David Lam.            *
 * All rights reserved.  Email: david@tokamakphysics.com                 *
 *                       Web: www.tokamakphysics.com                     *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files    *
 * LICENSE.TXT for more details.                                         *
 *                                                                       *
 *************************************************************************/

#ifndef NE_DEBUG_H
#define NE_DEBUG_H

#include <assert.h>

#ifdef VERIFY
#undef VERIFY
#endif

#ifdef VERIFYS
#undef VERIFYS
#endif

#ifdef ASSERT
#undef ASSERT
#endif

#ifdef ASSERTS
#undef ASSERTS
#endif

#ifdef BREAK
#undef BREAK
#endif

#include "Debug.h"

#if defined(_DEBUG)
    #define ASSERT(E)    assert(E)
#else
    #define ASSERT(E)    
#endif

#if defined(_DEBUG)

		#include "Settings.h"
		
		#if defined(NUTMEG_PLATFORM_BADA)
        	#include "FBase.h"
			#define TOKAMAK_OUTPUT(str) {AppLog(str);}
			#define TOKAMAK_OUTPUT_1(frmt,d) { AppLog(frmt, d); }
			#define TOKAMAK_OUTPUT_2(frmt,d1,d2) { AppLog(frmt, d1, d2); }
			#define TOKAMAK_OUTPUT_3(frmt,d1,d2,d3) { AppLog(frmt, d1, d2, d3); }
			#define TOKAMAK_OUTPUT_4(frmt,d1,d2,d3,d4) { AppLog(frmt, d1, d2, d3, d4); }
        #else
			#define TOKAMAK_OUTPUT(str)
			#define TOKAMAK_OUTPUT_1(frmt,d)
			#define TOKAMAK_OUTPUT_2(frmt,d1,d2)
			#define TOKAMAK_OUTPUT_3(frmt,d1,d2,d3)
			#define TOKAMAK_OUTPUT_4(frmt,d1,d2,d3,d4)
        #endif

#else

		#define TOKAMAK_OUTPUT(str)
		#define TOKAMAK_OUTPUT_1(frmt,d1)
		#define TOKAMAK_OUTPUT_2(frmt,d1,d2)
		#define TOKAMAK_OUTPUT_3(frmt,d1,d2,d3)
		#define TOKAMAK_OUTPUT_4(frmt,d1,d2,d3,d4)

#endif

#endif//NE_DEBUG_H
