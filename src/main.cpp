#include <ql/ql.hpp>

#include "app.hpp"
#include "model/constants.hpp"

int main() try
{
	ql::state_manager state_manager;
	state_manager.set_title("ql");
	state_manager.set_antialiasing_level(12);
	state_manager.set_dimension({ 1400u, 950u });
	state_manager.set_framerate_limit(constants::ticks_per_second);

	state_manager.add_state<app_state>();
	state_manager.game_loop();
}
catch (const std::exception& any)
{
	ql::println("exception: ", any.what());
}