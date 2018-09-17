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

#ifndef   	MIH_DEVICE_STATES_REQUEST_H
#define   	MIH_DEVICE_STATES_REQUEST_H

#include <ostream>
#include <stdint.h>
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class DeviceStatesRequest : public Tlv {
    public:
      enum Type {
        INVALID = 0x0000,
	BATTERY_LEVEL = 0x0001 << 0,
	DEVICE_INFO = 0x0001 << 1,
      };
      DeviceStatesRequest (uint16_t deviceStatesRequest = static_cast<uint16_t> (DeviceStatesRequest::INVALID));
      DeviceStatesRequest (DeviceStatesRequest const &o);
      uint16_t GetRequestedDeviceStates (void);
      DeviceStatesRequest operator = (DeviceStatesRequest const &o);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void Print (std::ostream &os) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (DeviceStatesRequest);
    protected:
      uint16_t m_deviceStatesRequest;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_DEVICE_STATES_REQUEST_H */
