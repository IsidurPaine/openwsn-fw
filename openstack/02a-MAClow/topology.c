#include "opendefs.h"
#include "topology.h"
#include "idmanager.h"

//=========================== defines =========================================


#define TOPOLOGY_MOTE1 0x6e
#define TOPOLOGY_MOTE2 0x56
#define TOPOLOGY_MOTE3 0x35
#define TOPOLOGY_MOTE4 0x17
#define TOPOLOGY_MOTE5 0xcc
#define TOPOLOGY_MOTE6 0xa4
#define TOPOLOGY_MOTE7 0x48
#define TOPOLOGY_MOTE8 0x82
#define TOPOLOGY_MOTE9 0x4f


//=========================== variables =======================================

//=========================== prototypes ======================================

//=========================== public ==========================================


bool topology_isAcceptablePacket(ieee802154_header_iht* ieee802514_header) {
	bool returnVal;

	returnVal=FALSE;
	switch (idmanager_getMyID(ADDR_64B)->addr_64b[6]) {

	// Topologia a catena

	case TOPOLOGY_MOTE1:
			if (ieee802514_header->src.addr_64b[6]==TOPOLOGY_MOTE2) {
				returnVal=TRUE;
			} else {
				returnVal=FALSE;
			}
			break;
		case TOPOLOGY_MOTE2:
			if (ieee802514_header->src.addr_64b[6]==TOPOLOGY_MOTE1 ||
					ieee802514_header->src.addr_64b[6]==TOPOLOGY_MOTE3) {
				returnVal=TRUE;
			} else {
				returnVal=FALSE;
			}
			break;
		case TOPOLOGY_MOTE3:
			if (ieee802514_header->src.addr_64b[6]==TOPOLOGY_MOTE2 ||
					ieee802514_header->src.addr_64b[6]==TOPOLOGY_MOTE4) {
				returnVal=TRUE;
			} else {
				returnVal=FALSE;
			}
			break;
		case TOPOLOGY_MOTE4:
				if (ieee802514_header->src.addr_64b[6]==TOPOLOGY_MOTE3 ||
						ieee802514_header->src.addr_64b[6]==TOPOLOGY_MOTE5) {
					returnVal=TRUE;
				} else {
					returnVal=FALSE;
				}
				break;
		case TOPOLOGY_MOTE5:
			if (ieee802514_header->src.addr_64b[6]==TOPOLOGY_MOTE4 ||
					ieee802514_header->src.addr_64b[6]==TOPOLOGY_MOTE6) {
				returnVal=TRUE;
			} else {
				returnVal=FALSE;
			}
			break;
		case TOPOLOGY_MOTE6:
			if (ieee802514_header->src.addr_64b[6]==TOPOLOGY_MOTE5 ||
					ieee802514_header->src.addr_64b[6]==TOPOLOGY_MOTE7) {
				returnVal=TRUE;
			} else {
				returnVal=FALSE;
			}
			break;
		case TOPOLOGY_MOTE7:
			if (ieee802514_header->src.addr_64b[6]==TOPOLOGY_MOTE6 ||
					ieee802514_header->src.addr_64b[6]==TOPOLOGY_MOTE8) {
				returnVal=TRUE;
			} else {
				returnVal=FALSE;
			}
			break;
		case TOPOLOGY_MOTE8:
			if (ieee802514_header->src.addr_64b[6]==TOPOLOGY_MOTE7 ||
					ieee802514_header->src.addr_64b[6]==TOPOLOGY_MOTE9) {
				returnVal=TRUE;
			} else {
				returnVal=FALSE;
			}
			break;
		case TOPOLOGY_MOTE9:
			if (ieee802514_header->src.addr_64b[6]==TOPOLOGY_MOTE8) {
				returnVal=TRUE;
			} else {
				returnVal=FALSE;
			}
			break;

	// Topologia a stella
	/*case TOPOLOGY_MOTE1:
		if (
				ieee802514_header->src.addr_64b[7]==TOPOLOGY_MOTE2 ||
				ieee802514_header->src.addr_64b[7]==TOPOLOGY_MOTE3 ||
				ieee802514_header->src.addr_64b[7]==TOPOLOGY_MOTE4 ||
				ieee802514_header->src.addr_64b[7]==TOPOLOGY_MOTE5 ||
				ieee802514_header->src.addr_64b[7]==TOPOLOGY_MOTE6 ||
				ieee802514_header->src.addr_64b[7]==TOPOLOGY_MOTE7 ||
				ieee802514_header->src.addr_64b[7]==TOPOLOGY_MOTE8 ||
				ieee802514_header->src.addr_64b[7]==TOPOLOGY_MOTE9) {
			returnVal=TRUE;
		}
		break;
	case TOPOLOGY_MOTE2:
		if (
				ieee802514_header->src.addr_64b[7]==TOPOLOGY_MOTE1 ) {
			returnVal=TRUE;
		}
		break;
	case TOPOLOGY_MOTE3:
		if (
				ieee802514_header->src.addr_64b[7]==TOPOLOGY_MOTE1 ) {
			returnVal=TRUE;
		}
		break;
	case TOPOLOGY_MOTE4:
		if (
				ieee802514_header->src.addr_64b[7]==TOPOLOGY_MOTE1 ) {
			returnVal=TRUE;
		}
		break;
	case TOPOLOGY_MOTE5:
		if (
				ieee802514_header->src.addr_64b[7]==TOPOLOGY_MOTE1 ) {
			returnVal=TRUE;
		}
		break;
	case TOPOLOGY_MOTE6:
		if (
				ieee802514_header->src.addr_64b[7]==TOPOLOGY_MOTE1 ) {
			returnVal=TRUE;
		}
		break;
	case TOPOLOGY_MOTE7:
		if (
				ieee802514_header->src.addr_64b[7]==TOPOLOGY_MOTE1 ) {
			returnVal=TRUE;
		}
		break;
	case TOPOLOGY_MOTE8:
		if (
				ieee802514_header->src.addr_64b[7]==TOPOLOGY_MOTE1 ) {
			returnVal=TRUE;
		}
		break;
	case TOPOLOGY_MOTE9:
		if (
				ieee802514_header->src.addr_64b[7]==TOPOLOGY_MOTE1 ) {
			returnVal=TRUE;
		}
		break;*/
	}
	return returnVal;
#else
	return TRUE;
#endif
}

//=========================== private =========================================
