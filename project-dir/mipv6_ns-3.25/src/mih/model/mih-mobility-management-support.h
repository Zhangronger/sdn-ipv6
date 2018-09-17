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

#ifndef   	MIH_MOBILITY_MANAGEMENT_SUPPORT_H
#define   	MIH_MOBILITY_MANAGEMENT_SUPPORT_H

#include <stdint.h>
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class MobilityManagementSupport : public Tlv {
    public:
      enum Type {
        INVALID = 0x0000,
	MOBILE_IPV4_RFC3344 = 0x0001 << 0,
	MOBILE_IPV4_RFC4857 = 0x0001 << 1,
	MOBILE_IPV6_RFC3775 = 0x0001 << 2,
	HIERARCHICAL_MOBILE_IPV6_RFC4140 = 0x0001 << 3,
	LOW_LATENCY_HANDOFFS_RFC4881 = 0x0001 << 4,
	FAST_HANDOVERS_MOBILE_IPV6_RFC4068 = 0x0001 << 5,
	IKEv2_MOBILITY_MULTIHOMING_RFC4555 = 0x0001 << 6,
      };
      MobilityManagementSupport (uint16_t supportedProtocols = MobilityManagementSupport::INVALID);
      MobilityManagementSupport (MobilityManagementSupport const &o);
      uint16_t GetSupportedProtocols (void);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (MobilityManagementSupport);
    protected:
      uint16_t m_bitmap;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_MOBILITY_MANAGEMENT_SUPPORT_H */
