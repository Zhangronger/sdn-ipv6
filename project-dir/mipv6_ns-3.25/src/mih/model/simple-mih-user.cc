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
#include "mih-function.h"
#include "simple-mih-user.h"

NS_LOG_COMPONENT_DEFINE ("SimpleMihUser");

namespace ns3 {
  namespace mih {

    NS_OBJECT_ENSURE_REGISTERED (SimpleMihUser);

    TypeId
    SimpleMihUser::GetTypeId (void)
    {
      static TypeId tid = TypeId ("ns3::mih::SimpleMihUser")
	.SetParent<Application> ()
	.AddConstructor<SimpleMihUser> ()
	;
      return tid;
    }
    SimpleMihUser::SimpleMihUser (void)
    {
      NS_LOG_FUNCTION_NOARGS ();
    }
    SimpleMihUser::~SimpleMihUser (void)
    {
      NS_LOG_FUNCTION_NOARGS ();
    }
    void
    SimpleMihUser::DoDispose (void)
    {
      NS_LOG_FUNCTION (this);
      Application::DoDispose ();
    }
    void
    SimpleMihUser::Start (void)
    {
      NS_LOG_FUNCTION (this);

      StartApplication ();
    }
    void
    SimpleMihUser::StartApplication (void)
    {
      NS_LOG_FUNCTION (this);

      Ptr<MihFunction> mihf = 0;
      mihf = GetObject<MihFunction> ();
      NS_ASSERT (mihf != 0);

      mihf->RegisterMihRegisterIndicationCallback (MakeCallback (&SimpleMihUser::RegisterIndication, this));
    }
    void
    SimpleMihUser::StopApplication (void)
    {
      NS_LOG_FUNCTION (this);
    }
    void
    SimpleMihUser::Register (MihfId destMihf)
    {
      NS_LOG_FUNCTION (this);

      Ptr<MihFunction> mihf = 0;
      mihf = GetObject<MihFunction> ();
      NS_ASSERT (mihf != 0);

      mihf->Register (destMihf,
                      LinkIdentifierList (),
                      RegistrationCode (),
                      MakeCallback (&SimpleMihUser::RegisterConfirm, this));
    }
    void
    SimpleMihUser::CapabilityDiscover (MihfId destMihf)
    {
      NS_LOG_FUNCTION (this);

      Ptr<MihFunction> mihf = 0;
      mihf = GetObject<MihFunction> ();
      NS_ASSERT (mihf != 0);
      
      mihf->CapabilityDiscover (destMihf,
				NetworkTypeAddressList (),
				EventList (),
				MihCommandList (),
				InformationServiceQueryTypeList (),
				TransportSupportList (),
				MakeBeforeBreakSupportList (),
				MakeCallback (&SimpleMihUser::ConfirmCapabilityDiscover, this));
    }
    void
    SimpleMihUser::EventSubscribe (MihfId destMihf,
				   LinkIdentifier destLinkIdentifier)
    {
      NS_LOG_FUNCTION (this);

      Ptr<MihFunction> mihf = 0;
      mihf = GetObject<MihFunction> ();
      NS_ASSERT (mihf != 0);

      mihf->EventSubscribe (destMihf,
			    destLinkIdentifier,
			    MakeCallback (&SimpleMihUser::ConfirmEventSubscribe, this),
			    EventList::LINK_DETECTED,
			    MakeCallback (&SimpleMihUser::RecvLinkDetected, this),
			    EventList::LINK_UP,
			    MakeCallback (&SimpleMihUser::RecvLinkUp, this),
			    EventList::LINK_DOWN,
			    MakeCallback (&SimpleMihUser::RecvLinkDown, this),
			    EventList::LINK_PARAMETERS_REPORT,
			    MakeCallback (&SimpleMihUser::RecvLinkParametersReport, this),
			    EventList::LINK_GOING_DOWN,
			    MakeCallback (&SimpleMihUser::RecvLinkGoingDown, this),
			    EventList::LINK_HANDOVER_IMMINENT,
			    MakeCallback (&SimpleMihUser::RecvLinkHandoverImminent, this),
			    EventList::LINK_HANDOVER_COMPLETE,
			    MakeCallback (&SimpleMihUser::RecvLinkHandoverComplete, this)
	);
    }
    void
    SimpleMihUser::LinkGetParameters (MihfId destMihf,
				      LinkIdentifier destLinkIdentifier)
    {
      NS_LOG_FUNCTION (this);

      Ptr<MihFunction> mihf = 0;
      mihf = GetObject<MihFunction> ();
      NS_ASSERT (mihf != 0);

      LinkIdentifierList links;
      links.push_back (Create<LinkIdentifier> (destLinkIdentifier));
      mihf->LinkGetParameters (destMihf,
			       DeviceStatesRequest (static_cast<uint16_t> (DeviceStatesRequest::DEVICE_INFO)),
			       links,
			       LinkStatusRequest (),
			       MakeCallback (&SimpleMihUser::ConfirmLinkGetParameters, this)
			       );
    }
    void
    SimpleMihUser::LinkConfigureThresholds (MihfId destMihf,
					    LinkIdentifier destLinkIdentifier)
    {
      NS_LOG_FUNCTION (this);

      Ptr<MihFunction> mihf = 0;
      mihf = GetObject<MihFunction> ();
      NS_ASSERT (mihf != 0);

      mihf->LinkConfigureThresholds (destMihf,
				     destLinkIdentifier,
				     LinkConfigurationParameterList (),
				     MakeCallback (&SimpleMihUser::ConfirmLinkConfigureThresholds, this)
				     );
    }
    void
    SimpleMihUser::LinkActions (MihfId destMihf,
				LinkIdentifier destLinkIdentifier)
    {
      NS_LOG_FUNCTION (this);

      Ptr<MihFunction> mihf = 0;
      mihf = GetObject<MihFunction> ();
      NS_ASSERT (mihf != 0);
      
      Ptr<LinkActionRequest> actionRequest = Create<LinkActionRequest> (destLinkIdentifier,
                                                                        LinkAction (LinkAction::LINK_POWER_DOWN),
                                                                        10); // 10
                                                                            // millisecond;
      
      LinkActionRequestList actions;
      actions.push_back (actionRequest);
      mihf->LinkActions (destMihf,
                         actions,
			 MakeCallback (&SimpleMihUser::ConfirmLinkActions, this)
			 );
    }

