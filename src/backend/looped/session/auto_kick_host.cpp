#include "backend/looped/looped.hpp"
#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	static bool bLastKickHost = false;
	void looped::session_auto_kick_host()
	{
		bool kick_host = *g_pointers->m_gta.m_is_session_started && g.session.spoof_host_token_type != 0 && g.session.kick_host_when_forcing_host;
		if (kick_host && !bLastKickHost) [[unlikely]]
		{
			g_player_service->iterate([](auto& plyr) {
				// Don't kick trusted players
				if (plyr.second->is_trusted || (g.session.trust_friends && plyr.second->is_friend()) 
					|| (plyr.second->is_modder && g.session.exclude_modders_from_kick_host))
						return;

				if (plyr.second->is_host())
				{
					player_command::get("smartkick"_J)->call(plyr.second, {});
				}
			});
		}
		bLastKickHost = kick_host;
	}
}
