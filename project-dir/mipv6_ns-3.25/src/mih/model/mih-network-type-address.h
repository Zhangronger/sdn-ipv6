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

#ifndef   	MIH_NETWORK_TYPE_ADDRESS_H
#define   	MIH_NETWORK_TYPE_ADDRESS_H

#include <vector>
#include <ostream>
#include "ns3/address.h"
#include "ns3/ref-count-base.h"
#include "mih-tlv.h"
#include "mih-link-type.h"

namespace ns3 {
  namespace mih {
    class NetworkTypeAddress : public RefCountBase, public Tlv {
    public:
      NetworkTypeAddress (LinkType linkType = LinkType (),
			  Address linkAddress = Address ());
      NetworkTypeAddress (NetworkTypeAddress const &o);
      LinkType GetLinkType (void);
      Address GetLinkAddress (void);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void Print (std::ostream &os) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (NetworkTypeAddress);
      static Ptr<NetworkTypeAddress> CreateFromTlvType (uint8_t tlvTypeValue);
    protected:
      friend std::ostream &operator << (std::ostream &os, const NetworkTypeAddress &a);
      LinkType m_linkType;
      Address m_linkAddress;
    };
    typedef std::vector<Ptr<NetworkTypeAddress> > NetworkTypeAddressList;
    typedef NetworkTypeAddressList::iterator NetworkTypeAddressListI;
    std::ostream &operator << (std::ostream &os, const NetworkTypeAddress &a);
    std::ostream &operator << (std::ostream &os, NetworkTypeAddressList &a);
    uint32_t GetTlvSerializedSize (NetworkTypeAddressList &networkTypeAddressList);
    void TlvSerialize (Buffer &buffer, NetworkTypeAddressList &networkTypeAddressList);
    uint32_t TlvDeserialize (Buffer &buffer, NetworkTypeAddressList &networkTypeAddressList);
    
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_NETWORK_TYPE_ADDRESS_H */
