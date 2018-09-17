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

#ifndef   	MIH_LINK_DETECTED_INFORMATION_H
#define   	MIH_LINK_DETECTED_INFORMATION_H

#include <stdint.h>
#include <vector>
#include "ns3/ptr.h"
#include "ns3/ref-count-base.h"
#include "mih-link-identifier.h"
#include "mih-network-identifier.h"
#include "mih-network-auxiliary-identifier.h"
#include "mih-signal-strength.h"
#include "mih-data-rate.h"
#include "mih-capability-flag.h"
#include "mih-network-capabilities.h"
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class LinkDetectedInformation : public RefCountBase, public Tlv {
    public:
      LinkDetectedInformation (void);
      LinkDetectedInformation (LinkIdentifier linkIdentifier,
			       NetworkIdentifier networkIdentifier,
			       NetworkAuxiliaryIdentifier networkAuxiliaryIdentifier,
			       SignalStrength signalStrength,
			       uint16_t sinr,
			       DataRate dataRate,
			       MihCapabilityFlag mihCapabilityFlag,
			       NetworkCapabilities networkCapabilities);
      LinkDetectedInformation (LinkDetectedInformation const &o);
      LinkIdentifier GetLinkIdentifier (void);
      NetworkIdentifier GetNetworkIdentifier (void);
      NetworkAuxiliaryIdentifier GetNetworkAuxiliaryIdentifier (void);
      SignalStrength GetSignalStrength (void);
      uint16_t GetSinr (void);
      DataRate GetDataRate (void);
      MihCapabilityFlag GetMihCapabilityFlag (void);
      NetworkCapabilities GetNetworkCapabilities (void);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (LinkDetectedInformation);
      static Ptr<LinkDetectedInformation> CreateFromTlvType (uint8_t val);
    protected:
      LinkIdentifier m_linkIdentifier;
      NetworkIdentifier m_networkIdentifier;
      NetworkAuxiliaryIdentifier m_networkAuxiliaryIdentifier;
      SignalStrength m_signalStrength;
      uint16_t m_sinr;
      DataRate m_dataRate;
      MihCapabilityFlag m_mihCapabilityFlag;
      NetworkCapabilities m_networkCapabilities;
    };
    typedef std::vector<Ptr<LinkDetectedInformation> > LinkDetectedInformationList;
    typedef LinkDetectedInformationList::iterator LinkDetectedInformationI;
    uint32_t GetTlvSerializedSize (const LinkDetectedInformationList &linkDetectedInformationList);
    void TlvSerialize (Buffer &buffer, const LinkDetectedInformationList &linkDetectedInformationList);
    uint32_t TlvDeserialize (Buffer &buffer, LinkDetectedInformationList &linkDetectedInformationList);
    std::ostream& operator << (std::ostream &os, LinkDetectedInformation &a);
    std::ostream& operator << (std::ostream&os, LinkDetectedInformationList &a);
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_LINK_DETECTED_INFORMATION_H */
