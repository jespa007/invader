#pragma once


class ChannelsInfo{
public:
	uint32_t msk_active_channels;
	uint8_t n_channels;
	float *channels;

	typedef struct{
		void (*ptr_function)(ChannelsInfo * c, void *user_data);
		void *user_data;
	} ResetChannelCallback;

	ResetChannelCallback on_reset_channels;

	typedef struct{
		void (*ptr_function)(ChannelsInfo * c, void *user_data);
		void *user_data;
	}SetChannelsCallback;

	SetChannelsCallback on_set_channels;

	//---------------------------------------------------------------------------------------------------------------------
	// STATIC

	static void copy(ChannelsInfo  * _dst, ChannelsInfo *  _src);

	//---------------------------------------------------------------------------------------------------------------------
	// PUBLIC
	ChannelsInfo(uint8_t n_channels);

	void copyTo(float *_dst);
	void print();
	~ChannelsInfo();

private:

};