    // Event callbacks;
    void
    SimpleMihUser::RecvLinkDetected (MihfId sourceIdentifier,
				     LinkDetectedInformationList detectedInfoList)
    {
      NS_LOG_FUNCTION (this);
      NS_LOG_LOGIC ("Source Mihf Identifier = " << sourceIdentifier << ", Link Detected Information List = {" << detectedInfoList << "}");
    }
    void 
    SimpleMihUser::RecvLinkUp (MihfId sourceIdentifier,
			       LinkIdentifier linkIdentifier, 
			       Address oldAR,
			       Address newAR,
			       bool ipRenewalFlag, 
			       MobilityManagementSupport mobilityProtocol)
    {
      NS_LOG_FUNCTION (this);
      NS_LOG_LOGIC ("Source Mihf Identifier = " << sourceIdentifier << ", from Link Identifier = " << linkIdentifier << ", Old AR = " << oldAR << ", New AR = " << newAR);
    }
    void
    SimpleMihUser::RecvLinkDown (MihfId sourceIdentifier,
				 LinkIdentifier linkIdentifier,
				 Address oldAR,
				 LinkDownReason reason)
    {
      NS_LOG_FUNCTION (this);
      NS_LOG_LOGIC ("Source Mihf Identifier = " << sourceIdentifier << ", from Link Identifier = " << linkIdentifier << ", Old AR = " << oldAR);
    }
    void 
    SimpleMihUser::RecvLinkParametersReport (MihfId sourceIdentifier, 
					     LinkIdentifier linkIdentifier,
					     LinkParameterReportList params)
    {
      NS_LOG_FUNCTION (this);
      NS_LOG_LOGIC ("Source Mihf Identifier = " << sourceIdentifier << ", from Link Identifier = " << linkIdentifier);
    }
    void
    SimpleMihUser::RecvLinkGoingDown (MihfId sourceIdentifier,
				      LinkIdentifier linkIdentifier,
				      uint64_t timeInterval,
				      LinkGoingDownReason reason)
    {
      NS_LOG_FUNCTION (this);
      NS_LOG_LOGIC ("Source Mihf Identifier = " << sourceIdentifier << ", from Link Identifier = " << linkIdentifier << ", Time Interval = " << (int) timeInterval << " ms");
    }
    void
    SimpleMihUser::RecvLinkHandoverImminent (MihfId sourceIdentifier, 
					     LinkIdentifier oldLinkIdentifier,
					     LinkIdentifier newLinkIdentifier, 
					     Address oldAR,
					     Address newAR)
    {
      NS_LOG_FUNCTION (this);
    }
    void
    SimpleMihUser::RecvLinkHandoverComplete (MihfId sourceIdentifier,
					     LinkIdentifier oldLinkIdentifier,
					     LinkIdentifier newLinkIdentifier,
					     Address oldAR, 
					     Address newAR,
					     Status status)
    {
      NS_LOG_FUNCTION (this);
      NS_LOG_INFO ("Source Mihf Identifier = " << sourceIdentifier << ", from Old Link Identifier = " << oldLinkIdentifier <<  ", to New Link Identifier = " << newLinkIdentifier <<", from Old AR = " << oldAR << ", to New AR = " << newAR << ", Status = " << status);
    }
    // Command Confirm Callbacks;
    void
    SimpleMihUser::ConfirmCapabilityDiscover (MihfId sourceIdentifier, 
					      Status status,
					      NetworkTypeAddressList networkTypeAddresses, 
					      EventList events, 
					      MihCommandList commands, 
					      InformationServiceQueryTypeList queries, 
					      TransportSupportList transports,
					      MakeBeforeBreakSupportList mbbs)
    {
      NS_LOG_FUNCTION (this);
      NS_LOG_INFO ("Source Mihf Identifier = " << sourceIdentifier << ", Status = " << status);
    }
    void
    SimpleMihUser::ConfirmEventSubscribe (MihfId sourceIdentifier, 
					  Status status, 
					  LinkIdentifier linkIdentifier,
					  EventList events)
    {
      NS_LOG_FUNCTION (this);
      NS_LOG_INFO ("Source Mihf Identifier = " << sourceIdentifier << ", Status = " << status << ", Link Identifier = " << linkIdentifier);
    }
    void
    SimpleMihUser::ConfirmLinkGetParameters (MihfId sourceIdentifier,
					     Status status, 
					     DeviceStatesResponseList deviceStates, 
					     LinkStatusResponseList)
    {
      NS_LOG_FUNCTION (this);
      NS_LOG_INFO ("Source Mihf Identifier = " << sourceIdentifier << ", Status = " << status);      
    }
    void SimpleMihUser::ConfirmLinkConfigureThresholds (MihfId sourceIdentifier, 
							Status status, 
							LinkIdentifier linkIdentifier, 
							LinkConfigurationStatusList configs)
    {
      NS_LOG_FUNCTION (this);
      NS_LOG_INFO ("Source Mihf Identifier = " << sourceIdentifier << ", Status = " << status << ", Link Identifier = " << linkIdentifier);
    }
    void
    SimpleMihUser::ConfirmLinkActions (MihfId sourceIdentifier, 
				       Status status,
				       LinkActionResponseList actionResponses)
    {
      NS_LOG_FUNCTION (this);
    }
    // Register callbacks;
    void 
    SimpleMihUser::RegisterIndication (MihfId mihfid,
                                       LinkIdentifierList linkIdentifiers,
                                       RegistrationCode code,
                                       MihRegisterResponseCallback responseCallback)
    {
      NS_LOG_FUNCTION (this);

      Ptr<MihFunction> mihf = 0;
      mihf = GetObject<MihFunction> ();
      NS_ASSERT (mihf != 0);
      
      
      responseCallback (mihf->GetMihfId (), 
                        Status (Status::SUCCESS),
                        60000); // 60 Seconds
    }

    void
    SimpleMihUser::RegisterConfirm (MihfId src,
                                    Status status,
                                    uint32_t delay)
    {
      NS_LOG_FUNCTION (this);
      
    }
    
  } // namespace mih
} // namespace ns3
