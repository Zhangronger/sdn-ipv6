/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2017 Jadavpur University, India
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
 * Author: Manoj Kumar Rana <manoj24.rana@gmail.com>
 */

#include "ns3/log.h"
#include "ns3/assert.h"
#include "ns3/packet.h"
#include "ns3/node.h"
#include "ns3/ipv6.h"
#include "ns3/ipv6-l3-protocol.h"
#include "ns3/ipv6-interface.h"
#include "ns3/ipv6-interface-address.h"
#include "ns3/ipv6-extension-header.h"
#include "ns3/ipv6-option-header.h"
#include "ns3/callback.h"
#include "ns3/icmpv6-l4-protocol.h"
#include "ns3/ipv6-static-routing-helper.h"
#include "ns3/ipv6-static-routing.h"
#include "ns3/ipv6-routing-table-entry.h"
#include "mipv6-header.h"
#include "mipv6-mobility.h"
#include "mipv6-demux.h"
#include "mipv6-l4-protocol.h"
#include "mipv6-mn.h"
#include "mipv6-tun-l4-protocol.h"
#include "ns3/udp-l4-protocol.h"
#include "ns3/tcp-l4-protocol.h"
#include "ns3/pointer.h"
#include "ns3/trace-source-accessor.h"


using namespace std;

NS_LOG_COMPONENT_DEFINE ("Mipv6Mn");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (Mipv6Mn);

TypeId
Mipv6Mn::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::Mipv6Mn")
    .SetParent<Mipv6Agent> ()
    .AddAttribute ("BList", "The binding list associated with this MN.",
                   PointerValue (),
                   MakePointerAccessor (&Mipv6Mn::m_buinf),
                   MakePointerChecker<BList> ())
    .AddTraceSource ("RxBA",
                     "Received BA packet from HA",
                     MakeTraceSourceAccessor (&Mipv6Mn::m_rxbaTrace),
                     "ns3::Mipv6Mn::RxBaTracedCallback")
    .AddTraceSource ("TxBU",
                     "Sent BU packet from MN",
                     MakeTraceSourceAccessor (&Mipv6Mn::m_txbuTrace),
                     "ns3::Mipv6Mn::TxBuTracedCallback")


    ;
  return tid;
}

Mipv6Mn::Mipv6Mn (std::list<Ipv6Address> haalist)
{
  m_Haalist = haalist;
  m_hsequence = 0;
  m_cnsequence = 0;
  m_roflag = false;
}

Mipv6Mn::~Mipv6Mn ()
{
  delete this;
}

