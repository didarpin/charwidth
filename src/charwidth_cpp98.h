/*
	Copyright (c) 2025 didarpin
	SPDX-License-Identifier: MIT
*/

#pragma once

#include <algorithm>

#include "def.h"

namespace charwidth {

enum Version {
	V_None = 0,
	V_7_0_0 = 70000,
	V_8_0_0 = 80000,
	V_9_0_0 = 90000,
	V_10_0_0 = 100000,
	V_11_0_0 = 110000,
	V_12_0_0 = 120000,
	V_12_1_0 = 120100,
	V_13_0_0 = 130000,
	V_14_0_0 = 140000,
	V_15_0_0 = 150000,
	V_15_1_0 = 150100,
	V_16_0_0 = 160000,
	V_17_0_0 = 170000,
};

typedef unsigned int u32;

}

namespace charwidth {
namespace details {

void EnsureIntSize4(void) {
	static char var[sizeof(int) == 4 ? 1 : -1];
	(void)var;
}

struct Node {
	u32 low;
	u32 high;
};

class G {
public:
	static Version version;
};

Version G::version = V_None;

}
}

#if CW_ENABLE_7_0_0 == 1
#include "7.0.0/cpp98.h"
#endif

#if CW_ENABLE_8_0_0 == 1
#include "8.0.0/cpp98.h"
#endif

#if CW_ENABLE_9_0_0 == 1
#include "9.0.0/cpp98.h"
#endif

#if CW_ENABLE_10_0_0 == 1
#include "10.0.0/cpp98.h"
#endif

#if CW_ENABLE_11_0_0 == 1
#include "11.0.0/cpp98.h"
#endif

#if CW_ENABLE_12_0_0 == 1
#include "12.0.0/cpp98.h"
#endif

#if CW_ENABLE_12_1_0 == 1
#include "12.1.0/cpp98.h"
#endif

#if CW_ENABLE_13_0_0 == 1
#include "13.0.0/cpp98.h"
#endif

#if CW_ENABLE_14_0_0 == 1
#include "14.0.0/cpp98.h"
#endif

#if CW_ENABLE_15_0_0 == 1
#include "15.0.0/cpp98.h"
#endif

#if CW_ENABLE_15_1_0 == 1
#include "15.1.0/cpp98.h"
#endif

#if CW_ENABLE_16_0_0 == 1
#include "16.0.0/cpp98.h"
#endif

#if CW_ENABLE_17_0_0 == 1
#include "17.0.0/cpp98.h"
#endif

namespace charwidth {

inline void SetVersion(Version version) {
	details::G::version = version;
}

inline void TreatAmbiguousAsWide() {
#if CW_ENABLE_7_0_0 == 1
	v_7_0_0::TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_8_0_0 == 1
	v_8_0_0::TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_9_0_0 == 1
	v_9_0_0::TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_10_0_0 == 1
	v_10_0_0::TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_11_0_0 == 1
	v_11_0_0::TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_12_0_0 == 1
	v_12_0_0::TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_12_1_0 == 1
	v_12_1_0::TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_13_0_0 == 1
	v_13_0_0::TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_14_0_0 == 1
	v_14_0_0::TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_15_0_0 == 1
	v_15_0_0::TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_15_1_0 == 1
	v_15_1_0::TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_16_0_0 == 1
	v_16_0_0::TreatAmbiguousAsWide();
#endif
#if CW_ENABLE_17_0_0 == 1
	v_17_0_0::TreatAmbiguousAsWide();
#endif
}

inline void TreatAmbiguousAsNarrow() {
#if CW_ENABLE_7_0_0 == 1
	v_7_0_0::TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_8_0_0 == 1
	v_8_0_0::TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_9_0_0 == 1
	v_9_0_0::TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_10_0_0 == 1
	v_10_0_0::TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_11_0_0 == 1
	v_11_0_0::TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_12_0_0 == 1
	v_12_0_0::TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_12_1_0 == 1
	v_12_1_0::TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_13_0_0 == 1
	v_13_0_0::TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_14_0_0 == 1
	v_14_0_0::TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_15_0_0 == 1
	v_15_0_0::TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_15_1_0 == 1
	v_15_1_0::TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_16_0_0 == 1
	v_16_0_0::TreatAmbiguousAsNarrow();
#endif
#if CW_ENABLE_17_0_0 == 1
	v_17_0_0::TreatAmbiguousAsNarrow();
#endif
}

inline int CharWidth(u32 c) {
	switch (details::G::version) {
#if CW_ENABLE_7_0_0 == 1
	case V_7_0_0: return v_7_0_0::CharWidth(c);
#endif
#if CW_ENABLE_8_0_0 == 1
	case V_8_0_0: return v_8_0_0::CharWidth(c);
#endif
#if CW_ENABLE_9_0_0 == 1
	case V_9_0_0: return v_9_0_0::CharWidth(c);
#endif
#if CW_ENABLE_10_0_0 == 1
	case V_10_0_0: return v_10_0_0::CharWidth(c);
#endif
#if CW_ENABLE_11_0_0 == 1
	case V_11_0_0: return v_11_0_0::CharWidth(c);
#endif
#if CW_ENABLE_12_0_0 == 1
	case V_12_0_0: return v_12_0_0::CharWidth(c);
#endif
#if CW_ENABLE_12_1_0 == 1
	case V_12_1_0: return v_12_1_0::CharWidth(c);
#endif
#if CW_ENABLE_13_0_0 == 1
	case V_13_0_0: return v_13_0_0::CharWidth(c);
#endif
#if CW_ENABLE_14_0_0 == 1
	case V_14_0_0: return v_14_0_0::CharWidth(c);
#endif
#if CW_ENABLE_15_0_0 == 1
	case V_15_0_0: return v_15_0_0::CharWidth(c);
#endif
#if CW_ENABLE_15_1_0 == 1
	case V_15_1_0: return v_15_1_0::CharWidth(c);
#endif
#if CW_ENABLE_16_0_0 == 1
	case V_16_0_0: return v_16_0_0::CharWidth(c);
#endif
#if CW_ENABLE_17_0_0 == 1
	case V_17_0_0: return v_17_0_0::CharWidth(c);
#endif
	default: return -1;
	}
}

}