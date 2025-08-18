/*
	Copyright (c) 2025 didarpin
	SPDX-License-Identifier: MIT
*/

#pragma once

#include <stdbool.h>

#include "def.h"
#include "type_c99.h"

typedef struct _CW_Node {
	cw_u32 low;
	cw_u32 high;
} _CW_Node;

#if CW_ENABLE_7_0_0 == 1
#include "7.0.0/c99.h"
#endif

#if CW_ENABLE_8_0_0 == 1
#include "8.0.0/c99.h"
#endif

#if CW_ENABLE_9_0_0 == 1
#include "9.0.0/c99.h"
#endif

#if CW_ENABLE_10_0_0 == 1
#include "10.0.0/c99.h"
#endif

#if CW_ENABLE_11_0_0 == 1
#include "11.0.0/c99.h"
#endif

#if CW_ENABLE_12_0_0 == 1
#include "12.0.0/c99.h"
#endif

#if CW_ENABLE_12_1_0 == 1
#include "12.1.0/c99.h"
#endif

#if CW_ENABLE_13_0_0 == 1
#include "13.0.0/c99.h"
#endif

#if CW_ENABLE_14_0_0 == 1
#include "14.0.0/c99.h"
#endif

#if CW_ENABLE_15_0_0 == 1
#include "15.0.0/c99.h"
#endif

#if CW_ENABLE_15_1_0 == 1
#include "15.1.0/c99.h"
#endif

#if CW_ENABLE_16_0_0 == 1
#include "16.0.0/c99.h"
#endif

#if CW_ENABLE_17_0_0 == 1
#include "17.0.0/c99.h"
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define UNUSED __attribute__((unused))
#else
	#define UNUSED
#endif

static CW_Version _cw_version = CW_V_None;

UNUSED static inline void CW_SetVersion(CW_Version version) {
	_cw_version = version;
}

UNUSED static inline void CW_TreatAmbiguousAsWide() {
#if CW_ENABLE_7_0_0 == 1
	_CW_7_0_0_TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_8_0_0 == 1
	_CW_8_0_0_TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_9_0_0 == 1
	_CW_9_0_0_TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_10_0_0 == 1
	_CW_10_0_0_TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_11_0_0 == 1
	_CW_11_0_0_TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_12_0_0 == 1
	_CW_12_0_0_TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_12_1_0 == 1
	_CW_12_1_0_TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_13_0_0 == 1
	_CW_13_0_0_TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_14_0_0 == 1
	_CW_14_0_0_TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_15_0_0 == 1
	_CW_15_0_0_TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_15_1_0 == 1
	_CW_15_1_0_TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_16_0_0 == 1
	_CW_16_0_0_TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_17_0_0 == 1
	_CW_17_0_0_TreatAmbiguousAsWide();
#endif
}

UNUSED static inline void CW_TreatAmbiguousAsNarrow() {
#if CW_ENABLE_7_0_0 == 1
	_CW_7_0_0_TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_8_0_0 == 1
	_CW_8_0_0_TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_9_0_0 == 1
	_CW_9_0_0_TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_10_0_0 == 1
	_CW_10_0_0_TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_11_0_0 == 1
	_CW_11_0_0_TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_12_0_0 == 1
	_CW_12_0_0_TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_12_1_0 == 1
	_CW_12_1_0_TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_13_0_0 == 1
	_CW_13_0_0_TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_14_0_0 == 1
	_CW_14_0_0_TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_15_0_0 == 1
	_CW_15_0_0_TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_15_1_0 == 1
	_CW_15_1_0_TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_16_0_0 == 1
	_CW_16_0_0_TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_17_0_0 == 1
	_CW_17_0_0_TreatAmbiguousAsNarrow();
#endif
}

UNUSED static inline int CW_CharWidth(cw_u32 c) {
	switch (_cw_version) {
#if CW_ENABLE_7_0_0 == 1
	case CW_V_7_0_0: return _CW_7_0_0_CharWidth(c);
#endif
#if CW_ENABLE_8_0_0 == 1
	case CW_V_8_0_0: return _CW_8_0_0_CharWidth(c);
#endif
#if CW_ENABLE_9_0_0 == 1
	case CW_V_9_0_0: return _CW_9_0_0_CharWidth(c);
#endif
#if CW_ENABLE_10_0_0 == 1
	case CW_V_10_0_0: return _CW_10_0_0_CharWidth(c);
#endif
#if CW_ENABLE_11_0_0 == 1
	case CW_V_11_0_0: return _CW_11_0_0_CharWidth(c);
#endif
#if CW_ENABLE_12_0_0 == 1
	case CW_V_12_0_0: return _CW_12_0_0_CharWidth(c);
#endif
#if CW_ENABLE_12_1_0 == 1
	case CW_V_12_1_0: return _CW_12_1_0_CharWidth(c);
#endif
#if CW_ENABLE_13_0_0 == 1
	case CW_V_13_0_0: return _CW_13_0_0_CharWidth(c);
#endif
#if CW_ENABLE_14_0_0 == 1
	case CW_V_14_0_0: return _CW_14_0_0_CharWidth(c);
#endif
#if CW_ENABLE_15_0_0 == 1
	case CW_V_15_0_0: return _CW_15_0_0_CharWidth(c);
#endif
#if CW_ENABLE_15_1_0 == 1
	case CW_V_15_1_0: return _CW_15_1_0_CharWidth(c);
#endif
#if CW_ENABLE_16_0_0 == 1
	case CW_V_16_0_0: return _CW_16_0_0_CharWidth(c);
#endif
#if CW_ENABLE_17_0_0 == 1
	case CW_V_17_0_0: return _CW_17_0_0_CharWidth(c);
#endif
	default: return -1;
	}
}