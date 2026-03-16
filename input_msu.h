#include "stdafx.h"
#include "stdint.h"

#ifndef __INPUT_MSU_H__
#define __INPUT_MSU_H__


class input_msu : public input_stubs
{
private:
	service_ptr_t<file>		m_File;
	pfc::array_t<t_uint8>	m_DecodeBuffer;

	uint32_t				m_PcmFileLength;
	uint32_t				m_PcmFileLoop;
	uint32_t				m_PcmFilePos;
	pfc::array_t<t_uint8>	m_PcmFile;			// in-memory copy of PCM file
	pfc::string8			m_PcmPath;			// PCM file path

public:
	input_msu();
	~input_msu();

	static bool g_is_our_path(const char *p_path, const char *p_extension) {
		return (::stricmp_utf8(p_extension, "pcm") == 0);
	}

	void open(service_ptr_t<file> p_filehint, const char * p_path, t_input_open_reason p_reason, abort_callback &p_abort);
	void get_info(file_info &p_info, abort_callback &p_abort);
	void decode_initialize(unsigned int p_flags, abort_callback &p_abort);
	bool decode_run(audio_chunk &p_chunk, abort_callback &p_abort);
	void decode_seek(double p_seconds, abort_callback &p_abort);
	bool decode_can_seek() { return true; }

	t_filestats2 get_stats2(uint32_t f, abort_callback &p_abort) { return m_File->get_stats2_(f, p_abort); }
	void remove_tags(abort_callback &) { throw exception_tagging_unsupported(); }
	void retag(const file_info &p_info, abort_callback &p_abort) { throw exception_tagging_unsupported(); }
	static bool g_is_our_content_type(const char *p_content_type) { return false; }
	static const char * g_get_name() { return "MSU-1 PCM Player"; }
	static GUID g_get_guid() {
		static const GUID guid = { 0x3d21bfc0, 0x2b91, 0x4362, { 0x97, 0xe4, 0x8c, 0x14, 0x67, 0x85, 0xfe, 0xcd } };
		return guid;
	}
};

#endif /* __INPUT_SNESAPU___ */