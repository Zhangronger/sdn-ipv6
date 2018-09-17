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

#ifndef   	MIH_LINK_IDENTIFIER_H
#define   	MIH_LINK_IDENTIFIER_H

#include <vector>
#include <ostream>
#include "ns3/address.h"
#include "ns3/ptr.h"
#include "ns3/ref-count-base.h"
#include "mih-tlv.h"
#include "mih-link-type.h"

namespace ns3 {
  namespace mih {
    class LinkIdentifier : public RefCountBase, public Tlv {
    public:
      LinkIdentifier (LinkType linkType = LinkType (), 
                      Address deviceLinkAddress = Address (),
                      Address poaLinkAddress = Address ());
      LinkIdentifier (LinkIdentifier const &o);
      LinkIdentifier& operator= (const LinkIdentifier &o);
      LinkType GetType (void);
      void SetType (LinkType linkType);
      Address GetDeviceLinkAddress (void);
      void SetDeviceLinkAddress (Address addr);
      Address GetPoALinkAddress (void);
      void SetPoALinkAddress (Address addr);
      bool IsEqual (LinkIdentifier const &o) const;
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void Print (std::ostream &os) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (LinkIdentifier);
      static Ptr<LinkIdentifier> CreateFromTlvType (uint8_t tlvTypeValue);
    protected:
      friend std::ostream &operator << (std::ostream &os, const LinkIdentifier &a);
      LinkType m_type;
      Address m_mobileNodeAddress;
      Address m_poaAddress;
    };
    typedef std::vector<Ptr<LinkIdentifier> > LinkIdentifierList;
    typedef LinkIdentifierList::iterator LinkIdentifierListI;
    std::ostream &operator << (std::ostream &os, const LinkIdentifier &a);
    std::ostream &operator << (std::ostream &os, LinkIdentifierList &a);
    uint32_t GetTlvSerializedSize (LinkIdentifierList &linkIdentifierList);
    void TlvSerialize (Buffer &buffer, LinkIdentifierList &linkIdentifierList);
    uint32_t TlvDeserialize (Buffer &buffer, LinkIdentifierList &inkIdentifierList);
  }
}

#endif 	    /* !MIH_LINK_IDENTIFIER_H */
