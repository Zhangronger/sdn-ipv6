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

#include "ns3/log.h"
#include "mih-make-before-break-support.h"

NS_LOG_COMPONENT_DEFINE ("MakeBeforeBreakSupport");

namespace ns3 {
  namespace mih {
    MakeBeforeBreakSupport::MakeBeforeBreakSupport (LinkType sourceLinkType,
						    LinkType destinationType,
						    bool supported) :
      m_sourceLinkType (sourceLinkType),
      m_destinationLinkType (destinationType),
      m_supported (supported)
    {}
    MakeBeforeBreakSupport::MakeBeforeBreakSupport (MakeBeforeBreakSupport const &o) :
      m_sourceLinkType (o.m_sourceLinkType),
      m_destinationLinkType (o.m_destinationLinkType),
      m_supported (o.m_supported)
    {}
    TLV_TYPE_HELPER_IMPLEM (MakeBeforeBreakSupport, TLV_MBB_HO_SUPPORT)
    Ptr<MakeBeforeBreakSupport> 
    MakeBeforeBreakSupport::CreateFromTlvType (uint8_t val)
    {
      NS_ASSERT (val == TLV_MBB_HO_SUPPORT);
      return Create<MakeBeforeBreakSupport> ();
    }
    LinkType 
    MakeBeforeBreakSupport::GetSourceLinkType (void)
    {
      return m_sourceLinkType;
    }
    LinkType 
    MakeBeforeBreakSupport::GetDestinationLinkType (void)
    {
      return m_destinationLinkType;
    }
    bool
    MakeBeforeBreakSupport::IsSupported (void)
    {
      return m_supported;
    }
    uint32_t 
    MakeBeforeBreakSupport::GetTlvSerializedSize (void) const
    {
      uint32_t payloadLength = 0;
      uint32_t lengthOfLengthField = 0;
      
      payloadLength = m_sourceLinkType.GetTlvSerializedSize () +
        m_destinationLinkType.GetTlvSerializedSize () +
        Tlv::GetSerializedSizeBool ();

        lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);

      return 1 + lengthOfLengthField + payloadLength;
    }
    void 
    MakeBeforeBreakSupport::Print (std::ostream &os) const
    {
      os << "["
        "Source Link Type = " << m_sourceLinkType << " "
        "Destination Link Type = " << m_destinationLinkType << " "
        "Supported = " << m_supported << "]" << std::endl
        ;
    }
    void
    MakeBeforeBreakSupport::TlvSerialize (Buffer &buffer) const
    {
      uint32_t formerBufferSize = buffer.GetSize ();
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLength = 0;

      payloadLength = m_sourceLinkType.GetTlvSerializedSize () +
        m_destinationLinkType.GetTlvSerializedSize () +
        Tlv::GetSerializedSizeBool ();

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);

      buffer.AddAtEnd (1 + lengthOfLengthField); // Type field +
                                                 // Length field only;
      
      Buffer::Iterator i = buffer.Begin ();
      i.Next (formerBufferSize);
      i.WriteU8 (GetTlvTypeValue ()); // Type field;
      Tlv::WritePayloadLengthField (i, payloadLength); // Length
                                                       // field;

      m_sourceLinkType.TlvSerialize (buffer);
      m_destinationLinkType.TlvSerialize (buffer);
      Tlv::SerializeBool (buffer, m_supported, TLV_MBB_HO_SUPPORT);
    }
    uint32_t 
    MakeBeforeBreakSupport::TlvDeserialize (Buffer &buffer)
    {
      uint32_t totalBytesRead = 0;
      uint32_t roomSize;
      uint32_t payloadLengthValue = 0;
      Buffer::Iterator i = buffer.Begin ();
      NS_ASSERT (i.ReadU8 () == GetTlvTypeValue ());
      totalBytesRead++;
      roomSize = i.ReadU8 ();
      totalBytesRead++;
      
      totalBytesRead += Tlv::ReadPayloadLengthField (i, roomSize, payloadLengthValue);
      buffer.RemoveAtStart (totalBytesRead);
      
      totalBytesRead += m_sourceLinkType.TlvDeserialize (buffer);
      totalBytesRead += m_destinationLinkType.TlvDeserialize (buffer);
      totalBytesRead += Tlv::DeserializeBool (buffer, m_supported, TLV_MBB_HO_SUPPORT);
      
      return totalBytesRead;
    }
    std::ostream &
    operator << (std::ostream &os, const MakeBeforeBreakSupport &a)
    {
      os <<
        "MakeBeforeBreakSupport = [\n\tSupported = " << a.m_supported << "\n\t"
                               << "Source Link Type = " << a.m_sourceLinkType << "\n\t"
                               << "Destination Link Type = " << a.m_destinationLinkType <<
        "\n]" << std::endl;
        ;
      return os;
    }
    std::ostream &
    operator << (std::ostream &os, MakeBeforeBreakSupportList &a)
    {
      for (MakeBeforeBreakSupportListI i = a.begin (); i != a.end (); i++)
        {
          os << *(*i);
        }
      return os;
    }
    uint32_t 
    GetTlvSerializedSize (MakeBeforeBreakSupportList &mbbHoSupportList)
    {
      return Tlv::GetSerializedSize<MakeBeforeBreakSupport> (mbbHoSupportList);
    }
    void 
    TlvSerialize (Buffer &buffer, MakeBeforeBreakSupportList &mbbHoSupportList)
    {
      return Tlv::Serialize<MakeBeforeBreakSupport> (buffer, mbbHoSupportList, TLV_MBB_HO_SUPPORT_LIST);
    }
    uint32_t 
    TlvDeserialize (Buffer &buffer, MakeBeforeBreakSupportList &mbbHoSupportList)
    {
      return Tlv::Deserialize<MakeBeforeBreakSupport> (buffer, mbbHoSupportList, TLV_MBB_HO_SUPPORT_LIST);
    }
  } // namespace mih
} // namespace ns3
