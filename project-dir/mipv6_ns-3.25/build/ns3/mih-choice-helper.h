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

#ifndef   	MIH_CHOICE_HELPER_H
#define   	MIH_CHOICE_HELPER_H

#include <map>
#include <stdint.h>
#include "ns3/ptr.h"
#include "ns3/assert.h"
#include "ns3/callback.h"
#include "ns3/simulation-singleton.h"
#include "mih-tlv-object-factory.h"

#define PRINT_POSITION                            \
  std::cerr << "file=" << __FILE__                \
  << ", line=" << __LINE__                        \
  << ", function=" << __FUNCTION__                \
  << std::endl;

#define CHOICE_HELPER_PURE_VIRTUAL_HEADER(parent)                       \
  virtual uint8_t GetType (void) = 0;                                   \
  static uint8_t Register (void);                                       \
  virtual ~parent (void);                                               \
  static Ptr<parent> CreateFromTlvType (uint8_t tlvTypeValue);          \


#define CHOICE_HELPER_PURE_VIRTUAL_IMPLEM(parent)                       \
  Ptr<parent>                                                           \
  parent::CreateFromTlvType (uint8_t tlvTypeValue)                      \
  {                                                                     \
    return SimulationSingleton<TlvObjectFactory<parent> >::Get ()->Create (tlvTypeValue); \
  }                                                                     \
  uint8_t                                                               \
  parent::Register (void)                                               \
  {                                                                     \
    static uint8_t typ = 0;                                             \
    typ++;                                                              \
    return typ;                                                         \
  }                                                                     \
  parent::~parent (void)                                                \
  {}                                                                    \

#define CHOICE_HELPER_HEADER(child,parent)        \
  virtual uint8_t GetType (void);                 \
  static uint8_t GetClassType (void);             \
  static Ptr<parent> Create (void);

#define CHOICE_HELPER_IMPLEM(child,parent)                      \
  Ptr<parent>                                                   \
  child::Create (void)                                          \
  {                                                             \
    return DynamicCast<parent,child> (ns3::Create<child> ());   \
  }                                                             \
  uint8_t                                                       \
  child::GetClassType (void)                                    \
  {                                                             \
    static uint8_t typ = parent::Register ();                   \
    return typ;                                                 \
  }                                                             \
  uint8_t                                                       \
  child::GetType (void)                                         \
  {                                                             \
    return GetClassType ();                                     \
  }


#endif 	    /* !MIH_CHOICE_HELPER_H */
