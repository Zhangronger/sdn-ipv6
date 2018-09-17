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

#include "mih-command-list.h"

namespace ns3 {
  namespace mih {
    MihCommandList::MihCommandList (uint32_t commands) :
      m_bitmap (commands)
    {}
    MihCommandList::MihCommandList (MihCommandList const &o)
    {
      m_bitmap = o.m_bitmap;
    }
    TLV_TYPE_HELPER_IMPLEM (MihCommandList, TLV_MIH_COMMAND_LIST)
    void 
    MihCommandList::SetCommandList (uint32_t supportedCommands)
    {
      m_bitmap = supportedCommands;
    }
    uint32_t 
    MihCommandList::GetCommandList (void)
    {
      return m_bitmap;
    }
    uint32_t 
    MihCommandList::GetTlvSerializedSize (void) const
    {
      return Tlv::GetSerializedSizeU32 ();
    }
    void 
    MihCommandList::Print (std::ostream &os) const
    {
      os <<
        "Commands = 0x" << std::hex << (uint32_t)m_bitmap 
                    << std::endl
        ;
    }
    void
    MihCommandList::TlvSerialize (Buffer &buffer) const
    {
      Tlv::SerializeU32 (buffer, m_bitmap, TLV_MIH_COMMAND_LIST);
    }
    uint32_t 
    MihCommandList::TlvDeserialize (Buffer &buffer)
    {
      return Tlv::DeserializeU32 (buffer, m_bitmap, TLV_MIH_COMMAND_LIST);
    }
  } // namespace mih
} // namespace ns3
