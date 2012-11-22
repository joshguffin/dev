#include "system/common.h"

#include "ibwrap/marketdata.h"

/*
   client_->reqMktData(1, contract, "", false);

100(Option Volume)
101(Option Open Interest)
104(Historical Volatility)
105(Average Opt Volume)
106(Option Implied Volatility)
107(Close Implied Volatility)
125(Bond analytic data)
165(Misc. Stats)
166(CScreen)
225(Auction)
232/221(Mark Price)
233(RTVolume)
236(inventory)
258/47(Fundamentals)
291(Close Implied Volatility)
293(TradeCount)
294(TradeRate)
295(VolumeRate)
318(LastRTHTrade)
370(ParticipationMonitor)
370(ParticipationMonitor)
377(CttTickTag)
377(CttTickTag)
381(IB Rate)
384(RfqTickRespTag)
384(RfqTickRespTag)
387(DMM)
388(Issuer Fundamentals)
391(IBWarrantImpVolCompeteTick)
407(FuturesMargins)
411(Real-Time Historical Volatility)
428(Monetary Close Price)
439(MonitorTickTag)
439(MonitorTickTag)

void
MarketData::setString(TickType type, const std::string& value)
{
   stringTicks_[type] = value;
}

void
MarketData::setDouble(TickType type, double value)
{
   doubleTicks_[type] = value;
}

void
MarketData::setUnsigned(TickType type, unsigned value)
{
   unsignedTicks_[type] = value;
}

*/