void Mipv6Mn::NotifyNewAggregate ()
{
  NS_LOG_FUNCTION (this);

  uint8_t buf1[8],buf2[16],buf[16];
  uint8_t i;

  if (GetNode () == 0)
    {
      Ptr<Node> node = this->GetObject<Node> ();
      SetNode (node);
      m_buinf = CreateObject<BList> (m_Haalist);
      m_buinf->SetNode (node);


      //Fetch any link-local address of the node
      Ptr<Ipv6> ip = GetNode ()->GetObject<Ipv6> ();
      Ipv6InterfaceAddress ads = ip->GetAddress (1,0);


//Set HAA and Forming HoA from HAA Prefix

      if (m_Haalist.size ())
        {
          m_buinf->SetHA (m_Haalist.front ()); // The first address
          (m_buinf->GetHA ()).GetBytes (buf1); //Fetching Prefix
          (ads.GetAddress ()).GetBytes (buf2); //Fetching interface identifier
          for (i = 0; i < 8; i++)
            {
              buf[i] = buf1[i];
            }
          for (i = 0; i < 8; i++)
            {
              buf[i + 8] = buf2[i + 8];
            }
          Ipv6Address addr (buf);
          m_buinf->SetHoa (addr);
          Ptr<Ipv6TunnelL4Protocol> tunnel4prot = GetNode ()->GetObject<Ipv6TunnelL4Protocol> ();
          tunnel4prot->SetHomeAddress (addr);
        }


      m_buinf->SetHomeInitCookie (0xFFFFFFFFFFFFFFFF);
      m_buinf->SetCareOfInitCookie (0xFFFFFFFFFFFFFFFF);
      m_buinf->SetHomeKeygenToken (0x0);
      m_buinf->SetCareOfKeygenToken (0x0);
      m_buinf->SetHomeNonceIndex (0x0);
      m_buinf->SetCareOfNonceIndex (0x0);
      m_buinf->SetCN ("0::0");
      m_OldinterfaceIndex = -1;


      Ptr<Icmpv6L4Protocol> icmpv6l4 = GetNode ()->GetObject<Icmpv6L4Protocol> ();
      icmpv6l4->SetNewIPCallback (MakeCallback (&Mipv6Mn::HandleNewAttachment, this));
      icmpv6l4->SetCheckAddressCallback (MakeCallback (&Mipv6Mn::CheckAddresses, this));

      Ptr<Ipv6L3Protocol> ipv6l3 = GetNode ()->GetObject<Ipv6L3Protocol> ();
      ipv6l3->SetPrefixCallback (MakeCallback (&Mipv6Mn::SetDefaultRouterAddress, this));

      Ptr<UdpL4Protocol> udpl4 = GetNode ()->GetObject<UdpL4Protocol> ();
      udpl4->SetMipv6Callback (MakeCallback (&BList::GetHoa, m_buinf));

      Ptr<TcpL4Protocol> tcpl4 = GetNode ()->GetObject<TcpL4Protocol> ();
      tcpl4->SetMipv6Callback (MakeCallback (&BList::GetHoa, m_buinf));

      Ptr<Ipv6TunnelL4Protocol> tunnell4 = GetNode ()->GetObject<Ipv6TunnelL4Protocol> ();
      tunnell4->SetCacheAddressList (m_Haalist);
      tunnell4->SetHA (m_buinf->GetHA ());
    }
  Mipv6Agent::NotifyNewAggregate ();
}


uint16_t Mipv6Mn::GetHomeBUSequence ()
{
  NS_LOG_FUNCTION (this);

  return ++m_hsequence;
}

uint16_t Mipv6Mn::GetCNBUSequence ()
{
  NS_LOG_FUNCTION (this);

  return ++m_cnsequence;
}


Ptr<Packet> Mipv6Mn::BuildHomeBU ()
{

  Ptr<Packet> p = Create<Packet> ();

//Adding home address option

  Ipv6ExtensionDestinationHeader destextnhdr;
  Ipv6HomeAddressOptionHeader homeopt;
  homeopt.SetHomeAddress (m_buinf->GetHoa ());
  destextnhdr.AddOption (homeopt);

  destextnhdr.SetNextHeader (59);
  p->AddHeader (destextnhdr);


  Ipv6MobilityBindingUpdateHeader bu;


  bu.SetSequence (m_buinf->GetHomeLastBindingUpdateSequence ());
  bu.SetFlagA (true);
  bu.SetFlagH (true);
  bu.SetFlagL (true);
  bu.SetFlagK (true);


  bu.SetLifetime ((uint16_t)Mipv6L4Protocol::MAX_BINDING_LIFETIME);

  p->AddHeader (bu);

  return p;
}

Ptr<Packet> Mipv6Mn::BuildCNBU ()
{

  Ptr<Packet> p = Create<Packet> ();

//Adding home address option

  Ipv6ExtensionDestinationHeader destextnhdr;
  Ipv6HomeAddressOptionHeader homeopt;
  homeopt.SetHomeAddress (m_buinf->GetHoa ());
  destextnhdr.AddOption (homeopt);

  destextnhdr.SetNextHeader (59);
  p->AddHeader (destextnhdr);


  Ipv6MobilityBindingUpdateHeader bu;


  bu.SetSequence (m_buinf->GetCNLastBindingUpdateSequence ());
  bu.SetFlagA (true);
  bu.SetFlagH (true);
  bu.SetFlagL (true);
  bu.SetFlagK (true);


  bu.SetLifetime ((uint16_t)Mipv6L4Protocol::MAX_BINDING_LIFETIME);

  p->AddHeader (bu);

  return p;
}



