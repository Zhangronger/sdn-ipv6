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

#ifndef   	MIH_DEVICE_STATES_RESPONSE_H
#define   	MIH_DEVICE_STATES_RESPONSE_H

#include <vector>
#include "ns3/ptr.h"
#include "ns3/ref-count-base.h"
#include "mih-choice-helper.h"
#include "mih-link-identifier.h"
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class DeviceStatesResponse : public RefCountBase, public Tlv {
    public:
      CHOICE_HELPER_PURE_VIRTUAL_HEADER (DeviceStatesResponse);
      virtual LinkIdentifier GetLinkIdentifier (void) = 0;
      virtual void SetLinkIdentifier (LinkIdentifier linkIdentifier) = 0;
      virtual uint32_t GetTlvSerializedSize (void) const = 0;
      virtual void Print (std::ostream &os) const = 0;
      virtual void TlvSerialize (Buffer &buffer) const = 0;
      virtual uint32_t TlvDeserialize (Buffer &buffer) = 0;
      TLV_TYPE_HELPER_HEADER (DeviceStatesResponse);
    protected:
    };
    typedef std::vector<Ptr<DeviceStatesResponse> > DeviceStatesResponseList;
    typedef DeviceStatesResponseList::iterator DeviceStatesResponseListI;
    uint32_t GetTlvSerializedSize (const DeviceStatesResponseList &deviceStatesResponseList);
    void TlvSerialize (Buffer &buffer, const DeviceStatesResponseList &deviceStatesResponseList);
    uint32_t TlvDeserialize (Buffer &buffer, DeviceStatesResponseList &deviceStatesResponseList);

    
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_DEVICE_STATES_RESPONSE_H */
