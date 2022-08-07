/*
Plugin Name
Copyright (C) <Year> <Developer> <Email Address>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include <obs-module.h>

#include "plugin-macros.generated.h"

#include "airplay.hpp"

extern "C" {

	OBS_DECLARE_MODULE()
	OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")


	static auto sourceName(void *v) -> const char *
	{
	return static_cast<AirPlay *>(v)->name();
	}

	static auto sourceCreate(obs_data *data, obs_source *obsSource) -> void *
	{
	return new AirPlay(data, obsSource);
	}

	static auto sourceDestroy(void *v) -> void
	{
	delete static_cast<AirPlay *>(v);
	}

	static auto sourceUpdate(void *v, obs_data_t *data) -> void
	{

	}

	static auto sourceWidth(void *v) -> uint32_t
	{
	return static_cast<AirPlay *>(v)->getWidth();
	}

	static auto sourceHeight(void *v) -> uint32_t
	{
	return static_cast<AirPlay *>(v)->getHeight();
	}

	static struct obs_source_info source = {.id = "AirPlay",
											.type = OBS_SOURCE_TYPE_INPUT,
											.output_flags = OBS_SOURCE_ASYNC_VIDEO | OBS_SOURCE_AUDIO,
											.get_name = sourceName,
											.create = sourceCreate,
											.destroy = sourceDestroy,
											.get_width = sourceWidth,
											.get_height = sourceHeight,
											.update = sourceUpdate,
											.icon_type = OBS_ICON_TYPE_DESKTOP_CAPTURE};

	bool obs_module_load(void)
	{
		obs_register_source(&source);
		blog(LOG_INFO, "plugin loaded successfully (version %s)",
			PLUGIN_VERSION);
		return true;
	}

	void obs_module_unload()
	{
		blog(LOG_INFO, "plugin unloaded");
	}
}
