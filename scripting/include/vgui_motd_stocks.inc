// TODO register cache buster as a shared plugin?
// have to figure out some way to ensure these extended features are discoverable

// if 0 cache buster will not pass dimensions to proxy page and assume default
#define CSGO_POPUP_FULL 0

/**
 * Displays an MOTD panel with CS:GO-specific options
 */
stock void CSGO_ShowMOTDPanel(int client, const char[] title, const char[] url,
		bool show = false, int width = CSGO_POPUP_FULL, int height = CSGO_POPUP_FULL) {
	KeyValues kv = new KeyValues("data");
	
	kv.SetString("title", title);
	kv.SetNum("type", MOTDPANEL_TYPE_URL);
	kv.SetString("msg", url);
	
	if (show) {
		// extended options handled by cache buster
		kv.SetNum("x-vgui-width", width);
		kv.SetNum("x-vgui-height", height);
	}
	
	ShowVGUIPanel(client, "info", kv, show);
	
	delete kv;
}

/**
 * Displays an MOTD panel with TF2-specific options
 */
stock void TF2_ShowMOTDPanel(int client, const char[] title, const char[] url, bool show = true,
		bool big = false) {
	KeyValues kv = new KeyValues("data");
	
	kv.SetString("title", title);
	kv.SetNum("type", MOTDPANEL_TYPE_URL);
	kv.SetString("msg", url);
	
	if (big) {
		kv.SetNum("customsvr", 1);
	}
	
	ShowVGUIPanel(client, "info", kv, show);
	
	delete kv;
}
