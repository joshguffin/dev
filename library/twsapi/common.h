#ifndef twsapi_common_h_INCLUDED
#define twsapi_common_h_INCLUDED

#define IB_USE_STD_STRING

#include "system/common.h"
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace TwsApi {
#include "twsapi/IB_LIBRARY/Shared/CommonDefs.h"
#include "twsapi/IB_LIBRARY/Shared/Contract.h"
#include "twsapi/IB_LIBRARY/Shared/EClient.h"
#include "twsapi/IB_LIBRARY/Shared/EClientSocketBase.h"
#include "twsapi/IB_LIBRARY/Shared/EWrapper.h"
#include "twsapi/IB_LIBRARY/Shared/Execution.h"
#include "twsapi/IB_LIBRARY/Shared/IBString.h"
#include "twsapi/IB_LIBRARY/Shared/Order.h"
#include "twsapi/IB_LIBRARY/Shared/OrderState.h"
#include "twsapi/IB_LIBRARY/Shared/ScannerSubscription.h"
#include "twsapi/IB_LIBRARY/Shared/StdAfx.h"
#include "twsapi/IB_LIBRARY/Shared/TwsSocketClientErrors.h"
#include "twsapi/IB_LIBRARY/Shared/shared_ptr.h"
}

#include "twsapi/helpers.h"

#include "stream.h"

#endif // twsapi_common_h_INCLUDED

