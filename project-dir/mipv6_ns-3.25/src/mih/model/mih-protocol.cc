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
#include "ns3/pointer.h"
#include "ns3/assert.h"
#include "ns3/packet.h"
#include "ns3/node.h"
#include "ns3/socket.h"
#include "ns3/socket-factory.h"
#include "ns3/packet.h"
#include "ns3/udp-socket-factory.h"
#include "ns3/tcp-socket-factory.h"
#include "mih-function.h"
#include "mih-protocol.h"
#include "mih-header.h"
#include "mih-remote-event-source-trap.h"

NS_LOG_COMPONENT_DEFINE ("MihProtocol");

namespace ns3 {
  namespace mih {

    NS_OBJECT_ENSURE_REGISTERED (MihProtocol);
    
    TypeId 
    MihProtocol::GetTypeId (void)
    {
      static TypeId tid = TypeId ("ns3::mih::MihProtocol")
	.SetParent<Object> ()
        .AddConstructor<MihProtocol> ()
        .AddAttribute ("Local", "The Address on which to Bind the rx socket.",
                       AddressValue (),
                       MakeAddressAccessor (&MihProtocol::m_local),
                       MakeAddressChecker ())
        .AddAttribute ("Protocol", "The type id of the protocol to use for the rx socket.",
                       TypeIdValue (UdpSocketFactory::GetTypeId ()),
                       MakeTypeIdAccessor (&MihProtocol::m_tid),
                       MakeTypeIdChecker ())
        .AddAttribute ("Node", "The MIH-enabled node on which the protocol is enabled.",
                       PointerValue (),
                       MakePointerAccessor (&MihProtocol::m_node),
                       MakePointerChecker<Node> ())
        ;
      return tid;
    }
    MihProtocol::MihProtocol (void)
    {
      NS_LOG_FUNCTION (this);
      m_serverSocket = 0;
      m_node = 0;
    }
    MihProtocol::~MihProtocol (void)
    {
      NS_LOG_FUNCTION (this);
      m_serverSocket = 0;
    }
    void
    MihProtocol::DoDispose (void)
    {
      NS_LOG_FUNCTION (this);
      m_serverSocket = 0;
      m_node = 0;
    }
    void
    MihProtocol::Init (void)
    {
      // Create the socket if not already
      if (m_serverSocket == 0)
        {
          m_serverSocket = Socket::CreateSocket (GetNode (), m_tid);
          m_serverSocket->Bind (m_local);
          m_serverSocket->Listen ();
        }
      m_serverSocket->SetRecvCallback (MakeCallback (&MihProtocol::HandleRead, this));
      m_serverSocket->SetAcceptCallback (
                                         MakeNullCallback<bool, Ptr<Socket>, const Address &> (),
                                         MakeCallback (&MihProtocol::ReceiveNewSessionRequest, this));
      NS_LOG_FUNCTION (this << m_serverSocket);

    }
    Ptr<Node>
    MihProtocol::GetNode() const
    {
      NS_LOG_FUNCTION (this);
      return m_node;
    }
    void 
    MihProtocol::SetNode (Ptr<Node> node)
    {
      NS_LOG_FUNCTION (this);
      m_node = node;
    }    
    bool
    MihProtocol::FindSessionByMihfId (MihfId toMihfId, SessionListI &i)
    {
      NS_LOG_FUNCTION (this);
      bool found = false;
      i = m_sessions.begin ();
      while (i != m_sessions.end ())
        {
          if ((*i)->GetToMihfId () == toMihfId)
            {
              found = true;
              return found;
            }
          i++;
        }
      return found;
    }
    bool
    MihProtocol::FindSessionByToAddress (Address toAddress, SessionListI &i)
    {
      NS_LOG_FUNCTION (this);
      bool found = false;
      i = m_sessions.begin ();
      while (i != m_sessions.end ())
        {
          if ((*i)->GetToAddress () == toAddress)
            {
              found = true;
              return found;
            }
          i++;
        }
      return found;
    }
    bool
    MihProtocol::FindSessionBySocket (Ptr<Socket> s, SessionListI &i)
    {
      NS_LOG_FUNCTION (this);
      bool found = false;
      i = m_sessions.begin ();
      while (i != m_sessions.end ())
        {
          if ((*i)->GetSocket () == s)
            {
              found = true;
              return found;
            }
          i++;
        }
      return found;
    }
    void 
    MihProtocol::AddDestinationEntry (MihfId mihfId, Address dest)
    {
      NS_LOG_FUNCTION (this);
      m_mihfIdTable[mihfId] = dest;
      return;
    }
    Ptr<Session>
    MihProtocol::GetSession (MihfId fromMihfid,
                             Address from,
                             MihfId toMihfId, 
                             Address to, 
                             Ptr<Socket> s)
    {
      NS_LOG_FUNCTION (this);

      SessionListI i;

      if (m_tid == UdpSocketFactory::GetTypeId ())
        {
          if (FindSessionByToAddress (to, i))
            {
              return (*i);
            }
          return 0;
          NS_ASSERT (0);
          Ptr<Session> session = Create<Session> ();
          session->GetRemoteEventSourceTrap ().SetSession (session);
          session->SetSocket (s);
          session->SetToMihfId (toMihfId);
          session->SetFromMihfId (fromMihfid);
          session->SetToAddress (to);
          session->SetFromAddress (from);
          session->SetInitComplete ();
          m_sessions.push_back (session);
          return session;
        }
      else if (m_tid == TcpSocketFactory::GetTypeId ())
        {
          if (!FindSessionBySocket (s, i))
            {
              NS_LOG_DEBUG ("You need first to create a connection  before a session can be searched for.");
              NS_ASSERT (0);
            }
          if (!(*i)->IsInitComplete ())
            {
              (*i)->SetFromMihfId (fromMihfid);
              (*i)->SetToMihfId (toMihfId);
              (*i)->SetFromAddress (from);
              (*i)->SetInitComplete ();
            }
          
          return *i;
        }
      else
        {
          NS_LOG_DEBUG ("Only UDP or TCP transport is allowed!");
          NS_ASSERT (0);
          return Create<Session> (); // Make the compiler happy.
        }
    }
    Ptr<Session>
    MihProtocol::StartSession (MihfId fromMihfId, 
                               Address from, 
                               MihfId toMihfId, 
                               Address to)
    {
      NS_LOG_FUNCTION (this);
      SessionListI i;
      if (FindSessionByToAddress (to, i))
        {
          return (*i);
        }
      
      Ptr<Session> session = Create<Session> ();
      session->GetRemoteEventSourceTrap ().SetSession (session);
      Ptr<Socket> socket = Socket::CreateSocket (GetNode(), m_tid);
      socket->Bind (from);
      socket->Connect (to);
      socket->SetRecvCallback (MakeCallback (&MihProtocol::HandleRead, this));
      session->SetSocket (socket);
      session->SetToMihfId (toMihfId);
      session->SetFromMihfId (fromMihfId);
      session->SetToAddress (to);
      session->SetFromAddress (from);
      session->SetInitComplete ();

      m_sessions.push_back (session);
      return session;
    }
    Address
    MihProtocol::ResolveMihfIdToAddress (MihfId mihfid)
    {
      NS_LOG_FUNCTION (this);
      Address addr = m_mihfIdTable[mihfid];
      //      NS_LOG_LOGIC ("MihfId : " << mihfid << " <==> " << addr << " Address");
      return addr;
    }
    void 
    MihProtocol::ReceiveNewSessionRequest (Ptr<Socket> s, const Address& from)
    {
      NS_LOG_FUNCTION (this);
      SessionListI i;
      if (FindSessionBySocket (s, i))
        {
          return;
        }
      Ptr<Session> session = Create<Session> ();
      session->GetRemoteEventSourceTrap ().SetSession (session);
      NS_LOG_DEBUG ("Arm a destructor event for this session!");
      s->SetRecvCallback (MakeCallback(&MihProtocol::HandleRead, this));
      session->SetToAddress (from);
      session->SetSocket (s);
      session->SetRegistered ();
      m_sessions.push_back (session);
      return;
    }
    void
    MihProtocol::HandleRead (Ptr<Socket> socket)
    {
      NS_LOG_FUNCTION (this << socket);
      Ptr<Packet> packet = 0;
      Ptr<Session> session = 0;
      Address from;

      while (packet = socket->RecvFrom (from))
        {
          MihHeader mihHeader;
          MihfId fromMihfId;
          MihfId toMihfId;
          uint8_t *packetData;
          uint32_t payloadSize;
          Buffer buffer;
          Ptr<MihFunction> mihFunction = GetObject<MihFunction> ();
          
          NS_ASSERT (mihFunction != 0);
          
          // Remove header before  accessing the payload
          packet->RemoveHeader (mihHeader);
          payloadSize = packet->GetSize ();
          packet->CopyData (packetData, payloadSize);
          buffer.AddAtStart (payloadSize);
          // Start removal of the payload;
          Buffer::Iterator i = buffer.Begin ();
          for (uint32_t j = 0; j < payloadSize; j++, packetData++)
            {
              i.WriteU8 (*packetData);
            }

          fromMihfId.TlvDeserialize (buffer);
          toMihfId.TlvDeserialize (buffer);

          NS_ASSERT (toMihfId == mihFunction->GetMihfId ());

          if (mihHeader.GetServiceId () == MihHeader::MANAGEMENT)
            {
              switch (mihHeader.GetActionId ())
                {
                case MihHeader::MIH_REGISTER :
                  if (mihHeader.GetOpCode () == MihHeader::REQUEST)
                    {
                      LinkIdentifierList linkIdentifierList;
                      RegistrationCode registrationCode;
                      TlvDeserialize (buffer, linkIdentifierList);
                      registrationCode.TlvDeserialize (buffer);
//                       session = GetSession (toMihfId, Address (), fromMihfId, from, socket);
                      if (session == 0)
                        {
                          session = Create<Session> ();
                          session->GetRemoteEventSourceTrap ().SetSession (session);
                          session->SetSocket (socket);
                          session->SetToMihfId (fromMihfId);
                          session->SetFromMihfId (toMihfId);
                          session->SetToAddress (from);
                          session->SetFromAddress (Address ());
                          session->SetInitComplete ();
                          m_sessions.push_back (session);
                        }
                      NS_ASSERT (session != 0);
                      session->SetRegistered ();
                      mihFunction->RegisterIndication (fromMihfId, 
                                                       linkIdentifierList, 
                                                       registrationCode, 
                                                       session->ReceiveRegisterRequest (packet,
                                                                                        mihHeader.GetTransactionId ()));
                    }
                  else if (mihHeader.GetOpCode () == MihHeader::RESPONSE)
                    {
                      Status status;
                      uint32_t validLifeTime = 0;
                      status.TlvDeserialize (buffer);
                      status.GetType () == Status::SUCCESS ?
                        Tlv::DeserializeU32 (buffer, validLifeTime, TLV_VALID_TIME_INTERVAL) :
                        validLifeTime = 0;
                      session = GetSession (toMihfId, Address (), fromMihfId, from, socket);
                      NS_ASSERT (session != 0);
                      session->SetRegistered ();
                      status.GetType () == Status::SUCCESS ? 
                        session->ReceiveRegisterResponse (fromMihfId, status, validLifeTime) : 
                        session->ReceiveRegisterResponse (fromMihfId, status);
                    }
                  else
                    {
                      NS_ASSERT (0);
                    }
                  break;
                case MihHeader::MIH_DEREGISTER :
                  NS_ASSERT (0);
                  break;
                case MihHeader::MIH_EVENT_SUBSCRIBE :
                  if (mihHeader.GetOpCode () == MihHeader::REQUEST)
                    {
                      LinkIdentifier linkIdentifier;
                      EventList events;
                      linkIdentifier.TlvDeserialize (buffer);
                      events.TlvDeserialize (buffer);

                      session = GetSession (toMihfId, Address (), fromMihfId, from, socket);
                      NS_ASSERT (session != 0);
                      NS_ASSERT (session->IsRegistered ());

                      RemoteEventSourceTrap &remoteEventSourceTrap = session->GetRemoteEventSourceTrap ();
                      
                      MihLinkDetectedIndicationCallback linkDetectedEventCallback1 = 
                        MakeNullCallback<void, MihfId, LinkDetectedInformationList> ();
                      EventList::Type linkDetectedEventType1 = 
                        EventList::INVALID;
                      MihLinkUpIndicationCallback linkUpEventCallback2 = 
                        MakeNullCallback<void, MihfId, LinkIdentifier, Address, Address, bool, MobilityManagementSupport> ();
                      EventList::Type linkUpEventType2 = 
                        EventList::INVALID;
                      MihLinkDownIndicationCallback linkDownEventCallback3 = 
                        MakeNullCallback<void, MihfId, LinkIdentifier, Address, LinkDownReason> ();
                      EventList::Type linkDownEventType3 =
                        EventList::INVALID;
                      MihLinkParametersReportIndicationCallback linkParamReportEventCallback4 = 
                        MakeNullCallback<void, MihfId, LinkIdentifier, LinkParameterReportList> ();
                      EventList::Type linkParamReportEventType4 = 
                        EventList::INVALID;
                      MihLinkGoingDownIndicationCallback linkGoingDownEventCallback5 = 
                        MakeNullCallback<void, MihfId, LinkIdentifier, uint64_t, LinkGoingDownReason> ();
                      EventList::Type linkGoingDownEventType5 =
                        EventList::INVALID;
                      MihLinkHandoverImminentIndicationCallback linkHOImminentEventCallback6 = 
                        MakeNullCallback<void, MihfId, LinkIdentifier, LinkIdentifier, Address, Address> ();
                      EventList::Type linkHOImminentEventType6 =
                        EventList::INVALID;
                      MihLinkHandoverCompleteIndicationCallback linkHOCompleteEventCallback7 = 
                        MakeNullCallback<void, MihfId, LinkIdentifier, LinkIdentifier, Address, Address, Status> ();
                      EventList::Type linkHOCompleteEventType7 = EventList::INVALID;
                      MihLinkPduTransmitStatusIndicationCallback linkPduTxStatusEventCallback8 = 
                        MakeNullCallback<void, MihfId, LinkIdentifier, uint16_t, bool> ();
                      EventList::Type linkPduTxStatusEventType8 = 
                        EventList::INVALID;

                      if (events.IsOfType (EventList::LINK_DETECTED))
                        {
                          linkDetectedEventCallback1 = MakeCallback (&RemoteEventSourceTrap::LinkDetected, 
                                                                     &remoteEventSourceTrap);
                          linkDetectedEventType1 = EventList::LINK_DETECTED;
                        }
                      if (events.IsOfType (EventList::LINK_UP))
                        {
                          linkUpEventCallback2 = MakeCallback (&RemoteEventSourceTrap::LinkUp, 
                                                               &remoteEventSourceTrap);
                          linkUpEventType2 = EventList::LINK_UP;
                        }
                      if (events.IsOfType (EventList::LINK_DOWN))
                        {
                          linkDownEventCallback3 = MakeCallback (&RemoteEventSourceTrap::LinkDown, 
                                                                 &remoteEventSourceTrap);
                          linkDownEventType3 = EventList::LINK_DOWN;
                        }
                      if (events.IsOfType (EventList::LINK_PARAMETERS_REPORT))
                        {
                          linkParamReportEventCallback4 = MakeCallback (&RemoteEventSourceTrap::LinkParametersReport,
                                                                        &remoteEventSourceTrap);
                          linkParamReportEventType4 = EventList::LINK_PARAMETERS_REPORT;
                        }
                      if (events.IsOfType (EventList::LINK_GOING_DOWN))
                        {
                          linkGoingDownEventCallback5 = MakeCallback (&RemoteEventSourceTrap::LinkGoingDown, 
                                                                      &remoteEventSourceTrap);
                          linkGoingDownEventType5 = EventList::LINK_GOING_DOWN;
                        }
                      if (events.IsOfType (EventList::LINK_HANDOVER_IMMINENT))
                        {
                          linkHOImminentEventCallback6 = MakeCallback (&RemoteEventSourceTrap::LinkHandoverImminent, 
                                                                       &remoteEventSourceTrap);
                          linkHOImminentEventType6 = EventList::LINK_HANDOVER_IMMINENT;
                        }
                      if (events.IsOfType (EventList::LINK_HANDOVER_COMPLETE))
                        {
                          linkHOCompleteEventCallback7 = MakeCallback (&RemoteEventSourceTrap::LinkHandoverComplete,
                                                                       &remoteEventSourceTrap);
                          linkHOCompleteEventType7 = EventList::LINK_HANDOVER_COMPLETE;
                        }
                      if (events.IsOfType (EventList::LINK_PDU_TRANSMIT_STATUS))
                        {
                          NS_LOG_DEBUG ("Don't transport Link PDU Tx Status Event!");
                          NS_ASSERT (0);
//                           linkPduTxStatusEventCallback8 = MakeCallback (&RemoteEventSourceTrap::LinkPduTxStatus, 
//                                                                         &remoteEventSourceTrap);
//                           linkPduTxStatusEventType8 = EventList::LINK_PDU_TRANSMIT_STATUS;
                        }
                      // Call Local EventSubscribe;
                      mihFunction->EventSubscribe (toMihfId,
                                                   linkIdentifier,
                                                   EventConfigurationInformation (),
                                                   linkDetectedEventType1,
                                                   linkDetectedEventCallback1,
                                                   linkUpEventType2,
                                                   linkUpEventCallback2,
                                                   linkDownEventType3,
                                                   linkDownEventCallback3,
                                                   linkParamReportEventType4,
                                                   linkParamReportEventCallback4,
                                                   linkGoingDownEventType5,
                                                   linkGoingDownEventCallback5,
                                                   linkHOImminentEventType6,
                                                   linkHOImminentEventCallback6,
                                                   linkHOCompleteEventType7,
                                                   linkHOCompleteEventCallback7,
                                                   linkPduTxStatusEventType8,
                                                   linkPduTxStatusEventCallback8,
                                                   session->ReceiveEventSubscribeRequest (packet, 
                                                                                          mihHeader.GetTransactionId ()));
                    }
                  else if (mihHeader.GetOpCode () == MihHeader::RESPONSE)
                    {
                      Status status;
                      LinkIdentifier linkIdentifier;
                      EventList events;

                      status.TlvDeserialize (buffer);
                      linkIdentifier.TlvDeserialize (buffer);
                      events.TlvDeserialize (buffer);

                      session = GetSession (toMihfId, 
                                            Address (), 
                                            fromMihfId,
                                            from, 
                                            socket);
                      NS_ASSERT (session != 0);
                      NS_ASSERT (session->IsRegistered ());
                      session->ReceiveEventSubscribeResponse (fromMihfId,
                                                              status,
                                                              linkIdentifier,
                                                              events);
                    }
                  else
                    {
                      NS_ASSERT (0);
                    }
                  break;
                case MihHeader::MIH_EVENT_UNSUBSCRIBE :
                  NS_ASSERT (0);
                  break;
                case MihHeader::MIH_CAPABILITY_DISCOVER :
                  if (mihHeader.GetOpCode () == MihHeader::REQUEST)
                    {
                      NetworkTypeAddressList networkTypeAddresses;
                      EventList events;
                      MihCommandList commands;
                      InformationServiceQueryTypeList informationServiceQueryTypes;
                      TransportSupportList transportSupports;
                      MakeBeforeBreakSupportList makeBeforeBreakSupports;
                      TlvDeserialize (buffer, networkTypeAddresses);
                      events.TlvDeserialize (buffer);
                      commands.TlvDeserialize (buffer);
                      informationServiceQueryTypes.TlvDeserialize (buffer);
                      transportSupports.TlvDeserialize (buffer);
                      TlvDeserialize (buffer, makeBeforeBreakSupports);
                      session = GetSession (toMihfId, Address (), fromMihfId, from, socket);
                      NS_ASSERT (session != 0);
                      NS_ASSERT (session->IsRegistered ());
                      
                      mihFunction->CapabilityDiscoverIndication (fromMihfId,
                                                                 networkTypeAddresses,
                                                                 events,
                                                                 commands,
                                                                 informationServiceQueryTypes,
                                                                 transportSupports,
                                                                 makeBeforeBreakSupports,
                                                                 session->ReceiveCapabilityDiscoverRequest (packet,
                                                                                                            mihHeader.GetTransactionId ()));
                    }
                  else if (mihHeader.GetOpCode () == MihHeader::RESPONSE)
                    {
                      Status status;
                      NetworkTypeAddressList networkTypeAddresses;
                      EventList events;
                      MihCommandList commands;
                      InformationServiceQueryTypeList miisQueries;
                      TransportSupportList transportOptions;
                      MakeBeforeBreakSupportList mbbSupportList;
                      
                      status.TlvDeserialize (buffer);
                      TlvDeserialize (buffer, networkTypeAddresses);
                      events.TlvDeserialize (buffer);
                      commands.TlvDeserialize (buffer);
                      miisQueries.TlvDeserialize (buffer);
                      transportOptions.TlvDeserialize (buffer);
                      TlvDeserialize (buffer, mbbSupportList);

                      session = GetSession (toMihfId, 
                                            Address (), 
                                            fromMihfId,
                                            from, 
                                            socket);
                      NS_ASSERT (session != 0);
                      NS_ASSERT (session->IsRegistered ());

                      session->ReceiveCapabilityDiscoverResponse (fromMihfId,
                                                                  status,
                                                                  networkTypeAddresses,
                                                                  events,
                                                                  commands,
                                                                  miisQueries,
                                                                  transportOptions,
                                                                  mbbSupportList);
                    }
                  else
                    {
                      NS_ASSERT (0);
                    }
                  break;
                default:
                  NS_ASSERT (0);
                }
            }
          else if (mihHeader.GetServiceId () == MihHeader::EVENT)
            {
              RemoteEventDestinationTrap remoteEventDestinationTrap;
              session = GetSession (toMihfId, 
                                    Address (), 
                                    fromMihfId,
                                    from, 
                                    socket);
              NS_ASSERT (session != 0);
              NS_ASSERT (session->IsRegistered ());
                      
              remoteEventDestinationTrap = session->GetRemoteEventDestinationTrap ();
              
              switch (mihHeader.GetActionId ())
                {
                case MihHeader::MIH_LINK_DETECTED :
                  {
                    LinkDetectedInformationList linkDetectedInformationList;
                    TlvDeserialize (buffer, linkDetectedInformationList);
                    remoteEventDestinationTrap.LinkDetected (fromMihfId,
                                                             linkDetectedInformationList);
                    break;
                  }
                case MihHeader::MIH_LINK_UP :
                  {
                    LinkIdentifier linkIdentifier; 
                    Address oldAR;
                    Address newAR; 
                    bool ipRenewalFlag; 
                    MobilityManagementSupport mbbSupport;
                    linkIdentifier.TlvDeserialize (buffer);
                    Tlv::Deserialize (buffer, oldAR, TLV_OLD_ACCESS_ROUTER);
                    Tlv::Deserialize (buffer, newAR, TLV_NEW_ACCESS_ROUTER);
                    Tlv::DeserializeBool (buffer, ipRenewalFlag, TLV_IP_RENEWAL_FLAG);
                    mbbSupport.TlvDeserialize (buffer);
                    remoteEventDestinationTrap.LinkUp (fromMihfId,
                                                       linkIdentifier,
                                                       oldAR,
                                                       newAR,
                                                       ipRenewalFlag,
                                                       mbbSupport);
                    break;
                  }
                case MihHeader::MIH_LINK_DOWN :
                  {
                    LinkIdentifier linkIdentifier;
                    Address oldAR;
                    LinkDownReason reasonCode;
                    
                    linkIdentifier.TlvDeserialize (buffer);
                    Tlv::Deserialize (buffer, oldAR, TLV_OLD_ACCESS_ROUTER);
                    reasonCode.TlvDeserialize (buffer);
                    remoteEventDestinationTrap.LinkDown (fromMihfId,
                                                         linkIdentifier,
                                                         oldAR,
                                                         reasonCode);
                    break;
                  }
                case MihHeader::MIH_LINK_PARAMETERS_REPORT :
                  {
                    LinkIdentifier linkIdentifier;
                    LinkParameterReportList parameters;
                    
                    linkIdentifier.TlvDeserialize (buffer);
                    TlvDeserialize (buffer, parameters);
                    remoteEventDestinationTrap.LinkParametersReport (fromMihfId,
                                                                     linkIdentifier,
                                                                     parameters);
                    break;
                  }
                case MihHeader::MIH_LINK_GOING_DOWN :
                  {
                    LinkIdentifier linkIdentifier;
                    uint64_t timeInterval;
                    LinkGoingDownReason reasonCode;
                    
                    linkIdentifier.TlvDeserialize (buffer);
                    Tlv::DeserializeU64 (buffer, timeInterval, TLV_TIME_INTERVAL);
                    reasonCode.TlvDeserialize (buffer);
                    
                    remoteEventDestinationTrap.LinkGoingDown (fromMihfId,
                                                              linkIdentifier,
                                                              timeInterval,
                                                              reasonCode);
                    break;
                  }
                case MihHeader::MIH_LINK_HANDOVER_IMMINENT :
                  {
                    LinkIdentifier oldLinkIdentifier;
                    LinkIdentifier newLinkIdentifier;
                    Address oldAR;
                    Address newAR;
                    
                    oldLinkIdentifier.TlvDeserialize (buffer);
                    newLinkIdentifier.TlvDeserialize (buffer);
                    Tlv::Deserialize (buffer, oldAR, TLV_OLD_ACCESS_ROUTER);
                    Tlv::Deserialize (buffer, newAR, TLV_NEW_ACCESS_ROUTER);
                    
                    remoteEventDestinationTrap.LinkHandoverImminent (fromMihfId,
                                                                     oldLinkIdentifier,
                                                                     newLinkIdentifier,
                                                                     oldAR,
                                                                     newAR);
                    break;
                  }
                case MihHeader::MIH_LINK_HANDOVER_COMPLETE :
                  {
                    LinkIdentifier oldLinkIdentifier;
                    LinkIdentifier newLinkIdentifier;
                    Address oldAR;
                    Address newAR;
                    Status handoverStatus;
                    
                    oldLinkIdentifier.TlvDeserialize (buffer);
                    newLinkIdentifier.TlvDeserialize (buffer);
                    Tlv::Deserialize (buffer, oldAR, TLV_OLD_ACCESS_ROUTER);
                    Tlv::Deserialize (buffer, newAR, TLV_NEW_ACCESS_ROUTER);
                    handoverStatus.TlvDeserialize (buffer);
                    
                    remoteEventDestinationTrap.LinkHandoverComplete (fromMihfId,
                                                                     oldLinkIdentifier,
                                                                     newLinkIdentifier,
                                                                     oldAR,
                                                                     newAR,
                                                                     handoverStatus);
                    break;
                  }
                default:
                  NS_LOG_DEBUG ("Specified event type is not suported");
                  NS_ASSERT (0);
                  break;
                }
            }
          else if (mihHeader.GetServiceId () == MihHeader::COMMAND)
            {
              switch (mihHeader.GetActionId ())
                {
                case MihHeader::MIH_LINK_GET_PARAMETERS :
                  if (mihHeader.GetOpCode () == MihHeader::REQUEST) {
                    DeviceStatesRequest deviceStatesRequest;
                    LinkIdentifierList linkIdentifierList;
                    LinkStatusRequest linkStatusRequest;
                    
                    deviceStatesRequest.TlvDeserialize (buffer);
                    TlvDeserialize (buffer, linkIdentifierList);
                    linkStatusRequest.TlvDeserialize (buffer);

                    session = GetSession (toMihfId,
                                          Address (),
                                          fromMihfId, 
                                          from,
                                          socket);
                    NS_ASSERT (session != 0);
                    NS_ASSERT (session->IsRegistered ());
                      
                    // Call local LinkGetParamters;
                    mihFunction->LinkGetParameters (toMihfId,
                                                    deviceStatesRequest,
                                                    linkIdentifierList,
                                                    linkStatusRequest,
                                                    session->ReceiveLinkGetParametersRequest (packet, 
                                                                                              mihHeader.GetTransactionId ()));
                  }
                  else if (mihHeader.GetOpCode () == MihHeader::RESPONSE)
                    {
                      Status status;
                      DeviceStatesResponseList deviceStatesResponseList;
                      LinkStatusResponseList linkStatusResponseList;
                      
                      status.TlvDeserialize (buffer);
                      TlvDeserialize (buffer, deviceStatesResponseList);
                      TlvDeserialize (buffer, linkStatusResponseList);

                      session = GetSession (toMihfId,
                                            Address (),
                                            fromMihfId, 
                                            from,
                                            socket);
                      NS_ASSERT (session != 0);
                      NS_ASSERT (session->IsRegistered ());
                      
                      session->ReceiveLinkGetParametersResponse (fromMihfId,
                                                                 status,
                                                                 deviceStatesResponseList,
                                                                 linkStatusResponseList);
                    }
                  else
                    {
                      NS_ASSERT (0);
                    }
                    break;
                case MihHeader::MIH_LINK_CONFIGURE_THRESHOLDS :
                  if (mihHeader.GetOpCode () == MihHeader::REQUEST)
                    {
                      LinkIdentifier linkIdentifier;
                      LinkConfigurationParameterList linkConfigurationParameters;

                      linkIdentifier.TlvDeserialize (buffer);
                      TlvDeserialize (buffer, linkConfigurationParameters);
                      

                      session = GetSession (toMihfId,
                                            Address (),
                                            fromMihfId, 
                                            from,
                                            socket);
                      NS_ASSERT (session != 0);
                      NS_ASSERT (session->IsRegistered ());
                      
                      // Call local LinkConfigureThresholds;
                      mihFunction->LinkConfigureThresholds (toMihfId,
                                                            linkIdentifier,
                                                            linkConfigurationParameters,
                                                            session->ReceiveLinkConfigureThresholdsRequest (packet, 
                                                                                                            mihHeader.GetTransactionId ()));
                    }
                  else if (mihHeader.GetOpCode () == MihHeader::RESPONSE)
                    {
                      Status status;
                      LinkIdentifier linkIdentifier;
                      LinkConfigurationStatusList linkConfigurationStatusList;
                      
                      status.TlvDeserialize (buffer);
                      linkIdentifier.TlvDeserialize (buffer);
                      TlvDeserialize (buffer, linkConfigurationStatusList);
                      
                      session = GetSession (toMihfId,
                                            Address (),
                                            fromMihfId, 
                                            from,
                                            socket);
                      NS_ASSERT (session != 0);
                      NS_ASSERT (session->IsRegistered ());
                      
                      session->ReceiveLinkConfigureThresholdsResponse (fromMihfId,
                                                                       status,
                                                                       linkIdentifier,
                                                                       linkConfigurationStatusList);
                    }
                  else
                    {
                      NS_ASSERT (0);
                    }
                  break;
                case MihHeader::MIH_LINK_ACTIONS :
                  NS_ASSERT (0);
                  break;
                case MihHeader::MIH_NET_HO_CANDIDATE_QUERY :
                  NS_ASSERT (0);
                  break;
                case MihHeader::MIH_MN_HO_CANDIDATE_QUERY :
                  NS_ASSERT (0);
                  break;
                case MihHeader::MIH_N2N_HO_QUERY_RESOURCES :
                  NS_ASSERT (0);
                  break;
                case MihHeader::MIH_MN_HO_COMMIT :
                  NS_ASSERT (0);
                  break;
                case MihHeader::MIH_NET_HO_COMMIT :
                  NS_ASSERT (0);
                  break;
                case MihHeader::MIH_N2N_HO_COMMIT :
                  NS_ASSERT (0);
                  break;
                case MihHeader::MIH_MN_HO_COMPLETE :
                  NS_ASSERT (0);
                  break;
                case MihHeader::MIH_N2N_HO_COMPLETE :
                  NS_ASSERT (0);
                  break;
                default:
                  NS_ASSERT (0);
                }              
            }
          else if (mihHeader.GetServiceId () == MihHeader::INFORMATION)
            {
              switch (mihHeader.GetActionId ())
                {
                case MihHeader::MIH_GET_INFORMATION :
                  NS_ASSERT (0);
                  break;
                default:
                  NS_ASSERT (0);
                }
            }
          else
            {
              NS_ASSERT (0);
            }
        }
    }
    void 
    MihProtocol::SendCapabilityDiscoverRequest (MihfId destinationIdentifier,
                                                NetworkTypeAddressList networkTypeAddresses,
                                                EventList events,
                                                MihCommandList commands,
                                                InformationServiceQueryTypeList informationServiceQueryTypes,
                                                TransportSupportList transportSupports,
                                                MakeBeforeBreakSupportList makeBeforeBreakSupports,
                                                MihCapabilityDiscoverConfirmCallback capabilityDiscoverConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
      MihfId selfMihfid = GetObject<MihFunction> ()->GetMihfId ();
      Buffer buffer;
      Address to = ResolveMihfIdToAddress (destinationIdentifier);
      Address from = ResolveMihfIdToAddress (selfMihfid);
      Ptr<Packet> packet;
      Ptr<Session> session;
      // TLV-Serialize in buffer;
      selfMihfid.TlvSerialize (buffer);
      destinationIdentifier.TlvSerialize (buffer);
      TlvSerialize (buffer, networkTypeAddresses);
      events.TlvSerialize (buffer);
      commands.TlvSerialize (buffer);
      informationServiceQueryTypes.TlvSerialize (buffer);
      transportSupports.TlvSerialize (buffer);
      TlvSerialize (buffer, makeBeforeBreakSupports);
      // Fill the packet with payload from buffer;
      packet = Create<Packet> (buffer.PeekData (), buffer.GetSize ());
      session = StartSession (selfMihfid, from, destinationIdentifier, to);
      session->SendCapabilityDiscoverRequest (packet, 
                                              capabilityDiscoverConfirmCallback);      
    }
    void 
    MihProtocol::SendRegisterRequest (MihfId destinationIdentifier,
                                      LinkIdentifierList linkIdentifierList,
                                      RegistrationCode registrationCode,
                                      MihRegisterConfirmCallback registerConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
      MihfId selfMihfid = GetObject<MihFunction> ()->GetMihfId ();
      Buffer buffer;
      Address to = ResolveMihfIdToAddress (destinationIdentifier);
      Address from = ResolveMihfIdToAddress (selfMihfid);
      Ptr<Packet> packet;
      Ptr<Session> session;
      // TLV-Serialize in buffer;
      selfMihfid.TlvSerialize (buffer);
      destinationIdentifier.TlvSerialize (buffer);
      TlvSerialize (buffer, linkIdentifierList);
      registrationCode.TlvSerialize (buffer);
      // Fill the packet with payload from buffer;
      packet = Create<Packet> (buffer.PeekData (), buffer.GetSize ());
      session = StartSession (selfMihfid, from, destinationIdentifier, to);
      session->SendRegisterRequest (packet,
                                    registerConfirmCallback);
    }
    void
    MihProtocol::SendDeRegisterRequest (MihfId destinationIdentifier,
                                        MihDeRegisterConfirmCallback deRegisterConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (0);
    }
    void
    MihProtocol::SendEventSubscribeRequest (MihfId destinationIdentifier,
                                            LinkIdentifier linkIdentifier,
                                            EventConfigurationInformation configurationInformation,
                                            EventList::Type linkDetectedEventType1,
                                            MihLinkDetectedIndicationCallback linkDetectedEventCallback1,
                                            EventList::Type linkUpEventType2,
                                            MihLinkUpIndicationCallback linkUpEventCallback2,
                                            EventList::Type linkDownEventType3,
                                            MihLinkDownIndicationCallback linkDownEventCallback3,
                                            EventList::Type linkParamReportEventType4,
                                            MihLinkParametersReportIndicationCallback linkParamReportEventCallback4,
                                            EventList::Type linkGoingDownEventType5,
                                            MihLinkGoingDownIndicationCallback linkGoingDownEventCallback5,
                                            EventList::Type linkHOImminentEventType6,
                                            MihLinkHandoverImminentIndicationCallback linkHOImminentEventCallback6,
                                            EventList::Type linkHOCompleteEventType7,
                                            MihLinkHandoverCompleteIndicationCallback linkHOCompleteEventCallback7,
                                            EventList::Type linkPduTxStatusEventType8,
                                            MihLinkPduTransmitStatusIndicationCallback linkPduTxStatusEventCallback8,
                                            MihEventSubscribeConfirmCallback subscribeConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (configurationInformation.GetLinkDetectedConfigurationN () == 0 && 
                 configurationInformation.GetLinkConfigurationParameterN () == 0);

      MihfId selfMihfid = GetObject<MihFunction> ()->GetMihfId ();
      Buffer buffer;
      Address to = ResolveMihfIdToAddress (destinationIdentifier);
      Address from = ResolveMihfIdToAddress (selfMihfid);
      Ptr<Packet> packet;
      Ptr<Session> session;
      // Mih Event List to send in the request;
      EventList events (EventList::INVALID);
      events.SetEventList (events.GetEventList () | linkDetectedEventType1);
      events.SetEventList (events.GetEventList () | linkUpEventType2);
      events.SetEventList (events.GetEventList () | linkDownEventType3);
      events.SetEventList (events.GetEventList () | linkParamReportEventType4);
      events.SetEventList (events.GetEventList () | linkGoingDownEventType5);
      events.SetEventList (events.GetEventList () | linkHOImminentEventType6);
      events.SetEventList (events.GetEventList () | linkHOCompleteEventType7);
      events.SetEventList (events.GetEventList () | linkPduTxStatusEventType8);
      // TLV-Serialize in buffer;
      selfMihfid.TlvSerialize (buffer);
      destinationIdentifier.TlvSerialize (buffer);
      linkIdentifier.TlvSerialize (buffer);
      // Extra configuration information is not supported yet!
      events.TlvSerialize (buffer);
      // Fill the packet with payload from buffer;
      packet = Create<Packet> (buffer.PeekData (), buffer.GetSize ());
      NS_LOG_LOGIC ("Packet Size = " << buffer.GetSize ());
      session = StartSession (selfMihfid, from, destinationIdentifier, to);
      session->SendEventSubscribeRequest (packet, 
                                          events, 
                                          linkDetectedEventCallback1,
                                          linkUpEventCallback2,
                                          linkDownEventCallback3,
                                          linkParamReportEventCallback4,
                                          linkGoingDownEventCallback5,
                                          linkHOImminentEventCallback6,
                                          linkHOCompleteEventCallback7,
                                          linkPduTxStatusEventCallback8,
                                          subscribeConfirmCallback);
    }
    void 
    MihProtocol::SendLinkGetParametersRequest (MihfId destinationIdentifier,
                                               DeviceStatesRequest deviceStatesRequest,
                                               LinkIdentifierList linkIdentifierList,
                                               LinkStatusRequest linkStatusRequest,
                                               MihLinkGetParametersConfirmCallback getParamtersConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
      MihfId selfMihfid = GetObject<MihFunction> ()->GetMihfId ();
      Buffer buffer;
      Address to = ResolveMihfIdToAddress (destinationIdentifier);
      Address from = ResolveMihfIdToAddress (selfMihfid);
      Ptr<Packet> packet;
      Ptr<Session> session;
      // TLV-Serialize in buffer;
      selfMihfid.TlvSerialize (buffer);
      destinationIdentifier.TlvSerialize (buffer);
      deviceStatesRequest.TlvSerialize (buffer);
      TlvSerialize (buffer, linkIdentifierList);
      linkStatusRequest.TlvSerialize (buffer);
      // Fill the packet with payload from buffer;
      packet = Create<Packet> (buffer.PeekData (), buffer.GetSize ());
      session = StartSession (selfMihfid, from, destinationIdentifier, to);
      session->SendLinkGetParametersRequest (packet,
                                             getParamtersConfirmCallback);
    }
    void
    MihProtocol::SendLinkConfigureThresholdsRequest (MihfId destinationIdentifier,
                                                     LinkIdentifier linkIdentifier,
                                                     LinkConfigurationParameterList linkConfigurationParameters,
                                                     MihLinkConfigureThresholdsConfirmCallback configureThresholdsConfiirmCallback)
    {
      NS_LOG_FUNCTION (this);
      MihfId selfMihfid = GetObject<MihFunction> ()->GetMihfId ();
      Buffer buffer;
      Address to = ResolveMihfIdToAddress (destinationIdentifier);
      Address from = ResolveMihfIdToAddress (selfMihfid);
      Ptr<Packet> packet;
      Ptr<Session> session;
      // TLV-Serialize in buffer;
      selfMihfid.TlvSerialize (buffer);
      destinationIdentifier.TlvSerialize (buffer);
      linkIdentifier.TlvSerialize (buffer);
      TlvSerialize (buffer, linkConfigurationParameters);
      // Fill the packet with payload from buffer;
      packet = Create<Packet> (buffer.PeekData (), buffer.GetSize ());
      session = StartSession (selfMihfid, from, destinationIdentifier, to);
      session->SendLinkConfigureThresholdsRequest (packet,
                                                   configureThresholdsConfiirmCallback);
    }
  } // namespace mih
} // namespace ns3
