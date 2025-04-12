#pragma once

#include <ql/ql.hpp>

#pragma once

struct main_example
{
	ql_sync();

	void init()
	{
	}

	void update(ql::update_manager& update)
	{
	}

	void draw(ql::render& render) const
	{
	}
};

struct main_state : ql::base_state
{
	main_example main;
	ql_sync_state(this->main);
};

namespace graphic
{
	void run()
	{
		ql::state_manager state_manager;
		state_manager.set_title("ql");
		state_manager.set_antialiasing_level(12);
		state_manager.set_dimension({1400u, 950u});

		state_manager.add_state<main_state>();
		state_manager.game_loop();
	}
}	 // namespace graphic