#ifndef TYPES_H
#define TYPES_H

typedef unsigned char uint_8;
typedef signed long int sint_32;//defining this like this becuase i'm not sure if a long int is 4 bytes or not, so can change later

enum CommandCodes {
	sync_flag = 0xAA,
	terminator = 0x00,
	get_mod_info = 0x01,
	set_data_components = 0x03,
	get_data = 0x04,
	set_config = 0x06,
	get_config = 0x07,
	save_config = 0x09,
	start_cal = 0x0A,
	stop_cal = 0x0B,
	get_cal_data = 0x0C,
	set_cal_data = 0x0E};

enum CompassResponse{
	mod_info_resp = 0x02,
	data_resp = 0x05,
	config_resp = 0x08,
	cal_data_resp = 0x0D};

enum Config_Id{
	declination = 0x01,
	true_north = 0x02,
	casamplefreq = 0x03,
	samplefreq = 0x04,
	period = 0x05,
	bigendian = 0x06,
	dampingsize = 0x07};

enum Data_Cid{
	XRaw = 0x01,
	YRaw = 0x02,
	XCal = 0x03,
	YCal = 0x04,
	Heading = 0x05,
	Magnitude = 0x06,
	Temperature = 0x07,
	Distortion = 0x08,
	CalStatus = 0x09};


struct ModInfoResp {
	char module_type[5];//four chars read from compass + null char i add later
	char firmware_version[5];
};

struct CalDataResp {
	uint_8 ByteCount;
	sint_32 XOffset;
	sint_32 YOffset;
	sint_32 XGain;
	sint_32 YGain;
	float phi;
	float CalibrationMagnitude;
};

struct compassData{//all posible types the compass can sends. when asked Distortion and Calstatus are suposed to be bools, but i think they are read a byte at a time, so should work as uint_8's.
        sint_32 XRaw;
        sint_32 YRaw;
        float XCal;
        float YCal;
        float Heading;
        float Magnitude;
        float Temperature;
        uint_8 Distortion;
        uint_8 CalStatus;
};

//const uint_8 dataresponsetype[9] = {XRaw, YRaw, XCal, YCal, Heading, Magnitude, Temperature, Distortion, CalStatus};
union spi_control_0{
	struct {
		unsigned char interupt_enable:1;//0 = disable
		unsigned char sytem_enable:1;//0 = disable
		unsigned char transmit_interrupt_enable:1;// 0 = disable
		unsigned char mode_select:1;// 0 = slave; 1= master
		unsigned char clock_polarity:1;//we want this = 0 (low = idle)
		unsigned char clock_phase:1;//0 = sample on odd edge (which i think we do)
		unsigned char slave_select_out_enable:1;//allow the slave select pin as output?? prob = 0
		unsigned char LSB_first:1;// 0 = msb first, 1= lsb first
	}bits;
	unsigned char byte;
};
union spi_control_1{
	struct {
		unsigned char :3;//offest 3
		unsigned char MODFEN:1;//0 = slave select is unused, 1 = slave select used w/ fault detection
		unsigned char BIDROE:1;//enables output buffer
		unsigned char :1;//offset 1
		unsigned char SPISWAI:1;//stops clock signal while in wait mode
		unsigned char SPC0:1;//allows bidirectional transfer on MOSI pin. 0 = both MOSI and MISO are used
	}bits;
	unsigned char byte;
};

union spi_baud_rate{
	struct {
		unsigned char :1;
		unsigned char baud_rate_preselect:3;
		unsigned char :1;
		unsigned char baud_rate_select:3;
	}bits;//see freescale paper for details
	unsigned char byte;

};

union spi_status_register{
	struct {
		unsigned char interrupt_flag:1;//1 = new data is in data register.  clear bu reading this and then reading the data register
		unsigned char :1;
		unsigned char transmit_empty_interrupt_flag:1;//transmit data register empty. to clear read this =1, then write to the data register
		unsigned char mode_fault_flag:1;//if modfen was set above, this will be oneif a fault was found
		unsigned char :4;
	}bits;
	unsigned char byte;
};
#endif //TYPES_H