Ptr<Packet> Mipv6Mn::BuildHoTI ()
{

  Ptr<Packet> p = Create<Packet> ();

  Ipv6HoTIHeader hoti;

  hoti.SetReserved2 (0);
  hoti.SetHomeInitCookie (m_buinf->GetHomeInitCookie ());

//Adding home address option

  Ipv6ExtensionDestinationHeader destextnhdr;
  Ipv6HomeAddressOptionHeader homeopt;
  homeopt.SetHomeAddress (m_buinf->GetHoa ());
  destextnhdr.AddOption (homeopt);

  destextnhdr.SetNextHeader (59);
  p->AddHeader (destextnhdr);


  p->AddHeader (hoti);

  return p;
}

Ptr<Packet> Mipv6Mn::BuildCoTI ()
{

  Ptr<Packet> p = Create<Packet> ();

  Ipv6CoTIHeader coti;

  coti.SetReserved2 (0);
  coti.SetCareOfInitCookie (m_buinf->GetCareOfInitCookie ());

//Adding home address option

  Ipv6ExtensionDestinationHeader destextnhdr;
  Ipv6HomeAddressOptionHeader homeopt;
  homeopt.SetHomeAddress (m_buinf->GetHoa ());
  destextnhdr.AddOption (homeopt);

  destextnhdr.SetNextHeader (59);
  p->AddHeader (destextnhdr);


  p->AddHeader (coti);

  return p;
}



void Mipv6Mn::HandleNewAttachment (Ipv6Address ipr)
{
  if (!ipr.IsLinkLocal () )// && !ipr.IsEqual(m_buinf->GetHoa()))
    {
      Ipv6Address coa = ipr;
      m_buinf->SetCoa (coa);

      ClearTunnelAndRouting ();
      Ptr<Ipv6> ipv6 = GetNode ()->GetObject<Ipv6> ();
      NS_ASSERT (ipv6);


      //preset header information
      m_buinf->SetHomeLastBindingUpdateSequence (GetHomeBUSequence ());
      //Cut to micro-seconds
      m_buinf->SetHomeLastBindingUpdateTime (MicroSeconds (Simulator::Now ().GetMicroSeconds ()));
      //reset (for the first registration)
      m_buinf->ResetHomeRetryCount ();

      Ptr<Packet> p = BuildHomeBU ();

      //save packet
      m_buinf->SetHomeBUPacket (p);


      //send BU
      NS_LOG_FUNCTION (this << p->GetSize ());
      


      
      SendMessage (p->Copy (), m_buinf->GetHA (), 64);
      Ptr<Packet> pkt = p->Copy ();
      m_txbuTrace (pkt, m_buinf->GetCoa (), m_buinf->GetHA ());


      m_buinf->StartHomeRetransTimer ();

      if (m_buinf->IsHomeReachable ())
        {
          m_buinf->MarkHomeRefreshing ();
        }
      else
        {
          m_buinf->MarkHomeUpdating ();
        }
    }
}

