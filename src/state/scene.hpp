#pragma once

#include <ql/ql.hpp>

struct scene
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

struct scene_state : ql::base_state
{
	scene scene;
	ql_sync_state(this->scene);
};