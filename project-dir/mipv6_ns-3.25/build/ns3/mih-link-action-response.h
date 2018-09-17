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

#ifndef   	MIH_LINK_ACTION_RESPONSE_H
#define   	MIH_LINK_ACTION_RESPONSE_H

#include <vector>
#include "ns3/address.h"
#include "ns3/ref-count-base.h"
#include "mih-link-type.h"
#include "mih-tlv.h"
#include "mih-scan-response.h"

namespace ns3 {
  namespace mih {
    class LinkActionResponse : public RefCountBase, public Tlv {
    public:
      enum ActionResult {
	SUCCESS = 0,
	FAILURE = 1,
	REFUSED = 2,
	INCAPABLE = 3,
      };
      LinkActionResponse (LinkType linkType = LinkType (),
			  Address l2Address = Address (),
			  enum ActionResult actionResult = LinkActionResponse::FAILURE);
      LinkActionResponse (LinkActionResponse const &o);
      LinkType GetLinkType (void);
      Address GetDeviceLinkAddress (void);
      enum ActionResult GetActionResult (void);
      ScanResponseListI GetScanResponseListBegin (void);
      ScanResponseListI GetScanResponseListEnd (void);
      uint32_t GetScanResponseN (void);
      void AddScanResponse (Ptr<ScanResponse> scanResponse);
      void SetScanResponseList (ScanResponseList scanResponseList);
      ScanResponseList GetScanResponseList (void);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (LinkActionResponse);
      static Ptr<LinkActionResponse> CreateFromTlvType (uint8_t val);
    protected:
      friend std::ostream& operator << (std::ostream &os, const LinkActionResponse &rhs);
      LinkType m_linkType;
      Address m_mobileNodeAddress;
      enum ActionResult m_linkActionResult;
      ScanResponseList m_scanResponseList;
    };
    typedef std::vector<Ptr<LinkActionResponse> > LinkActionResponseList;
    typedef LinkActionResponseList::iterator LinkActionResponseListI;
    uint32_t GetTlvSerializedSize (const LinkActionResponseList &linkActionResponseList);
    void TlvSerialize (Buffer &buffer, const LinkActionResponseList &linkActionResponseList);
    uint32_t TlvDeserialize (Buffer &buffer, LinkActionResponseList &linkActionResponseList);

    std::ostream& operator << (std::ostream &os, const LinkActionResponse &rhs);
    std::ostream& operator << (std::ostream &os, const LinkActionResponseList &rhs);
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_LINK_ACTION_RESPONSE_H */