uint8_t Mipv6Mn::HandleBA (Ptr<Packet> packet, const Ipv6Address &src, const Ipv6Address &dst, Ptr<Ipv6Interface> interface)
{

  // Options are not implemented yet!!

  NS_LOG_FUNCTION (this << packet << src << dst << interface << "HANDLE BACK");

  Ptr<Packet> p = packet->Copy ();
  Ptr<Packet> pkt = packet->Copy ();
  m_rxbaTrace (pkt, src, dst, interface);

  Ipv6MobilityBindingAckHeader ba;
  Ipv6ExtensionType2RoutingHeader exttype2;

  p->RemoveHeader (ba);
  p->RemoveHeader (exttype2);

  Ptr<Mipv6Demux> mipv6Demux = GetNode ()->GetObject<Mipv6Demux> ();
  NS_ASSERT (mipv6Demux);

  Ptr<Mipv6Mobility> ipv6Mobility = mipv6Demux->GetMobility (ba.GetMhType ());
  NS_ASSERT (ipv6Mobility);

  //check for sequence
  if (IsHomeMatch (src) && (m_buinf->GetHoa ()).IsEqual (exttype2.GetHomeAddress ()))
    {
      if (m_buinf->GetHomeLastBindingUpdateSequence () != ba.GetSequence ())
        {
          NS_LOG_LOGIC ("Sequence mismatch. Ignored. this: "
                        << m_buinf->GetHomeLastBindingUpdateSequence ()
                        << ", from: "
                        << ba.GetSequence ());

          return 0;
        }

      //check status code
      switch (ba.GetStatus ())
        {
        case Mipv6Header::BA_STATUS_BINDING_UPDATE_ACCEPTED:
          {
            m_buinf->StopHomeRetransTimer ();
            m_buinf->SetHomeAddressRegistered (true);
            m_buinf->SetHomeBUPacket (0);
            m_buinf->SetHomeReachableTime (Seconds (ba.GetLifetime ()));


            if (ba.GetLifetime () > 0)
              {
                if (!(m_buinf->GetHoa ()).IsEqual (m_buinf->GetCoa ()))
                  {
                    SetupTunnelAndRouting ();
                  }

                m_buinf->MarkHomeReachable ();

                //Setup lifetime
                m_buinf->StopHomeRefreshTimer ();
                m_buinf->StartHomeRefreshTimer ();
                m_buinf->StopHomeReachableTimer ();
                m_buinf->StartHomeReachableTimer ();
                if (IsRouteOptimizationRequired () && !m_buinf->GetCN ().IsEqual ("0::0") && !(m_buinf->GetHoa ()).IsEqual (m_buinf->GetCoa ()))
                  {
                    Ptr<Packet> p = BuildHoTI ();
                    m_buinf->SetHoTIPacket (p);
                    m_buinf->ResetHoTIRetryCount ();
                    SendMessage (p->Copy (), m_buinf->GetCN (), 64);
                    m_buinf->StartHoTIRetransTimer ();
                  }
              }
            else
              {
                ClearTunnelAndRouting ();
              }



            break;
          }

        default:
          NS_LOG_LOGIC ("Error occurred code=" << ba.GetStatus ());

        }

      return 0;
    }
  else if (src.IsEqual (m_buinf->GetCN ()) && (m_buinf->GetHoa ()).IsEqual (exttype2.GetHomeAddress ()))
    {
      if (m_buinf->GetCNLastBindingUpdateSequence () != ba.GetSequence ())
        {
          NS_LOG_LOGIC ("Sequence mismatch. Ignored. this: "
                        << m_buinf->GetCNLastBindingUpdateSequence ()
                        << ", from: "
                        << ba.GetSequence ());

          return 0;
        }

      //check status code
      switch (ba.GetStatus ())
        {
        case Mipv6Header::BA_STATUS_BINDING_UPDATE_ACCEPTED:
          {
            m_buinf->StopCNRetransTimer ();
            m_buinf->SetCNBUPacket (0);
            m_buinf->SetCNReachableTime (Seconds (ba.GetLifetime ()));


            if (ba.GetLifetime () > 0)
              {

                m_buinf->MarkCNReachable ();

                //Setup lifetime
                m_buinf->StopCNRefreshTimer ();
                m_buinf->StartCNRefreshTimer ();
                m_buinf->StopCNReachableTimer ();
                m_buinf->StartCNReachableTimer ();
              }

            break;
          }

        default:
          NS_LOG_LOGIC ("Error occurred code=" << ba.GetStatus ());
        }

      return 0;

    }

  else
    {
      NS_LOG_LOGIC ("Error occurred code, No source found");
    }

  return 0;

}

bool Mipv6Mn::IsHomeMatch (Ipv6Address addr)
{
  std::list<Ipv6Address>::iterator iter = std::find (m_Haalist.begin (), m_Haalist.end (), addr);
  if ( m_Haalist.end () == iter )
    {
      return false;
    }
  else
    {
      return true;
    }
}

Ipv6Address Mipv6Mn::GetCoA ()
{
return m_buinf->GetCoa ();
}


