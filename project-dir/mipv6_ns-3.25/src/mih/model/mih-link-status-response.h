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

#ifndef   	MIH_LINK_STATUS_RESPONSE_H
#define   	MIH_LINK_STATUS_RESPONSE_H

#include <vector>
#include <stdint.h>
#include "ns3/ptr.h"
#include "ns3/ref-count-base.h"
#include "mih-link-identifier.h"
#include "mih-link-states-response.h"
#include "mih-link-parameter.h"
#include "mih-link-descriptors-response.h"
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class LinkStatusResponse : public RefCountBase, public Tlv {
    public:
      LinkStatusResponse (LinkIdentifier linkIdentifier = LinkIdentifier ());
      LinkStatusResponse (LinkStatusResponse const &o);
      LinkIdentifier GetLinkIdentifier (void);
      LinkStatesResponseListI GetLinkStatesResponseListBegin (void);
      LinkStatesResponseListI GetLinkStatesResponseListEnd (void);
      void AddLinkStatesResponse (LinkStatesResponse *linkStatesResponse);
      uint32_t GetLinkStatesResponseN (void);
      void SetLinkStatesResponseList (LinkStatesResponseList linkStatesResponseList);
      LinkParameterListI GetLinkParameterListBegin (void);
      LinkParameterListI GetLinkParameterListEnd (void);
      void AddLinkParameter (LinkParameter *linkParameter);
      uint32_t GetLinkParameterN (void);
      void SetLinkParameterList (LinkParameterList linkParameterList);
      LinkDescriptorsResponseListI GetLinkDescriptorsResponseListBegin (void);
      LinkDescriptorsResponseListI GetLinkDescriptorsResponseListEnd (void);
      void AddLinkDescriptorsResponse (LinkDescriptorsResponse *linkDescriptorResponse);
      uint32_t GetLinkDescriptorsResponseN (void);
      void SetLinkDescriptorsResponseList (LinkDescriptorsResponseList linkDescriptorsResponseList);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (LinkStatusResponse);
      static Ptr<LinkStatusResponse> CreateFromTlvType (uint8_t val);
    protected:
      LinkIdentifier m_linkIdentifier;
      LinkStatesResponseList m_linkStatesResponseList;
      LinkParameterList m_linkParameterList;
      LinkDescriptorsResponseList m_linkDescriptorsResponseList;
    };
    typedef std::vector<Ptr<LinkStatusResponse> > LinkStatusResponseList;
    typedef LinkStatusResponseList::iterator LinkStatusResponseI;
    uint32_t GetTlvSerializedSize (const LinkStatusResponseList &linkStatusResponseList);
    void TlvSerialize (Buffer &buffer, const LinkStatusResponseList &linkStatusResponseList);
    uint32_t TlvDeserialize (Buffer &buffer, LinkStatusResponseList &linkStatusResponseList);
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_LINK_STATUS_RESPONSE_H */
