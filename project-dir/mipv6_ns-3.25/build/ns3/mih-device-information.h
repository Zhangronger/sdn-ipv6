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

#ifndef   	MIH_DEVICE_INFORMATION_H
#define   	MIH_DEVICE_INFORMATION_H

#include <string>
#include "mih-choice-helper.h"
#include "mih-device-states-response.h"
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class DeviceInformation : public DeviceStatesResponse {
    public:
      enum {
	MAX_LEN = 253,
      };
      DeviceInformation (std::string deviceInformation = "");
      DeviceInformation (DeviceInformation const &o);
      const char* PeekString (void);
      CHOICE_HELPER_HEADER (DeviceInformation, DeviceStatesResponse);
      virtual LinkIdentifier GetLinkIdentifier (void);
      virtual void SetLinkIdentifier (LinkIdentifier linkIdentifier);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void Print (std::ostream &os) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (DeviceInformation);
    protected:
      std::string m_deviceInformation;
      LinkIdentifier m_linkIdentifier;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_DEVICE_INFORMATION_H */
