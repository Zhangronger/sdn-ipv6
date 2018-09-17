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
#include "ns3/assert.h"
#include "ns3/ptr.h"
#include "mih-function.h"
#include "mih-protocol.h"

NS_LOG_COMPONENT_DEFINE ("MihFunction");

#define EVENT_SUBSCRIBE_SWITCH(eventType,cb)            \
  switch (eventType)                                    \
    {                                                   \
 case EventList::LINK_DETECTED :                        \
  {                                                     \
  linkDetectedEventCallback1.Assign (cb);                       \
  linkDetectedEventType1 = EventList::LINK_DETECTED;            \
  break;                                                        \
  }                                                             \
 case EventList::LINK_UP :                                      \
 {                                                              \
  linkUpEventCallback2.Assign (cb);                             \
  linkUpEventType2 = EventList::LINK_UP;                        \
  break;                                                        \
 }                                                              \
 case EventList::LINK_DOWN :                                    \
 {                                                              \
 linkDownEventCallback3.Assign (cb);                            \
 linkDownEventType3 = EventList::LINK_DOWN;                     \
 break;                                                         \
 }                                                              \
 case EventList::LINK_PARAMETERS_REPORT :                       \
 {                                                              \
 linkParamReportEventCallback4.Assign (cb);                             \
 linkParamReportEventType4 = EventList::LINK_PARAMETERS_REPORT;         \
 break;                                                                 \
 }                                                                      \
 case EventList::LINK_GOING_DOWN :                                      \
 {                                                                      \
 linkGoingDownEventCallback5.Assign (cb);                               \
 linkGoingDownEventType5 = EventList::LINK_GOING_DOWN;                  \
 break;                                                                 \
 }                                                                      \
 case EventList::LINK_HANDOVER_IMMINENT :                               \
 {                                                                      \
 linkHOImminentEventCallback6.Assign (cb);                              \
 linkHOImminentEventType6 = EventList::LINK_HANDOVER_IMMINENT;          \
 break;                                                                 \
 }                                                                      \
 case EventList::LINK_HANDOVER_COMPLETE :                               \
 {                                                                      \
 linkHOCompleteEventCallback7.Assign (cb);                              \
 linkHOCompleteEventType7 = EventList::LINK_HANDOVER_COMPLETE;          \
 break;                                                                 \
 }                                                                      \
 case EventList::LINK_PDU_TRANSMIT_STATUS :                             \
 {                                                                      \
 linkPduTxStatusEventCallback8.Assign (cb);                             \
 linkPduTxStatusEventType8 = EventList::LINK_PDU_TRANSMIT_STATUS;       \
 break;                                                                 \
 }                                                                      \
 case EventList::INVALID :                                              \
   break;                                                               \
 default:                                                               \
 {                                                                      \
   NS_LOG_DEBUG("Event Type = " << (int)eventType);                     \
   NS_ASSERT (0);                                                       \
 }                                                                      \
    }                                                                   \

