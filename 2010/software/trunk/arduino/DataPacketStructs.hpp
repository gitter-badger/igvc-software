#ifndef DataPacketStructs_H_
#define DataPacketStructs_H_

#include "standard_types.hpp"

//length of header
#define PACKET_HEADER_SIZE 14

typedef unsigned char byte;

//Packet Header
typedef struct __attribute__((__packed__))
{
	int32 timestamp_sec;
	int32 timestamp_usec;
	uint32 packetnum;
	byte cmd;
	byte size;
} header_t; //orig arduino - should be same as laptop

//Data types

//Error Frame
typedef struct __attribute__((__packed__))
{
	int16 errnum;
	byte * msg;
} error_pk_t;

//Encoder Data
typedef struct __attribute__((__packed__))
{
	int16 dl;
	int16 dr;
	uint16 dt;
} encoder_reply_t;
typedef struct __attribute__((__packed__))
{
	int16 dl;//ticks
	int16 dr;//ticks
	uint32 dt;//millis
} reply_dtick_t; // orig arduino

//Current Data
typedef struct __attribute__((__packed__))
{
	int16 il;
	int16 ir;
} current_reply_t;
//Joystick Data
typedef struct __attribute__((__packed__))
{
	int16 joy_x;
	int16 joy_y;
} joystick_reply_t;

/*
typedef struct  __attribute__((__packed__))
{
	int16 currentl;
	int16 currentr;
	uint32 dt;
} reply_current_t; //orig arduino
*/
//Motor Speed Frame
typedef struct __attribute__((__packed__))
{
	byte leftDir;
	byte sl;
	byte rightDir;
	byte sr;
} speed_set_t;

//Sonar Data Frame
typedef struct __attribute__((__packed__))
{
	int16 id;
	int16 range;
} sonar_range_t; //range in milimeters

#endif //DataPacketStructs_H_
