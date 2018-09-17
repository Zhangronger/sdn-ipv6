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

#ifndef   	MIH_LINK_PARAMETER_80211_H
#define   	MIH_LINK_PARAMETER_80211_H

#include <stdint.h>
#include "mih-choice-helper.h"
#include "mih-link-parameter-type.h"

namespace ns3 {
  namespace mih {
    class LinkParameter80211 : public LinkParameterType {
    public:
      enum Type {
        INVALID = 0xff,
	BEACON_CHANNEL_RSSI = 0,
	NO_QOS_RESOURCE_AVAILABLE = 1,
	MULTICAST_PACKET_LOSS_RATE = 2,
      };
      LinkParameter80211 (uint8_t paramterCode = LinkParameter80211::INVALID);
      LinkParameter80211 (LinkParameter80211 const &o);
      uint8_t GetParameterCode (void);
      CHOICE_HELPER_HEADER (LinkParameter80211, LinkParameterType);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void Print (std::ostream &os) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (LinkParameter80211);
    protected:
      uint8_t m_parameterCode;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_LINK_PARAMETER_80211_H */
