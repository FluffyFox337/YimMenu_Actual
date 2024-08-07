#pragma once
#include "gta/joaat.hpp"
#include "memory/pattern.hpp"

namespace big
{
	// a lightweight script function wrapper inspired by https://github.com/Parik27/V.Rainbomizer/blob/master/src/mission/missions_YscUtils.hh
	class script_function
	{
		rage::joaat_t m_script;
		const memory::pattern m_pattern;
		int32_t m_offset;
		int32_t m_ip;
		std::string m_name;

	public:
		script_function(const std::string& name, const rage::joaat_t script, const std::string& pattern, int32_t offset);
		void populate_ip();
		void call(rage::scrThread* thread, rage::scrProgram* program, const std::vector<uint64_t>& args);
		void call_latent(rage::scrThread* thread, rage::scrProgram* program, const std::vector<uint64_t>& args, bool& done);

		// for pure functions that do not need access to thread stack
		void static_call(const std::vector<uint64_t>& args);

		void operator()(const std::vector<uint64_t>& args);
	};

	namespace scr_functions
	{
		static inline script_function join_ceo("JC", "freemode"_J, "2D 04 1D 00 00 5D", 0);
		static inline script_function set_freemode_session_active("SFSA", "freemode"_J, "2D 00 02 00 00 75 5D ? ? ? 50", 0);
		static inline script_function dance_loop("DL", "am_mp_nightclub"_J, "2D 00 14 00 00 4F ? ? 47 ? ? 5D ? ? ? 56", 0);
		static inline script_function init_nightclub_script("INS", "am_mp_nightclub"_J, "2D 00 11 00 00 4F", 0);

		static inline script_function save_to_datafile("STD", "fm_race_creator"_J, "2D 01 03 00 00 71 2C", 0);
		static inline script_function load_from_datafile("LFD", "fm_race_creator"_J, "2D 04 0D 00 00 71 2C", 0);

		static inline script_function modshop_loop("ML", "carmod_shop"_J, "2D 00 07 00 00 71 51", 0);
		static inline script_function setup_modshop("SM", "carmod_shop"_J, "2D 04 12 00 00 38 00 51", 0);

		static inline script_function reset_session_data("RSD", "pausemenu_multiplayer"_J, "2D 02 7D 00 00", 0);
	}
}