uint8_t Mipv6Mn::HandleHoT (Ptr<Packet> packet, const Ipv6Address &src, const Ipv6Address &dst, Ptr<Ipv6Interface> interface)
{
  NS_LOG_FUNCTION (this << packet << src << dst << interface << "HANDLE HoT");

  Ptr<Packet> p = packet->Copy ();

  Ipv6HoTHeader hot;
  Ipv6ExtensionType2RoutingHeader exttype2;

  p->RemoveHeader (hot);
  p->RemoveHeader (exttype2);

  Ptr<Mipv6Demux> mipv6Demux = GetNode ()->GetObject<Mipv6Demux> ();
  NS_ASSERT (mipv6Demux);

  Ptr<Mipv6Mobility> ipv6Mobility = mipv6Demux->GetMobility (hot.GetMhType ());
  NS_ASSERT (ipv6Mobility);

  //check for timestamp and sequence
  if (m_buinf->GetHomeInitCookie () != hot.GetHomeInitCookie () )
    {
      NS_LOG_LOGIC ("Home Init Cookie mismatch. Ignored. this: "
                    << m_buinf->GetHomeInitCookie ()
                    << ", from: "
                    << hot.GetHomeInitCookie ());

    }
  if (!((m_buinf->GetHoa ()).IsEqual (exttype2.GetHomeAddress ())))
    {
      NS_LOG_LOGIC ("Home Address mismatch. Ignored. this: ");
      return 0;
    }

  m_buinf->StopHoTIRetransTimer ();
  m_buinf->SetHoTIPacket (0);
  m_buinf->SetHomeNonceIndex (hot.GetHomeNonceIndex ());
  m_buinf->SetHomeKeygenToken (hot.GetHomeKeygenToken ());

  Ptr<Packet> pc = BuildCoTI ();
  m_buinf->SetCoTIPacket (pc);
  m_buinf->ResetCoTIRetryCount ();
  SendMessage (pc->Copy (), m_buinf->GetCN (), 64);
  m_buinf->StartCoTIRetransTimer ();


  return 0;
}

uint8_t Mipv6Mn::HandleCoT (Ptr<Packet> packet, const Ipv6Address &src, const Ipv6Address &dst, Ptr<Ipv6Interface> interface)
{
  NS_LOG_FUNCTION (this << packet << src << dst << interface << "HANDLE CoT");

  Ptr<Packet> p = packet->Copy ();

  Ipv6CoTHeader cot;
  Ipv6ExtensionType2RoutingHeader exttype2;

  p->RemoveHeader (cot);
  p->RemoveHeader (exttype2);

  Ptr<Mipv6Demux> mipv6Demux = GetNode ()->GetObject<Mipv6Demux> ();
  NS_ASSERT (mipv6Demux);

  Ptr<Mipv6Mobility> ipv6Mobility = mipv6Demux->GetMobility (cot.GetMhType ());
  NS_ASSERT (ipv6Mobility);

  //check for sequence
  if (m_buinf->GetCareOfInitCookie () != cot.GetCareOfInitCookie () )
    {
      NS_LOG_LOGIC ("Care of Init Cookie mismatch. Ignored. this: "
                    << m_buinf->GetCareOfInitCookie ()
                    << ", from: "
                    << cot.GetCareOfInitCookie ());

    }

  m_buinf->StopCoTIRetransTimer ();
  m_buinf->SetCoTIPacket (0);
  m_buinf->SetCareOfNonceIndex (cot.GetCareOfNonceIndex ());
  m_buinf->SetCareOfKeygenToken (cot.GetCareOfKeygenToken ());

  if (!((m_buinf->GetHoa ()).IsEqual (exttype2.GetHomeAddress ())))
    {
      NS_LOG_LOGIC ("Home Address mismatch. Ignored. this: ");
      return 0;
    }


  //preset header information
  m_buinf->SetCNLastBindingUpdateSequence (GetCNBUSequence ());
  //Cut to micro-seconds
  m_buinf->SetCNLastBindingUpdateTime (MicroSeconds (Simulator::Now ().GetMicroSeconds ()));
  //reset (for the first registration)
  m_buinf->ResetCNRetryCount ();

  Ptr<Packet> pc = BuildCNBU ();

  //save packet
  m_buinf->SetCNBUPacket (pc);

  NS_LOG_FUNCTION (this << pc->GetSize ());
  SendMessage (pc->Copy (), m_buinf->GetCN (), 64);

  m_buinf->StartCNRetransTimer ();



  return 0;
}