namespace ns3 {
  namespace mih {
    TypeId 
    MihFunction::GetTypeId (void)
    {
      static TypeId tid = TypeId ("ns3::mih::MihFunction")
	.SetParent<Object> ()
        .AddConstructor<MihFunction> ()
        .AddAttribute ("MihfId", "MIH Function Identifier",
                       MihfIdValue (MihfId ("default-mihf-id@ns3")),
                       MakeMihfIdAccessor (&MihFunction::SetMihfId,
                                           &MihFunction::GetMihfId),
                       MakeMihfIdChecker ())
        ;
      return tid;
    }
    MihFunction::MihFunction (void) :
      m_mihfId (),
      m_registeredMihLinkSapList (),
      m_postponedActionsConfirmCallback (MakeNullCallback<void, MihfId, Status, LinkActionResponseList> ()),
      m_linkActionResponseList (),
      m_linkActionConfirmEventIds (),
      m_linkActionsCompleteEvent (),
      m_actionRequestN (0),
      m_linkActionsComplete (false)
    {
      NS_LOG_FUNCTION (this);
    }
    MihFunction::~MihFunction (void)
    {
      NS_LOG_FUNCTION (this);
    }
    void
    MihFunction::DoDispose (void)
    {
      NS_LOG_FUNCTION (this);
      if (!m_linkActionConfirmEventIds.empty ())
        {
          for (uint32_t j = 0; j < m_linkActionConfirmEventIds.size (); j++)
            {
              if (m_linkActionConfirmEventIds[j].IsRunning ())
                {
                  m_linkActionConfirmEventIds[j].Cancel ();
                }
            }
          m_linkActionConfirmEventIds.clear ();
        }
      if (m_linkActionsCompleteEvent.IsRunning ())
        {
          m_linkActionsCompleteEvent.Cancel ();
        }
      if (!m_linkActionResponseList.empty ())
        {
          m_linkActionResponseList.clear ();
        }
      Object::DoDispose ();
    }
    MihfId
    MihFunction::GetMihfId (void) const
    {
      NS_LOG_FUNCTION (this);
      return m_mihfId;
    }
    void
    MihFunction::SetMihfId (MihfId mihfId)
    {
      NS_LOG_FUNCTION (this);
      m_mihfId = mihfId;
    }
    MihLinkSapListI 
    MihFunction::GetRegisteredMihLinkSapListBegin (void)
    {
      NS_LOG_FUNCTION (this);
      return m_registeredMihLinkSapList.begin ();
    }
    MihLinkSapListI 
    MihFunction::GetRegisteredMihLinkSapListEnd (void)
    {
      NS_LOG_FUNCTION (this);
      return m_registeredMihLinkSapList.end ();
    }
    uint32_t 
    MihFunction::GetRegisteredMihLinkSapListN (void)
    {
      NS_LOG_FUNCTION (this);
      return m_registeredMihLinkSapList.size ();
    }
    bool
    MihFunction::Register (Ptr<MihLinkSap> sap)
    {
      NS_LOG_FUNCTION (this);
      MihLinkSapListI iter;
      
      if (FindMihLinkSap (sap->GetLinkIdentifier (), iter))
        {
          return false;
        }
      m_registeredMihLinkSapList.push_back (sap);
      return true;
    }
    bool 
    MihFunction::FindMihLinkSap (LinkIdentifier linkIdentifier, MihLinkSapListI &iter)
    {
      NS_LOG_FUNCTION (this);
      bool found = false;
      LinkType linkType (linkIdentifier.GetType ());
      Address linkAddress = linkIdentifier.GetDeviceLinkAddress ();
      iter = GetRegisteredMihLinkSapListBegin ();
      while (iter != GetRegisteredMihLinkSapListEnd ())
        {
          if ((*iter)->GetLinkType () == linkType && 
              (*iter)->GetLinkAddress () == linkAddress)
            {
              found = true;
              return found;
            }
          iter++;
        }
      return found;
    }
    void 
    MihFunction::CapabilityDiscover (MihfId destinationIdentifier,
				     NetworkTypeAddressList networkTypeAddresses,
				     EventList events,
				     MihCommandList commands,
				     InformationServiceQueryTypeList informationServiceQueryTypes,
				     TransportSupportList transportSupports,
				     MakeBeforeBreakSupportList makeBeforeBreakSupports,
				     MihCapabilityDiscoverConfirmCallback capabilityDiscoverConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
      if (destinationIdentifier == GetMihfId ())
	{
	  NetworkTypeAddressList networkTypeAddressList;
	  MakeBeforeBreakSupportList mbbSupports;
	  for (MihLinkSapListI i = GetRegisteredMihLinkSapListBegin (); i != GetRegisteredMihLinkSapListEnd (); i++)
	    {
	      networkTypeAddressList.push_back (Create<NetworkTypeAddress> ((*i)->GetLinkType (),
                                                                            (*i)->GetLinkAddress ()));
	    }
	  mbbSupports.push_back (Create<MakeBeforeBreakSupport> (LinkType (LinkType::WIRELESS_802_11), 
								 LinkType (LinkType::WIRELESS_802_11), 
								 true));
	  mbbSupports.push_back (Create<MakeBeforeBreakSupport> (LinkType (LinkType::WIRELESS_802_11), 
								 LinkType (LinkType::WIRELESS_802_16), 
								 true));
	  mbbSupports.push_back (Create<MakeBeforeBreakSupport> (LinkType (LinkType::WIRELESS_802_16), 
								 LinkType (LinkType::WIRELESS_802_16), 
								 true));
	  capabilityDiscoverConfirmCallback (GetMihfId (),
					     Status (Status::SUCCESS),
					     networkTypeAddressList,
					     EventList (EventList::LINK_DETECTED | 
                                                        EventList::LINK_UP | 
							EventList::LINK_DOWN | 
                                                        EventList::LINK_PARAMETERS_REPORT | 
							EventList::LINK_GOING_DOWN |
                                                        EventList::LINK_HANDOVER_IMMINENT | 
							EventList::LINK_HANDOVER_COMPLETE |
                                                        EventList::LINK_PDU_TRANSMIT_STATUS),
					     MihCommandList (MihCommandList::LINK_GET_PARAMETERS | 
							     MihCommandList::LINK_CONFIGURE_THRESHOLDS | 
							     MihCommandList::LINK_ACTIONS | 
							     MihCommandList::NET_HO_CANDIDATE_QUERY | 
							     MihCommandList::NET_HO_COMMIT | 
							     MihCommandList::N2N_HO_QUERY_RESOURCES | 
							     MihCommandList::N2N_HO_COMMIT | 
							     MihCommandList::N2N_HO_COMPLETE | 
							     MihCommandList::MN_HO_CANDIDATE_QUERY | 
							     MihCommandList::MN_HO_COMMIT | 
							     MihCommandList::MN_HO_COMPLETE),
					     InformationServiceQueryTypeList (InformationServiceQueryTypeList::INVALID),
					     TransportSupportList (TransportSupportList::UDP |
                                                                   TransportSupportList::TCP ),
					     mbbSupports);
	}
      else
	{
	  Ptr<MihProtocol> mihProtocol = 0;
          mihProtocol = GetObject<MihProtocol> ();
          NS_ASSERT (mihProtocol);
	  mihProtocol->SendCapabilityDiscoverRequest (destinationIdentifier,
                                                      networkTypeAddresses, 
                                                      events, 
                                                      commands,
                                                      informationServiceQueryTypes, 
                                                      transportSupports,
                                                      makeBeforeBreakSupports, 
                                                      capabilityDiscoverConfirmCallback);
	}
    }
    void
    MihFunction::CapabilityDiscoverIndication (MihfId mihfId,
                                               NetworkTypeAddressList networkTypeAddresses,
                                               EventList events,
                                               MihCommandList commands,
                                               InformationServiceQueryTypeList informationServiceQueryTypes,
                                               TransportSupportList transportSupports,
                                               MakeBeforeBreakSupportList makeBeforeBreakSupports,
                                               MihCapabilityDiscoverResponseCallback capabilityDiscoverResponseCallback)
    {
      NS_LOG_FUNCTION (this);
      m_mihCapabilityDiscoverIndicationTracedCallback (mihfId,
                                                       networkTypeAddresses,
                                                       events,
                                                       commands,
                                                       informationServiceQueryTypes,
                                                       transportSupports,
                                                       makeBeforeBreakSupports,
                                                       capabilityDiscoverResponseCallback);
    }
    void 
    MihFunction::RegisterMihCapabilityDiscoverIndicationCallback (MihCapabilityDiscoverIndicationCallback capabilityDiscoverIndicationCallback)
    {
      NS_LOG_FUNCTION (this);
      m_mihCapabilityDiscoverIndicationTracedCallback.ConnectWithoutContext (capabilityDiscoverIndicationCallback);
    }
    void 
    MihFunction::Register (MihfId destinationIdentifier,
			   LinkIdentifierList linkIdentifierList,
			   RegistrationCode registrationCode,
			   MihRegisterConfirmCallback registerConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (destinationIdentifier != GetMihfId ());
      Ptr<MihProtocol> mihProtocol = 0;
      mihProtocol = GetObject<MihProtocol> ();
      NS_ASSERT (mihProtocol);
      mihProtocol->SendRegisterRequest (destinationIdentifier,
                                        linkIdentifierList,
                                        registrationCode,
                                        registerConfirmCallback);
    }
    void 
    MihFunction::RegisterMihRegisterIndicationCallback (MihRegisterIndicationCallback registerIndicationCallback)
    {
      NS_LOG_FUNCTION (this);
      m_mihRegisterIndicationTracedCallback.ConnectWithoutContext (registerIndicationCallback);
    }
    void
    MihFunction::RegisterIndication (MihfId mihfid, 
                                     LinkIdentifierList linkIdentifierList, 
                                     RegistrationCode registrationCode, 
                                     MihRegisterResponseCallback responseCallback)
    {
      NS_LOG_FUNCTION (this);
      m_mihRegisterIndicationTracedCallback (mihfid, 
                                             linkIdentifierList, 
                                             registrationCode, 
                                             responseCallback);
    }
    void 
    MihFunction::DeRegister (MihfId destinationIdentifier,
			     MihDeRegisterConfirmCallback deRegisterConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (destinationIdentifier != GetMihfId ());
      Ptr<MihProtocol> mihProtocol = 0;
      mihProtocol = GetObject<MihProtocol> ();
      NS_ASSERT (mihProtocol);

      mihProtocol->SendDeRegisterRequest (destinationIdentifier,
                                          deRegisterConfirmCallback);
    }
    void 
    MihFunction::RegisterMihDeRegisterIndicationCallback (MihDeRegisterIndicationCallback deRegister)
    {
      NS_LOG_FUNCTION (this);
      m_mihDeRegisterIndicationTracedCallback.ConnectWithoutContext (deRegister);
    }
    void
    MihFunction::EventSubscribe (MihfId destinationIdentifier,
                                 LinkIdentifier linkIdentifier,
                                 MihEventSubscribeConfirmCallback subscribeConfirmCallback,
                                 EventList::Type eventType1,
                                 CallbackBase cb1,
                                 EventList::Type eventType2,
                                 CallbackBase cb2,
                                 EventList::Type eventType3,
                                 CallbackBase cb3,
                                 EventList::Type eventType4,
                                 CallbackBase cb4,
                                 EventList::Type eventType5,
                                 CallbackBase cb5,
                                 EventList::Type eventType6,
                                 CallbackBase cb6,
                                 EventList::Type eventType7,
                                 CallbackBase cb7,
                                 EventList::Type eventType8,
                                 CallbackBase cb8)
    {
      NS_LOG_FUNCTION (this);
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

      EVENT_SUBSCRIBE_SWITCH (eventType1, cb1);
      EVENT_SUBSCRIBE_SWITCH (eventType2, cb2);
      EVENT_SUBSCRIBE_SWITCH (eventType3, cb3);
      EVENT_SUBSCRIBE_SWITCH (eventType4, cb4);
      EVENT_SUBSCRIBE_SWITCH (eventType5, cb5);
      EVENT_SUBSCRIBE_SWITCH (eventType6, cb6);
      EVENT_SUBSCRIBE_SWITCH (eventType7, cb7);
      EVENT_SUBSCRIBE_SWITCH (eventType8, cb8);

      EventSubscribe (destinationIdentifier,
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
                      subscribeConfirmCallback);
    }
    void
    MihFunction::EventSubscribe (MihfId destinationIdentifier,
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
      if (destinationIdentifier == GetMihfId ())
        {
          MihLinkSapListI mihLinkSapI;
          NS_ASSERT (configurationInformation.GetLinkDetectedConfigurationN () == 0 && 
                     configurationInformation.GetLinkConfigurationParameterN () == 0);
          EventList events (EventList::INVALID);
          if (!FindMihLinkSap (linkIdentifier, mihLinkSapI))
            {
              NS_LOG_DEBUG ("Illegal MihLinkSap search!");
              subscribeConfirmCallback (GetMihfId (), 
                                        Status (Status::REJECTED),
                                        linkIdentifier, 
                                        events);
              return;
            }
          LinkEventSubscribeConfirm linkEventSubscribeConfirm;
          linkEventSubscribeConfirm = (*mihLinkSapI)->EventSubscribe (linkDetectedEventType1,
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
                                                                      linkPduTxStatusEventCallback8);
          subscribeConfirmCallback (GetMihfId (),
                                    linkEventSubscribeConfirm.GetStatus (), 
                                    (*mihLinkSapI)->GetLinkIdentifier (), 
                                    linkEventSubscribeConfirm.GetEventList ());
        }
      else
        {
          Ptr<MihProtocol> mihProtocol = 0;
          mihProtocol = GetObject<MihProtocol> ();
          NS_ASSERT (mihProtocol);
          mihProtocol->SendEventSubscribeRequest (destinationIdentifier,
                                                  linkIdentifier,
                                                  configurationInformation,
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
                                                  subscribeConfirmCallback);
        }
    }
    void 
    MihFunction::EventUnsubscribe (MihfId destinationIdentifier,
				   LinkIdentifier linkIdentifier,
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
                                   MihEventUnsubscribeConfirmCallback unsubscribeConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
      NS_FATAL_ERROR ("Not yet implemented!");
    }
    void 
    MihFunction::LinkGetParameters (MihfId destinationIdentifier,
				    DeviceStatesRequest deviceStatesRequest,
				    LinkIdentifierList linkIdentifierList,
				    LinkStatusRequest linkStatusRequest,
				    MihLinkGetParametersConfirmCallback getParamtersConfirmCallback)
    {
      NS_LOG_FUNCTION (this);

      MihfId mihfid = GetMihfId ();

      NS_LOG_LOGIC ("Source Identifier = " << mihfid << ", Destination Identifier = " << destinationIdentifier << ", Link Identifier List = " << linkIdentifierList);
      if (destinationIdentifier == GetMihfId ())
        {
          MihLinkSapListI mihLinkSapI;
          DeviceStatesResponseList deviceStatesResponses;
          LinkStatusResponseList linkStatusResponses;
          Status status (Status::SUCCESS);
          
          if (linkIdentifierList.size () != 0) // Browse only a subset
                                               // of registered MihLinkSaps
            {
              for (LinkIdentifierListI i = linkIdentifierList.begin (); i != linkIdentifierList.end (); i++)
                {
                  if (!FindMihLinkSap ((**i), mihLinkSapI))
                    {
                      NS_LOG_WARN ("Illegal MihLinkSap search!");
                      NS_ASSERT (0);
                      status.SetType (Status::UNSPECIFIED_FAILURE);
                      continue;
                    }
                  LinkGetParametersConfirm linkGetParametersConfirm;
                  linkGetParametersConfirm = (*mihLinkSapI)->GetParameters (linkStatusRequest.GetLinkParameterTypeList (),
                                                                            linkStatusRequest.GetLinkStatesRequest (),
                                                                            linkStatusRequest.GetLinkDescriptorsRequest ());
                  if (linkGetParametersConfirm.GetStatus ().GetType () != Status::SUCCESS)
                    {
                      status.SetType (linkGetParametersConfirm.GetStatus ().GetType ());
                      break;
                    }

                  Ptr<LinkStatusResponse> linkStatusResponse = Create<LinkStatusResponse>(**i);
                  linkStatusResponse->SetLinkStatesResponseList (linkGetParametersConfirm.GetLinkStatesResponseList ());
                  linkStatusResponse->SetLinkParameterList (linkGetParametersConfirm.GetLinkParameterList ());
                  linkStatusResponse->SetLinkDescriptorsResponseList (linkGetParametersConfirm.GetLinkDescriptorsResponseList ());
                  
                  Ptr<DeviceStatesResponse> deviceStatesResponse = (*mihLinkSapI)->GetDeviceStates ();

                  linkStatusResponses.push_back (linkStatusResponse);
                  deviceStatesResponses.push_back (deviceStatesResponse);
                }
            }
          else // Browse all of the registered MihLinkSaps
            {
              for (mihLinkSapI = GetRegisteredMihLinkSapListBegin (); mihLinkSapI != GetRegisteredMihLinkSapListEnd (); mihLinkSapI++)
                {
                  LinkGetParametersConfirm linkGetParametersConfirm;
                  linkGetParametersConfirm = (*mihLinkSapI)->GetParameters (linkStatusRequest.GetLinkParameterTypeList (),
                                                                            linkStatusRequest.GetLinkStatesRequest (),
                                                                            linkStatusRequest.GetLinkDescriptorsRequest ());
                  if (linkGetParametersConfirm.GetStatus ().GetType () != Status::SUCCESS)
                    {
                      status.SetType (linkGetParametersConfirm.GetStatus ().GetType ());
                      break;
                    }

                  Ptr<LinkStatusResponse> linkStatusResponse = Create<LinkStatusResponse>((*mihLinkSapI)->GetLinkIdentifier ());
                  linkStatusResponse->SetLinkStatesResponseList (linkGetParametersConfirm.GetLinkStatesResponseList ());
                  linkStatusResponse->SetLinkParameterList (linkGetParametersConfirm.GetLinkParameterList ());
                  linkStatusResponse->SetLinkDescriptorsResponseList (linkGetParametersConfirm.GetLinkDescriptorsResponseList ());
                  
                  Ptr<DeviceStatesResponse> deviceStatesResponse = (*mihLinkSapI)->GetDeviceStates ();

                  linkStatusResponses.push_back (linkStatusResponse);
                  deviceStatesResponses.push_back (deviceStatesResponse);
                }
            }
          getParamtersConfirmCallback (GetMihfId (),
                                       status,
                                       deviceStatesResponses,
                                       linkStatusResponses);
        }
      else
        {
          Ptr<MihProtocol> mihProtocol = 0;
          mihProtocol = GetObject<MihProtocol> ();
          NS_ASSERT (mihProtocol);
          mihProtocol->SendLinkGetParametersRequest (destinationIdentifier,
                                                     deviceStatesRequest,
                                                     linkIdentifierList,
                                                     linkStatusRequest,
                                                     getParamtersConfirmCallback);
        }
    }
    void 
    MihFunction::LinkConfigureThresholds (MihfId destinationIdentifier,
					  LinkIdentifier linkIdentifier,
					  LinkConfigurationParameterList linkConfigurationParameters,
					  MihLinkConfigureThresholdsConfirmCallback configureThresholdsConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
      if (destinationIdentifier == GetMihfId ())
        {
          MihLinkSapListI mihLinkSapI;
          if (!FindMihLinkSap (linkIdentifier, mihLinkSapI))
            {
              NS_LOG_WARN ("Illegal MihLinkSap search!");
              NS_ASSERT (0);
              configureThresholdsConfirmCallback (GetMihfId (),
                                                  Status (Status::UNSPECIFIED_FAILURE),
                                                  linkIdentifier,
                                                  LinkConfigurationStatusList ());
              return;
            }
          LinkConfigureThresholdsConfirm configureThresholdsConfirm;
          configureThresholdsConfirm = (*mihLinkSapI)->ConfigureThresholds (linkConfigurationParameters);
          configureThresholdsConfirmCallback (GetMihfId (),
                                              configureThresholdsConfirm.GetStatus (),
                                              linkIdentifier,
                                              configureThresholdsConfirm.GetLinkConfigurationStatusList ());
          
        }
      else
        {
          Ptr<MihProtocol> mihProtocol = 0;
          mihProtocol = GetObject<MihProtocol> ();
          NS_ASSERT (mihProtocol);
          mihProtocol->SendLinkConfigureThresholdsRequest (destinationIdentifier,
                                                           linkIdentifier,
                                                           linkConfigurationParameters,
                                                           configureThresholdsConfirmCallback);
        }
    }
    void 
    MihFunction::LinkActions (MihfId destinationIdentifier,
			      LinkActionRequestList actionRequestList,
			      MihLinkActionsConfirmCallback actionsConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (!actionsConfirmCallback.IsNull ());
      m_postponedActionsConfirmCallback = actionsConfirmCallback;
      if (destinationIdentifier == GetMihfId ())
        {
          uint64_t totalDelay = 0;
          if (actionRequestList.size () == 0)
            {
              NS_LOG_LOGIC ("Zero Action requests were given, returning immediately...");
              LinkActionsComplete ();
              return;
            }
          for (LinkActionRequestListI i = actionRequestList.begin (); i != actionRequestList.end (); i++)
            {
              MihLinkSapListI linkSapIter;
              if (!FindMihLinkSap ((*i)->GetLinkIdentifier (), linkSapIter))
                {
                  NS_LOG_LOGIC ("Link Identifier : " << (*i)->GetLinkIdentifier () 
                                << " was not found by Mih Function : " << GetMihfId ());
                  continue;
                }
              EventId eventId = (*linkSapIter)->Action ((*i)->GetLinkAction (),
                                                        (*i)->GetActionExecutionDelay (),
                                                        (*i)->GetPoaAddress (),
                                                        MakeCallback (&MihFunction::ConfirmLinkAction, this));
              m_linkActionConfirmEventIds.push_back (eventId);
              totalDelay += (*i)->GetActionExecutionDelay ();
              m_actionRequestN++;
            }
          if (m_actionRequestN == 0)
            {
              m_linkActionsCompleteEvent = Simulator::Schedule (MilliSeconds (totalDelay),
                                                                &MihFunction::LinkActionsComplete,
                                                                this);
            }
          else
            {
              m_linkActionsCompleteEvent = Simulator::Schedule (MilliSeconds (totalDelay + 5), /* safety, 5 ms*/
                                                                &MihFunction::LinkActionsComplete,
                                                                this);
            }
        }
      else
        {
          Ptr<MihProtocol> mihProtocol = 0;
          mihProtocol = GetObject<MihProtocol> ();
          NS_ASSERT (mihProtocol);
//           mihProtocol->SendLinkActions (destinationIdentifier,
//                                         actionRequestList,
//                                         actionsConfirmCallback);
        }
    }    
    void 
    MihFunction::ConfirmLinkAction (Status status, 
                                    ScanResponseList scans,
                                    LinkActionResponse::ActionResult actionResult,
                                    LinkIdentifier linkIdentifier)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (status.GetType () != Status::AUTHORIZATION_FAILURE);
      if (m_linkActionsComplete)
        {
          return;
        }
      Ptr<LinkActionResponse> actionResponse = Create<LinkActionResponse> (linkIdentifier.GetType (),
                                                                           linkIdentifier.GetDeviceLinkAddress (),
                                                                           actionResult);
      if (status.GetType () == Status::SUCCESS)
        {
          actionResponse->SetScanResponseList (scans);
        }
      m_linkActionResponseList.push_back (actionResponse);
      
      if (m_linkActionResponseList.size () == m_actionRequestN)
        {
          NS_ASSERT (m_linkActionsCompleteEvent.IsRunning ());
          m_linkActionsCompleteEvent.Cancel ();
          m_linkActionsComplete = true;
          LinkActionsComplete ();
        }
    }
    void
    MihFunction::LinkActionsComplete (void)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (m_linkActionsCompleteEvent.IsExpired ());
      if (!m_linkActionsComplete) // Timer timeout!
        {
          m_linkActionsComplete = true;
        }
      for (uint32_t j = 0; j < m_linkActionConfirmEventIds.size (); j++)
        {
          if (m_linkActionConfirmEventIds[j].IsRunning ())
            {
              m_linkActionConfirmEventIds[j].Cancel ();
            }
        }
      NS_ASSERT (!m_postponedActionsConfirmCallback.IsNull ());
      m_postponedActionsConfirmCallback (GetMihfId (), 
                                         Status (Status::SUCCESS),
                                         m_linkActionResponseList);
      m_postponedActionsConfirmCallback = MakeNullCallback<void, MihfId, Status, LinkActionResponseList> ();
    }
  } // namespace mih
} // namespace ns3
