#pragma once

#include <ql/ql.hpp>

namespace graphic
{
	struct circle
	{
		ql::circle c;

		circle()
		{
			this->c.set_radius(50.f);
			this->c.set_color(ql::get_random_color());

			this->c.set_center(ql::random(ql::vec2(10, 10)));
		}

		void draw(ql::render& draw) const
		{
			draw.draw(this->c);
		}
	};

	struct main_state : ql::base_state
	{
		ql::view_control view;
		circle circle;

		void init() override
		{
			this->call_on_resize();

			this->view.set_hitbox(*this);
		}

		void updating() override
		{
			this->update(this->view);
		}

		void drawing() override
		{
			this->draw(this->circle, this->view);
		}
	};

	void run()
	{
		ql::state_manager state_manager;
		state_manager.set_title("ql");
		state_manager.set_antialiasing_level(12);
		state_manager.set_dimension({1400u, 950u});

		state_manager.add_state<main_state>();
		state_manager.game_loop();
	}
}