/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */            
/*
 * Copyright (c) 2008 IT-SUDPARIS
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as 
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Providence SALUMU M. <Providence.Salumu_Munga@it-sudparis.eu>
 */

#ifndef   	MIH_SCAN_RESPONSE_H
#define   	MIH_SCAN_RESPONSE_H

#include <vector>
#include "ns3/ref-count-base.h"
#include "ns3/address.h"
#include "mih-network-identifier.h"
#include "mih-signal-strength.h"

namespace ns3 {
  namespace mih {
    class ScanResponse : public RefCountBase {
    public:
      ScanResponse (Address poaL2Address = Address (),
		    NetworkIdentifier networkIdentifier = NetworkIdentifier (), 
		    SignalStrength signalStrength = SignalStrength ());
      ScanResponse (ScanResponse const &o);
      Address GetPoALinkAddress (void);
      NetworkIdentifier GetNetworkIdentifier (void);
      SignalStrength GetSignalStrength (void);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (ScanResponse);
      static Ptr<ScanResponse> CreateFromTlvType (uint8_t val);
    protected:
      Address m_poaLinkAddress;
      NetworkIdentifier m_networkIdentifier;
      SignalStrength m_signalStrength;
    };
    typedef std::vector<Ptr<ScanResponse> > ScanResponseList;
    typedef ScanResponseList::iterator ScanResponseListI;
    uint32_t GetTlvSerializedSize (const ScanResponseList &scanResponseList);
    void TlvSerialize (Buffer &buffer, const ScanResponseList &scanResponseList);
    uint32_t TlvDeserialize (Buffer &buffer, ScanResponseList &scanResponseList);
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_SCAN_RESPONSE_H */
