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

#ifndef   	MIH_NETWORK_CAPABILITIES_H
#define   	MIH_NETWORK_CAPABILITIES_H

#include <stdint.h>
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class NetworkCapabilities : public Tlv {
    public:
      enum Type {
        INVALID = 0x00000000,
	SECURITY = 0x00000001 << 0,
	QOS_CLASS_0 = 0x00000001 << 1,
	QOS_CLASS_1 = 0x00000001 << 2,
	QOS_CLASS_2 = 0x00000001 << 3,
	QOS_CLASS_3 = 0x00000001 << 4,
	QOS_CLASS_4 = 0x00000001 << 5,
	QOS_CLASS_5 = 0x00000001 << 6,
	INTERNET_ACCESS = 0x00000001 << 7,
	EMERGENCY_SERVICES = 0x00000001 << 8,
	MIH_CAPABILITY = 0x00000001 << 9,
      };
      NetworkCapabilities (uint32_t networkCapabilities = NetworkCapabilities::INVALID);
      NetworkCapabilities (NetworkCapabilities const &o);
      uint32_t GetNetworkCapabilities (void);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (NetworkCapabilities);
    protected:
      uint32_t m_bitmap;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_NETWORK_CAPABILITIES_H */
