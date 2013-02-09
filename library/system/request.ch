#ifndef system_request_ch_INCLUDED
#define system_request_ch_INCLUDED

template <typename T>
inline void
Request::notify(const T& item)
{
   Consumers::iterator it  = consumers_.begin();
   Consumers::iterator end = consumers_.end();
   for (; it != end; ++it)
      (*it)->handle(item);
}

template <typename T>
inline void
Request::Tick(TickerId tid, TickType type, const T& value)
{
   TickerStore& tickers = Tickers();

   TickerStore::iterator loc = tickers.find(tid);
   if (loc == tickers.end()) {
      LOG
         << "Request::Tick: ticker " << tid << " not found ("
         << type << '=' << value << ')'
         << endm;
      return;
   }

   RequestPtr& request = loc->second;
   request->update(type, value);
}

#endif // system_request_ch_INCLUDED
