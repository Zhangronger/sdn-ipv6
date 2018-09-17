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

#ifndef   	MIH_LINK_ACTION_REQUEST_H
#define   	MIH_LINK_ACTION_REQUEST_H

#include <vector>
#include <stdint.h>
#include "ns3/ref-count-base.h"
#include "mih-link-identifier.h"
#include "mih-link-action.h"
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class LinkActionRequest : public RefCountBase, public Tlv {
    public:
      LinkActionRequest (LinkIdentifier linkIdentifier = LinkIdentifier (),
			 LinkAction action = LinkAction (),
			 uint64_t actionExecutionDelay = 0);
      LinkActionRequest (LinkActionRequest const &o);
      LinkIdentifier GetLinkIdentifier (void);
      Address GetPoaAddress (void);
      void SetPoaAddress (Address poaAddress);
      LinkAction GetLinkAction (void);
      uint64_t GetActionExecutionDelay (void);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (LinkActionRequest);
      static Ptr<LinkActionRequest> CreateFromTlvType (uint8_t val);
    protected:
      LinkIdentifier m_linkIdentifier;
      Address m_poaAddress;
      LinkAction m_linkAction;
      uint64_t m_linkActionExecutionDelay; // Milliseconds;
    };
    typedef std::vector<Ptr<LinkActionRequest> > LinkActionRequestList;
    typedef LinkActionRequestList::iterator LinkActionRequestListI;
    uint32_t GetTlvSerializedSize (const LinkActionRequestList &linkActionRequestList);
    void TlvSerialize (Buffer &buffer, const LinkActionRequestList &linkActionRequestList);
    uint32_t TlvDeserialize (Buffer &buffer, LinkActionRequestList &linkActionRequestList);
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_LINK_ACTION_REQUEST_H */
