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

#include "ns3/assert.h"
#include "ns3/log.h"
#include "mih-header.h"

NS_LOG_COMPONENT_DEFINE ("ns3::mih::MihHeader");

namespace ns3 {
  namespace mih {
    TypeId
    MihHeader::GetTypeId (void)
    {
      static TypeId tid = TypeId ("ns3::mih::MihHeader")
	.SetParent<Header> ()
	.AddConstructor<MihHeader> ();
      return tid;
    }
    TypeId
    MihHeader::GetInstanceTypeId (void) const
    {
      return GetTypeId ();
    }
    MihHeader::MihHeader (void) :
      m_version (),
      m_ackRequest (0),
      m_ackResponse (0),
      m_uir (0),
      m_moreFragment (0),
      m_fragmentNumber (0),
      m_sid (0),
      m_opcode (0),
      m_transactionId (0),
      m_payloadLength (0)
    {}
    void 
    MihHeader::SetVersion (enum VersionE version)
    {
      m_version = static_cast<uint16_t> (version);
    }
    enum MihHeader::VersionE 
    MihHeader::GetVersion (void)
    {
      return static_cast<enum MihHeader::VersionE> (m_version);
    }
    void 
    MihHeader::SetServiceId (enum MihHeader::ServiceIdE sid)
    {
      m_sid = static_cast<uint16_t> (sid);
    }
    enum MihHeader::ServiceIdE 
    MihHeader::GetServiceId (void)
    {
      return static_cast<enum MihHeader::ServiceIdE> (m_sid);
    }
    void 
    MihHeader::SetOpCode (enum MihHeader::OpCodeE opcode)
    {
      m_opcode = static_cast<uint16_t> (opcode);
    }
    enum MihHeader::OpCodeE
    MihHeader::GetOpCode (void)
    {
      return static_cast<enum MihHeader::OpCodeE> (m_opcode);
    }
    void
    MihHeader::SetActionId (enum MihHeader::ActionIdE aid)
    {
      m_aid = static_cast<uint16_t> (aid);
    }
    enum MihHeader::ActionIdE 
    MihHeader::GetActionId (void)
    {
      return static_cast<enum MihHeader::ActionIdE> (m_aid);
    }
    void 
    MihHeader::SetTransactionId (uint16_t transactionId)
    {
      m_transactionId = transactionId;
    }
    uint16_t 
    MihHeader::GetTransactionId (void)
    {
      return m_transactionId;
    }
    void 
    MihHeader::SetPayloadLength (uint16_t payloadLength)
    {
      m_payloadLength = payloadLength;
    }
    uint16_t 
    MihHeader::GetPayloadLength (void)
    {
      return m_payloadLength;
    }
    uint32_t 
    MihHeader::GetSerializedSize (void) const
    {
      return 8; // eight bytes
    }
    void
    MihHeader::Print (std::ostream &os) const
    {
      os << "["
	"\n\tVersion " << m_version << " "
	 << "\n\tACK-Req=0x" << std::hex << m_ackRequest << std::dec << " "
	 << "\n\tACK-Rsp=0x" << std::hex << m_ackResponse << std::dec << " "
	 << "\n\tUIR=0x" << std::hex << m_uir << std::dec << " "
	 << "\n\tM=0x" << std::hex << m_moreFragment << std::dec << " "
	 << "\n\tFN=0x" << std::hex << m_fragmentNumber << std::dec << " "
	 << "\n\tSID=" << std::dec << (uint16_t) m_sid << " "
	 << "\n\tOpcode=" << std::dec << (uint16_t) m_opcode << " "
	 << "\n\tAID=" << std::dec << (uint16_t) m_aid << std::dec << " "
	 << "\n\tTransaction ID=" << std::dec << (uint16_t) m_transactionId << " "
	 << "\n\tPayload Length=" << std::dec << (uint16_t) m_payloadLength << "\n]" 
	 << std::endl
	;
    }
    void 
    MihHeader::Serialize (Buffer::Iterator start) const
    {
      Buffer::Iterator i = start;
      uint16_t vaaumf = (m_version << 12) | 
	(m_ackRequest << 11) | 
	(m_ackResponse << 10) |
	(m_uir << 9) |
	(m_moreFragment << 8) |
	(m_fragmentNumber << 1);
      i.WriteHtonU16 (vaaumf);

      uint16_t mid = (m_sid << 12) |
	(m_opcode << 10) |
	(m_aid);
      i.WriteHtonU16 (mid);
      i.WriteHtonU16 (m_transactionId);
      i.WriteHtonU16 (m_payloadLength);
    }
    uint32_t 
    MihHeader::Deserialize (Buffer::Iterator start)
    {
      Buffer::Iterator i = start;

      uint16_t vaaumf = 0;
      vaaumf = i.ReadNtohU16();
      m_version = (vaaumf >> 12) & 0x000f;
      NS_ASSERT (m_version == static_cast<uint16_t> (MihHeader::VERSION_ONE));
      m_ackRequest = (vaaumf >> 11) & 0x0001;
      m_ackResponse = (vaaumf >> 10) & 0x0001;
      m_uir = (vaaumf >> 9) & 0x0001;
      m_moreFragment = (vaaumf >> 8) & 0x0001;
      m_fragmentNumber = (vaaumf >> 1) & 0x007f;

      uint16_t mid = 0;
      mid = i.ReadNtohU16();
      m_sid = (mid >> 12) & 0x000f;
      m_opcode = (mid >> 10) & 0x0003;
      m_aid = mid & 0x03ff;

      m_transactionId = i.ReadNtohU16();
      m_payloadLength = i.ReadNtohU16();

      return GetSerializedSize();
    }
  } // namespace mih
} // namespace ns3
