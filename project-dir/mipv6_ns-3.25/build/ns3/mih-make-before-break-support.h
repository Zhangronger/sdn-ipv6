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

#ifndef   	MIH_MAKE_BEFORE_BREAK_SUPPORT_H
#define   	MIH_MAKE_BEFORE_BREAK_SUPPORT_H

#include <vector>
#include <ostream>
#include "ns3/ptr.h"
#include "ns3/ref-count-base.h"
#include "mih-tlv.h"
#include "mih-link-type.h"

namespace ns3 {
  namespace mih {
    class MakeBeforeBreakSupport : public RefCountBase, public Tlv {
    public:
      MakeBeforeBreakSupport (LinkType sourceLinkType = LinkType (),
			      LinkType destinationType = LinkType (),
			      bool supported = true);
      MakeBeforeBreakSupport (MakeBeforeBreakSupport const &o);
      LinkType GetSourceLinkType (void);
      LinkType GetDestinationLinkType (void);
      bool IsSupported (void);
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void Print (std::ostream &os) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      TLV_TYPE_HELPER_HEADER (MakeBeforeBreakSupport);
      static Ptr<MakeBeforeBreakSupport> CreateFromTlvType (uint8_t val);
    protected:
      friend std::ostream & operator << (std::ostream &os, const MakeBeforeBreakSupport &a);
      LinkType m_sourceLinkType;
      LinkType m_destinationLinkType;
      bool m_supported;
    };
    typedef std::vector<Ptr<MakeBeforeBreakSupport> > MakeBeforeBreakSupportList;
    typedef MakeBeforeBreakSupportList::iterator MakeBeforeBreakSupportListI;
    std::ostream & operator << (std::ostream &os, const MakeBeforeBreakSupport &a);
    std::ostream & operator << (std::ostream &os, MakeBeforeBreakSupportList &a);
    uint32_t GetTlvSerializedSize (MakeBeforeBreakSupportList &mbbHoSupportList);
    void TlvSerialize (Buffer &buffer, MakeBeforeBreakSupportList &mbbHoSupportList);
    uint32_t TlvDeserialize (Buffer &buffer, MakeBeforeBreakSupportList &mbbHoSupportList);    
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_MAKE_BEFORE_BREAK_SUPPORT_H */