bool Mipv6Mn::SetupTunnelAndRouting ()
{
  Ptr<Ipv6TunnelL4Protocol> th = GetNode ()->GetObject<Ipv6TunnelL4Protocol> ();
  NS_ASSERT (th);

  uint16_t tunnelIf = th->AddTunnel (m_buinf->GetHA ());

  m_buinf->SetTunnelIfIndex (tunnelIf);





  Ipv6StaticRoutingHelper staticRoutingHelper;
  Ptr<Ipv6> ipv6 = GetNode ()->GetObject<Ipv6> ();

  Ptr<Ipv6StaticRouting> staticRouting = staticRoutingHelper.GetStaticRouting (ipv6);
  Ipv6RoutingTableEntry routeentry (staticRouting->GetDefaultRoute ());

  m_OldPrefixToUse = routeentry.GetPrefixToUse ();

  staticRouting->RemoveRoute (routeentry.GetDest (), routeentry.GetDestNetworkPrefix (), routeentry.GetInterface (), routeentry.GetPrefixToUse ());

  uint8_t buf1[8],buf2[16],buf[16];
  (routeentry.GetPrefixToUse ()).GetBytes (buf1);
  (m_defaultrouteraddress).GetBytes (buf2);
  for (int i = 0; i < 8; i++)
    {
      buf[i] = buf1[i];
    }
  for (int i = 0; i < 8; i++)
    {
      buf[i + 8] = buf2[i + 8];
    }
  Ipv6Address addr (buf);

  staticRouting->AddHostRouteTo (m_buinf->GetHA (), addr, m_IfIndex, Ipv6Address ("::"), 0);
  m_OldinterfaceIndex = m_IfIndex;
  staticRouting->AddNetworkRouteTo (routeentry.GetDest (), routeentry.GetDestNetworkPrefix (), m_defaultrouteraddress, m_buinf->GetTunnelIfIndex (), routeentry.GetPrefixToUse (), 0);
  staticRouting->RemoveRoute (Ipv6Address ("fe80::"), Ipv6Prefix (64), m_buinf->GetTunnelIfIndex (), Ipv6Address ("fe80::"));



  return true;


}

void Mipv6Mn::ClearTunnelAndRouting ()
{
  NS_LOG_FUNCTION (this);

  Ipv6StaticRoutingHelper staticRoutingHelper;
  Ptr<Ipv6> ipv6 = GetNode ()->GetObject<Ipv6> ();


  Ptr<Ipv6StaticRouting> staticRouting = staticRoutingHelper.GetStaticRouting (ipv6);

  staticRouting->RemoveRoute (Ipv6Address ("::"), Ipv6Prefix::GetZero (), m_buinf->GetTunnelIfIndex (), m_OldPrefixToUse);
  staticRouting->RemoveRoute (m_buinf->GetHA (), Ipv6Prefix (128), m_OldinterfaceIndex, Ipv6Address ("::"));

  //clear tunnel
  Ptr<Ipv6TunnelL4Protocol> th = GetNode ()->GetObject<Ipv6TunnelL4Protocol> ();
  NS_ASSERT (th);

  th->RemoveTunnel (m_buinf->GetHA ());

  m_buinf->SetTunnelIfIndex (-1);
}


void Mipv6Mn::SetRouteOptimizationReuiredField (bool roflag)
{
  m_roflag = roflag;
}


bool Mipv6Mn::IsRouteOptimizationRequired ()
{
  return m_roflag;
}

void Mipv6Mn::SetDefaultRouterAddress (Ipv6Address addr,  uint32_t index)
{
  m_defaultrouteraddress = addr;
  m_IfIndex = index;
}

bool Mipv6Mn::CheckAddresses (Ipv6Address ha, Ipv6Address hoa)
{
  if (ha.IsEqual (m_buinf->GetHA ()) && hoa.IsEqual (m_buinf->GetHoa ()))
    {
      return true;
    }
  return false;
}

Ipv6Address Mipv6Mn::GetHomeAddress ()
{
return m_buinf->GetHoa ();
}

} /* namespace ns3 */

